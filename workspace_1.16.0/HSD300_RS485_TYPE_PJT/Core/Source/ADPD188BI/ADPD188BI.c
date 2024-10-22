
/* Includes ------------------------------------------------------------------*/
#include "..\Source\HSD300_FW.h"


uint32_t startTime = 0;
uint16_t Data_A = 0;
uint16_t Data_B = 0;
uint16_t check_Data_A=0;
uint16_t check_Data_B=0;

uint16_t IR_Offset = 712;
uint16_t Blue_IR_Offset = 1235;

uint8_t read_fifo_state=0;

#define adp_array_size 20      // <<< GET SAMPLING DATA ARRAY for median filter
uint16_t Data_A_array[adp_array_size]={0};
uint16_t Data_B_array[adp_array_size]={0};

uint16_t processed_A;
uint16_t processed_B;

uint16_t median_ADP_Data_A, median_ADP_Data_B;

HAL_StatusTypeDef adpd_status = HAL_OK;

struct CsPin csPin = {SMK_CS__GPIO_Port, SMK_CS__Pin};


//----------------------------------------------------------------------------------------------------------------------

void setDeviceMode(SPI_HandleTypeDef hspi, DeviceStates state, struct CsPin csPin) {
    uint16_t registerValue = 0;
    switch (state) {
        case STANDBY:
            registerValue = 0x00;
            break;
        case PROGRAM:
            registerValue = 0x01;
            break;
        case NORMAL:
            registerValue = 0x02;
            break;
        default:
        	registerValue = 0x00;
            break;
    }
    while(writeToRegister(MODE_REGISTER, registerValue, hspi, csPin, true) != HAL_OK);
}

//----------------------------------------------------------------------------------------------------------------------

HAL_StatusTypeDef writeToRegister(const uint8_t registerAddress, const uint16_t data, SPI_HandleTypeDef hspi, struct CsPin csPin, bool isVerifyWriting) {
    uint16_t dataRead = 0;
    // address 7bits ,1bit W/R =1
    union SpiRegisterData spiRegisterData = {.dataFormat = {0, 0, 0, 0}};
    spiRegisterData.dataFormat.registerAddress = registerAddress;
    spiRegisterData.dataFormat.writeReadBit = 0x01;  // :1 이니까 16비트 중 하위 1비트만 들어가. 그니까 0x02를 넣어도 하위비트 1이 들어가는거지
    spiRegisterData.dataFormat.msb = (data >> 8) & 0xFF; // MSB // & 0xFF는 하위 두비트만 추출하는거지
    spiRegisterData.dataFormat.lsb = data & 0xFF;    // LSB // 만약 데이터가 0001 0010 0011 0100 이라면 상위 두 비트 자르고 0011 0100만 추출
    /*
     0001 0010 0011 0100  (0x1234)
	 &
	 0000 0000 1111 1111  (0x00FF)
	 -------------------
	 0000 0000 0011 0100  (0x34)
     */

    HAL_GPIO_WritePin(csPin.gpio, csPin.gpioPinMask, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi, (uint8_t *) &spiRegisterData, 3, 100);

    HAL_GPIO_WritePin(csPin.gpio, csPin.gpioPinMask, GPIO_PIN_SET);
    if (isVerifyWriting) {
        dataRead = readRegisterData(registerAddress, hspi, csPin);
        if (dataRead == data) {
            return HAL_OK;
        }
        return HAL_ERROR;
    }
    return HAL_OK;
}

//----------------------------------------------------------------------------------------------------------------------

uint16_t readRegisterData(const uint8_t registerAddress, SPI_HandleTypeDef hspi, struct CsPin csPin) {

    uint8_t rxData[3] = {0, 0, 0};
    // address 7bits ,1bit W/R =0
    union SpiRegisterData spiRegisterData = {.dataFormat = {0, 0, 0, 0}};
    spiRegisterData.dataFormat.registerAddress = registerAddress;
    spiRegisterData.dataFormat.writeReadBit = 0x00;


    HAL_GPIO_WritePin(csPin.gpio, csPin.gpioPinMask, GPIO_PIN_RESET);
    // register size is always 2 bytes + 1 Byte for Address
    HAL_SPI_TransmitReceive(&hspi, (uint8_t *) (&spiRegisterData), rxData, 3, 100);
    HAL_GPIO_WritePin(csPin.gpio, csPin.gpioPinMask, GPIO_PIN_SET);
    return ((rxData[1] << 8) + rxData[2]);
}

//----------------------------------------------------------------------------------------------------------------------

HAL_StatusTypeDef smokeSensorADPD188Detect(SPI_HandleTypeDef hspi, struct CsPin csPin) {
    // check for ID
    union DeviceIdRegister deviceIdRegister = {.bytes = {0, 0}};
    deviceIdRegister.raw = readRegisterData(DEVICE_ID_REGISTER, hspi, csPin);
    if (deviceIdRegister.bytes.deviceID == DEFAULT_DEVICE_ID) {
        return HAL_OK;
    }
    return HAL_ERROR;
}

//----------------------------------------------------------------------------------------------------------------------

HAL_StatusTypeDef smokeSensorADPD188Init(SPI_HandleTypeDef hspi, struct CsPin csPin) {
    uint16_t mode = 0;
    //read_fifo_state=0;
    // run  recommended start-up sequence defined in the DS P 24

    // 1- enable 32K clock
    union SampleClockRegister sampleClockRegister = {.bits = {0x12, 0, 1, 0, 0x26}};
    while(writeToRegister(SAMPLE_CLK_REGISTER, sampleClockRegister.raw, hspi, csPin, true) != HAL_OK);

    // 2- go to Program mode
    setDeviceMode(hspi, PROGRAM, csPin);
    // 3-   additional configurations --> default config
    // config the sensor with recommended configurations except for sampling frequency and fifo update
    config(hspi, csPin);

    // 4-go to Normal Mode
    setDeviceMode(hspi, NORMAL, csPin);
    mode = readRegisterData(MODE_REGISTER, hspi, csPin);

    HAL_Delay(500);

    startTime = HAL_GetTick();

    if (mode == 2)  // mode =2  --> Normal mode
    {
        return HAL_OK;
    }
    return HAL_ERROR;

    // startTime = HAL_GetTick();
}


//----------------------------------------------------------------------------------------------------------------------


HAL_StatusTypeDef terminateNormalOperation(SPI_HandleTypeDef hspi, struct CsPin csPin)
{
    // DS P25

    // 1- go to program mode
    setDeviceMode(hspi, PROGRAM, csPin);
    // 2- no config
    // 3- clear all interrupts and clear fifo
    union StatusRegister statusRegister = {.bits = {0, 0, 0, 0, 0}, .raw = 0};

    statusRegister.raw = 0x80FF;
    while(writeToRegister(STATUS_REGISTER, statusRegister.raw, hspi, csPin, true) != HAL_OK);
    return HAL_OK;
}

//----------------------------------------------------------------------------------------------------------------------


uint8_t Mode_Flag = 0;
_ADP_rawData readRawData;
_ADP_rawData readFifo(SPI_HandleTypeDef hspi, struct CsPin csPin)
{
  // read 64 bits of fifo  (32 bits for each slot )
    uint16_t rxData[4] = {};
    union FifoData fifoData = {.bytes = {0, 0}, .raw = 0};

    // read Fifo data
     if (read_fifo_state==0)
     {
       uint32_t cnt_1000ms_fifo=HAL_GetTick();

       // after 1000 ms, data reading start!
       if ( abs(startTime - cnt_1000ms_fifo) >= 1000 )
       {
    	 uint8_t isChange = 0;
    	 if(abs(ui.IR_Offset - IR_Offset) > 20)
    	 {
    		 ui.IR_Offset = IR_Offset;
    		 isChange = 1;
    	 }
    	 if(abs(ui.Blue_IR_Offset - Blue_IR_Offset) > 20){
    		 ui.Blue_IR_Offset = Blue_IR_Offset;
    		 isChange = 1;
    	 }
    	 if(isChange){
             EEPROM.SaveData_Flag = 1;
    	 }
         read_fifo_state = 1;
       }
     }


    for (uint8_t i = 0; i < 4; i++)
    {
        rxData[i] = readRegisterData(FIFO_ACCESS_REGISTER, hspi, csPin);
    }

    // **** reset program mode to make fifo data safty ****

/*
    Mode_Flag ^=1;
    if(Mode_Flag==0)
    {
    	setDeviceMode(hspi, PROGRAM, csPin);
    }
    else
    {
    	setDeviceMode(hspi, NORMAL, csPin);
    }
    */


    setDeviceMode(hspi, PROGRAM, csPin);

   // HAL_Delay(2);

    setDeviceMode(hspi, NORMAL, csPin);



    // copy rxData into fifoData structure
    memcpy(&fifoData.raw, rxData, 8);

    // adp raw data
    Data_A = (fifoData.raw >> 32)&0xffff;  // blue_led value default 780~790
    Data_B = fifoData.raw&0xffff;          // infra_red_led value default 480~500

    // check_err_data using stop point-----
    readRawData.raw_ADP_Data_A=Data_A;
    readRawData.raw_ADP_Data_B=Data_B;

    return readRawData;


}



uint16_t check_A=0;
uint16_t check_B;


//----------------------------------------------------------------------------------------------------------------------


uint32_t A = 0;
uint16_t avg_data_A=0,avg_data_B=0;

bool isTimeout = false;
uint16_t final_IR_adp_val;
uint16_t final_Blue_adp_val;
#define backNoiseArray 100
uint16_t Data_A_backNoise[backNoiseArray];
uint16_t Data_B_backNoise[backNoiseArray];
uint32_t Data_A_Offset_Sum = 0;
uint32_t Data_B_Offset_Sum = 0;
uint32_t offset_cnt = 0;
uint16_t Data_A_Offset = 0;
uint16_t Data_B_Offset = 0;
_result_adp_data ADP_RESULT;

_result_adp_data readData(SPI_HandleTypeDef hspi, struct CsPin csPin)    // 구조체 변수 ADP_RESULT 리턴
{
  _ADP_rawData raw_adp_data = {0,0};
  _ADP_rawData dummy_data = {0,0};
  //update Fifo with new readings
  union DataAccessCtrl dataAccessCtrl = {.bits={0, 0, 0, 0}, .raw = 0};  // {.raw = 0}; 그냥 이렇게만 써도 된다는거 같음
  writeToRegister(DATA_ACCESS_CONTROL_REGISTER, dataAccessCtrl.raw, hspi, csPin, true);

  // if sampling  time is elapsed Hold Samples in the Fifo
  dataAccessCtrl.bits.slotADataHold = 1;
  dataAccessCtrl.bits.slotBDataHold = 1;

  writeToRegister(DATA_ACCESS_CONTROL_REGISTER, dataAccessCtrl.raw, hspi, csPin, true);





  if (read_fifo_state==0)
  {
    //Calc average ADP data to delete background noise
    dummy_data = readFifo(hspi,csPin);
    for (uint8_t k=0; k<backNoiseArray; k++)
	{
		Data_A_backNoise[k]=Data_A_backNoise[k+1];
		Data_B_backNoise[k]=Data_B_backNoise[k+1];
	}
	Data_A_backNoise[backNoiseArray-1]=dummy_data.raw_ADP_Data_A;
	Data_B_backNoise[backNoiseArray-1]=dummy_data.raw_ADP_Data_B;
	Data_A_Offset_Sum += dummy_data.raw_ADP_Data_A;
	Data_B_Offset_Sum += dummy_data.raw_ADP_Data_B;
	offset_cnt++;

	uint32_t sum_Data_A=0,sum_Data_B=0;
	for (uint8_t k=0; k<backNoiseArray; k++)
	{
		sum_Data_A+=Data_A_backNoise[k];
		sum_Data_B+=Data_B_backNoise[k];
		check_A=sum_Data_A;
	}
	Data_A_Offset = Data_A_Offset_Sum / offset_cnt;
	Data_B_Offset = Data_B_Offset_Sum / offset_cnt;
	Blue_IR_Offset=sum_Data_A/backNoiseArray; // value err
	check_B=avg_data_A;
	IR_Offset=sum_Data_B/backNoiseArray;

  }
  else
  {
	  raw_adp_data = readFifo(hspi, csPin);
  }






  // 데이터 처리
  processed_A = raw_adp_data.raw_ADP_Data_A-ui.Blue_IR_Offset >= 0 ? raw_adp_data.raw_ADP_Data_A - ui.Blue_IR_Offset : 0;
  processed_B = raw_adp_data.raw_ADP_Data_B-ui.IR_Offset >= 0 ? raw_adp_data.raw_ADP_Data_B - ui.IR_Offset : 0;
/*  _final_filt_data filting_finish_data = filting_data(processed_A,processed_B);

  ADP_RESULT.result_Blue_val = filting_finish_data.final_filt_Data_A;
  ADP_RESULT.result_IR_val = filting_finish_data.final_filt_Data_B;
*/
//  ADP_RESULT.result_Blue_val = raw_adp_data.raw_ADP_Data_A;
//  ADP_RESULT.result_IR_val = raw_adp_data.raw_ADP_Data_B;
  ADP_RESULT.result_Blue_val = processed_A;
  ADP_RESULT.result_IR_val = processed_B;

  //raw_adp_data.raw = 0; // initialize

  return ADP_RESULT;
}

//----------------------------------------------------------------------------------------------------------------------

void config(SPI_HandleTypeDef hspi, struct CsPin csPin) {

    // write recommanded configurations  DS P42
    //while (writeToRegister(0x11, 0x30A9, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x11, 0x20A9, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x12, 0x0028, hspi, csPin, true) != HAL_OK); // 16 Hz ***********
    /*
     * Sampling frequency: fSAMPLE = 32 kHz/(Register 0x12, Bits[15:0] × 4).
For example, 100 Hz = 0x0050; 200 Hz = 0x0028
     */
    while (writeToRegister(0x14, 0x011D, hspi, csPin, true) != HAL_OK); // when using fifo data read
//    while (writeToRegister(0x14, 0x550, hspi, csPin, true) != HAL_OK);  // when using independence slot channel
    while (writeToRegister(0x15, 0x0, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x17, 0x09, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x18, 0x00, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x19, 0x3FFF, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x1A, 0x3FFF, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x1B, 0x3FFF, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x1D, 0x09, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x1E, 0x00, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x1F, 0x3FFF, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x20, 0x3FFF, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x21, 0x3FFF, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x22, 0x3539, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x23, 0x3536, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x24, 0x1530, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x25, 0x630C, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x30, 0x320, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x31, 0x040E, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x35, 0x320, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x36, 0x040E, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x39, 0x22F0, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x3B, 0x22F0, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x3C, 0x31C6, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x42, 0x1C34, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x43, 0xADA5, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x44, 0x1C34, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x45, 0xADA5, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x58, 0x0544, hspi, csPin, true) != HAL_OK);
    while (writeToRegister(0x54, 0x0AA0, hspi, csPin, true) != HAL_OK);
}

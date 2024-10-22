/*
 * EEPROM.c
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#include "..\Source\HSD300_FW.h"

extern SPI_HandleTypeDef hspi2;
/* Private function prototypes -----------------------------------------------*/
_EEPROM EEPROM;


SPI_HandleTypeDef * EEPROM_SPI;


uint16_t EEPROM_addr = 0x5AD6;

uint8_t offset_Flag = 0;

/* Private function ----------------------------------------------------------*/
void EEPROM_Comm(uint8_t* T_buffer, uint8_t* R_buffer, unsigned int num);
EEPROM_Operations EEPROM_SPI_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
EEPROM_Operations EEPROM_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
EEPROM_Operations EEPROM_SPI_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
uint8_t EEPROM_SPI_WaitStandbyState(void);

uint8_t EEPROM_SendByte(uint8_t byte);
void EEPROM_WriteEnable(void);
void EEPROM_WriteDisable(void);
void EEPROM_WriteStatusRegister(uint8_t regval);
uint8_t EEPROM_ReadStatusRegister(void);

void EEPROM_WriteEnable(void);
void EEPROM_WriteDisable(void);

void EEPROM_SPI_SendInstruction(uint8_t *instruction, uint8_t size);
void EEPROM_Factory_Reset();

void EEPROM_Comm(uint8_t* T_buffer, uint8_t* R_buffer, unsigned int num)
{
	EEPROM_CS_OFF(); // Hal_writePin(reset)
	//WP_EEPROM_OFF();
	//HOLD_EEPROM_ON();    // CS low

	HAL_SPI_TransmitReceive(EEPROM_SPI, T_buffer, R_buffer, num, 10);
	EEPROM.Result  = EEPROM_SPI->ErrorCode;

   	EEPROM_CS_ON();
   	//WP_EEPROM_ON();
   	//HOLP_EEPROM_OFF();   // CS high
}

/****************************************************************************/
/*	Overview	:										*/
/*	Return value:	void													*/
/****************************************************************************/
void EEPROM_init(void)
{
	EEPROM_SPI_INIT(&hspi2);

	EEPROM.TxBuff[0] = EEPROM_RDSR;
	EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, 2);

	EEPROM.TxBuff[0] = EEPROM_READ;
	EEPROM.TxBuff[1] = (EEPROM_addr >> 8) & 0xFF;
	EEPROM.TxBuff[2] = EEPROM_addr & 0x00FF;
	for(uint8_t i = 3; i < EEPROM_BUF_MAX; i++){
		EEPROM.TxBuff[i] = 0x00;
	}
	EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, EEPROM_BUF_MAX);
	if(EEPROM.RxBuff[28] != 0xD8 && EEPROM.RxBuff[29] != 0xD8)
	{
		EEPROM_Factory_Reset();
	}
	else
	{
		if(EEPROM.RxBuff[4] == 0xFF && EEPROM.RxBuff[3] == 0xFF){
			ui.temp_warring = 45;
			ui.temp_warring_hex = 4500;
		}
		else{
			ui.temp_warring_hex = (EEPROM.RxBuff[3] & 0xFF) | (EEPROM.RxBuff[4] << 8);
			if(ui.temp_warring_hex > 9999){
				ui.temp_warring_hex = 9999;
			}
			ui.temp_warring = (uint16_t)(ui.temp_warring_hex / 100);
		}
		if(EEPROM.RxBuff[5] == 0xFF && EEPROM.RxBuff[6] == 0xFF){
			ui.temp_alarm = 60;
			ui.temp_alarm_hex = 6000;
		}
		else{
			ui.temp_alarm_hex	= (EEPROM.RxBuff[5] & 0xFF) | (EEPROM.RxBuff[6] << 8);
			if(ui.temp_alarm_hex > 9999){
				ui.temp_alarm_hex = 9999;
			}
			ui.temp_alarm = (uint16_t)(ui.temp_alarm_hex / 100);
		}
		if((EEPROM.RxBuff[7] == 0xFF && EEPROM.RxBuff[8] == 0xFF) || (EEPROM.RxBuff[7] == 0x00 && EEPROM.RxBuff[8] == 0x00)){
			read_fifo_state = 0;
		}
		else{
			read_fifo_state = 1;
			ui.IR_Offset = (EEPROM.RxBuff[8] << 8) | (EEPROM.RxBuff[7] & 0xFF);
		}
		if((EEPROM.RxBuff[9] == 0xFF && EEPROM.RxBuff[10] == 0xFF) || (EEPROM.RxBuff[9] == 0x00 && EEPROM.RxBuff[10] == 0x00)){
			read_fifo_state = 0;
		}
		else{
			read_fifo_state = 1;
			ui.Blue_IR_Offset = (EEPROM.RxBuff[9] << 8) | (EEPROM.RxBuff[10] & 0xFF);
		}
		if(EEPROM.RxBuff[11] == 0){
			ui.temp_alarm_enable = 0;
		}
		else{
			ui.temp_alarm_enable = 1;
		}
		if(EEPROM.RxBuff[12] == 0){
			ui.temp_warring_maintain_bit = 0;
		}
		else{
			ui.temp_warring_maintain_bit = 1;
		}
		if(EEPROM.RxBuff[13] == 0){
			ui.temp_alarm_maintain_bit = 0;
		}
		else{
			ui.temp_alarm_maintain_bit = 1;
		}
		if(EEPROM.RxBuff[20] == 1)
		{
			ui.End_Code = 1;
		}
		else
		{
			ui.End_Code = 0;
		}
		if(EEPROM.RxBuff[22] == 0xFF){
			ui.SMK_Level = RANK_1;
		}
		else{
			ui.SMK_Level = EEPROM.RxBuff[22];
		}
		if(EEPROM.RxBuff[23] == 0xff)
		{
			ui.Protocol_Type = 1;
		}
		else
		{
			ui.Protocol_Type = EEPROM.RxBuff[23];
		}

	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void EEPROM_routine(void)  // 1000ms
{
	//EEPROM TEST
	//EEPROM_SPI_WriteBuffer(EEPROM.Buff, (uint16_t)0x01, EEPROM_BUFFER_SIZE);
	if(EEPROM.SaveData_Flag == 1)  // EEPROM.SaveData_Flag == 1 --> 저장할 데이터가 있음을 의미하는것이 아닌가
	{
		EEPROM.TxBuff[0] = EEPROM_WREN;
		EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, 1);        // HAL_SPI_TransmitReceive()
		//HAL_Delay(10);
		EEPROM.TxBuff[0] = EEPROM_RDSR;
		EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, 2);

		EEPROM.TxBuff[0] = EEPROM_WRITE;          // 쓰기 명령 전송
		EEPROM.TxBuff[1] = EEPROM_addr >> 8;      // high byte // 데이터를 쓸 상위 주소
		EEPROM.TxBuff[2] = EEPROM_addr & 0x00FF;  // low byte  // 데이터를 쓸 하위 주소
		EEPROM.TxBuff[3] = (uint16_t)(ui.temp_warring_hex & 0xFF);  // ui 구조체에 있는 변수를 버퍼에 저장
		EEPROM.TxBuff[4] = (uint16_t)(ui.temp_warring_hex >>8);
		EEPROM.TxBuff[5] = (uint16_t)(ui.temp_alarm_hex & 0xFF);
		EEPROM.TxBuff[6] = (uint16_t)(ui.temp_alarm_hex >>8);
		EEPROM.TxBuff[7] = (ui.IR_Offset & 0xFF);
		EEPROM.TxBuff[8] = (ui.IR_Offset >> 8);
		EEPROM.TxBuff[9] = (ui.Blue_IR_Offset & 0xFF);
		EEPROM.TxBuff[10] = (ui.Blue_IR_Offset >> 8);
		EEPROM.TxBuff[11] = ui.temp_alarm_enable;
		EEPROM.TxBuff[12] = ui.temp_warring_maintain_bit;
		EEPROM.TxBuff[13] = ui.temp_alarm_maintain_bit;
		EEPROM.TxBuff[14] = 0x00;
		EEPROM.TxBuff[15] = 0x00;
		EEPROM.TxBuff[16] = 0x00;
		EEPROM.TxBuff[17] = 0x00;
		EEPROM.TxBuff[18] = 0x00;
		EEPROM.TxBuff[19] = 0x00;
		EEPROM.TxBuff[20] = ui.End_Code;
		EEPROM.TxBuff[21] = 0x00;
		EEPROM.TxBuff[22] = ui.SMK_Level;
		EEPROM.TxBuff[23] = ui.Protocol_Type;
		EEPROM.TxBuff[24] = 0x00;
		EEPROM.TxBuff[25] = 0x00;
		EEPROM.TxBuff[26] = 0x00;
		EEPROM.TxBuff[27] = 0;//Adc.ZO_flag;

		EEPROM.TxBuff[28] = 0xD8;
		EEPROM.TxBuff[29] = 0xD8;

		EEPROM.Checksum = 0;
		for(int i = 3; i < 28; i++)
		{
			EEPROM.Checksum += EEPROM.TxBuff[i];     // 3번부터 27번까지 데이터 다 더해서 30~31에 8바이트씩 나눠서 넣는데
		}											 // 나중에 데이터가 올바르게 기록되었는지 확인 용도인거 같음

		EEPROM.TxBuff[30] = (uint16_t)(EEPROM.Checksum & 0xFF);
		EEPROM.TxBuff[31] = (uint16_t)(EEPROM.Checksum >>8);

		EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, EEPROM_BUF_MAX);
		//HAL_Delay(10);
		EEPROM.SaveData_Flag = 0;
	}
	if(EEPROM.Result != 0)
	{
		EEPROM.Error_cnt ++;
	}
	if((EEPROM.Error_cnt == 5) && (EEPROM.Error == 0))
	{
		EEPROM.Error = 1;
	}
}


void EEPROM_SPI_INIT(SPI_HandleTypeDef * hspi) {
    EEPROM_SPI = hspi;
}

/**
  * @brief  Writes more than one byte to the EEPROM with a single WRITE cycle
  *         (Page WRITE sequence).
  *
  * @note   The number of byte can't exceed the EEPROM page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the EEPROM, must be equal
  *         or less than "EEPROM_PAGESIZE" value.
  * @retval EEPROM_Operations value: EEPROM_STATUS_COMPLETE or EEPROM_STATUS_ERROR
  */
EEPROM_Operations EEPROM_SPI_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite) {
    while (EEPROM_SPI->State != HAL_SPI_STATE_READY) {
        //osDelay(1);
    }

    HAL_StatusTypeDef spiTransmitStatus;

    EEPROM_WriteEnable();

    /*
        We gonna send commands in one packet of 3 bytes
     */
    uint8_t header[3];

    header[0] = EEPROM_WRITE;   // Send "Write to Memory" instruction
    header[1] = WriteAddr >> 8; // Send 16-bit address
    header[2] = WriteAddr;

    // Select the EEPROM: Chip Select low
    EEPROM_CS_OFF();

    EEPROM_SPI_SendInstruction((uint8_t*)header, 3);

    // Make 5 attemtps to write the data
    for (uint8_t i = 0; i < 5; i++) {
        spiTransmitStatus = HAL_SPI_Transmit(EEPROM_SPI, pBuffer, NumByteToWrite, 100);

        if (spiTransmitStatus == HAL_BUSY) {
           // osDelay(5);
        } else {
            break;
        }
    }

    // Deselect the EEPROM: Chip Select high
    EEPROM_CS_ON();

    // Wait the end of EEPROM writing
    EEPROM_SPI_WaitStandbyState();

    // Disable the write access to the EEPROM
    EEPROM_WriteDisable();

    if (spiTransmitStatus == HAL_ERROR) {
        return EEPROM_STATUS_ERROR;
    } else {
        return EEPROM_STATUS_COMPLETE;
    }
}

/**
  * @brief  Writes block of data to the EEPROM. In this function, the number of
  *         WRITE cycles are reduced, using Page WRITE sequence.
  *
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the EEPROM.
  * @param  WriteAddr: EEPROM's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the EEPROM.
  * @retval EEPROM_Operations value: EEPROM_STATUS_COMPLETE or EEPROM_STATUS_ERROR
  */
EEPROM_Operations EEPROM_SPI_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite) {
    uint16_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
    uint16_t EEPROM_DataNum = 0;

    EEPROM_Operations pageWriteStatus = EEPROM_STATUS_PENDING;

    Addr = WriteAddr % EEPROM_PAGESIZE;
    count = EEPROM_PAGESIZE - Addr;
    NumOfPage =  NumByteToWrite / EEPROM_PAGESIZE;
    NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;

    if (Addr == 0) { /* WriteAddr is EEPROM_PAGESIZE aligned  */
        if (NumOfPage == 0) { /* NumByteToWrite < EEPROM_PAGESIZE */
            EEPROM_DataNum = NumByteToWrite;
            pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

            if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                return pageWriteStatus;
            }

        } else { /* NumByteToWrite > EEPROM_PAGESIZE */
            while (NumOfPage--) {
                EEPROM_DataNum = EEPROM_PAGESIZE;
                pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

                if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                    return pageWriteStatus;
                }

                WriteAddr +=  EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }

            EEPROM_DataNum = NumOfSingle;
            pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

            if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                return pageWriteStatus;
            }
        }
    } else { /* WriteAddr is not EEPROM_PAGESIZE aligned  */
        if (NumOfPage == 0) { /* NumByteToWrite < EEPROM_PAGESIZE */
            if (NumOfSingle > count) { /* (NumByteToWrite + WriteAddr) > EEPROM_PAGESIZE */
                temp = NumOfSingle - count;
                EEPROM_DataNum = count;
                pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

                if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                    return pageWriteStatus;
                }

                WriteAddr +=  count;
                pBuffer += count;

                EEPROM_DataNum = temp;
                pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);
            } else {
                EEPROM_DataNum = NumByteToWrite;
                pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);
            }

            if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                return pageWriteStatus;
            }
        } else { /* NumByteToWrite > EEPROM_PAGESIZE */
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / EEPROM_PAGESIZE;
            NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;

            EEPROM_DataNum = count;

            pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

            if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                return pageWriteStatus;
            }

            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--) {
                EEPROM_DataNum = EEPROM_PAGESIZE;

                pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

                if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                    return pageWriteStatus;
                }

                WriteAddr +=  EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }

            if (NumOfSingle != 0) {
                EEPROM_DataNum = NumOfSingle;

                pageWriteStatus = EEPROM_SPI_WritePage(pBuffer, WriteAddr, EEPROM_DataNum);

                if (pageWriteStatus != EEPROM_STATUS_COMPLETE) {
                    return pageWriteStatus;
                }
            }
        }
    }

    return EEPROM_STATUS_COMPLETE;
}

/**
  * @brief  Reads a block of data from the EEPROM.
  *
  * @param  pBuffer: pointer to the buffer that receives the data read from the EEPROM.
  * @param  ReadAddr: EEPROM's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the EEPROM.
  * @retval None
  */
EEPROM_Operations EEPROM_SPI_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead) {
    while (EEPROM_SPI->State != HAL_SPI_STATE_READY) {
    }

    /*
        We gonna send all commands in one packet of 3 bytes
     */

    uint8_t header[3];

    header[0] = EEPROM_READ;    // Send "Read from Memory" instruction
    header[1] = ReadAddr >> 8;  // Send 16-bit address
    header[2] = ReadAddr;

    // Select the EEPROM: Chip Select low
    EEPROM_CS_OFF();

    /* Send WriteAddr address byte to read from */
    EEPROM_SPI_SendInstruction(header, 3);

    while (HAL_SPI_Receive(EEPROM_SPI, (uint8_t*)pBuffer, NumByteToRead, 200) == HAL_BUSY) {
    };

    // Deselect the EEPROM: Chip Select high
    EEPROM_CS_ON();

    return EEPROM_STATUS_COMPLETE;
}

uint8_t EEPROM_SPI_WaitStandbyState(void) {
    uint8_t sEEstatus[1] = { 0x00 };
    uint8_t command[1] = { EEPROM_RDSR };

    // Select the EEPROM: Chip Select low
    EEPROM_CS_OFF();

    // Send "Read Status Register" instruction
    EEPROM_SPI_SendInstruction((uint8_t*)command, 1);

    // Loop as long as the memory is busy with a write cycle
    do {

        while (HAL_SPI_Receive(EEPROM_SPI, (uint8_t*)sEEstatus, 1, 200) == HAL_BUSY) {
            //osDelay(1);
        };

        //osDelay(1);

    } while ((sEEstatus[0] & EEPROM_WIP_FLAG) == SET); // Write in progress

    // Deselect the EEPROM: Chip Select high
    EEPROM_CS_ON();

    return 0;
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  *
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t EEPROM_SendByte(uint8_t byte) {
    uint8_t answerByte;

    /* Loop while DR register in not empty */
    while (EEPROM_SPI->State == HAL_SPI_STATE_RESET) {
        //osDelay(1);
    }

    /* Send byte through the SPI peripheral */
    if (HAL_SPI_Transmit(EEPROM_SPI, &byte, 1, 200) != HAL_OK) {
        Error_Handler();
    }

    /* Wait to receive a byte */
    while (EEPROM_SPI->State == HAL_SPI_STATE_RESET) {
        //osDelay(1);
    }

    /* Return the byte read from the SPI bus */
    if (HAL_SPI_Receive(EEPROM_SPI, &answerByte, 1, 200) != HAL_OK) {
        Error_Handler();
    }

    return (uint8_t)answerByte;
}

/**
  * @brief  Enables the write access to the EEPROM.
  *
  * @param  None
  * @retval None
  */
void EEPROM_WriteEnable(void) {
    // Select the EEPROM: Chip Select low
    EEPROM_CS_OFF();

    uint8_t command[1] = { EEPROM_WREN };
    /* Send "Write Enable" instruction */
    EEPROM_SPI_SendInstruction((uint8_t*)command, 1);

    // Deselect the EEPROM: Chip Select high
    EEPROM_CS_ON();
}

/**
  * @brief  Disables the write access to the EEPROM.
  *
  * @param  None
  * @retval None
  */
void EEPROM_WriteDisable(void) {
    // Select the EEPROM: Chip Select low
    EEPROM_CS_OFF();

    uint8_t command[1] = { EEPROM_WRDI };

    /* Send "Write Disable" instruction */
    EEPROM_SPI_SendInstruction((uint8_t*)command, 1);

    // Deselect the EEPROM: Chip Select high
    EEPROM_CS_ON();
}


/**
 * @brief Low level function to send header data to EEPROM
 *
 * @param instruction array of bytes to send
 * @param size        data size in bytes
 */
void EEPROM_SPI_SendInstruction(uint8_t *instruction, uint8_t size) {
    while (EEPROM_SPI->State == HAL_SPI_STATE_RESET) {
    }

    if (HAL_SPI_Transmit(EEPROM_SPI, (uint8_t*)instruction, (uint16_t)size, 200) != HAL_OK) {
        Error_Handler();
    }
}
void EEPROM_Factory_Reset(void)
{
	EEPROM.TxBuff[0] = EEPROM_WREN;
	EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, 1);
	//HAL_Delay(10);
	EEPROM.TxBuff[0] = EEPROM_RDSR;
	EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, 2);

	ui.temp_warring_hex = 4500;
	ui.temp_warring = ui.temp_warring_hex / 100;
	ui.temp_alarm_hex = 6000;
	ui.temp_alarm = ui.temp_alarm_hex / 100;
	ui.temp_alarm_enable = 1;
	ui.temp_warring_maintain_bit = 0;
	ui.temp_alarm_maintain_bit = 0;
	ui.SMK_Level = RANK_1;
	ui.Protocol_Type = 1;  // Default is OnOff Protocal
	ui.End_Code			= 1;
	// Zero_Offset�� 2.9 ~ 3.2���� �ʱ� ���� �� ����(HSD200) - �ּҰ� Default ����

	EEPROM.TxBuff[0] = EEPROM_WRITE;
	EEPROM.TxBuff[1] = EEPROM_addr >> 8;      // high byte
	EEPROM.TxBuff[2] = EEPROM_addr & 0x00FF;  // low byte
	EEPROM.TxBuff[3] = (uint16_t)(ui.temp_warring_hex & 0xFF);
	EEPROM.TxBuff[4] = (uint16_t)(ui.temp_warring_hex >>8);
	EEPROM.TxBuff[5] = (uint16_t)(ui.temp_alarm_hex & 0xFF);
	EEPROM.TxBuff[6] = (uint16_t)(ui.temp_alarm_hex >>8);
	EEPROM.TxBuff[7] = (ui.IR_Offset & 0xFF);
	EEPROM.TxBuff[8] = (ui.IR_Offset >> 8);
	EEPROM.TxBuff[9] = (ui.Blue_IR_Offset & 0xFF);
	EEPROM.TxBuff[10] = (ui.Blue_IR_Offset >> 8);
	EEPROM.TxBuff[11] = ui.temp_alarm_enable;
	EEPROM.TxBuff[12] = ui.temp_warring_maintain_bit;
	EEPROM.TxBuff[13] = ui.temp_alarm_maintain_bit;
	EEPROM.TxBuff[14] = 0x00;
	EEPROM.TxBuff[15] = 0x00;
	EEPROM.TxBuff[16] = 0x00;
	EEPROM.TxBuff[17] = 0x00;
	EEPROM.TxBuff[18] = 0x00;
	EEPROM.TxBuff[19] = 0x00;
	EEPROM.TxBuff[20] = ui.End_Code;
	EEPROM.TxBuff[21] = 0x00;
	EEPROM.TxBuff[22] = ui.SMK_Level;
	EEPROM.TxBuff[23] = ui.Protocol_Type;
	EEPROM.TxBuff[24] = 0x00;
	EEPROM.TxBuff[25] = 0x00;
	EEPROM.TxBuff[26] = 0x00;
	EEPROM.TxBuff[27] = 0;//Adc.ZO_flag;

	EEPROM.TxBuff[28] = 0xD8;
	EEPROM.TxBuff[29] = 0xD8;

	EEPROM.Checksum = 0;
	for(int i = 3; i < 28; i++)
	{
		EEPROM.Checksum += EEPROM.TxBuff[i];
	}

	EEPROM.TxBuff[30] = (uint16_t)(EEPROM.Checksum & 0xFF);
	EEPROM.TxBuff[31] = (uint16_t)(EEPROM.Checksum >>8);

	EEPROM_Comm(EEPROM.TxBuff, EEPROM.RxBuff, EEPROM_BUF_MAX);
	//HAL_Delay(10);
}

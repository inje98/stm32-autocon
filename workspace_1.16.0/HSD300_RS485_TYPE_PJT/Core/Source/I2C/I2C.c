/*
 * I2C.c
 *
 *  Created on: Nov 6, 2023
 *      Author: autocontech
 */

/* Includes ------------------------------------------------------------------*/
#include "..\Source\HSD300_FW.h"

//SHT30
uint32_t Temp_Check_Test=0;
uint32_t Humi_Check_Test=0;

extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;

_SHT30_Dev Int_SHT30;
_SHT30_Dev Ext_SHT30;

uint8_t i2c3_write[2];			// I2C 쓰기 버퍼
uint8_t i2c3_read[6];			// I2C 읽기 버퍼
uint8_t i2c3_read_state[3];		// I2C 상태 읽기 버퍼

uint8_t i2c3_period_cnt = 1;	// 센서 데이터 읽기 주기 변경용 CNT

uint8_t I_temp_acc_cnt = 0;
uint8_t I_humi_acc_cnt = 0;
int32_t I_temp_acc[20];
int32_t I_humi_acc[20];
uint32_t I2C3_Total_reset = 0;

I2C_STATUS_REGISTER i2c_Status;

uint8_t u1f_sensor_error = SENSOR_NOT_ERROR;	// 센서 에러 데이터 저장

float temp_correction = -4.0;
float humi_correction = 2.2;

// 온도 습도 변환
float ff_cTemp = 0;
float ff_humidity = 0;

float Calibration_ff_cTemp = 0;




uint32_t i2c3_state;
uint32_t i2c3_error;
uint32_t i2c3_success = 0;
uint32_t i2c3_error_cnt = 0;
uint8_t i2c3_error_flag = 0;

uint8_t u1f_temp_crc_error_cnt = 0;
uint8_t u1f_humi_crc_error_cnt = 0;
uint8_t u1f_crc_error_flag = 0;


//VL53L3CX
_VL53L3CX_Main VL53L3CX_Main;

uint32_t i2c3_state_VL53L3CX;
uint32_t i2c3_error_VL53L3CX;

int32_t Distance;

int32_t Distance1;

uint8_t VL53L3CX_Buffer[4]={0,};

void FUN_I2C_SHT30_Init(void);
void FUN_I2C_SHT30_Routine(void);
void I2C_SHT30_Task(void* argument);


void sfun_I2C_Measurement_results(_SHT30_Dev *sht30);
void sfun_I2C_Measurement_conversion(_SHT30_Dev *sht30);
void sfun_I2C_Acc_Data(_SHT30_Dev *sht30);
void sfun_I2C_Measurement_Error_Check(_SHT30_Dev *sht30);
void sfun_I2C_Status_Check(_SHT30_Dev *sht30);
uint8_t sfun_sht30_crc8(const uint8_t *data, int len);

int16_t FUN_I2C_sht30_ctemp_100times_rtn(void);
int16_t FUN_I2C_sht30_humi_100times_rtn(void);

uint8_t FUN_I2C_SensorError_rtn(void);

void FUN_I2C_SensorError_Init(void);

uint8_t FUN_Test_I2C_SensorReset_rtn(void);

float sfun_Temp_sensor_calibration(float ft_ntc, float ft_sensor);

void FUN_I2C_VL53L3CX_Init(void);
void FUN_I2C_VL53L3CX_Routine(void);
void I2C_VL53L3CX_Task(void* argument);

void FUN_I2C_SHT30_Init(void)
{
	i2c3_write[0] = (uint8_t)(CMD_SINGLE_EN_HIGH >> 8);
	i2c3_write[1] = (uint8_t)(CMD_SINGLE_EN_HIGH & 0xFF);
	//구조체 추가
	Ext_SHT30.I2C_Handle = &hi2c2;
	Int_SHT30.I2C_Handle = &hi2c3;

	Ext_SHT30.I2C_Addr = TEMP_SENSOR_ADDR;
	Ext_SHT30.i2c_period_cnt = 1;
	Ext_SHT30.temp_acc_cnt = 0;
	Ext_SHT30.i2c_total_reset = 0;
	Ext_SHT30.i2c_success = 0;
	Ext_SHT30.i2c_error_cnt = 0;
	Ext_SHT30.i2c_error_flag = 0;
	Ext_SHT30.temp_crc_error_cnt = 0;
	Ext_SHT30.humi_crc_error_cnt = 0;
	Ext_SHT30.crc_error_flag = 0;
	Ext_SHT30.sensor_error = SENSOR_NOT_ERROR;
	Ext_SHT30.warring_cnt = 0;
	Ext_SHT30.alarm_cnt = 0;


	Int_SHT30.I2C_Addr = TEMP_SENSOR_ADDR;
	Int_SHT30.i2c_period_cnt = 1;
	Int_SHT30.humi_acc_cnt = 0;
	Int_SHT30.i2c_total_reset = 0;
	Int_SHT30.i2c_success = 0;
	Int_SHT30.i2c_error_cnt = 0;
	Int_SHT30.i2c_error_flag = 0;
	Int_SHT30.temp_crc_error_cnt = 0;
	Int_SHT30.humi_crc_error_cnt = 0;
	Int_SHT30.crc_error_flag = 0;
	Int_SHT30.sensor_error = SENSOR_NOT_ERROR;
	Int_SHT30.warring_cnt = 0;
	Int_SHT30.alarm_cnt = 0;

	memcpy(Ext_SHT30.i2c_write_buff, i2c3_write, 2);
	memcpy(Int_SHT30.i2c_write_buff, i2c3_write, 2);

	HAL_I2C_Master_Transmit(Ext_SHT30.I2C_Handle, Ext_SHT30.I2C_Addr, Ext_SHT30.i2c_write_buff, 2, 100);
	HAL_I2C_Master_Transmit(Int_SHT30.I2C_Handle, Int_SHT30.I2C_Addr, Int_SHT30.i2c_write_buff, 2, 100);
	//HAL_I2C_Master_Transmit(&hi2c2, 0x45, i2c3_write, 2, 100);
}
void FUN_SHT30_Routine(_SHT30_Dev *sht30){  	// 250ms마다 호출
	sht30->i2c_state = HAL_I2C_GetState(sht30->I2C_Handle); // sht30->I2C_Handle->State
	sht30->i2c_error = HAL_I2C_GetError(sht30->I2C_Handle); // sht30->I2C_Handle->ErrorCode

	if((sht30->i2c_state == HAL_I2C_STATE_READY) && (sht30->i2c_error == HAL_I2C_ERROR_NONE))   //sht30->i2c_state가 준비상태이고, sht30->i2c_error 에러 없으면
		{
			// 주기 처리
			if(sht30->i2c_period_cnt == 4) { 			// 250ms * 4 =  // 1초마다 //
				sht30->i2c_period_cnt = 0;

				// 측정 결과 저장 : I2C 통신 진행
				sfun_I2C_Measurement_results(sht30); 	// 이런거 호출 // 센서 데이터를 받고 다시 측정하라고 명령 보내고

				// 결과 데이터 온습도로 변환
				sfun_I2C_Measurement_conversion(sht30); // 받은 온습도 값 무결성 확인 후 값 정제후 sht30 구조체 변수에 저장

				// 온습도 데이터 누적 저장
				sfun_I2C_Acc_Data(sht30);				// sht30->temp_acc[], sht30->humi_acc[] 배열에 차곡차곡 저장

				// 누적 데이터로 리셋 하는 함수 - 테스트상 현재 제외
				sfun_I2C_Measurement_Error_Check(sht30);//
			}

			sht30->i2c_period_cnt++;

			// 실행 카운터 증가 - |||210825 추가|||
			sht30->i2c_success++;

			// 실행 카운터 일정치 이상 증가시 에러 카운터 초기화 - |||210825 추가|||
			if(sht30->i2c_success >= 40)
			{
				sht30->i2c_error_cnt = 0;
			}
		}
		//
		else
		{
			sht30->i2c_error_cnt++;
		}

		// 250ms * 40 = 10초
		// 에러 카운터 일정치 누적시 - |||210825 추가|||
		if(sht30->i2c_error_cnt == 40) //10초
		{
			HAL_I2C_DeInit(sht30->I2C_Handle);		// I2C 초기화 해제 - |||210825 추가|||

			HAL_Delay(10);				// 일정 딜레이 (10ms) - |||210825 추가|||

			if (HAL_I2C_Init(sht30->I2C_Handle) != HAL_OK)  // I2C 초기화 진행 - |||210825 추가|||
			{
				Error_Handler();
			}
			if (HAL_I2CEx_ConfigAnalogFilter(sht30->I2C_Handle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
			{
				Error_Handler();
			}
			if (HAL_I2CEx_ConfigDigitalFilter(sht30->I2C_Handle, 0) != HAL_OK)
			{
				Error_Handler();
			}

			sht30->i2c_success = 0;	// 실행 카운터 제거 - |||210825 추가|||

			sht30->i2c_error_cnt++;		// 에러 카운터 증가 - |||210825 추가|||
		}

		if(sht30->i2c_error_cnt >= 50) 	// 초기화 후에도 카운터 누적시 에러 (ex. 온도 센서 고장시)
		{
			sht30->i2c_error_flag = 1;
		}

		// 에러 체크
		if((sht30->crc_error_flag == 1) ||(sht30->i2c_error_flag == 1))
		{
			sht30->sensor_error = SENSOR_ERROR;
		}
		else
		{
			sht30->sensor_error = SENSOR_NOT_ERROR;
		}

}

void FUN_I2C_SHT30_Routine(void)
{
	FUN_SHT30_Routine(&Int_SHT30);
	FUN_SHT30_Routine(&Ext_SHT30);
}

void FUN_I2C_INT_SHT30_Routine(void){  	// 250ms 마다 호출
	FUN_SHT30_Routine(&Int_SHT30);
	ui.i_temp_100times = (uint16_t)(Int_SHT30.temperature * 100);
	ui.i_humi_100times = (uint16_t)(Int_SHT30.humidity * 100);
}
void FUN_I2C_EXT_SHT30_Routine(void){	// 250ms 마다 호출
	FUN_SHT30_Routine(&Ext_SHT30);
	ui.temp_100times = (uint16_t)(Ext_SHT30.temperature * 100);
	ui.humi_100times = (uint16_t)(Ext_SHT30.humidity * 100);
	if(ui.temp_alarm_enable){
		if(ui.temp_warring_maintain_bit == 1 && ui.temp_warring_bit != 1){
			if(Ext_SHT30.temperature > ui.temp_warring){
				Ext_SHT30.warring_cnt ++;
				if(Ext_SHT30.warring_cnt >= 5){
					ui.temp_warring_bit = 1;
					Ext_SHT30.warring_cnt = 0;
				}
			}
		}
		else if(ui.temp_warring_maintain_bit == 0){
			if(Ext_SHT30.temperature > ui.temp_warring){
				Ext_SHT30.warring_cnt ++;
				if(Ext_SHT30.warring_cnt >= 5){
					ui.temp_warring_bit = 1;
					Ext_SHT30.warring_cnt = 0;
				}
			}
			else if(ui.temp_warring_bit == 1){
				ui.temp_warring_bit = 0;
				Ext_SHT30.warring_cnt = 0;
			}
		}
		if(ui.temp_alarm_maintain_bit == 1 && ui.temp_alarm_bit != 1){
			if(Ext_SHT30.temperature > ui.temp_alarm){
				Ext_SHT30.alarm_cnt ++;
				if(Ext_SHT30.alarm_cnt >= 5){
					ui.temp_alarm_bit = 1;
					Ext_SHT30.alarm_cnt = 0;
				}
			}
		}
		else if(ui.temp_warring_maintain_bit == 0){
			if(Ext_SHT30.temperature > ui.temp_alarm){
				Ext_SHT30.alarm_cnt ++;
				if(Ext_SHT30.alarm_cnt >= 5){
					ui.temp_alarm_bit = 1;
					Ext_SHT30.alarm_cnt = 0;
				}
			}
			else if(ui.temp_alarm_bit == 1){
				ui.temp_alarm_bit = 0;
				Ext_SHT30.alarm_cnt = 0;
			}
		}
	}
	Error.SHT30_Error = Ext_SHT30.i2c_error_flag;
}


/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void sfun_I2C_Measurement_results(_SHT30_Dev *sht30)												// 250ms * 4 = 1초마다
{
	HAL_I2C_Master_Receive(sht30->I2C_Handle, sht30->I2C_Addr, sht30->i2c_read_buff, 6, 100);  		// 센서로부터 데이터 수신

	sht30->i2c_write_buff[0] = (uint8_t)(CMD_SINGLE_EN_HIGH >> 8);
	sht30->i2c_write_buff[1] = (uint8_t)(CMD_SINGLE_EN_HIGH & 0xFF);   						   		// buf에 저장
	HAL_I2C_Master_Transmit(sht30->I2C_Handle, sht30->I2C_Addr, sht30->i2c_write_buff, 2, 100);		// 센서로 다시 측정하라는 명령인듯. 100은 타임아웃
}

// 수신 데이터 온도 습도로 환산
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void sfun_I2C_Measurement_conversion(_SHT30_Dev *sht30)  // 250ms * 4 = 1초마다
{
// 1. 온도값 CRC 계산이 맞으면
	if(sht30->i2c_read_buff[2] == sfun_sht30_crc8(&sht30->i2c_read_buff[0],2))   // sfun_sht30_crc8() : 센서에서 온도 데이터가 손상됐는지, 정확한지 확인 하는거인듯
	{
	// 1-1. 온도값 데이터 환산
		int temp = (sht30->i2c_read_buff[0] * 256 + sht30->i2c_read_buff[1]);
		sht30->temperature = -45 + (175 * temp / 65535.0) + temp_correction;  // 온도값 정제하는거인듯
		sht30->temp_hex = (uint16_t)(sht30->temperature * 10);
		sht30->crc_error_flag = 0;
		sht30->temp_crc_error_cnt = 0;
	} else
	{
		// 온도값 CRC 에러 카운터 증가 : 센서 데이터 에러
		sht30->temp_crc_error_cnt++;  											// sfun_sht30_crc8() 확인 해보니 무결하지 않다! -> 에러 카운트 증가

	}

// 2. 습도값 CRC 계산이 맞으면
	if(sht30->i2c_read_buff[5] == sfun_sht30_crc8(&sht30->i2c_read_buff[3],2)) {
	// 2-1. 습도값 데이터 환산
		sht30->humidity = (100 * (sht30->i2c_read_buff[3] * 256 + sht30->i2c_read_buff[4]) / 65535.0) + 5 + humi_correction;
		// 습도 보정 +5% 210826
		if(sht30->humidity >= 100)
		{
			sht30->humidity = 100;
		}

		sht30->humi_hex = (uint16_t)(sht30->humidity * 10);
		sht30->crc_error_flag = 0;
		sht30->humi_crc_error_cnt = 0;
	} else {
		// 습도값 CRC 에러 카운터 증가 : 센서 데이터 에러
		sht30->humi_crc_error_cnt++;
	}

	if((sht30->temp_crc_error_cnt >= 10)||
	  (sht30->humi_crc_error_cnt >= 10)) {
		sht30->crc_error_flag = 1;
	}
	else {
		sht30->crc_error_flag = 0;
	}
	Temp_Check_Test = ceil(sht30->temperature);
	Humi_Check_Test = ceil(sht30->humidity);
	//printf("Temp %d, Humi %d\n",Temp_Check_Test, Humi_Check_Test);
}

// 온습도 데이터 누적 : 20개
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void sfun_I2C_Acc_Data(_SHT30_Dev *sht30)          // sht30 구조체 변수에 넣은 값 sht30->temp_acc,humi_acc 배열에 차곡차곡 저장 250ms * 4 = 1초마다 인덱스 바뀌면서 저장될듯
{
	sht30->temp_acc[sht30->temp_acc_cnt] = (sht30->temperature * 1000);
	sht30->humi_acc[sht30->humi_acc_cnt] = (sht30->humidity * 1000);

	if(sht30->temp_acc_cnt == 19) {
		sht30->temp_acc_cnt = 0;
	} else {
		++sht30->temp_acc_cnt;
	}
}

// 누적 데이터로 리셋 여부 체크 / 리셋 실행
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void sfun_I2C_Measurement_Error_Check(_SHT30_Dev *sht30)
{
	uint8_t u1t_t_chk = 0;
	uint8_t u1t_h_chk = 0;

	for(uint8_t i = 0; i < 19; i++) {
		if(sht30->temp_acc[i] == sht30->temp_acc[i+1]) {
			u1t_t_chk++;
		} else {break;}
		if(sht30->humi_acc[i] == sht30->humi_acc[i+1]) {
			u1t_h_chk++;
		} else {break;}
	}

	if((u1t_t_chk == 19) || (u1t_h_chk == 19)) {
		// I2C RESET
		sht30->i2c_write_buff[0] = (uint8_t)(CMD_SOFT_RESET >> 8);
		sht30->i2c_write_buff[1] = (uint8_t)(CMD_SOFT_RESET & 0xFF);

		HAL_I2C_Master_Transmit(sht30->I2C_Handle, sht30->I2C_Addr, sht30->i2c_write_buff, 2, 100);
		while(HAL_I2C_STATE_READY != HAL_I2C_GetState(sht30->I2C_Handle));

		sht30->i2c_total_reset++;
	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void sfun_I2C_Status_Check(_SHT30_Dev *sht30)
{
	// 상태 초기화
	if(sht30->i2c_period_cnt == 1) {
		sht30->i2c_write_buff[0] = (uint8_t)(CMD_CLEAR_STATUS_REGISTER >> 8);
		sht30->i2c_write_buff[1] = (uint8_t)(CMD_CLEAR_STATUS_REGISTER & 0xFF);

		HAL_I2C_Master_Transmit(sht30->I2C_Handle, sht30->I2C_Addr, sht30->i2c_write_buff, 2, 100);
		while(HAL_I2C_STATE_READY != HAL_I2C_GetState(sht30->I2C_Handle));
	}
	// 상태 읽어오기
	if(sht30->i2c_period_cnt == 2) {
		sht30->i2c_write_buff[0] = (uint8_t)(CMD_STATUS_REGISTER >> 8);
		sht30->i2c_write_buff[1] = (uint8_t)(CMD_STATUS_REGISTER & 0xFF);

		HAL_I2C_Master_Transmit(sht30->I2C_Handle, sht30->I2C_Addr, sht30->i2c_write_buff, 2, 100);
		while(HAL_I2C_STATE_READY != HAL_I2C_GetState(sht30->I2C_Handle));
		HAL_I2C_Master_Receive(sht30->I2C_Handle, sht30->I2C_Addr, sht30->i2c_read_state_buff, 3, 100);
		while(HAL_I2C_STATE_READY != HAL_I2C_GetState(sht30->I2C_Handle));

		if(sht30->i2c_read_state_buff[2] == sfun_sht30_crc8(&sht30->i2c_read_state_buff[0],2)) {
			sht30->i2c_Status.monitor_all = (((uint16_t)sht30->i2c_read_state_buff[0]) << 8) | (uint16_t)sht30->i2c_read_state_buff[1];
		}else {
			sht30->i2c_Status.monitor_all = 0xFFFF;
		}
	}
}

/* Polynomial: 0x31 (x8 + x5 + x4 + 1)
 * Initialization: 0xFF
 * Final XOR: 0x00
 * Example: CRC (0xBEEF) = 0x92 */
// CRC-8
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
uint8_t sfun_sht30_crc8(const uint8_t *data, int len)  // 받은 온도 데이터의 무결성 확인 이라고만 일단 알아둬보자
{
    uint8_t crc = 0xff;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

// 온도값 호출에 사용
// 1. 온도값에 x100배를 반환(float -> int16으로 변환)
// 2. 소수점 2째자리까지 표현
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
int16_t FUN_I2C_sht30_ctemp_100times_rtn(void)
{
	int16_t d2t_temp_rtn = 0;
	float ft_dummy = 0;


	//온도 켈리브레이션 추가 20220908 추가

	Calibration_ff_cTemp = ff_cTemp;//sfun_Temp_sensor_calibration(ff_NTC_temp,ff_cTemp);

	ft_dummy = Calibration_ff_cTemp * 100;


	d2t_temp_rtn = (int16_t)ft_dummy;

	return d2t_temp_rtn;
}

// 습도값 호출에 사용
// 1.습도값에 x100배를 반환(float -> int16으로 변환)
// 2. 소수점 2째자리까지 표현
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
int16_t FUN_I2C_sht30_humi_100times_rtn(void)
{
	int16_t d2t_humi_rtn = 0;
	float ft_dummy = 0;

	ft_dummy = ff_humidity * 100;

	d2t_humi_rtn = (int16_t)ft_dummy;

	return d2t_humi_rtn;
}

// 센서 에러 호출
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
uint8_t FUN_I2C_SensorError_rtn(void)
{
	return u1f_sensor_error;
}

// 센서 에러 제거
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_I2C_SensorError_Init(void)
{
	u1f_sensor_error = SENSOR_NOT_ERROR;
}



// 센서 에러 호출
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
uint8_t FUN_Test_I2C_SensorReset_rtn(void)
{
	return I2C3_Total_reset;
}






float sfun_Temp_sensor_calibration(float ft_ntc, float ft_sensor)
{
	// ntc - Sensor
	float ft_result_value = 0;
//	int16_t d2t_result_value = 0;
	float ft_n_c_difference = ft_ntc - ft_sensor;
	float ft_correction_value = 0;

	// 온도 센서 20도 이하 구간
	if(ft_sensor <= 20.0f)
	{
		// 보정 수치 없음. (오차 3도 미만 구간)
		if(ft_n_c_difference < 3.0f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 3도 이상 5도 미만 구간)
		else if(ft_n_c_difference < 5.0f)
		{
			ft_correction_value = (2.25f * ft_n_c_difference) - 6.25f;
		}
		// 보정 수식 고정값 적용 (오차 5도 이상 구간)
		else
		{
			ft_correction_value = 4.5f;
		}
	}
	else if(ft_sensor <= 30.0f)// 20도 초과  < 온도 센서 <= 30도 이하 구간
	{
		// 보정 수치 없음. (오차 3도 미만 구간)
		if(ft_n_c_difference < 3.0f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 3도 이상 5도 미만 구간)
		else if(ft_n_c_difference < 5.0f)
		{
			ft_correction_value = (2.25f * ft_n_c_difference) - 6.25f;
		}
		// 보정 수식 고정값 적용 (오차 5도 이상 구간)
		else
		{
			ft_correction_value = 4.5f;
		}
	}
	else if(ft_sensor <= 40.0f) // 30도 초과  < 온도 센서 <= 40도 이하 구간
	{
		// 보정 수치 없음. (오차 3도 미만 구간)
		if(ft_n_c_difference < 3.0f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 3도 이상 5도 미만 구간)
		else if(ft_n_c_difference < 5.0f)
		{
			ft_correction_value = (2.2f * ft_n_c_difference) - 6.1f;
		}
		// 보정 수식 고정값 적용 (오차 5도 이상 구간)
		else
		{
			ft_correction_value = 4.4f;
		}
	}
	else if(ft_sensor <= 50.0f) // 40도 초과  < 온도 센서 <= 50도 이하 구간
	{
		// 보정 수치 없음. (오차 2.8도 미만 구간)
		if(ft_n_c_difference < 2.8f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 2.8도 이상 4.8도 미만 구간)
		else if(ft_n_c_difference < 4.8f)
		{
			ft_correction_value = (2.2f * ft_n_c_difference) - 5.66f;
		}
		// 보정 수식 고정값 적용 (오차 4.8도 이상 구간)
		else
		{
			ft_correction_value = 4.4f;
		}
	}
	else if(ft_sensor <= 60.0f) // 50도 초과  < 온도 센서 <= 60도 이하 구간
	{
		// 보정 수치 없음. (오차 2.8도 미만 구간)
		if(ft_n_c_difference < 2.8f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 2.8도 이상 4.8도 미만 구간)
		else if(ft_n_c_difference < 4.8f)
		{
			ft_correction_value = (2.2f * ft_n_c_difference) - 5.66f;
		}
		// 보정 수식 고정값 적용 (오차 4.8도 이상 구간)
		else
		{
			ft_correction_value = 4.2f;
		}
	}
	else if(ft_sensor <= 70.0f) // 60도 초과  < 온도 센서 <= 70도 이하 구간
	{
		// 보정 수치 없음. (오차 2.8도 미만 구간)
		if(ft_n_c_difference < 2.8f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 2.8도 이상 4.8도 미만 구간)
		else if(ft_n_c_difference < 4.8f)
		{
			ft_correction_value = (2.0f * ft_n_c_difference) - 7.5f;
		}
		// 보정 수식 고정값 적용 (오차 4.8도 이상 구간)
		else
		{
			ft_correction_value = 3.5f;
		}
	}
	else // 70도 초과  < 온도 센서 구간
	{
		// 보정 수치 없음. (오차 2.8도 미만 구간)
		if(ft_n_c_difference < 2.8f)
		{
			ft_correction_value = 0.0f;
		}
		// 보정 수식 적용. (오차 2.8도 이상 4.8도 미만 구간)
		else if(ft_n_c_difference < 4.8f)
		{
			ft_correction_value = (2.0f * ft_n_c_difference) - 7.5f;
		}
		// 보정 수식 고정값 적용 (오차 4.8도 이상 구간)
		else
		{
			ft_correction_value = 3.5f;
		}
	}

	ft_result_value = ft_sensor - ft_correction_value;

//	d2t_result_value = (int16_t)(ft_result_value * 100);

//	return d2t_result_value;

	return ft_result_value;
}

void FUN_I2C_VL53L3CX_Init(void)
{
	MX_TOF_Init();

	HAL_Delay(5);
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	Void													*/
/****************************************************************************/
void FUN_I2C_VL53L3CX_Routine(void)
{
	i2c3_state_VL53L3CX = HAL_I2C_GetState(&hi2c3);
	i2c3_error_VL53L3CX = HAL_I2C_GetError(&hi2c3);
	MX_TOF_Process();

//	if(Check_1 < 0)
//		Check_1 = 0;
	//printf("Distance : %d , Status : %d\n", Check_1, Check_2);
}

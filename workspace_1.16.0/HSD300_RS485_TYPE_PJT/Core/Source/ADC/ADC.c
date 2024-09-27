/*
 * ADC.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "..\Source\HSD300_FW.h"

/* Private variables ---------------------------------------------------------*/
#define ADC_BUFF_MAX 30

extern ADC_HandleTypeDef hadc2;

ADC_HandleTypeDef* SENSOR_ADC;
uint32_t AdcIntCnt = 0;
uint32_t adc_val;
uint16_t adc_value[ADC_BUFF_MAX];
uint8_t a_index = 0;
uint16_t Co_Sensor;
float ppm;
#define Faraday  96500.0
float vout;
/*-------Prototype Declaration----------------------------------------------*/
void SENSOR_ADC_init();
uint16_t FUN_ADC_GetValue();
uint16_t movingAverageFilter(uint16_t * buf);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) { // 인터럽트 방식은 HAL_ADC_Start_DMA()를 안쓰니까 안쓰는듯?
	adc_value[a_index] = adc_val;                        // 5ms 마다 폴링방식 쓰는거 같음
	vout = (float)(adc_value[a_index]/4096.0)*3.3;
	if(++a_index >= ADC_BUFF_MAX){
		a_index = 0;
	}
	AdcIntCnt++;
	HAL_ADC_Stop_DMA(SENSOR_ADC);
}
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_Init(ADC_HandleTypeDef* hadc)
{
	//ADC Parameter Reset
	for(int i = 0; i < ADC_BUFF_MAX; i++)
	{
		adc_value[i] = 0;
	}
	SENSOR_ADC_init(hadc);
}
void SENSOR_ADC_init(ADC_HandleTypeDef* hadc)
{
	SENSOR_ADC = hadc;
	//HAL_ADC_Start_DMA(SENSOR_ADC, (uint32_t *)adc_val, 1);       // DMA 꺼놨네?
}

uint16_t FUN_ADC_GetValue()  // 딱 SENSOR_ADC 값을 받아서 value에 넣어서 리턴
{
	uint16_t value = 0;
	//uint8_t status = 0;
	/*status = */
	HAL_ADC_Start(SENSOR_ADC);
	HAL_ADC_PollForConversion(SENSOR_ADC, 100);
	value = HAL_ADC_GetValue(SENSOR_ADC);
	HAL_ADC_Stop(SENSOR_ADC);
	return value;
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_Routine(void)  // 5ms 마다 이리로 온다.
{
	//Polling
	adc_value[a_index] = FUN_ADC_GetValue();           // 5ms마다 SENSOR_ADC값 넣어주는데. 5ms마다 a_index 증가하면서 배열 방마다 툭툭 넣어주는거지
	Co_Sensor = movingAverageFilter(&adc_value[0]);    // 그 평균을 CO_Sensor에 넣어주고
	vout = (float)(Co_Sensor/4096.0)*3.3 ;             // 아날로그 센서 값을 전압으로 치환하는거 아닐까싶음
	//ppm = Co_Sensor / 100;
	ui.co_100times = Co_Sensor;                        // RS485에 있는 [2] ~ [3] NTC 온도 라는데 일단 몰라 일단 Pass
	if(++a_index >= ADC_BUFF_MAX)                      // ADC_BUFF_MAX가 30이니까 5ms * 30 = 0.15초 마다 인덱스 초기화
	{
		a_index = 0;
	}

	//DMA
	//HAL_ADC_Start_DMA(SENSOR_ADC, (uint32_t *)adc_val, 1);
}

uint16_t movingAverageFilter(uint16_t * buf)
{
	uint8_t valid_cnt = 0;
	uint16_t totalSum = 0;
	uint16_t average = 0;

	for(uint8_t i = 0; i < ADC_BUFF_MAX; i++)
	{
		if(buf[i] > 0){
			valid_cnt++;
			totalSum += buf[i];
		}
	}
	if(valid_cnt > 0)
	{
		average = totalSum / valid_cnt;
	}
	return average;

}

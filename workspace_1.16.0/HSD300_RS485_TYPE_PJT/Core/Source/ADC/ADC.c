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

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	adc_value[a_index] = adc_val;
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
	//HAL_ADC_Start_DMA(SENSOR_ADC, (uint32_t *)adc_val, 1);
}

uint16_t FUN_ADC_GetValue()
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
void FUN_ADC_Routine(void)
{
	//Polling
	adc_value[a_index] = FUN_ADC_GetValue();
	Co_Sensor = movingAverageFilter(&adc_value[0]);
	vout = (float)(Co_Sensor/4096.0)*3.3 ;
	//ppm = Co_Sensor / 100;
	ui.co_100times = Co_Sensor;
	if(++a_index >= ADC_BUFF_MAX)
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

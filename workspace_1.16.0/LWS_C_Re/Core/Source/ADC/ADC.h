/*
 * ADC.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define ADC1_ON							(0)
#define ADC2_ON							(1)

#define ADC1_SEL0_M_LOW()				HAL_GPIO_WritePin(ADC1_SEL0_M_GPIO_Port, ADC1_SEL0_M_Pin, GPIO_PIN_RESET)
#define ADC1_SEL0_M_HIGH()				HAL_GPIO_WritePin(ADC1_SEL0_M_GPIO_Port, ADC1_SEL0_M_Pin, GPIO_PIN_SET)
#define ADC1_SEL1_M_LOW()				HAL_GPIO_WritePin(ADC1_SEL1_M_GPIO_Port, ADC1_SEL1_M_Pin, GPIO_PIN_RESET)
#define ADC1_SEL1_M_HIGH()				HAL_GPIO_WritePin(ADC1_SEL1_M_GPIO_Port, ADC1_SEL1_M_Pin, GPIO_PIN_SET)
#define ADC1_SEL2_M_LOW()				HAL_GPIO_WritePin(ADC1_SEL2_M_GPIO_Port, ADC1_SEL2_M_Pin, GPIO_PIN_RESET)
#define ADC1_SEL2_M_HIGH()				HAL_GPIO_WritePin(ADC1_SEL2_M_GPIO_Port, ADC1_SEL2_M_Pin, GPIO_PIN_SET)

#define ADC2_SEL0_M_LOW()				HAL_GPIO_WritePin(ADC2_SEL0_M_GPIO_Port, ADC2_SEL0_M_Pin, GPIO_PIN_RESET)
#define ADC2_SEL0_M_HIGH()				HAL_GPIO_WritePin(ADC2_SEL0_M_GPIO_Port, ADC2_SEL0_M_Pin, GPIO_PIN_SET)
#define ADC2_SEL1_M_LOW()				HAL_GPIO_WritePin(ADC2_SEL1_M_GPIO_Port, ADC2_SEL1_M_Pin, GPIO_PIN_RESET)
#define ADC2_SEL1_M_HIGH()				HAL_GPIO_WritePin(ADC2_SEL1_M_GPIO_Port, ADC2_SEL1_M_Pin, GPIO_PIN_SET)
#define ADC2_SEL2_M_LOW()				HAL_GPIO_WritePin(ADC2_SEL2_M_GPIO_Port, ADC2_SEL2_M_Pin, GPIO_PIN_RESET)
#define ADC2_SEL2_M_HIGH()				HAL_GPIO_WritePin(ADC2_SEL2_M_GPIO_Port, ADC2_SEL2_M_Pin, GPIO_PIN_SET)

#define ADC_CH_SELECT_1						(0)
#define ADC_CH_SELECT_2						(1)
#define ADC_CH_SELECT_3						(2)
#define ADC_CH_SELECT_4						(3)
#define ADC_CH_SELECT_5						(4)
#define ADC_CH_SELECT_6						(5)
#define ADC_CH_SELECT_7						(6)
#define ADC_CH_SELECT_8						(7)

/* Private variables ---------------------------------------------------------*/
typedef struct
{
	uint8_t ADC_Channel;
	uint8_t Adc1_ChannelSelect_Error_flag;
	uint8_t Adc2_ChannelSelect_Error_flag;
	uint16_t Adc_Voltage_CntBuffer[8];
	float Adc_Voltage_SumBuffer[8];
	float Adc_Voltage_AvgBuffer[8];
	uint8_t Mux_Flag;
} _Adc;
extern _Adc Adc;


/* Private function prototypes -----------------------------------------------*/
void FUN_ADC_Init(void);
void FUN_ADC_Routine(void);
void FUN_ADC_AvgValueReset(void);

#endif /* ADC_ADC_H_ */

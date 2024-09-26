/*
 * ADC.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

/* Includes ------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

extern uint16_t Co_Sensor;

/* Private function prototypes -----------------------------------------------*/
void FUN_ADC_Init(ADC_HandleTypeDef* hadc);
void FUN_ADC_Routine(void);

#endif /* ADC_ADC_H_ */

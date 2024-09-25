/*
 * TIM.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef TIM_TIM_H_
#define TIM_TIM_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define Winch_A_SPEED				(1)
#define Winch_B_SPEED				(2)
#define Align_SPEED					(3)


#define Align_Frequency_Output()			HAL_GPIO_TogglePin(OUT_CH30_GPIO_Port, OUT_CH30_Pin)
#define Winch_A_Frequency_Output()			HAL_GPIO_TogglePin(OUT_CH32_GPIO_Port, OUT_CH32_Pin)
#define Winch_B_Frequency_Output()			HAL_GPIO_TogglePin(OUT_CH34_GPIO_Port, OUT_CH34_Pin)

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
typedef struct
{
	uint16_t Tim4_Prescalor;
	uint16_t Tim5_Prescalor;
	uint16_t Tim7_Prescalor;
	uint16_t Tim4_Period;
	uint16_t Tim5_Period;
	uint16_t Tim7_Period;

	uint8_t RPM_Flag;
}_TIM;
extern _TIM TIM;

/* Private function prototypes -----------------------------------------------*/
void FUN_TIM_Init(void);
void FUN_TIM_Routine(void);
void FUN_Frequency_Ctrl(uint8_t u1t_ch, uint16_t u2t_frequency);
void FUN_HILS_Frequency_Ctrl(void);
#endif /* TIM_TIM_H_ */

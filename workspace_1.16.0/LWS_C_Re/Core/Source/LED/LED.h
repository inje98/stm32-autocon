/*
 * LED.h
 *
 *  Created on: 2022. 9. 7.
 *      Author: hgson
 */

#ifndef LED_LED_H_
#define LED_LED_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define CNT_OFFSET			(0)

#define LED_LOW				(0)
#define LED_HIGH			(1)

#define LED_1_SEL			(0)
#define LED_2_SEL			(1)
#define LED_3_SEL			(2)
#define LED_4_SEL			(3)

// LED ON - High
#define LED_1_ON()			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET)
#define LED_2_ON()			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET)
#define LED_3_ON()			HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET)
#define LED_4_ON()			HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET)

// LED OFF - Low
#define LED_1_OFF()			HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET)
#define LED_2_OFF()			HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET)
#define LED_3_OFF()			HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET)
#define LED_4_OFF()			HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET)

/* Private variables ---------------------------------------------------------*/
typedef struct
{
	uint8_t LED_Check_Cnt;
	uint8_t GUI_Check_Cnt;
} _LED;
extern _LED LED;
/* Private function prototypes -----------------------------------------------*/
void FUN_LED_Routine(void);

#endif /* LED_LED_H_ */

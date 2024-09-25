/*
 * LED.c
 *
 *  Created on: 2022. 9. 7.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "main.h"

#include "LED.h"
#include "../Control/Control.h"

/* Private variables ---------------------------------------------------------*/
_LED LED;

/* Private function prototypes -----------------------------------------------*/
void FUN_LED_GUICheck(void);
void FUN_LED_Output(uint8_t u1t_LED_SEL, uint8_t u1t_led_state);

/* Private function prototypes -----------------------------------------------*/
void FUN_LED_Routine(void)
{
	FUN_LED_GUICheck();

	if(LED.LED_Check_Cnt <= 0 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_LOW);
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_3_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 5 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_HIGH);
		FUN_LED_Output(LED_2_SEL, LED_HIGH);
		FUN_LED_Output(LED_3_SEL, LED_HIGH);
		FUN_LED_Output(LED_4_SEL, LED_HIGH);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 10 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_LOW);
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_3_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 15 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_HIGH);
		FUN_LED_Output(LED_2_SEL, LED_HIGH);
		FUN_LED_Output(LED_3_SEL, LED_HIGH);
		FUN_LED_Output(LED_4_SEL, LED_HIGH);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 20 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_LOW);
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_3_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 25 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_HIGH);
		FUN_LED_Output(LED_2_SEL, LED_HIGH);
		FUN_LED_Output(LED_3_SEL, LED_HIGH);
		FUN_LED_Output(LED_4_SEL, LED_HIGH);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 30 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_LOW);
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_3_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 35 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_HIGH);
		FUN_LED_Output(LED_2_SEL, LED_HIGH);
		FUN_LED_Output(LED_3_SEL, LED_HIGH);
		FUN_LED_Output(LED_4_SEL, LED_HIGH);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 40 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_LOW);
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_3_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 45 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_HIGH);
		FUN_LED_Output(LED_2_SEL, LED_HIGH);
		FUN_LED_Output(LED_3_SEL, LED_HIGH);
		FUN_LED_Output(LED_4_SEL, LED_HIGH);
		LED.LED_Check_Cnt++;
	}
	else if(LED.LED_Check_Cnt <= 50 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_1_SEL, LED_LOW);
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_3_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);
		LED.LED_Check_Cnt++;
	}
	else
	{
		LED.LED_Check_Cnt = 51 + CNT_OFFSET;
		FUN_LED_Output(LED_1_SEL, LED_HIGH);
		Control.Status_01.Bit.Status2 = 1;
		Control.Status_01.Bit.Status3 = 1;
	}

	LED.GUI_Check_Cnt++;
}

void FUN_LED_GUICheck(void)
{
	if(LED.GUI_Check_Cnt < 50 + CNT_OFFSET)
	{
		FUN_LED_Output(LED_2_SEL, LED_HIGH);
		FUN_LED_Output(LED_4_SEL, LED_HIGH);

		Control.Status_01.Bit.Status0 = 1;
		Control.Status_01.Bit.Status4 = 1;
	}
	else
	{
		LED.GUI_Check_Cnt = 50;
		FUN_LED_Output(LED_2_SEL, LED_LOW);
		FUN_LED_Output(LED_4_SEL, LED_LOW);

		Control.Status_01.Bit.Status0 = 0;
		Control.Status_01.Bit.Status4 = 0;
	}
}


// 입력 : LED 선택, LED 상태
void FUN_LED_Output(uint8_t u1t_LED_SEL, uint8_t u1t_LED_state)
{
	switch(u1t_LED_SEL)
	{
		case LED_1_SEL:
			if(u1t_LED_state == LED_HIGH)	// LED 켜기
			{
				LED_1_ON();
			}
			else
			{								// LED 끄기
				LED_1_OFF();
			}
			break;
		case LED_2_SEL:
			if(u1t_LED_state == LED_HIGH)
			{
				LED_2_ON();
			}
			else
			{
				LED_2_OFF();
			}
			break;
		case LED_3_SEL:
			if(u1t_LED_state == LED_HIGH)
			{
				LED_3_ON();
			}
			else
			{
				LED_3_OFF();
			}
			break;
		case LED_4_SEL:
			if(u1t_LED_state == LED_HIGH)
			{
				LED_4_ON();
			}
			else
			{
				LED_4_OFF();
			}
			break;
	}
}

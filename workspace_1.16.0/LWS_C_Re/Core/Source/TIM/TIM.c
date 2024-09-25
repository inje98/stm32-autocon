/*
 * ADC.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "TIM.h"
#include "..\Control\Control.h"
#include "..\Encoder\Encoder.h"
#include "..\HILS\HILS.h"
#include "..\GPIO\GPO.h"
#include "..\RS485\RS485.h"

//#include "../Control/Control.h"

/* Private variables ---------------------------------------------------------*/

/*-------Macro Declaration----------------------------------------------------*/
#define TIMER_100us				(9)
#define TIMER_250us				(24)		//4kHz
#define TIMER_500us				(49)
#define TIMER_1ms				(99)
#define TIMER_2ms				(199)
#define TIMER_5ms				(499)
#define TIMER_10ms				(999)
#define TIMER_100ms				(9999)
#define TIMER_1000ms			(99999)

/* Private function prototypes -----------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;

uint32_t u4f_tim2_cnt = 0;

uint8_t u1f_tim_100us_trg = 0;
uint8_t u1f_tim_250us_trg = 0;
uint8_t u1f_tim_500us_trg = 0;
uint8_t u1f_tim_1ms_trg = 0;
uint8_t u1f_tim_2ms_trg = 0;
uint8_t u1f_tim_5ms_trg = 0;
uint8_t u1f_tim_10ms_trg = 0;
uint8_t u1f_tim_100ms_trg = 0;
uint8_t u1f_tim_1000ms_trg = 0;

/* Private function prototypes -----------------------------------------------*/
void TIM4_User_Setting(uint16_t u2t_prescaler, uint16_t u2t_period);
void TIM5_User_Setting(uint16_t u2t_prescaler, uint16_t u2t_period);
void TIM7_User_Setting(uint16_t u2t_prescaler, uint16_t u2t_period);

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_TIM_Init(void)
{
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_Base_Start_IT(&htim2);
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_TIM_Routine(void)
{

}

uint64_t Timer_Check = 0;
uint64_t Timer_Check_1 = 0;
uint64_t Timer_Check_2 = 0;
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
uint32_t Check_100ms = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  if (htim->Instance == TIM1)
	  {
	    HAL_IncTick();
	  }

	if(htim->Instance==TIM2)
	{
		if((u4f_tim2_cnt % (TIMER_100us + 1)) == 0) {				// 100us
			u1f_tim_100us_trg = 1;
		}

		if((u4f_tim2_cnt % (TIMER_250us + 1)) == 0) {				// 250us
			u1f_tim_250us_trg = 1;
		}

		if((u4f_tim2_cnt % (TIMER_500us + 1)) == 0) {				// 500us
			u1f_tim_500us_trg = 1;
		}

		if((u4f_tim2_cnt % (TIMER_1ms + 1)) == 0) {					// 1ms
			u1f_tim_1ms_trg = 1;
		}

		if((u4f_tim2_cnt % (TIMER_2ms + 1)) == 0) {					// 2ms
			u1f_tim_2ms_trg = 1;
			Timer_Check++;
		}

		if((u4f_tim2_cnt % (TIMER_5ms + 1)) == 0) {					// 5ms
			u1f_tim_5ms_trg = 1;
			Timer_Check_1++;
		}

		if((u4f_tim2_cnt % (TIMER_10ms + 1)) == 0) {				// 10ms
			u1f_tim_10ms_trg = 1;
			Timer_Check_2++;
		}

		if((u4f_tim2_cnt % (TIMER_100ms + 1)) == 2) {				// 100ms
			u1f_tim_100ms_trg = 1;
			Check_100ms++;
		}

		if((u4f_tim2_cnt % (TIMER_1000ms + 1)) == 2) {				// 1000ms
			u1f_tim_1000ms_trg = 1;
		}
		u4f_tim2_cnt++;
		FUN_Encoder_Routine();
	}

	// 윈치드럼 유압모터 A 속도(TA)
	if(htim->Instance==TIM4)
	{
		Winch_A_Frequency_Output();
	}

	// 윈치드럼 유압모터 B 속도(TA)
	if(htim->Instance==TIM5)
	{
		Winch_B_Frequency_Output();
	}

	// 권선정렬 유압모터 속도(TA)
	if(htim->Instance==TIM7)
	{
		Align_Frequency_Output();
	}
}

void FUN_Frequency_Ctrl(uint8_t u1t_ch, uint16_t u2t_frequency)
{
	uint16_t u2t_freq_val = 0;

	u2t_freq_val = (5000 / u2t_frequency ) - 1;

	if(u1t_ch == Winch_A_SPEED)
	{
		TIM4_User_Setting(10799,u2t_freq_val/2);
		HAL_TIM_Base_Start_IT(&htim4);
	}
	else if(u1t_ch == Winch_B_SPEED)
	{
		TIM5_User_Setting(10799,u2t_freq_val/2);
		HAL_TIM_Base_Start_IT(&htim5);
	}
	else if(u1t_ch == Align_SPEED)
	{
		TIM7_User_Setting(10799,u2t_freq_val/2);
		HAL_TIM_Base_Start_IT(&htim7);
	}
	else;
}

void FUN_HILS_Frequency_Ctrl(void)
{
	if(HILS_START == FUN_RS485_Ctrl_hils_action_U1())
	{
		//Winch_A 출력 제어
		if(HILS.HILS_Output.HILS_AO_Float[7] > 0)		//A
		{
			OUTPUT_CH_31_LOW();						// 방향제어
			FUN_Frequency_Ctrl(Winch_A_SPEED, HILS.HILS_Output.HILS_AO_Float[7]*3.45);
		}
		else if(HILS.HILS_Output.HILS_AO_Float[7] == 0)
		{
			HAL_TIM_Base_DeInit(&htim4);
			OUTPUT_CH_31_HIGH();
			OUTPUT_CH_32_HIGH();
		}
		else if(HILS.HILS_Output.HILS_AO_Float[7] < 0)
		{
			OUTPUT_CH_31_HIGH();					// 방향제어
			FUN_Frequency_Ctrl(Winch_A_SPEED, -(HILS.HILS_Output.HILS_AO_Float[7]*3.45));
		}

		//Winch_B 출력 제어
		if(HILS.HILS_Output.HILS_AO_Float[8] > 0)		//B
		{
			OUTPUT_CH_33_LOW();						// 방향제어
			FUN_Frequency_Ctrl(Winch_B_SPEED, HILS.HILS_Output.HILS_AO_Float[8]*3.45);
		}
		else if(HILS.HILS_Output.HILS_AO_Float[8] == 0)
		{
			HAL_TIM_Base_DeInit(&htim5);
			OUTPUT_CH_33_HIGH();
			OUTPUT_CH_34_HIGH();
		}
		else if(HILS.HILS_Output.HILS_AO_Float[8] < 0)
		{
			OUTPUT_CH_33_HIGH();					// 방향제어
			FUN_Frequency_Ctrl(Winch_B_SPEED, -(HILS.HILS_Output.HILS_AO_Float[8]*3.45));
		}

		//Align 출력제어
		if(HILS.HILS_Output.HILS_AO_Float[9] > 0)		//권선
		{
			OUTPUT_CH_29_LOW();						// 방향제어
			FUN_Frequency_Ctrl(Align_SPEED, HILS.HILS_Output.HILS_AO_Float[9]);
		}
		else if(HILS.HILS_Output.HILS_AO_Float[9] == 0)
		{
			HAL_TIM_Base_DeInit(&htim7);
			OUTPUT_CH_29_HIGH();
			OUTPUT_CH_30_HIGH();
		}
		else if(HILS.HILS_Output.HILS_AO_Float[9] < 0)
		{
			OUTPUT_CH_29_HIGH();					// 방향제어
			FUN_Frequency_Ctrl(Align_SPEED, -(HILS.HILS_Output.HILS_AO_Float[9]));
		}

		Control.Float_Data.WinchDrumHydMotorASpeed = HILS.HILS_Output.HILS_AO_Float[7];
		Control.Float_Data.WinchDrumHydMotorBSpeed = HILS.HILS_Output.HILS_AO_Float[8];
		Control.Float_Data.AlignHydMotorSpeed = HILS.HILS_Output.HILS_AO_Float[9];
	}
}

/****************************************************************************/
/*	Overview	:	TIM4 Prescaler, Period 사용자 임의 설정 변경					*/
/*	Return value:	void													*/
/****************************************************************************/
void TIM4_User_Setting(uint16_t u2t_prescaler, uint16_t u2t_period)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = u2t_prescaler;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = u2t_period;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
	  Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
	  Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
	  Error_Handler();
  }

}

/****************************************************************************/
/*	Overview	:	TIM5 Prescaler, Period 사용자 임의 설정 변경					*/
/*	Return value:	void													*/
/****************************************************************************/
void TIM5_User_Setting(uint16_t u2t_prescaler, uint16_t u2t_period)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = u2t_prescaler;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = u2t_period;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
	  Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
	  Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
	  Error_Handler();
  }

}

/****************************************************************************/
/*	Overview	:	TIM7 Prescaler, Period 사용자 임의 설정 변경					*/
/*	Return value:	void													*/
/****************************************************************************/
void TIM7_User_Setting(uint16_t u2t_prescaler, uint16_t u2t_period)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = u2t_prescaler;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = u2t_period;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
	  Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
	  Error_Handler();
  }

}

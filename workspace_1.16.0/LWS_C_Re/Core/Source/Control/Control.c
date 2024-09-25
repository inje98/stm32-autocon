/*
 * Control.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Control.h"

#include "..\GPIO\GPO.h"
#include "..\GPIO\GPI.h"
#include "..\TIM\TIM.h"
#include "..\DAC\DAC.h"
#include "..\ADC\ADC.h"
#include "..\LED\LED.h"
#include "..\RS485\RS485.h"
#include "..\Encoder\Encoder.h"
#include "..\EEPROM\EEPROM.h"
#include "..\HILS\HILS.h"
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
extern uint8_t u1f_tim_100us_trg;
extern uint8_t u1f_tim_250us_trg;
extern uint8_t u1f_tim_500us_trg;
extern uint8_t u1f_tim_1ms_trg;
extern uint8_t u1f_tim_2ms_trg;
extern uint8_t u1f_tim_5ms_trg;
extern uint8_t u1f_tim_10ms_trg;
extern uint8_t u1f_tim_100ms_trg;
extern uint8_t u1f_tim_1000ms_trg;

/* Private function prototypes -----------------------------------------------*/
void FUN_Control_Parameter_Reset(void);
void FUN_Control_tim2_100us_routine();
void FUN_Control_tim2_250us_routine();
void FUN_Control_tim2_500us_routine();
void FUN_Control_tim2_1ms_routine();
void FUN_Control_tim2_2ms_routine();
void FUN_Control_tim2_5ms_routine();
void FUN_Control_tim2_10ms_routine();
void FUN_Control_tim2_100ms_routine();
void FUN_Control_tim2_1000ms_routine();

/* Private function ----------------------------------------------------------*/


/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_Init(void)
{
	FUN_TIM_Init();

	FUN_EEPROM_Init();

	FUN_ADC_Init();

	FUN_DAC_Init();

	FUN_GPO_Init();

	FUN_RS485_Init();

	FUN_Encoder_Init();

	FUN_HILS_Init();

	FUN_Control_Parameter_Reset();
}

/****************************************************************************/
/*	Overview	:	Control Parameter Reset									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_Parameter_Reset(void)
{
	Control.Status_01.LWS_C_Status = 0;
	Control.Status_02.LWS_C_Status = 0;

	Control.Mode.LWS_C_Mode = 0;

	Control.Error.LWS_C_Error = 0;

	Control.Input_ch.Input_Alldata = 0;

	for(uint8_t i=0; i<3; i++)
	{
		Control.Output_ch.Output_Alldata[i] = 0;
	}

	Control.Float_Data.AI_ADC_In1_Ch2_Volt = 0;
	Control.Float_Data.AI_ADC_In1_Ch3_Volt = 0;
	Control.Float_Data.AI_ADC_In1_Ch4_Volt = 0;
	Control.Float_Data.AI_ADC_In2_Ch1_Volt = 0;
	Control.Float_Data.AI_ADC_In2_Ch2_Volt = 0;
	Control.Float_Data.AI_ADC_In2_Ch3_Volt = 0;
	Control.Float_Data.AI_ADC_In2_Ch4_Volt = 0;
	Control.Float_Data.Dac3_Ch0_Volt = 0;
	Control.Float_Data.Dac3_Ch1_Volt = 0;
	Control.Float_Data.Dac3_Ch2_Volt = 0;
	Control.Float_Data.Dac3_Ch3_Volt = 0;
	Control.Float_Data.Dac3_Ch4_Volt = 0;
	Control.Float_Data.Dac3_Ch5_Volt = 0;
	Control.Float_Data.Encoder_1 = 0;
	Control.Float_Data.Encoder_2 = 0;
	Control.Float_Data.WinchDrumHydMotorASpeed = 0;
	Control.Float_Data.WinchDrumHydMotorBSpeed = 0;
	Control.Float_Data.AlignHydMotorSpeed = 0;
	Control.Float_Data.Dac3_Ch0_Volt = 0;
	Control.Float_Data.Dac3_Ch1_Volt = 0;
	Control.Float_Data.Dac3_Ch2_Volt = 0;
	Control.Float_Data.Dac3_Ch3_Volt = 0;
	Control.Float_Data.Dac3_Ch4_Volt = 0;
	Control.Float_Data.Dac3_Ch5_Volt = 0;
	Control.Float_Data.Dac4_Ch2_Volt = 0;
	Control.Float_Data.Dac4_Ch3_Volt = 0;
	Control.Float_Data.Dac4_Ch4_Volt = 0;
	Control.Float_Data.Dac4_Ch5_Volt = 0;
	Control.Float_Data.Dac4_Ch6_Volt = 0;
	Control.Float_Data.Dac4_Ch7_Volt = 0;
	Control.Float_Data.Dac4_Ch8_Volt = 0;
	Control.Float_Data.Dac4_Ch9_Volt = 0;
	Control.Float_Data.Dac4_Ch10_Volt = 0;
	Control.Float_Data.Dac4_Ch11_Volt = 0;
	Control.Float_Data.Dac4_Ch12_Volt = 0;
	Control.Float_Data.Dac4_Ch13_Volt = 0;
	Control.Float_Data.Dac5_Ch0_Volt = 0;
	Control.Float_Data.Dac5_Ch1_Volt = 0;
	Control.Float_Data.Dac5_Ch2_Volt = 0;
	Control.Float_Data.Dac5_Ch3_Volt = 0;
	Control.Float_Data.Dac5_Ch4_Volt = 0;
	Control.Float_Data.Dac5_Ch5_Volt = 0;
	Control.Float_Data.Dac5_Ch6_Volt = 0;
	Control.Float_Data.Dac5_Ch7_Volt = 0;
	for(uint8_t i=0; i<10; i++)
	{
		Control.LWS_C_HILS[i] = 0;
	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_Routine(void)
{
	FUN_RS485_Rx_Data_Save();

	if(u1f_tim_100us_trg == 1)
	{
		u1f_tim_100us_trg = 0;
		FUN_Control_tim2_100us_routine();
	}

	if(u1f_tim_250us_trg == 1)
	{
		u1f_tim_250us_trg = 0;
		FUN_Control_tim2_250us_routine();
	}

	if(u1f_tim_500us_trg == 1)
	{
		u1f_tim_500us_trg = 0;
		FUN_Control_tim2_500us_routine();
	}

	if(u1f_tim_1ms_trg == 1)
	{
		u1f_tim_1ms_trg = 0;
		FUN_Control_tim2_1ms_routine();
	}

	if(u1f_tim_2ms_trg == 1)
	{
		u1f_tim_1ms_trg = 0;
		FUN_Control_tim2_2ms_routine();
	}

	if(u1f_tim_5ms_trg == 1)
	{
		u1f_tim_5ms_trg = 0;
		FUN_Control_tim2_5ms_routine();
	}

	if(u1f_tim_10ms_trg == 1)
	{
		u1f_tim_10ms_trg = 0;
		FUN_Control_tim2_10ms_routine();
	}

	if(u1f_tim_100ms_trg == 1)
	{
		u1f_tim_100ms_trg = 0;
		FUN_Control_tim2_100ms_routine();
	}

	if(u1f_tim_1000ms_trg == 1)
	{
		u1f_tim_1000ms_trg = 0;
		FUN_Control_tim2_1000ms_routine();
	}
}

/****************************************************************************/
/*	Overview	:	10kHz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_100us_routine(void)
{
	FUN_Encoder_Output_Set();
}

/****************************************************************************/
/*	Overview	:	4kHz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_250us_routine(void)
{
	FUN_HILS_Routine();
}

/****************************************************************************/
/*	Overview	:	2kHz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_500us_routine(void)
{
	FUN_GPI_PortCheck();		// Input Pin Status 확인
	FUN_GPO_PortCheck();		// Output Port Status 확인
	FUN_GPO_Routine();			// Output Port 출력
}

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
/****************************************************************************/
/*	Overview	:	1kHz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_1ms_routine(void)
{
	FUN_DAC_Routine();
}

/****************************************************************************/
/*	Overview	:	500Hz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_2ms_routine(void)
{
}

/****************************************************************************/
/*	Overview	:	200Hz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_5ms_routine(void)
{
	FUN_ADC_Routine();
}


/****************************************************************************/
/*	Overview	:	100Hz													*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_10ms_routine(void)
{
}


/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_100ms_routine(void)
{
	FUN_LED_Routine();
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Control_tim2_1000ms_routine(void)
{
	FUN_EEPROM_Routine();

//	FUN_HILS_Frequency_Ctrl();
}

/*
 * DAC.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "DAC.h"
#include "main.h"
#include "LTC2666.h"
#include "LTC2668.h"
#include "..\RS485\RS485.h"
#include "..\HILS\HILS.h"
#include "..\Control\Control.h"

/* Private variables ---------------------------------------------------------*/
_Dac Dac;
_Control Control;

/* Private function prototypes -----------------------------------------------*/
void DAC_Converter_4ma_Init(void);
static float sfun_DAC_Converter_gain_offset(float ft_data, float ft_gain, float ft_offset);

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_DAC_Init(void)
{
	FUN_DAC_SPI5_Init();		// mA
	FUN_DAC_SPI4_Init();		// mA
	FUN_DAC_SPI3_Init();		// V

	DAC_Converter_4ma_Init();
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_DAC_Routine(void)
{
	//HILS 출력
	if(HILS_START == FUN_RS485_Ctrl_hils_action_U1())
	{
		Control.Float_Data.Dac4_Ch5_Volt = (HILS.HILS_Output.HILS_AO_Float[0]);
		Control.Float_Data.Dac4_Ch4_Volt = (HILS.HILS_Output.HILS_AO_Float[1]);
		Control.Float_Data.Dac4_Ch3_Volt = (HILS.HILS_Output.HILS_AO_Float[2]);
		Control.Float_Data.Dac3_Ch1_Volt = (HILS.HILS_Output.HILS_AO_Float[3]);
		Control.Float_Data.Dac3_Ch0_Volt = (HILS.HILS_Output.HILS_AO_Float[6]);
		Control.Float_Data.Dac5_Ch3_Volt = (HILS.HILS_Output.HILS_AO_Float[10]);
		Control.Float_Data.Dac4_Ch7_Volt = (HILS.HILS_Output.HILS_AO_Float[11]);
		Control.Float_Data.Dac4_Ch6_Volt = (HILS.HILS_Output.HILS_AO_Float[12]);
		Control.Float_Data.Dac5_Ch5_Volt = (HILS.HILS_Output.HILS_AO_Float[13]);
		Control.Float_Data.Dac3_Ch2_Volt = (HILS.HILS_Output.HILS_AO_Float[14]);
		Control.Float_Data.Dac4_Ch9_Volt = (HILS.HILS_Output.HILS_AO_Float[15]);
		Control.Float_Data.Dac4_Ch8_Volt = (HILS.HILS_Output.HILS_AO_Float[16]);
		Control.Float_Data.Dac5_Ch0_Volt = (HILS.HILS_Output.HILS_AO_Float[17]);
		Control.Float_Data.Dac3_Ch3_Volt = (HILS.HILS_Output.HILS_AO_Float[18]);
		Control.Float_Data.Dac4_Ch11_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[19]);						// 투인양장치: 서보실린더1(팽창) 압력변환기
		Control.Float_Data.Dac4_Ch10_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[20]);						// 투인양장치: 서보실린더1(수축) 압력변환기
		Control.Float_Data.Dac5_Ch6_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[21]);						// 투인양장치: 서보실린더1 LVDT
		Control.Float_Data.Dac3_Ch4_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[22]);						// 투인양장치 서보실린더1: 비례제어밸브 에러신호
		Control.Float_Data.Dac4_Ch13_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[23]);						// 투인양장치: 서보실린더2(팽창) 압력변환기
		Control.Float_Data.Dac4_Ch12_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[24]);						// 투인양장치: 서보실린더2(수축) 압력변환기
		Control.Float_Data.Dac5_Ch1_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[25]);						// 투인양장치: 서보실린더2 LVDT
		Control.Float_Data.Dac3_Ch5_Volt	 =	(HILS.HILS_Output.HILS_AO_Float[26]);						// 투인양장치 서보실린더2: 비례제어밸브 에러신호

		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH5, Control.Float_Data.Dac4_Ch5_Volt);	// 동력공급장치: 압력변환기(윈치동력)
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH4, Control.Float_Data.Dac4_Ch4_Volt);	// 동력공급장치: 압력변환기(투인양동력)
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH3, Control.Float_Data.Dac4_Ch3_Volt);	// 동력공급장치: 유량계(투인양동력)
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH1, Control.Float_Data.Dac3_Ch1_Volt);	// 동력공급장치 비상구동: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH0, Control.Float_Data.Dac3_Ch0_Volt);	// 윈치조립체 권선구동 : 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH3, Control.Float_Data.Dac5_Ch3_Volt);	// 윈치조립체 : 장력센서
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH7, Control.Float_Data.Dac4_Ch7_Volt);	// 투인양장치: 실린더1(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH6, Control.Float_Data.Dac4_Ch6_Volt);	// 투인양장치: 실린더1(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH5, Control.Float_Data.Dac5_Ch5_Volt);	// 투인양장치: 메인실린더1 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH2, Control.Float_Data.Dac3_Ch2_Volt);	// 투인양장치 메인실린더1: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH9, Control.Float_Data.Dac4_Ch9_Volt);	// 투인양장치: 실린더2(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH8, Control.Float_Data.Dac4_Ch8_Volt);	// 투인양장치: 실린더2(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH0, Control.Float_Data.Dac5_Ch0_Volt);	// 투인양장치: 메인실린더2 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH3, Control.Float_Data.Dac3_Ch3_Volt);	// 투인양장치 메인실린더2: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH11, Control.Float_Data.Dac4_Ch11_Volt);		// 투인양장치: 서보실린더1(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH10, Control.Float_Data.Dac4_Ch10_Volt);		// 투인양장치: 서보실린더1(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH6, Control.Float_Data.Dac5_Ch6_Volt);		// 투인양장치: 서보실린더1 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH4, Control.Float_Data.Dac3_Ch4_Volt);		// 투인양장치 서보실린더1: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH13, Control.Float_Data.Dac4_Ch13_Volt);		// 투인양장치: 서보실린더2(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH12, Control.Float_Data.Dac4_Ch12_Volt);		// 투인양장치: 서보실린더2(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH1, Control.Float_Data.Dac5_Ch1_Volt);		// 투인양장치: 서보실린더2 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH5, Control.Float_Data.Dac3_Ch5_Volt);		// 투인양장치 서보실린더2: 비례제어밸브 에러신호

	// 강제 출력
	}
	else
	{
		Control.Float_Data.Dac4_Ch5_Volt	 =	RS485.HILS_UC_Output_Float[0];						// 동력공급장치: 압력변환기(윈치동력)
		Control.Float_Data.Dac4_Ch4_Volt	 =	RS485.HILS_UC_Output_Float[1];						// 동력공급장치: 압력변환기(투인양동력)
		Control.Float_Data.Dac4_Ch3_Volt	 =	RS485.HILS_UC_Output_Float[2];						// 동력공급장치: 유량계(투인양동력)
		Control.Float_Data.Dac3_Ch1_Volt	 =	RS485.HILS_UC_Output_Float[3];						// 동력공급장치 비상구동: 비례제어밸브 에러신호
		Control.Float_Data.Dac3_Ch0_Volt	 =	RS485.HILS_UC_Output_Float[6];						// 윈치조립체 권선구동 : 비례제어밸브 에러신호
		Control.Float_Data.Dac5_Ch3_Volt	 =	RS485.HILS_UC_Output_Float[10];						// 윈치조립체 : 장력센서
		Control.Float_Data.Dac4_Ch7_Volt	 =	RS485.HILS_UC_Output_Float[11];						// 투인양장치: 실린더1(팽창) 압력변환기
		Control.Float_Data.Dac4_Ch6_Volt	 =	RS485.HILS_UC_Output_Float[12];						// 투인양장치: 실린더1(수축) 압력변환기
		Control.Float_Data.Dac5_Ch5_Volt	 =	RS485.HILS_UC_Output_Float[13];						// 투인양장치: 메인실린더1 LVDT
		Control.Float_Data.Dac3_Ch2_Volt	 =	RS485.HILS_UC_Output_Float[14];						// 투인양장치 메인실린더1: 비례제어밸브 에러신호
		Control.Float_Data.Dac4_Ch9_Volt	 =	RS485.HILS_UC_Output_Float[15];						// 투인양장치: 실린더2(팽창) 압력변환기
		Control.Float_Data.Dac4_Ch8_Volt	 =	RS485.HILS_UC_Output_Float[16];						// 투인양장치: 실린더2(수축) 압력변환기
		Control.Float_Data.Dac5_Ch0_Volt	 =	RS485.HILS_UC_Output_Float[17];						// 투인양장치: 메인실린더2 LVDT
		Control.Float_Data.Dac3_Ch3_Volt	 =	RS485.HILS_UC_Output_Float[18];						// 투인양장치 메인실린더2: 비례제어밸브 에러신호
		Control.Float_Data.Dac4_Ch11_Volt	 =	RS485.HILS_UC_Output_Float[19];						// 투인양장치: 서보실린더1(팽창) 압력변환기
		Control.Float_Data.Dac4_Ch10_Volt	 =	RS485.HILS_UC_Output_Float[20];						// 투인양장치: 서보실린더1(수축) 압력변환기
		Control.Float_Data.Dac5_Ch6_Volt	 =	RS485.HILS_UC_Output_Float[21];						// 투인양장치: 서보실린더1 LVDT
		Control.Float_Data.Dac3_Ch4_Volt	 =	RS485.HILS_UC_Output_Float[22];						// 투인양장치 서보실린더1: 비례제어밸브 에러신호
		Control.Float_Data.Dac4_Ch13_Volt	 =	RS485.HILS_UC_Output_Float[23];						// 투인양장치: 서보실린더2(팽창) 압력변환기
		Control.Float_Data.Dac4_Ch12_Volt	 =	RS485.HILS_UC_Output_Float[24];						// 투인양장치: 서보실린더2(수축) 압력변환기
		Control.Float_Data.Dac5_Ch1_Volt	 =	RS485.HILS_UC_Output_Float[25];						// 투인양장치: 서보실린더2 LVDT
		Control.Float_Data.Dac3_Ch5_Volt	 =	RS485.HILS_UC_Output_Float[26];						// 투인양장치 서보실린더2: 비례제어밸브 에러신호

		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH5, Control.Float_Data.Dac4_Ch5_Volt);		// 동력공급장치: 압력변환기(윈치동력)
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH4, Control.Float_Data.Dac4_Ch4_Volt);		// 동력공급장치: 압력변환기(투인양동력)
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH3, Control.Float_Data.Dac4_Ch3_Volt);		// 동력공급장치: 유량계(투인양동력)
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH1, Control.Float_Data.Dac3_Ch1_Volt);		// 동력공급장치 비상구동: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH0, Control.Float_Data.Dac3_Ch0_Volt);		// 윈치조립체 권선구동 : 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH3, Control.Float_Data.Dac5_Ch3_Volt);		// 윈치조립체 : 장력센서
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH7, Control.Float_Data.Dac4_Ch7_Volt);		// 투인양장치: 실린더1(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH6, Control.Float_Data.Dac4_Ch6_Volt);		// 투인양장치: 실린더1(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH5, Control.Float_Data.Dac5_Ch5_Volt);		// 투인양장치: 메인실린더1 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH2, Control.Float_Data.Dac3_Ch2_Volt);		// 투인양장치 메인실린더1: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH9, Control.Float_Data.Dac4_Ch9_Volt);		// 투인양장치: 실린더2(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH8, Control.Float_Data.Dac4_Ch8_Volt);		// 투인양장치: 실린더2(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH0, Control.Float_Data.Dac5_Ch0_Volt);		// 투인양장치: 메인실린더2 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH3, Control.Float_Data.Dac3_Ch3_Volt);		// 투인양장치 메인실린더2: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH11, Control.Float_Data.Dac4_Ch11_Volt);		// 투인양장치: 서보실린더1(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH10, Control.Float_Data.Dac4_Ch10_Volt);		// 투인양장치: 서보실린더1(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH6, Control.Float_Data.Dac5_Ch6_Volt);		// 투인양장치: 서보실린더1 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH4, Control.Float_Data.Dac3_Ch4_Volt);		// 투인양장치 서보실린더1: 비례제어밸브 에러신호
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH13, Control.Float_Data.Dac4_Ch13_Volt);		// 투인양장치: 서보실린더2(팽창) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH12, Control.Float_Data.Dac4_Ch12_Volt);		// 투인양장치: 서보실린더2(수축) 압력변환기
		FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH1, Control.Float_Data.Dac5_Ch1_Volt);		// 투인양장치: 서보실린더2 LVDT
		FUN_DAC_Converter_set_dac_code(DAC3_CH_SEL, DAC3_CH5, Control.Float_Data.Dac3_Ch5_Volt);		// 투인양장치 서보실린더2: 비례제어밸브 에러신호
	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void DAC_Converter_4ma_Init(void)
{
	//SPI3,5 송신을 통해 초기 DAC값을 4mA로 설정
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH5, 	mA_4);		// 동력공급장치: 압력변환기(윈치동력)
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH4, 	mA_4);		// 동력공급장치: 압력변환기(투인양동력)
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH3, 	mA_4);		// 동력공급장치: 유량계(투인양동력)
	FUN_DAC_Converter_set_dac_code(SPI_5,		DAC5_CH3, 	mA_4);		// 윈치조립체 : 장력센서
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH7, 	mA_4);		// 투인양장치: 실린더1(팽창) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH6, 	mA_4);		// 투인양장치: 실린더1(수축) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_5,		DAC5_CH5, 	mA_4);		// 투인양장치: 메인실린더1
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH9, 	mA_4);		// 투인양장치: 실린더2(팽창) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH8, 	mA_4);		// 투인양장치: 실린더2(수축) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_5,		DAC5_CH0, 	mA_4);		// 투인양장치: 메인실린더2 LVDT
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH11,	mA_4);		// 투인양장치: 서보실린더1(팽창) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH10,	mA_4);		// 투인양장치: 서보실린더1(수축) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_5,		DAC5_CH6, 	mA_4);		// 투인양장치: 서보실린더1 LVDT
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH13,	mA_4);		// 투인양장치: 서보실린더2(팽창) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_4,		DAC4_CH12,	mA_4);		// 투인양장치: 서보실린더2(수축) 압력변환기
	FUN_DAC_Converter_set_dac_code(SPI_5,		DAC5_CH1, 	mA_4);		// 투인양장치: 서보실린더2 LVDT
}

// FAT기준 Gain, Offset 초기화 버젼
float Offset_DAC3[6] = {0, 0, 0, 0, 0, 0};
float Offset_DAC4[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float Offset_DAC5[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//float Gain_DAC3[6] = {1.29, 1.4, 1.38, 1.387, 1.387, 1.387};
float Gain_DAC4[14] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
float Gain_DAC5[8] = {5, 5, 5, 5, 5, 5, 5, 5};

// 현장 제어기 기준
float Gain_DAC3[6] = {1.29, 1.3, 1.3, 1.3, 1.3, 1.3};

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_DAC_Converter_set_dac_code(uint8_t SPI_Select, uint8_t u1t_dac_address, float ft_dac_volt)
{
	float ft_dummy = 0;
	float ft_convert_val = 0;

	if(SPI_Select == SPI_3)
	{
//		ft_dummy = (ft_dac_volt / 13) * 10;
		ft_dummy = ft_dac_volt;

		// 윈치조립체 권선구동 : 비례제어밸브 에러신호
		if(u1t_dac_address == DAC3_CH0)
		{
			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, Offset_DAC3[0], Gain_DAC3[0]);

		}
		// 윈치조립체 비상구동 : 비례제어밸브 에러신호
		else if(u1t_dac_address == DAC3_CH1)
		{
			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, Offset_DAC3[1], Gain_DAC3[1]);

		}
		// 투인양장치 메인실린더1 : 비례제어밸브 에러신호
		else if(u1t_dac_address == DAC3_CH2)
		{

			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, Offset_DAC3[2], Gain_DAC3[2]);

		}
		// 투인양장치 메인실린더2 : 비례제어밸브 에러신호
		else if(u1t_dac_address == DAC3_CH3)
		{
			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, Offset_DAC3[3], Gain_DAC3[3]);

		}
		// 투인양장치 서보실린더1 : 비례제어밸브 에러신호
		else if(u1t_dac_address == DAC3_CH4)
		{
			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, Offset_DAC3[4], Gain_DAC3[4]);

		}
		// 투인양장치 서보실린더2 : 비례제어밸브 에러신호
		else if(u1t_dac_address == DAC3_CH5)
		{
			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, Offset_DAC3[5], Gain_DAC3[5]);

		}
		// SPARE
		else
		{
			ft_convert_val = ((ft_dac_volt / 13) * 10);	// 0 ~ 13V => 0 ~ 10V
		}
		FUN_DAC_LTC2666_Get_Dac_Code(SPI_3, u1t_dac_address, ft_convert_val);
	}

	else if(SPI_Select == SPI_4)
	{
		if(u1t_dac_address == DAC4_CH0)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[0], Gain_DAC4[0]);
		}
		else if(u1t_dac_address == DAC4_CH1)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[1], Gain_DAC4[1]);
		}
		// 동력공급장치 : 온도센서(저유기조립체)
		else if(u1t_dac_address == DAC4_CH2)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[2], Gain_DAC4[2]);
		// 동력공급장치 : 유량계(투인양동력
		}
		else if(u1t_dac_address == DAC4_CH3)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[3], Gain_DAC4[3]);
		// 동력공급장치 : 압력변환기(투인양동력)
		}
		else if(u1t_dac_address == DAC4_CH4)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[4], Gain_DAC4[4]);
		// 동력공급장치 : 압력변환기(윈치동력)
		}
		else if(u1t_dac_address == DAC4_CH5)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[5], Gain_DAC4[5]);
		// 투인양장치 : 실린더1(수축) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH6)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[6], Gain_DAC4[6]);
		// 투인양장치 : 실린더1(팽창) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH7)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[7], Gain_DAC4[7]);
		// 투인양장치 : 실린더2(수축) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH8)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[8], Gain_DAC4[8]);
		// 투인양장치 : 실린더2(팽창) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH9)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[9], Gain_DAC4[9]);
		// 투인양장치 : 서보실린더1(수축) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH10)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[10], Gain_DAC4[10]);
		// 투인양장치 : 서보실린더1(팽창) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH11)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[11], Gain_DAC4[11]);
		// 투인양장치 : 서보실린더2(수축) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH12)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[12], Gain_DAC4[12]);
		// 투인양장치 : 서보실린더2(팽창) 압력변환기
		}
		else if(u1t_dac_address == DAC4_CH13)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC4[13], Gain_DAC4[13]);
		// 제외
		}
		else;

		ft_convert_val = -ft_dummy;

		FUN_DAC_LTC2668_Get_Dac_Code(SPI_4, u1t_dac_address, ft_convert_val);
	}
	else if(SPI_Select == SPI_5)
	{
		// 장력 센서
		if(u1t_dac_address == DAC5_CH3)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[3], Gain_DAC5[3]);
		// 메인 실린더1 LVDT
		}
		else if(u1t_dac_address == DAC5_CH5)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[5], Gain_DAC5[5]);
		// 메인 실린더2 LVDT
		}
		else if(u1t_dac_address == DAC5_CH0)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[0], Gain_DAC5[0]);
		// 서보 실린더1 LVDT
		}
		else if(u1t_dac_address == DAC5_CH6)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[6], Gain_DAC5[6]);
		// 서보 실린더2 LVDT
		}
		else if(u1t_dac_address == DAC5_CH1)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[1], Gain_DAC5[1]);
		// 그립퍼1 LVDT
		}
		else if(u1t_dac_address == DAC5_CH7)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[7], Gain_DAC5[7]);
		// 그립퍼2 LVDT
		}
		else if(u1t_dac_address == DAC5_CH2)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[2], Gain_DAC5[2]);
		// 그립퍼3 LVDT
		}
		else if(u1t_dac_address == DAC5_CH4)
		{
			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset_DAC5[4], Gain_DAC5[4]);
		// 제외
		}
		else;

		// 전류 부호 변환 :(-V -> +mA)로 출력
		ft_convert_val = -ft_dummy;

		FUN_DAC_LTC2666_Get_Dac_Code(SPI_5, u1t_dac_address, ft_convert_val);
	} else ;
}

//// 기존 버젼
///****************************************************************************/
///*	Overview	:															*/
///*	Return value:	void													*/
///****************************************************************************/
//void FUN_DAC_Converter_set_dac_code(uint8_t SPI_Select, uint8_t u1t_dac_address, float ft_dac_volt)
//{
//	float ft_dummy = 0;
//	float ft_convert_val = 0;
//
//	if(SPI_Select == SPI_3)
//	{
//		ft_dummy = (ft_dac_volt / 13) * 10;
//
//		// 윈치조립체 권선구동 : 비례제어밸브 에러신호
//		if(u1t_dac_address == DAC3_CH0)
//		{
////			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, 0.021, 0.987);
//			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, -0.009, 1);
//		// 윈치조립체 비상구동 : 비례제어밸브 에러신호
//		}
//		else if(u1t_dac_address == DAC3_CH1)
//		{
////			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, 0.01, 0.9735);
//			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, -0.016, 1);
//		// 투인양장치 메인실린더1 : 비례제어밸브 에러신호
//		}
//		else if(u1t_dac_address == DAC3_CH2)
//		{
////			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, (-0.020), 0.9985);
//			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, 0.027, 1);
//		// 투인양장치 메인실린더2 : 비례제어밸브 에러신호
//		}
//		else if(u1t_dac_address == DAC3_CH3)
//		{
////			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, (-0.004), 0.994);
//			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, 0.014, 1);
//		// 투인양장치 서보실린더1 : 비례제어밸브 에러신호
//		}
//		else if(u1t_dac_address == DAC3_CH4)
//		{
////			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, 0.020, 0.966);
//			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, 0.001, 1);
//		// 투인양장치 서보실린더2 : 비례제어밸브 에러신호
//		}
//		else if(u1t_dac_address == DAC3_CH5)
//		{
////			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, (-0.004), 0.97484);
//			ft_convert_val = sfun_DAC_Converter_gain_offset(ft_dummy, -0.021, 1);
//		// SPARE
//		}
//		else
//		{
//			ft_convert_val = ((ft_dac_volt / 13) * 10);	// 0 ~ 13V => 0 ~ 10V
//		}
//		FUN_DAC_LTC2666_Get_Dac_Code(SPI_3, u1t_dac_address, ft_convert_val);
//	}
//
//	else if(SPI_Select == SPI_4)
//	{
//		if(u1t_dac_address == DAC4_CH0)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, 0, 4.86);
//		}
//		else if(u1t_dac_address == DAC4_CH1)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, 0, 4.86);
//		}
//		// 동력공급장치 : 온도센서(저유기조립체)
//		else if(u1t_dac_address == DAC4_CH2)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.01), 4.86);
//		// 동력공급장치 : 유량계(투인양동력
//		}
//		else if(u1t_dac_address == DAC4_CH3)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.04), 4.935);
//		// 동력공급장치 : 압력변환기(투인양동력)
//		}
//		else if(u1t_dac_address == DAC4_CH4)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.04), 4.93);
//		// 동력공급장치 : 압력변환기(윈치동력)
//		}
//		else if(u1t_dac_address == DAC4_CH5)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.04), 4.94);
//		// 투인양장치 : 실린더1(수축) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH6)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.008), 4.955);
//		// 투인양장치 : 실린더1(팽창) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH7)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.90);
//		// 투인양장치 : 실린더2(수축) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH8)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.00), 4.98);
//		// 투인양장치 : 실린더2(팽창) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH9)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, Offset, 4.933);
//		// 투인양장치 : 서보실린더1(수축) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH10)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.99);
//		// 투인양장치 : 서보실린더1(팽창) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH11)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.004), 4.94);
//		// 투인양장치 : 서보실린더2(수축) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH12)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.91);
//		// 투인양장치 : 서보실린더2(팽창) 압력변환기
//		}
//		else if(u1t_dac_address == DAC4_CH13)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.02), 4.91);
//		// 제외
//		}
//		else;
//
//		ft_convert_val = -ft_dummy;
//
//		FUN_DAC_LTC2668_Get_Dac_Code(SPI_4, u1t_dac_address, ft_convert_val);
//	}
//	else if(SPI_Select == SPI_5)
//	{
//		// 장력 센서
//		if(u1t_dac_address == DAC5_CH3)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-(0.006 * 4.91)), 4.91);
//		// 메인 실린더1 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH5)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.957);
//		// 메인 실린더2 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH0)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (-0.01), 4.95);
//		// 서보 실린더1 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH6)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.01), 4.98);
//		// 서보 실린더2 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH1)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.92);
//		// 그립퍼1 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH7)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.94);
//		// 그립퍼2 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH2)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.02), 4.94);
//		// 그립퍼3 LVDT
//		}
//		else if(u1t_dac_address == DAC5_CH4)
//		{
//			ft_dummy = sfun_DAC_Converter_gain_offset(ft_dac_volt, (0.00), 4.975);
//		// 제외
//		}
//		else;
//
//		// 전류 부호 변환 :(-V -> +mA)로 출력
//		ft_convert_val = -ft_dummy;
//
//		FUN_DAC_LTC2666_Get_Dac_Code(SPI_5, u1t_dac_address, ft_convert_val);
//	} else ;
//}

/****************************************************************************/
/*	Overview	:	각 출력별 DAC Gain 조절										*/
/*	Return value:	void													*/
/****************************************************************************/
static float sfun_DAC_Converter_gain_offset(float ft_data, float ft_offset, float ft_gain)
{
	float ft_val = 0;
	ft_val = (ft_data + ft_offset) / ft_gain;	// 0 ~ 13V => 0 ~ 10V

	return ft_val;
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_DAC_Converter_Gripper(void)
{
	Control.Float_Data.Dac5_Ch7_Volt = RS485.Gripper_Output_Float[0];				// 투인양장치: 그립퍼 LVDT1
	Control.Float_Data.Dac5_Ch2_Volt = RS485.Gripper_Output_Float[1];				// 투인양장치: 그립퍼 LVDT2
	Control.Float_Data.Dac5_Ch4_Volt = RS485.Gripper_Output_Float[2];				// 투인양장치: 그립퍼 LVDT3

	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH7, Control.Float_Data.Dac5_Ch7_Volt);
	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH2, Control.Float_Data.Dac5_Ch2_Volt);
	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH4, Control.Float_Data.Dac5_Ch4_Volt);
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_DAC_Converter_Oil(void)
{
	Control.Float_Data.Dac4_Ch2_Volt = RS485.Oil_Output_Float;						// 동력공급장치: 온도센서(저유기조립체)

	FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH2, Control.Float_Data.Dac4_Ch2_Volt);
}

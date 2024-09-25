/*
 * ADC.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "ADC.h"
#include "..\Control\Control.h"
#include "main.h"

/* Private variables ---------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc2;
uint8_t Check_A;
_Adc Adc;

/*-------Prototype Declaration----------------------------------------------*/
void FUN_ADC_Parameter_Reset(void);
float FUN_ADC_VoltageConvert(uint8_t Adc_Select_cnt, uint8_t Adc_Channel_cnt);
void FUN_ADC_ChannelSelect(uint8_t Adc_Select_cnt, uint8_t Adc_Channel_cnt);
void FUN_ADC_Average_Calculator(float Adc_Voltage, uint8_t Adc_Channel_cnt);

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_Init(void)
{
	//ADC Parameter Reset
	FUN_ADC_Parameter_Reset();
	//시작시 ADC채널 1번으로 초기화
	ADC1_SEL0_M_LOW();
	ADC1_SEL1_M_LOW();
	ADC1_SEL2_M_LOW();
	ADC2_SEL0_M_LOW();
	ADC2_SEL1_M_LOW();
	ADC2_SEL2_M_LOW();
}

/****************************************************************************/
/*	Overview	:	ADC Parameter Reset										*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_Parameter_Reset(void)
{
	Adc.ADC_Channel = 0;
	Adc.Mux_Flag = 0;
	Adc.Adc1_ChannelSelect_Error_flag = 0;
	Adc.Adc2_ChannelSelect_Error_flag = 0;
	for(uint8_t i = 0; i < 8; i++)
	{
		Adc.Adc_Voltage_CntBuffer[i] = 0;
		Adc.Adc_Voltage_SumBuffer[i] = 0;
		Adc.Adc_Voltage_AvgBuffer[i] = 0;
	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_Routine(void)
{
	// 변환된 Voltage값 저장용
	float ADC_Dummy_1 = 0;

	if(Adc.Mux_Flag == 0)
	{
		switch(Adc.ADC_Channel)
		{
			case ADC_CH_SELECT_1:
				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_1);
				break;
			case ADC_CH_SELECT_2:
				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_2);
				break;
			case ADC_CH_SELECT_3:
				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_3);
				break;
			case ADC_CH_SELECT_4:
				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_4);
				break;
			case ADC_CH_SELECT_5:
				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_5);
				break;
			case ADC_CH_SELECT_6:
				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_6);
				break;
			case ADC_CH_SELECT_7:
				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_7);
				break;
			case ADC_CH_SELECT_8:
				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_8);
				break;
		}
		Adc.Mux_Flag = 1;
	}
	else if(Adc.Mux_Flag == 1)
	{
		// 루틴마다 채널을 순환하며 ADC Average Voltage 값을 저장함
		// ADC Average Voltage 값은 exturn 된다.
		switch(Adc.ADC_Channel)
		{
			case ADC_CH_SELECT_1:
//				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_1);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC1_ON, ADC_CH_SELECT_1);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_1);
				Control.Float_Data.AI_ADC_In1_Ch1_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_1];
				break;
			case ADC_CH_SELECT_2:
//				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_2);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC1_ON, ADC_CH_SELECT_2);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_2);
				Control.Float_Data.AI_ADC_In1_Ch2_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_2];
				break;
			case ADC_CH_SELECT_3:
//				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_3);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC1_ON, ADC_CH_SELECT_3);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_3);
				Control.Float_Data.AI_ADC_In1_Ch3_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_3];
				break;
			case ADC_CH_SELECT_4:
//				FUN_ADC_ChannelSelect(ADC1_ON,ADC_CH_SELECT_4);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC1_ON, ADC_CH_SELECT_4);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_4);
				Control.Float_Data.AI_ADC_In1_Ch4_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_4];
				break;
			case ADC_CH_SELECT_5:
//				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_5);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC2_ON, ADC_CH_SELECT_5);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_5);
				Control.Float_Data.AI_ADC_In2_Ch1_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_5];
				break;
			case ADC_CH_SELECT_6:
//				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_6);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC2_ON, ADC_CH_SELECT_6);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_6);
				Control.Float_Data.AI_ADC_In2_Ch2_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_6];
				break;
			case ADC_CH_SELECT_7:
//				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_7);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC2_ON, ADC_CH_SELECT_7);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_7);
				Control.Float_Data.AI_ADC_In2_Ch3_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_7];
				break;
			case ADC_CH_SELECT_8:
//				FUN_ADC_ChannelSelect(ADC2_ON,ADC_CH_SELECT_8);
				ADC_Dummy_1 = FUN_ADC_VoltageConvert(ADC2_ON, ADC_CH_SELECT_8);
				FUN_ADC_Average_Calculator(ADC_Dummy_1, ADC_CH_SELECT_8);
				Control.Float_Data.AI_ADC_In2_Ch4_Volt = Adc.Adc_Voltage_AvgBuffer[ADC_CH_SELECT_8];
				break;
			default :
				Adc.ADC_Channel = 0;
				break;
		}

		//ADC 채널 1~7 순환
		Adc.ADC_Channel++;

		//ADC 채널 8부터 1로 초기화
		if(Adc.ADC_Channel >= 8)
		{
			Adc.ADC_Channel = 0;
		}

		Adc.Mux_Flag = 0;
	}


}
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
// ADC Select sheet
// ------------------------------------//
//	│	A2	│	A1	│	A0	│	CH	│  //
//	│	0	│	0	│	0	│	1	│  //
//	│	0	│	0	│	1	│	2	│  //
//	│	0	│	1	│	0	│	3	│  //
//	│	0	│	1	│	1	│	4	│  //
//	│	1	│	0	│	0	│	5	│  //
//	│	1	│	0	│	1	│	6	│  //
//	│	1	│	1	│	0	│	7	│  //
//	│	1	│	1	│	1	│	8	│  //
// ------------------------------------//
void FUN_ADC_ChannelSelect(uint8_t Adc_Select_cnt, uint8_t Adc_Channel_cnt)
{
	if(Adc_Select_cnt == ADC1_ON)
	{
		switch(Adc_Channel_cnt)
		{
			case 0:
				// 채널 1 Set, 동력공급장치 윈치구동: 비례제어밸브
				ADC1_SEL0_M_LOW();
				ADC1_SEL1_M_LOW();
				ADC1_SEL2_M_LOW();
				break;
			case 1:
				// 채널 2 Set, 윈치조립체 비상구동 : 비례제어밸브
				ADC1_SEL0_M_HIGH();
				ADC1_SEL1_M_LOW();
				ADC1_SEL2_M_LOW();
				break;
			case 2:
				// 채널 3 Set, 윈치조립체 권성구동 : 비례제어밸브
				ADC1_SEL0_M_LOW();
				ADC1_SEL1_M_HIGH();
				ADC1_SEL2_M_LOW();
				break;
			case 3:
				// 채널 4 Set, Spare
				ADC1_SEL0_M_HIGH();
				ADC1_SEL1_M_HIGH();
				ADC1_SEL2_M_LOW();
				break;
			default :
				Adc.Adc1_ChannelSelect_Error_flag = 1;
				break;
		}
	}
	else if(Adc_Select_cnt == ADC2_ON)
	{
		switch(Adc_Channel_cnt)
		{
			case 4:
				// 채널 4 Set, 투인양장치 서보실린더1 : 비례제어밸브
				ADC2_SEL0_M_LOW();
				ADC2_SEL1_M_LOW();
				ADC2_SEL2_M_LOW();
				break;
			case 5:
				// 채널 5 Set, 투인양장치 서보실린더2 : 비례제어밸브
				ADC2_SEL0_M_HIGH();
				ADC2_SEL1_M_LOW();
				ADC2_SEL2_M_LOW();
				break;
			case 6:
				// 채널 6 Set, 투인양장치 메인실린더1 : 비례제어밸브
				ADC2_SEL0_M_LOW();
				ADC2_SEL1_M_HIGH();
				ADC2_SEL2_M_LOW();
				break;
			case 7:
				// 채널 7 Set, 투인양장치 메인실린더2 : 비례제어밸브
				ADC2_SEL0_M_HIGH();
				ADC2_SEL1_M_HIGH();
				ADC2_SEL2_M_LOW();
				break;
			default :
				Adc.Adc2_ChannelSelect_Error_flag = 1;
				break;
		}
	}
}

//// Gain, Offset FAT 버젼
//float Gain_ADC_P[8] = {0.945, 0.945, 0.945, 1, 0.945, 0.945, 0.945, 0.945};
//float Gain_ADC_N[8] = {1, 1, 1.005, 1, 0.978, 0.978,  0.99, 0.987};
//float Offset_ADC[8] = {0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4};

// 공장에서 재측정
float Gain_ADC_P[8] = {1, 1, 1, 1, 1, 1, 1, 1};
float Gain_ADC_N[8] = {1, 1, 1, 1, 1, 1, 1, 1};
float Offset_ADC[8] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	float													*/
/****************************************************************************/
float FUN_ADC_VoltageConvert(uint8_t Adc_Select_cnt, uint8_t Adc_Channel_cnt)
{
	uint32_t Adc_dummy_1 = 0;		// ADC 값 저장
	float Adc_dummy_2 = 0;			// 저장 값 변환
	float Adc_Voltage = 0;			// 변환된 전압의 조정값

	if(Adc_Select_cnt == ADC1_ON)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 10);
		Adc_dummy_1 = HAL_ADC_GetValue(&hadc1);
	}
	else if(Adc_Select_cnt == ADC2_ON)
	{
		HAL_ADC_Start(&hadc2);
		HAL_ADC_PollForConversion(&hadc2, 10);
		Adc_dummy_1 = HAL_ADC_GetValue(&hadc2);
	}

	Adc_dummy_2 = (((float) Adc_dummy_1 / 4095) * (20)) - 10;	// -10 ~ 10V

	switch(Adc_Channel_cnt)
	{
		case 0:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[0];
			if(Adc_dummy_2 > 0)
			{
				// 채널 1 Set, 동력공급장치 윈치구동: 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[0];
			}
			else
			{
				// 채널 1 Set, 동력공급장치 윈치구동: 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[0];
			}

			break;
		case 1:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[1];
			if(Adc_dummy_2 > 0)
			{
				// 채널 2 Set, 윈치조립체 비상구동 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[1];
			}
			else
			{
				// 채널 2 Set, 윈치조립체 비상구동 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[1];
			}
			break;
		case 2:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[2];
			if(Adc_dummy_2 > 0)
			{
				// 채널 3 Set, 윈치조립체 권성구동 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[2];
			}
			else
			{
				// 채널 3 Set, 윈치조립체 권성구동 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[2];
			}
			break;
		case 3:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[3];
			if(Adc_dummy_2 > 0)
			{
				// 채널 4 Set, Spare
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[3];
			}
			else
			{
				// 채널 4 Set, Spare
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[3];
			}
			break;
		case 4:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[4];
			if(Adc_dummy_2 > 0)
			{
				// 채널 5 Set, 투인양장치 서보실린더1 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[4];
			}
			else
			{
				// 채널 5 Set, 투인양장치 서보실린더1 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[4];
			}
			break;
		case 5:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[5];
			if(Adc_dummy_2 > 0)
			{
				// 채널 6 Set, 투인양장치 서보실린더2 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[5];
			}
			else
			{
				// 채널 6 Set, 투인양장치 서보실린더2 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[5];
			}
			break;
		case 6:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[6];
			if(Adc_dummy_2 > 0)
			{
				// 채널 7 Set, 투인양장치 메인실린더1 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[6];
			}
			else
			{
				// 채널 7 Set, 투인양장치 메인실린더1 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[6];
			}
			break;
		case 7:
			Adc_dummy_2 = Adc_dummy_2 - Offset_ADC[7];
			if(Adc_dummy_2 > 0)
			{
				// 채널 8 Set, 투인양장치 메인실린더2 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_P[7];
			}
			else
			{
				// 채널 8 Set, 투인양장치 메인실린더2 : 비례제어밸브
				Adc_Voltage = Adc_dummy_2 / Gain_ADC_N[7];
			}
			break;
		default :
			break;
	}

	if(Adc_Select_cnt == ADC1_ON)
	{
		HAL_ADC_Stop(&hadc1);
	}
	else if(Adc_Select_cnt == ADC2_ON)
	{
		HAL_ADC_Stop(&hadc2);
	}

	return Adc_Voltage;
}

//// 기존 코드
///****************************************************************************/
///*	Overview	:															*/
///*	Return value:	float													*/
///****************************************************************************/
//float FUN_ADC_VoltageConvert(uint8_t Adc_Select_cnt, uint8_t Adc_Channel_cnt)
//{
//	uint32_t Adc_dummy_1 = 0;		// ADC 값 저장
//	float Adc_dummy_2 = 0;			// 저장 값 변환
//	float Adc_Voltage = 0;			// 변환된 전압의 조정값
//
//	if(Adc_Select_cnt == ADC1_ON)
//	{
//		HAL_ADC_Start(&hadc1);
//		HAL_ADC_PollForConversion(&hadc1, 10);
//		Adc_dummy_1 = HAL_ADC_GetValue(&hadc1);
//	}
//	else if(Adc_Select_cnt == ADC2_ON)
//	{
//		HAL_ADC_Start(&hadc2);
//		HAL_ADC_PollForConversion(&hadc2, 10);
//		Adc_dummy_1 = HAL_ADC_GetValue(&hadc2);
//	}
//
//	Adc_dummy_2 = (((float) Adc_dummy_1 / 4095) * (20)) - 10;	// -10 ~ 10V
//
//	switch(Adc_Channel_cnt)
//	{
//		case 0:
//			// 채널 1 Set, 동력공급장치 윈치구동: 비례제어밸브
//			Adc_Voltage = (Adc_dummy_2 - 1.00) / 0.8249;
//			break;
//		case 1:
//			// 채널 2 Set, 윈치조립체 비상구동 : 비례제어밸브
//			Adc_Voltage = (-Adc_dummy_2 + 0.93) / 0.825;
//			break;
//		case 2:
//			// 채널 3 Set, 윈치조립체 권성구동 : 비례제어밸브
//			Adc_Voltage = (Adc_dummy_2 - 1.00) / 0.8249;
//			break;
//		case 3:
//			// 채널 4 Set, Spare
//			Adc_Voltage = -Adc_dummy_2;
//			break;
//		case 4:
//			// 채널 4 Set, 투인양장치 서보실린더1 : 비례제어밸브
//			Adc_Voltage = (Adc_dummy_2 - 1.065) / 0.820;
//			break;
//		case 5:
//			// 채널 5 Set, 투인양장치 서보실린더2 : 비례제어밸브
//			Adc_Voltage = (Adc_dummy_2 - 1.065) / 0.820;
//			break;
//		case 6:
//			// 채널 6 Set, 투인양장치 메인실린더1 : 비례제어밸브
//			Adc_Voltage = (Adc_dummy_2 - 1.04) / 0.820;
//			break;
//		case 7:
//			// 채널 7 Set, 투인양장치 메인실린더2 : 비례제어밸브
//			Adc_Voltage = (Adc_dummy_2 - 1.065) / 0.820;
//			break;
//		default :
//			break;
//	}
//
//	if(Adc_Select_cnt == ADC1_ON)
//	{
//		HAL_ADC_Stop(&hadc1);
//	}
//	else if(Adc_Select_cnt == ADC2_ON)
//	{
//		HAL_ADC_Stop(&hadc2);
//	}
//
//	return Adc_Voltage;
//}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_Average_Calculator(float Adc_Voltage, uint8_t Adc_Channel_cnt)
{
	// Adc_Channel_cnt => 1~7 채널
	// 2000회 누적 시 리셋 후 다시 평균 값 계산
	if(Adc.Adc_Voltage_CntBuffer[Adc_Channel_cnt] >= 10)
	{
		Adc.Adc_Voltage_CntBuffer[Adc_Channel_cnt] = 0;
		Adc.Adc_Voltage_SumBuffer[Adc_Channel_cnt] = 0;
		Adc.Adc_Voltage_AvgBuffer[Adc_Channel_cnt] = 0;
	}

	Adc.Adc_Voltage_CntBuffer[Adc_Channel_cnt] += 1;

	Adc.Adc_Voltage_SumBuffer[Adc_Channel_cnt] += Adc_Voltage;

	Adc.Adc_Voltage_AvgBuffer[Adc_Channel_cnt] = Adc.Adc_Voltage_SumBuffer[Adc_Channel_cnt] / Adc.Adc_Voltage_CntBuffer[Adc_Channel_cnt];
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_ADC_AvgValueReset(void)
{
	for(uint8_t Adc_AvgReset_i = 0; Adc_AvgReset_i < 8; Adc_AvgReset_i++)
	{
		Adc.Adc_Voltage_CntBuffer[Adc_AvgReset_i] = 0;
		Adc.Adc_Voltage_SumBuffer[Adc_AvgReset_i] = 0;
		Adc.Adc_Voltage_AvgBuffer[Adc_AvgReset_i] = 0;
	}
}


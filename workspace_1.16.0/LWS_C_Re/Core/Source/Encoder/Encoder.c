/*
 * Encoder.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "Encoder.h"
#include "math.h"
#include "main.h"
#include "..\RS485\RS485.h"
#include "..\HILS\HILS.h"
#include "..\Control\Control.h"

/* Private variables ---------------------------------------------------------*/
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
_Encoder Encoder;

/* Private function prototypes -----------------------------------------------*/

/****************************************************************************/
/*	Overview	:	SPI1, 2 DMA Enable Setting								*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Encoder_Init(void)
{
	// 초기화
	Encoder.SPI1_Tx_Cplt_Flag = 0;
	Encoder.SPI1_Tx_Cplt_Cnt = 0;
	Encoder.SPI2_Tx_Cplt_Flag = 0;
	Encoder.SPI2_Tx_Cplt_Cnt = 0;
	Encoder.Encoder_1_Output_Value = 0;
	Encoder.Encoder_2_Output_Value = 0;
	for(uint8_t i =0; i<2; i++)
	{
		Encoder.SPI1_Tx_Buffer[i] = 0;
		Encoder.SPI2_Tx_Buffer[i] = 0;
	}

	HAL_SPI_Transmit_DMA(&hspi1, Encoder.SPI2_Tx_Buffer, 1);			// 16Bit * 1
	HAL_SPI_Transmit_DMA(&hspi2, Encoder.SPI1_Tx_Buffer, 1);			// 16Bit * 1
}

/****************************************************************************/
/*	Overview	:	SPI1, 2 Enable Routine									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Encoder_Routine(void)
{
	if(Encoder.SPI1_Tx_Cplt_Flag == 1)
	{
		++Encoder.SPI1_Tx_Cplt_Cnt;

		if(Encoder.SPI1_Tx_Cplt_Cnt == 3)
		{
			Encoder.SPI1_Tx_Cplt_Cnt = 0;

		Encoder.SPI1_Tx_Cplt_Flag = 0;

		__HAL_SPI_ENABLE(&hspi1);
		}
	}

	if(Encoder.SPI2_Tx_Cplt_Flag == 1)
	{
		++Encoder.SPI2_Tx_Cplt_Cnt;

		if(Encoder.SPI2_Tx_Cplt_Cnt == 3)
		{
			Encoder.SPI2_Tx_Cplt_Cnt = 0;

			Encoder.SPI2_Tx_Cplt_Flag = 0;

			__HAL_SPI_ENABLE(&hspi2);
		}
	}
}

// 100us 주기
/****************************************************************************/
/*	Overview	:	OutputBuffer Set In Control								*/
/*	Return value:	Void													*/
/****************************************************************************/
void FUN_Encoder_Output_Set(void)
{
	if(HILS_START == FUN_RS485_Ctrl_hils_action_U1())
	{
		Control.Float_Data.Encoder_1 = HILS.HILS_Output.HILS_AO_Float[4];	// 윈치드럼 각도(엔코더 01)
		Control.Float_Data.Encoder_2 = HILS.HILS_Output.HILS_AO_Float[5];	// 권선정렬 각도(엔코더 02)

		FUN_Encoder_OutputBuffer_Set(EncoderSelect_1, Control.Float_Data.Encoder_1); 	// 윈치드럼 각도(엔코더 01)
		FUN_Encoder_OutputBuffer_Set(EncoderSelect_2, Control.Float_Data.Encoder_2); 	// 권선정렬 각도(엔코더 02)
	}
	else	//강제출력
	{
		Control.Float_Data.Encoder_1 = RS485.HILS_UC_Output_Float[4];	// 윈치드럼 각도(엔코더 01)
		Control.Float_Data.Encoder_2 = RS485.HILS_UC_Output_Float[5];	// 권선정렬 각도(엔코더 02)

		FUN_Encoder_OutputBuffer_Set(EncoderSelect_1, Control.Float_Data.Encoder_1); 	// 윈치드럼 각도(엔코더 01)
		FUN_Encoder_OutputBuffer_Set(EncoderSelect_2, Control.Float_Data.Encoder_2); 	// 권선정렬 각도(엔코더 02)
	}
}

/****************************************************************************/
/*	Overview	:	Control, SPI1, 2 Buffer에 Data 저장						*/
/*	Return value:	Void													*/
/****************************************************************************/
void FUN_Encoder_OutputBuffer_Set(uint8_t Encoder_Select, float Encoder_Value)
{
	Encoder_Value = 360 - Encoder_Value;

	switch(Encoder_Select)
	{
		case EncoderSelect_1:
			Encoder.Encoder_1_Output_Value = Encoder_Value;
			Encoder_Degree_To_Data(EncoderSelect_1);
			break;
		case EncoderSelect_2:
			Encoder.Encoder_2_Output_Value = Encoder_Value;
			Encoder_Degree_To_Data(EncoderSelect_2);
			break;
	}
}

/****************************************************************************/
/*	Overview	:	Encoder SPI Buffer Set									*/
/*	Return value:	Void													*/
/****************************************************************************/
void Encoder_Degree_To_Data(uint8_t Encoder_Select)
{
	float Encoder_Float_Dummy = 0;
	double Encoder_Double_Dummy = 0;
	uint16_t Encoder_Buffer = 0;

	switch(Encoder_Select)
	{
		case EncoderSelect_1:
			Encoder_Float_Dummy = Encoder.Encoder_1_Output_Value * 0x7FFF / 360;		// degree -> data
			break;
		case EncoderSelect_2:
			Encoder_Float_Dummy = Encoder.Encoder_2_Output_Value * 0x7FFF / 360;		// degree -> data
			break;
	}

	Encoder_Double_Dummy = (double)Encoder_Float_Dummy;							//

	Encoder_Double_Dummy = floor(Encoder_Double_Dummy + 0.5);								// 소수점 자리 반올림

	Encoder_Float_Dummy = (float)Encoder_Double_Dummy;							// degree 값 반환 (형 변환)

	Encoder_Buffer = (uint16_t)Encoder_Float_Dummy;				// data (float) -> uint32_t

	/*	16-bit write access to data register at TxE event:
	*	SPI_DR= 0x40A;
	*	16-bit read access from data register at RxNE event:
	*	unit16_t var;
	*	var= SPI_DR var=0x040A
	*/
	// (RM0410.pdf p.1323)
	switch(Encoder_Select)
	{
		case EncoderSelect_1:
			Encoder.SPI1_Tx_Buffer[1] = (uint8_t)(Encoder_Buffer >> 8) & 0xFF;
			Encoder.SPI1_Tx_Buffer[1] |= 0x80;
			Encoder.SPI1_Tx_Buffer[0] = (uint8_t)Encoder_Buffer & 0xFF;
			break;
		case EncoderSelect_2:
			Encoder.SPI2_Tx_Buffer[1] = (uint8_t)(Encoder_Buffer >> 8) & 0xFF;
			Encoder.SPI2_Tx_Buffer[1] |= 0x80;
			Encoder.SPI2_Tx_Buffer[0] = (uint8_t)Encoder_Buffer & 0xFF;
			break;
		default :
			break;
	}
}

/****************************************************************************/
/*	Overview	:	SPI1, 2 Tx Callback Check and Disable					*/
/*	Return value:	Void													*/
/****************************************************************************/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI1)
	{
		__HAL_SPI_DISABLE(&hspi1);

		Encoder.SPI1_Tx_Cplt_Flag = 1;
	}
	if(hspi->Instance == SPI2)
	{
		__HAL_SPI_DISABLE(&hspi2);

		Encoder.SPI2_Tx_Cplt_Flag = 1;
	}
}

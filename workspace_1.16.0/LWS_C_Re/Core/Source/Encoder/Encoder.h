/*
 * Encoder.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define EncoderSelect_1				(0)
#define EncoderSelect_2				(1)

/* Private variables ---------------------------------------------------------*/
typedef struct
{
	uint8_t SPI1_Tx_Cplt_Flag;
	uint8_t SPI1_Tx_Cplt_Cnt;

	uint8_t SPI2_Tx_Cplt_Flag;
	uint8_t SPI2_Tx_Cplt_Cnt;

	uint8_t SPI1_Tx_Buffer[2];				// SPI1 송신용 버퍼 8bit * 2
	uint8_t SPI2_Tx_Buffer[2];				// SPI2 송신용 버퍼 8bit * 2

	uint8_t SPI_DMA_Flag;

	float Encoder_1_Output_Value;
	float Encoder_2_Output_Value;
} _Encoder;
extern _Encoder Encoder;


/* Private function prototypes -----------------------------------------------*/
void FUN_Encoder_Init(void);
void FUN_Encoder_Routine(void);
void FUN_Encoder_Output_Set(void);
void FUN_Encoder_OutputBuffer_Set(uint8_t Encoder_Select, float Encoder_Value);
void FUN_Encoder_Transfer_Buffer(uint8_t Encoder_Select);
void Encoder_Degree_To_Data(uint8_t Encoder_Select);

#endif /* ENCODER_ENCODER_H_ */

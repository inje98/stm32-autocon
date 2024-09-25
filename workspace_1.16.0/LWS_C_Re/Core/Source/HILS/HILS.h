/*
 * HILS.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef HILS_HILS_H_
#define HILS_HILS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

typedef struct
{
	uint8_t LWS_C_HILS_Cmd[4];
	uint8_t LWS_C_HILS_DI[8];
	float LWS_C_HILS_AI[8];
	uint8_t LWS_C_HILS_OUTSET[18];
	float LWS_C_HILS_PARA[20];

	uint8_t HILS_Start_Flag;
	uint8_t HILS_Stop_Flag;
	uint8_t HILS_Change_Flag;
	uint8_t HILS_Change_Cnt;
	uint8_t HILS_Spare;
} HILS_INPUT_VALUE;

typedef struct
{
	uint8_t HILS_DO_Int[19];			//HILS DO ����
	float HILS_AO_Float[27];			//HILS AO ����
	float HILS_Monitoring[15];
	uint16_t HILS_Mode;
	uint16_t HILS_Status;
	uint16_t HILS_Error;
	uint16_t HILS_Alarm;
} HILS_OUTPUT_VALUE;

typedef struct
{
	HILS_INPUT_VALUE			HILS_Input;
	HILS_OUTPUT_VALUE			HILS_Output;
} _HILS;
extern _HILS HILS;


/* Private function prototypes -----------------------------------------------*/
void FUN_HILS_Init(void);
void FUN_HILS_Routine(void);

#endif /* HILS_HILS_H_ */

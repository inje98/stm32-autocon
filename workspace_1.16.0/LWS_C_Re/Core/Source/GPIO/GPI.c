/*
 * GPI.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "GPI.h"
#include "..\Control\Control.h"

/* Private variables ---------------------------------------------------------*/

_GPI GPI;

/* Private function prototypes -----------------------------------------------*/
static uint8_t FUN_GPI_Input(uint8_t u1t_inport);

/****************************************************************************/
/*	Overview	:	GPI Port Inverse Read									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPI_PortCheck(void)
{
	Control.Input_ch.Bit.In_ch1 = FUN_GPI_Input(PORT_NUM_1)^1;			// 무부하밸브(윈치동력)
	Control.Input_ch.Bit.In_ch2 = FUN_GPI_Input(PORT_NUM_2)^1;			// 무부하밸브(투인양동력)
	Control.Input_ch.Bit.In_ch3 = FUN_GPI_Input(PORT_NUM_3)^1;			// 방향전환밸브(수냉식냉각기)
	Control.Input_ch.Bit.In_ch4 = FUN_GPI_Input(PORT_NUM_4)^1;			// 차단밸브(수냉식냉각기)
	Control.Input_ch.Bit.In_ch5 = FUN_GPI_Input(PORT_NUM_5)^1;			// 차단밸브(축압기 충전)
	Control.Input_ch.Bit.In_ch6 = FUN_GPI_Input(PORT_NUM_6)^1;			// 차단밸브(윈치동력)
	Control.Input_ch.Bit.In_ch7 = FUN_GPI_Input(PORT_NUM_7)^1;			// 윈치조립체 : 방향전환밸브(권선브레이크)
	Control.Input_ch.Bit.In_ch8 = FUN_GPI_Input(PORT_NUM_8)^1;			// 윈치조립체 : 방향전환밸브(보조브레이크)
	Control.Input_ch.Bit.In_ch9 = FUN_GPI_Input(PORT_NUM_9)^1;			// 윈치조립체 : 방향전환밸브(보조절단기)
	Control.Input_ch.Bit.In_ch10 = FUN_GPI_Input(PORT_NUM_10)^1;		// 윈치조립체 : 방향전환밸브(주브레이크)
	Control.Input_ch.Bit.In_ch11 = FUN_GPI_Input(PORT_NUM_11)^1;		// 윈치조립체 : 방향전환밸브(주절단기)
	Control.Input_ch.Bit.In_ch12 = FUN_GPI_Input(PORT_NUM_12)^1;		// 투인양장치 : 청수잠금밸브(세척기)
	Control.Input_ch.Bit.In_ch13 = FUN_GPI_Input(PORT_NUM_13)^1;		// 확성기
//	Control.Input_ch.Bit.In_ch14 = FUN_GPI_Input(PORT_NUM_14)^1;
//	Control.Input_ch.Bit.In_ch15 = FUN_GPI_Input(PORT_NUM_15)^1;
//	Control.Input_ch.Bit.In_ch16 = FUN_GPI_Input(PORT_NUM_16)^1;
	Control.Input_ch.Bit.In_ch17 = FUN_GPI_Input(PORT_NUM_17)^1;		// 동력공급장치: 냉각기 구동명령
	Control.Input_ch.Bit.In_ch18 = FUN_GPI_Input(PORT_NUM_18)^1;		// 동력공급장치: 히터 구동명령
}

/****************************************************************************/
/*	Overview	:	Return Input Port State									*/
/*	Return value:	uint8_t													*/
/****************************************************************************/
// 입력에 포트 IN_Channel 번호를 넣음.
// 출력에 입력 표트의 정보가 출력됨.
static uint8_t FUN_GPI_Input(uint8_t u1t_inport)
{
	uint8_t u1t_input_val = 0;
	uint8_t u1t_ret = 0;

	switch(u1t_inport)
	{
		case PORT_NUM_1:								// INPUT PORT Channel Number
			if(InputPort_HIGH == InputPort_CH_1)
			{											// 입력 값 비교 		if(INPUT == HI)
				u1t_input_val = InputPort_HIGH;			// HI 저장
			}
			else
			{
				u1t_input_val = InputPort_LOW;			// LO 저장
			}
		break;

		case PORT_NUM_2:
			if(InputPort_HIGH == InputPort_CH_2)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_3:
			if(InputPort_HIGH == InputPort_CH_3)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_4:
			if(InputPort_HIGH == InputPort_CH_4)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_5:
			if(InputPort_HIGH == InputPort_CH_5)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_6:
			if(InputPort_HIGH == InputPort_CH_6)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_7:
			if(InputPort_HIGH == InputPort_CH_7)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_8:
			if(InputPort_HIGH == InputPort_CH_8)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_9:
			if(InputPort_HIGH == InputPort_CH_9)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_10:
			if(InputPort_HIGH == InputPort_CH_10)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_11:
			if(InputPort_HIGH == InputPort_CH_11)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_12:
			if(InputPort_HIGH == InputPort_CH_12)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_13:
			if(InputPort_HIGH == InputPort_CH_13)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_14:
			if(InputPort_HIGH == InputPort_CH_14){
				u1t_input_val = InputPort_HIGH;
			} else {
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_15:
			if(InputPort_HIGH == InputPort_CH_15){
				u1t_input_val = InputPort_HIGH;
			} else {
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_16:
			if(InputPort_HIGH == InputPort_CH_16){
				u1t_input_val = InputPort_HIGH;
			} else {
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_17:
			if(InputPort_HIGH == InputPort_CH_17)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		case PORT_NUM_18:
			if(InputPort_HIGH == InputPort_CH_18)
			{
				u1t_input_val = InputPort_HIGH;
			}
			else
			{
				u1t_input_val = InputPort_LOW;
			}
		break;

		default:
		break;
	}

	u1t_ret = u1t_input_val;

	return u1t_ret;
}

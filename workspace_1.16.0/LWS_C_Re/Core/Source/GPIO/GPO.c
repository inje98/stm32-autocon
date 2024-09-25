/*
 * GPO.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "GPO.h"

#include "main.h"
#include "..\Control\Control.h"
#include "..\RS485\RS485.h"
#include "..\HILS\HILS.h"

/* Private variables ---------------------------------------------------------*/

_GPO GPO;

uint8_t GPO_Test[48];

void FUN_GPO_PortCheck(void );
/****************************************************************************/
/*	Overview	:	출력 초기상태를 High로 설정									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Init(void)
{
	OUTPUT_CH_1_HIGH();
	OUTPUT_CH_2_HIGH();
	OUTPUT_CH_3_HIGH();
	OUTPUT_CH_4_HIGH();
	OUTPUT_CH_5_HIGH();
	OUTPUT_CH_6_HIGH();
	OUTPUT_CH_7_HIGH();
	OUTPUT_CH_8_HIGH();
	OUTPUT_CH_9_HIGH();
	OUTPUT_CH_10_HIGH();
	OUTPUT_CH_11_HIGH();
	OUTPUT_CH_12_HIGH();
	OUTPUT_CH_13_HIGH();
	OUTPUT_CH_14_HIGH();
	OUTPUT_CH_15_HIGH();
	OUTPUT_CH_16_HIGH();
	OUTPUT_CH_17_HIGH();
	OUTPUT_CH_18_HIGH();
	OUTPUT_CH_19_HIGH();
	OUTPUT_CH_20_HIGH();
	OUTPUT_CH_21_HIGH();
	OUTPUT_CH_22_HIGH();
	OUTPUT_CH_23_HIGH();
	OUTPUT_CH_24_HIGH();
	OUTPUT_CH_25_HIGH();
	OUTPUT_CH_26_HIGH();
	OUTPUT_CH_27_HIGH();
	OUTPUT_CH_28_HIGH();
	OUTPUT_CH_29_HIGH();
	OUTPUT_CH_30_HIGH();
	OUTPUT_CH_31_HIGH();
	OUTPUT_CH_32_HIGH();
	OUTPUT_CH_33_HIGH();
	OUTPUT_CH_34_HIGH();
	OUTPUT_CH_35_HIGH();
	OUTPUT_CH_36_HIGH();
	OUTPUT_CH_37_HIGH();
	OUTPUT_CH_38_HIGH();
	OUTPUT_CH_39_HIGH();
	OUTPUT_CH_40_HIGH();
	OUTPUT_CH_41_HIGH();
	OUTPUT_CH_42_HIGH();
	OUTPUT_CH_43_HIGH();
	OUTPUT_CH_44_HIGH();
	OUTPUT_CH_45_HIGH();
	OUTPUT_CH_46_HIGH();
	OUTPUT_CH_47_HIGH();
	OUTPUT_CH_48_HIGH();
}

/****************************************************************************/
/*	Overview	:	GPO Port Inverse Read														*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_PortCheck(void)
{
	// Read OUTPUT PORT State
	Control.Output_ch.Bit.Out_ch1 = OUTPUT_CH_1_READ()^1;
	Control.Output_ch.Bit.Out_ch2 = OUTPUT_CH_2_READ()^1;
	Control.Output_ch.Bit.Out_ch3 = OUTPUT_CH_3_READ()^1;
	Control.Output_ch.Bit.Out_ch4 = OUTPUT_CH_4_READ()^1;
	Control.Output_ch.Bit.Out_ch5 = OUTPUT_CH_5_READ()^1;
	Control.Output_ch.Bit.Out_ch6 = OUTPUT_CH_6_READ()^1;
	Control.Output_ch.Bit.Out_ch7 = OUTPUT_CH_7_READ()^1;
	Control.Output_ch.Bit.Out_ch8 = OUTPUT_CH_8_READ()^1;
	Control.Output_ch.Bit.Out_ch9 = OUTPUT_CH_9_READ()^1;
	Control.Output_ch.Bit.Out_ch10 = OUTPUT_CH_10_READ()^1;
	Control.Output_ch.Bit.Out_ch11 = OUTPUT_CH_11_READ()^1;
	Control.Output_ch.Bit.Out_ch12 = OUTPUT_CH_12_READ()^1;
	Control.Output_ch.Bit.Out_ch13 = OUTPUT_CH_13_READ()^1;
	Control.Output_ch.Bit.Out_ch14 = OUTPUT_CH_14_READ()^1;
	Control.Output_ch.Bit.Out_ch15 = OUTPUT_CH_15_READ()^1;
	Control.Output_ch.Bit.Out_ch16 = OUTPUT_CH_16_READ()^1;
	Control.Output_ch.Bit.Out_ch17 = OUTPUT_CH_17_READ()^1;
	Control.Output_ch.Bit.Out_ch18 = OUTPUT_CH_18_READ()^1;
	Control.Output_ch.Bit.Out_ch19 = OUTPUT_CH_19_READ()^1;
	Control.Output_ch.Bit.Out_ch20 = OUTPUT_CH_20_READ()^1;
	Control.Output_ch.Bit.Out_ch21 = OUTPUT_CH_21_READ()^1;
	Control.Output_ch.Bit.Out_ch22 = OUTPUT_CH_22_READ()^1;
	Control.Output_ch.Bit.Out_ch23 = OUTPUT_CH_23_READ()^1;
	Control.Output_ch.Bit.Out_ch24 = OUTPUT_CH_24_READ()^1;
	Control.Output_ch.Bit.Out_ch25 = OUTPUT_CH_25_READ()^1;
	Control.Output_ch.Bit.Out_ch26 = OUTPUT_CH_26_READ()^1;
	Control.Output_ch.Bit.Out_ch27 = OUTPUT_CH_27_READ()^1;
	Control.Output_ch.Bit.Out_ch28 = OUTPUT_CH_28_READ()^1;
	Control.Output_ch.Bit.Out_ch29 = OUTPUT_CH_29_READ()^1;
	Control.Output_ch.Bit.Out_ch30 = OUTPUT_CH_30_READ()^1;
	Control.Output_ch.Bit.Out_ch31 = OUTPUT_CH_31_READ()^1;
	Control.Output_ch.Bit.Out_ch32 = OUTPUT_CH_32_READ()^1;
	Control.Output_ch.Bit.Out_ch33 = OUTPUT_CH_33_READ()^1;
	Control.Output_ch.Bit.Out_ch34 = OUTPUT_CH_34_READ()^1;
	Control.Output_ch.Bit.Out_ch35 = OUTPUT_CH_35_READ()^1;
	Control.Output_ch.Bit.Out_ch36 = OUTPUT_CH_36_READ()^1;
	Control.Output_ch.Bit.Out_ch37 = OUTPUT_CH_37_READ()^1;
	Control.Output_ch.Bit.Out_ch38 = OUTPUT_CH_38_READ()^1;
	Control.Output_ch.Bit.Out_ch39 = OUTPUT_CH_39_READ()^1;
	Control.Output_ch.Bit.Out_ch40 = OUTPUT_CH_40_READ()^1;
	Control.Output_ch.Bit.Out_ch41 = OUTPUT_CH_41_READ()^1;
	Control.Output_ch.Bit.Out_ch42 = OUTPUT_CH_42_READ()^1;
	Control.Output_ch.Bit.Out_ch43 = OUTPUT_CH_43_READ()^1;
//	Control.Output_ch.Bit.Out_ch44 = OUTPUT_CH_44_READ()^1;
//	Control.Output_ch.Bit.Out_ch45 = OUTPUT_CH_45_READ()^1;
//	Control.Output_ch.Bit.Out_ch46 = OUTPUT_CH_46_READ()^1;
//	Control.Output_ch.Bit.Out_ch47 = OUTPUT_CH_47_READ()^1;
//	Control.Output_ch.Bit.Out_ch48 = OUTPUT_CH_48_READ()^1;
}

/****************************************************************************/
/*	Overview	:	GPO Main Routine														*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Routine(void)
{
	// HILS 출력
	if(HILS_START == FUN_RS485_Ctrl_hils_action_U1())
	{
		FUN_GPO_Output(OUTPUT_PORT_NUM_7,	HILS.HILS_Output.HILS_DO_Int[0]^1);						// 동력공급장치 : 압력스위치(부스터)
		FUN_GPO_Output(OUTPUT_PORT_NUM_13,	HILS.HILS_Output.HILS_DO_Int[1]^1);						// 동력공급장치 : 압력스위치(투인양동력)
		FUN_GPO_Output(OUTPUT_PORT_NUM_9,	HILS.HILS_Output.HILS_DO_Int[2]^1);						// 동력공급장치 : 압력스위치(압력초과)
		FUN_GPO_Output(OUTPUT_PORT_NUM_5,	HILS.HILS_Output.HILS_DO_Int[3]^1);						// 동력공급장치 : 압력스위치(감김)
		FUN_GPO_Output(OUTPUT_PORT_NUM_14,	HILS.HILS_Output.HILS_DO_Int[4]^1);						// 동력공급장치 : 압력스위치(풀림)
		FUN_GPO_Output(OUTPUT_PORT_NUM_6,	HILS.HILS_Output.HILS_DO_Int[5]^1);						// 동력공급장치 : 압력스위치(권선)
		FUN_GPO_Output(OUTPUT_PORT_NUM_15,	HILS.HILS_Output.HILS_DO_Int[6]^1);						// 동력공급장치 : 필터막힘스위치(리턴)
		FUN_GPO_Output(OUTPUT_PORT_NUM_16,	HILS.HILS_Output.HILS_DO_Int[7]^1);						// 동력공급장치 : 필터막힘스위치(부스터펌프)
		FUN_GPO_Output(OUTPUT_PORT_NUM_17,	HILS.HILS_Output.HILS_DO_Int[8]^1);						// 동력공급장치 : 필터막힘스위치(윈치구동) =????
		FUN_GPO_Output(OUTPUT_PORT_NUM_18,	HILS.HILS_Output.HILS_DO_Int[9]^1);						// 동력공급장치 : 필터막힘스위치(투인양)
		FUN_GPO_Output(OUTPUT_PORT_NUM_21,	HILS.HILS_Output.HILS_DO_Int[10]^1);					// 윈치조립체 : 근접센서(우측A)
		FUN_GPO_Output(OUTPUT_PORT_NUM_22,	HILS.HILS_Output.HILS_DO_Int[11]^1);					// 윈치조립체 : 근접센서(우측B)
		FUN_GPO_Output(OUTPUT_PORT_NUM_23,	HILS.HILS_Output.HILS_DO_Int[12]^1);					// 윈치조립체 : 근접센서(좌측A)
		FUN_GPO_Output(OUTPUT_PORT_NUM_24,	HILS.HILS_Output.HILS_DO_Int[13]^1);					// 윈치조립체 : 근접센서(좌측B)
		FUN_GPO_Output(OUTPUT_PORT_NUM_20,	HILS.HILS_Output.HILS_DO_Int[14]^1);					// 윈치조립체 : 5회전 감지스위치
		FUN_GPO_Output(OUTPUT_PORT_NUM_26,	HILS.HILS_Output.HILS_DO_Int[15]^1);					// 윈치조립체 : 압력스위치(권선브레이크)
		FUN_GPO_Output(OUTPUT_PORT_NUM_28,	HILS.HILS_Output.HILS_DO_Int[16]^1);					// 윈치조립체 : 압력스위치(밴드브레이크)
		FUN_GPO_Output(OUTPUT_PORT_NUM_27,	HILS.HILS_Output.HILS_DO_Int[17]^1);					// 윈치조립체 : 압력스위치(모터브레이크)
		FUN_GPO_Output(OUTPUT_PORT_NUM_19,	HILS.HILS_Output.HILS_DO_Int[18]^1);					// 동력공급장치 윈치동력 : 비례제어밸브 에러신호 =????

	}
	// 강제 출력
	else
	{
		FUN_GPO_Output(OUTPUT_PORT_NUM_7,	RS485.HILS_UC_Output_Int[0]^1);				// [0]: 압력스위치(부스터)
		FUN_GPO_Output(OUTPUT_PORT_NUM_13,	RS485.HILS_UC_Output_Int[1]^1);				// [1]: 압력스위치(투인양동력)
		FUN_GPO_Output(OUTPUT_PORT_NUM_9,	RS485.HILS_UC_Output_Int[2]^1);				// [2]: 압력스위치(압력초과)
		FUN_GPO_Output(OUTPUT_PORT_NUM_5,	RS485.HILS_UC_Output_Int[3]^1);				// [3]: 압력스위치(감김)
		FUN_GPO_Output(OUTPUT_PORT_NUM_14,	RS485.HILS_UC_Output_Int[4]^1);				// [4]: 압력스위치(풀림)
		FUN_GPO_Output(OUTPUT_PORT_NUM_6,	RS485.HILS_UC_Output_Int[5]^1);				// [5]: 압력스위치(권선)

		FUN_GPO_Output(OUTPUT_PORT_NUM_15,	RS485.HILS_UC_Output_Int[6]^1);				// [6]: 필터막힘스위치(리턴)
		FUN_GPO_Output(OUTPUT_PORT_NUM_16,	RS485.HILS_UC_Output_Int[7]^1);				// [7]: 필터막힘스위치(부스터펌프)
		FUN_GPO_Output(OUTPUT_PORT_NUM_17,	RS485.HILS_UC_Output_Int[8]^1);				// [8]: 필터막힘스위치(윈치구동)
		FUN_GPO_Output(OUTPUT_PORT_NUM_18,	RS485.HILS_UC_Output_Int[9]^1);				// [9]: 필터막힘스위치(투인양)

		FUN_GPO_Output(OUTPUT_PORT_NUM_21,	RS485.HILS_UC_Output_Int[10]^1);			// [10]: 권선 근접센서(우측A)
		FUN_GPO_Output(OUTPUT_PORT_NUM_22,	RS485.HILS_UC_Output_Int[11]^1);			// [11]: 권선 근접센서(우측B)
		FUN_GPO_Output(OUTPUT_PORT_NUM_23,	RS485.HILS_UC_Output_Int[12]^1);			// [12]: 권선 근접센서(좌측A)
		FUN_GPO_Output(OUTPUT_PORT_NUM_24,	RS485.HILS_UC_Output_Int[13]^1);			// [13]: 권선 근접센서(좌측B)
		FUN_GPO_Output(OUTPUT_PORT_NUM_20,	RS485.HILS_UC_Output_Int[14]^1);			// [14]: 5회전 감지스위치
		FUN_GPO_Output(OUTPUT_PORT_NUM_26,	RS485.HILS_UC_Output_Int[15]^1);			// [15]: 압력스위치(권서브레이크)
		FUN_GPO_Output(OUTPUT_PORT_NUM_28,	RS485.HILS_UC_Output_Int[16]^1);			// [16]: 압력스위치(주브레이크)
		FUN_GPO_Output(OUTPUT_PORT_NUM_27,	RS485.HILS_UC_Output_Int[17]^1);			// [17]: 압력스위치(보조브레이크)
		FUN_GPO_Output(OUTPUT_PORT_NUM_19,	RS485.HILS_UC_Output_Int[18]^1);			// [18]: 비례밸브 에러(드럼구동)

//		FUN_GPO_Output(OUTPUT_PORT_NUM_7,	RS485.HILS_UC_Output_Int[0]^1);				// 동력공급장치 : 압력스위치(부스터)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_13,	RS485.HILS_UC_Output_Int[1]^1);				// 동력공급장치 : 압력스위치(투인양동력)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_9,	RS485.HILS_UC_Output_Int[2]^1);				// 동력공급장치 : 압력스위치(압력초과)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_5,	RS485.HILS_UC_Output_Int[3]^1);				// 동력공급장치 : 압력스위치(감김)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_14,	RS485.HILS_UC_Output_Int[4]^1);				// 동력공급장치 : 압력스위치(풀림)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_6,	RS485.HILS_UC_Output_Int[5]^1);				// 동력공급장치 : 압력스위치(권선)
//
//		FUN_GPO_Output(OUTPUT_PORT_NUM_15,	RS485.HILS_UC_Output_Int[6]^1);				// 동력공급장치 : 필터막힘스위치(리턴)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_16,	RS485.HILS_UC_Output_Int[7]^1);				// 동력공급장치 : 필터막힘스위치(부스터펌프)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_17,	RS485.HILS_UC_Output_Int[8]^1);				// 동력공급장치 : 필터막힘스위치(윈치구동) =????
//		FUN_GPO_Output(OUTPUT_PORT_NUM_18,	RS485.HILS_UC_Output_Int[9]^1);				// 동력공급장치 : 필터막힘스위치(투인양)
//
//		FUN_GPO_Output(OUTPUT_PORT_NUM_21,	RS485.HILS_UC_Output_Int[10]^1);			// 윈치조립체 : 근접센서(우측A)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_22,	RS485.HILS_UC_Output_Int[11]^1);			// 윈치조립체 : 근접센서(우측B)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_23,	RS485.HILS_UC_Output_Int[12]^1);			// 윈치조립체 : 근접센서(좌측A)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_24,	RS485.HILS_UC_Output_Int[13]^1);			// 윈치조립체 : 근접센서(좌측B)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_20,	RS485.HILS_UC_Output_Int[14]^1);			// 윈치조립체 : 5회전 감지스위치
//		FUN_GPO_Output(OUTPUT_PORT_NUM_26,	RS485.HILS_UC_Output_Int[15]^1);			// 윈치조립체 : 압력스위치(권선브레이크)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_28,	RS485.HILS_UC_Output_Int[16]^1);			// 윈치조립체 : 압력스위치(주브레이크)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_27,	RS485.HILS_UC_Output_Int[17]^1);			// 윈치조립체 : 압력스위치(보조브레이크)
//		FUN_GPO_Output(OUTPUT_PORT_NUM_19,	RS485.HILS_UC_Output_Int[18]^1);			// 동력공급장치 윈치동력 : 비례제어밸브 에러신호 =????
	}
}

/****************************************************************************/
/*	Overview	:	Return Input Port State									*/
/*	Return value:	uint8_t													*/
/****************************************************************************/
void FUN_GPO_Output(uint8_t u1t_outport, uint8_t u1t_val)
{
	switch(u1t_outport)
	{
		case OUTPUT_PORT_NUM_1:							// OUTPUT PORT Channel Number 1
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_1_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_1_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_2:							// OUTPUT PORT Channel Number 2
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_2_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_2_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_3:							// OUTPUT PORT Channel Number 3
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_3_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_3_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_4:							// OUTPUT PORT Channel Number 4
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_4_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_4_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_5:							// OUTPUT PORT Channel Number 5
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_5_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_5_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_6:							// OUTPUT PORT Channel Number 6
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_6_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_6_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_7:							// OUTPUT PORT Channel Number 7
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_7_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_7_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_8:							// OUTPUT PORT Channel Number 8
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_8_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_8_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_9:							// OUTPUT PORT Channel Number 9
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_9_HIGH();						// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_9_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_10:						// OUTPUT PORT Channel Number 10
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_10_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_10_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_11:						// OUTPUT PORT Channel Number 11
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_11_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_11_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_12:						// OUTPUT PORT Channel Number 12
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_12_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_12_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_13:						// OUTPUT PORT Channel Number 13
			if(OUTPUT_PORT_HIGH == u1t_val)
										{				// 출력 HI Command
				OUTPUT_CH_13_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_13_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_14:						// OUTPUT PORT Channel Number 14
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_14_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_14_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_15:						// OUTPUT PORT Channel Number 15
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_15_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_15_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_16:						// OUTPUT PORT Channel Number 16
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_16_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_16_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_17:						// OUTPUT PORT Channel Number 17
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_17_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_17_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_18:						// OUTPUT PORT Channel Number 18
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_18_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_18_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_19:						// OUTPUT PORT Channel Number 19
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_19_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_19_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_20:						// OUTPUT PORT Channel Number 20
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_20_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_20_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_21:						// OUTPUT PORT Channel Number 21
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_21_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_21_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_22:						// OUTPUT PORT Channel Number 22
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_22_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_22_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_23:						// OUTPUT PORT Channel Number 23
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_23_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_23_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_24:						// OUTPUT PORT Channel Number 24
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_24_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_24_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_25:						// OUTPUT PORT Channel Number 25
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_25_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_25_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_26:						// OUTPUT PORT Channel Number 26
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_26_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_26_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_27:						// OUTPUT PORT Channel Number 27
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_27_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_27_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_28:						// OUTPUT PORT Channel Number 28
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_28_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_28_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_29:						// OUTPUT PORT Channel Number 29
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_29_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_29_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_30:						// OUTPUT PORT Channel Number 30
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_30_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_30_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_31:						// OUTPUT PORT Channel Number 31
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_31_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_31_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_32:						// OUTPUT PORT Channel Number 32
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_32_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_32_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_33:						// OUTPUT PORT Channel Number 33
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_33_HIGH();					// HIGH 출력
			}else
			{											// 출력 LO Command
				OUTPUT_CH_33_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_34:						// OUTPUT PORT Channel Number 34
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_34_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_34_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_35:						// OUTPUT PORT Channel Number 35
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_35_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_35_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_36:						// OUTPUT PORT Channel Number 36
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_36_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_36_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_37:						// OUTPUT PORT Channel Number 37
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_37_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_37_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_38:						// OUTPUT PORT Channel Number 38
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_38_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_38_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_39:						// OUTPUT PORT Channel Number 39
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_39_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_39_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_40:						// OUTPUT PORT Channel Number 40
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_40_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_40_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_41:						// OUTPUT PORT Channel Number 41
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_41_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_41_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_42:						// OUTPUT PORT Channel Number 42
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_42_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_42_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_43:						// OUTPUT PORT Channel Number 43
			if(OUTPUT_PORT_HIGH == u1t_val)
			{											// 출력 HI Command
				OUTPUT_CH_43_HIGH();					// HIGH 출력
			}
			else
			{											// 출력 LO Command
				OUTPUT_CH_43_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_44:							// OUTPUT PORT Channel Number 44
			if(OUTPUT_PORT_HIGH == u1t_val){				// 출력 HI Command
				OUTPUT_CH_44_HIGH();						// HIGH 출력
			} else {									// 출력 LO Command
				OUTPUT_CH_44_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_45:							// OUTPUT PORT Channel Number 45
			if(OUTPUT_PORT_HIGH == u1t_val){				// 출력 HI Command
				OUTPUT_CH_45_HIGH();						// HIGH 출력
			} else {									// 출력 LO Command
				OUTPUT_CH_45_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_46:							// OUTPUT PORT Channel Number 46
			if(OUTPUT_PORT_HIGH == u1t_val){				// 출력 HI Command
				OUTPUT_CH_46_HIGH();						// HIGH 출력
			} else {									// 출력 LO Command
				OUTPUT_CH_46_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_47:							// OUTPUT PORT Channel Number 47
			if(OUTPUT_PORT_HIGH == u1t_val){				// 출력 HI Command
				OUTPUT_CH_47_HIGH();						// HIGH 출력
			} else {									// 출력 LO Command
				OUTPUT_CH_47_LOW();						// LOW 출력
			}
		break;

		case OUTPUT_PORT_NUM_48:							// OUTPUT PORT Channel Number 48
			if(OUTPUT_PORT_HIGH == u1t_val){				// 출력 HI Command
				OUTPUT_CH_48_HIGH();						// HIGH 출력
			} else {									// 출력 LO Command
				OUTPUT_CH_48_LOW();						// LOW 출력
			}
		break;

		default:

		break;
	}
}

/****************************************************************************/
/*	Overview	:	Gripper Output	Setting									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Gripper(void)
{
	// 그립퍼
	FUN_GPO_Output(OUTPUT_PORT_NUM_37,	RS485.Gripper_Output_Int[0]^1);		// 투인양장치 : 근접스위치1
	FUN_GPO_Output(OUTPUT_PORT_NUM_38,	RS485.Gripper_Output_Int[1]^1);		// 투인양장치 : 근접스위치2
	FUN_GPO_Output(OUTPUT_PORT_NUM_39,	RS485.Gripper_Output_Int[2]^1);		// 투인양장치 : 근접스위치3
	FUN_GPO_Output(OUTPUT_PORT_NUM_40,	RS485.Gripper_Output_Int[3]^1);		// 투인양장치 : 근접스위치4
	FUN_GPO_Output(OUTPUT_PORT_NUM_41,	RS485.Gripper_Output_Int[4]^1);		// 투인양장치 : 근접스위치5
	FUN_GPO_Output(OUTPUT_PORT_NUM_42,	RS485.Gripper_Output_Int[5]^1);		// 투인양장치 : 근접스위치6
}

/****************************************************************************/
/*	Overview	:	Oil Output	Setting										*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Oil(void)
{
	// 저유기
	FUN_GPO_Output(OUTPUT_PORT_NUM_8,	RS485.Oil_Output_Int[0]^1);				// 동력공급장치 : 압력스위치(수냉식냉각기)
	FUN_GPO_Output(OUTPUT_PORT_NUM_1,	RS485.Oil_Output_Int[1]^1);				// 동력공급장치 : 레벨스위치1(저유기조립체)
	FUN_GPO_Output(OUTPUT_PORT_NUM_2,	RS485.Oil_Output_Int[2]^1);				// 동력공급장치 : 레벨스위치2(저유기조립체)
	FUN_GPO_Output(OUTPUT_PORT_NUM_3,	RS485.Oil_Output_Int[3]^1);				// 동력공급장치 : 레벨스위치3(저유기조립체)
}

/****************************************************************************/
/*	Overview	:	Cutter Output	Setting									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Cutter(void)
{
	// 절단기
	FUN_GPO_Output(OUTPUT_PORT_NUM_10,	RS485.Cutter_Output_Int[0]^1);		// 동력공급장치 : 압력스위치(축압기 부족1)
	FUN_GPO_Output(OUTPUT_PORT_NUM_11,	RS485.Cutter_Output_Int[1]^1);		// 동력공급장치 : 압력스위치(축압기 부족2)
	FUN_GPO_Output(OUTPUT_PORT_NUM_12,	RS485.Cutter_Output_Int[2]^1);		// 동력공급장치 : 압력스위치(축압기 충전완료)
	FUN_GPO_Output(OUTPUT_PORT_NUM_36,	RS485.Cutter_Output_Int[3]^1);		// 윈치조립체 : 칼날감지센서(주절단기)
	FUN_GPO_Output(OUTPUT_PORT_NUM_35,	RS485.Cutter_Output_Int[4]^1);		// 윈치조립체 : 칼날감지센서(보조절단기)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Cutter_Output_Int[5]^1);			// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Cutter_Output_Int[6]^1);			// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Cutter_Output_Int[7]^1);			// SPARE
}

/****************************************************************************/
/*	Overview	:	Cleaner Output	Setting									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Cleaner(void)
{
	// 세척기
	FUN_GPO_Output(OUTPUT_PORT_NUM_43,	RS485.Cleaner_Output_Int[0]^1);		// 투인양장치 : 압력스위치(세척기)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_38,	RS485.Cleaner_Output_Int[1]^1);
//	FUN_GPO_Output(OUTPUT_PORT_NUM_39,	RS485.Cleaner_Output_Int[2]^1);
//	FUN_GPO_Output(OUTPUT_PORT_NUM_40,	RS485.Cleaner_Output_Int[3]^1);
//	FUN_GPO_Output(OUTPUT_PORT_NUM_41,	RS485.Cleaner_Output_Int[4]^1);
//	FUN_GPO_Output(OUTPUT_PORT_NUM_42,	RS485.Cleaner_Output_Int[5]^1);
//	FUN_GPO_Output(OUTPUT_PORT_NUM_40,	RS485.Cleaner_Output_Int[6]^1);
//	FUN_GPO_Output(OUTPUT_PORT_NUM_41,	RS485.Cleaner_Output_Int[7]^1);
}

/****************************************************************************/
/*	Overview	:	Emergency Output	Setting								*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPO_Emergency(void)
{
	// 비상정지스위치
	FUN_GPO_Output(OUTPUT_PORT_NUM_25,	RS485.Emergency_Output_Int[0]^1);	// 동력공급장치 : 비상정지스위치
	FUN_GPO_Output(OUTPUT_PORT_NUM_4,	RS485.Emergency_Output_Int[1]^1);	// 윈치조립체 : 비상정지스위치
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Emergency_Output_Int[2]^1);		// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Emergency_Output_Int[3]^1);		// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Emergency_Output_Int[4]^1);		// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Emergency_Output_Int[5]^1);		// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Emergency_Output_Int[6]^1);		// SPARE
//	FUN_GPO_Output(OUTPUT_PORT_NUM_,	RS485.Emergency_Output_Int[7]^1);		// SPARE
}

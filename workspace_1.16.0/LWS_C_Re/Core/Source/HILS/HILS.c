/*
 * HILS.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "HILS.h"
#include "main.h"
#include "Lws_HilsCtrl_240218_v_1_0.h" /* Model's header file */
#include "rtwtypes.h"
#include "../Control/Control.h"
#include "../RS485/RS485.h"
#include "../GPIO/GPO.h"
/* Private variables ---------------------------------------------------------*/
_HILS HILS;
HILS_INPUT_VALUE 	HILS_INPUT;
HILS_OUTPUT_VALUE 	HILS_OUTPUT;

extern ExtU_Lws_HilsCtrl_240218_v_1__T Lws_HilsCtrl_240218_v_1_0_U;
extern ExtY_Lws_HilsCtrl_240218_v_1__T Lws_HilsCtrl_240218_v_1_0_Y;

/* Private function prototypes -----------------------------------------------*/
void FUN_HILS_Input_Routine(void);
void FUN_HILS_Output_Routine(void);

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_HILS_Init(void)
{
	Lws_HilsCtrl_240218_v_1_0_initialize();
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_HILS_Routine(void)
{
	FUN_HILS_Input_Routine();
	Lws_HilsCtrl_240218_v_1_0_step();
	FUN_HILS_Output_Routine();
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_HILS_Input_Routine(void)
{
	if(RS485.HILS_Start_Stop_Cmd == 1)
	{
		HILS.HILS_Input.HILS_Start_Flag = 1;

		HILS.HILS_Input.HILS_Stop_Flag = 0;
	}
	else
	{
		HILS.HILS_Input.HILS_Stop_Flag = 1;

		HILS.HILS_Input.HILS_Start_Flag = 0;
	}

	if(HILS.HILS_Input.HILS_Change_Flag == 1)
	{
		HILS.HILS_Input.HILS_Change_Cnt++;

		if(HILS.HILS_Input.HILS_Change_Cnt >= 11)
		{
			HILS.HILS_Input.HILS_Change_Flag = 0;
		}
	}
	else
	{
		HILS.HILS_Input.HILS_Change_Flag = 0;
		HILS.HILS_Input.HILS_Change_Cnt = 0;
	}

	HILS.HILS_Input.LWS_C_HILS_Cmd[0] = HILS.HILS_Input.HILS_Start_Flag;
	HILS.HILS_Input.LWS_C_HILS_Cmd[1] = HILS.HILS_Input.HILS_Stop_Flag;
	HILS.HILS_Input.LWS_C_HILS_Cmd[2] = HILS.HILS_Input.HILS_Change_Flag;
	HILS.HILS_Input.LWS_C_HILS_Cmd[3] = HILS.HILS_Input.HILS_Spare;

	HILS.HILS_Input.LWS_C_HILS_DI[0] = Control.Input_ch.Bit.In_ch1;						// 무부하밸브(윈치동력)
	HILS.HILS_Input.LWS_C_HILS_DI[1] = Control.Input_ch.Bit.In_ch2;						// 무부하밸브(투인양동력)
	HILS.HILS_Input.LWS_C_HILS_DI[2] = Control.Input_ch.Bit.In_ch6;						// 차단밸브(윈치동력)
	HILS.HILS_Input.LWS_C_HILS_DI[3] = Control.Input_ch.Bit.In_ch7;						// 방향전환밸브(권선브레이크)
	HILS.HILS_Input.LWS_C_HILS_DI[4] = Control.Input_ch.Bit.In_ch10;					// 방향전환밸브(주브레이크)
	HILS.HILS_Input.LWS_C_HILS_DI[5] = Control.Input_ch.Bit.In_ch8;						// 방향전환밸브(보조브레이크)
	HILS.HILS_Input.LWS_C_HILS_DI[6] = FUN_RS485_Ctrl_hils_action_U1();					// HILS 시작

	HILS.HILS_Input.LWS_C_HILS_AI[0] = Control.Float_Data.AI_ADC_In1_Ch2_Volt;		// 동력공급장치 비상구동: 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[1] = Control.Float_Data.AI_ADC_In1_Ch1_Volt;		// 윈치조립체 드럼구동 : 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[2] = Control.Float_Data.AI_ADC_In1_Ch3_Volt;		// 윈치조립체 권선구동 : 비례제어밸브
//	HILS.HILS_Input.LWS_C_HILS_AI[3] = Control.Float_Data.AI_ADC_In2_Ch1_Volt;		// 투인양장치 메인실린더1 : 비례제어밸브
//	HILS.HILS_Input.LWS_C_HILS_AI[4] = Control.Float_Data.AI_ADC_In2_Ch2_Volt;		// 투인양장치 메인실린더2 : 비례제어밸브
//	HILS.HILS_Input.LWS_C_HILS_AI[5] = Control.Float_Data.AI_ADC_In2_Ch3_Volt;		// 투인양장치 보조실린더1 : 비례제어밸브
//	HILS.HILS_Input.LWS_C_HILS_AI[6] = Control.Float_Data.AI_ADC_In2_Ch4_Volt;		// 투인양장치 보조실린더2 : 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[3] = Control.Float_Data.AI_ADC_In2_Ch3_Volt;		// 투인양장치 보조실린더1 : 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[4] = Control.Float_Data.AI_ADC_In2_Ch4_Volt;		// 투인양장치 보조실린더2 : 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[5] = Control.Float_Data.AI_ADC_In2_Ch1_Volt;		// 투인양장치 메인실린더1 : 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[6] = Control.Float_Data.AI_ADC_In2_Ch2_Volt;		// 투인양장치 메인실린더2 : 비례제어밸브
	HILS.HILS_Input.LWS_C_HILS_AI[7] = Control.Float_Data.AO_Spare_01;					// Spare01

	for(uint8_t i = 0; i < 20; i++)
	{
		HILS.HILS_Input.LWS_C_HILS_PARA[i] = RS485.LwsA_Parameter[i]; //LwsWtuA_PARA[u1t_i];
	}

	for(uint8_t i = 0; i < 18; i++)
	{
		HILS.HILS_Input.LWS_C_HILS_OUTSET[i] = RS485.LwsA_HILS_Init_Value[i];
	}

	/*
	 * [0] : 무부하밸브(윈치동력)
	 * [1] : 무부하밸브(투인양동력)
	 * [2] : 차단밸브(윈치동력)
	 * [3] : 방향전환밸브(권선브레이크)
	 * [4] : 방향전환밸브(주브레이크)
	 * [5] : 방향전환밸브(보조브레이크)
	 * [6] : Spare01
	 * [7] : Spare02
	 */

	for(uint8_t i = 0; i < 8; i++)
	{
		Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[i] = HILS.HILS_Input.LWS_C_HILS_DI[i];
	}

	/*
	 * 	[0] : 동력공급장치 비상구동: 비례제어밸브
	 * 	[1] : 윈치조립체 드럼구동 : 비례제어밸브
	 * 	[2] : 윈치조립체 권선구동 : 비례제어밸브
	 * 	[3] : 투인양장치 메인실린더1 : 비례제어밸브
	 * 	[4] : 투인양장치 메인실린더2 : 비례제어밸브
	 * 	[5] : 투인양장치 보조실린더1 : 비례제어밸브
	 * 	[6] : 투인양장치 보조실린더2 : 비례제어밸브
	 * 	[7] : Spare01
	 */
	for(uint8_t i = 0; i < 8; i++)
	{
		Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[i] = HILS.HILS_Input.LWS_C_HILS_AI[i];
	}

	/*
	 * [0] : HILS 모드 동작 시작
	 * [1] : HILS 모드 동작 종료
	 * [2] : 동작조건 변경 - 변경이 있을때 Trig 형태
	 * [3] : 명령 Spare
	 */
	for(uint8_t i = 0; i < 4; i++)
	{
		Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsCmd[i] = HILS.HILS_Input.LWS_C_HILS_Cmd[i];
	}

	/*
	 * [0] : 필터막힘스위치(리턴) 출력 설정
	 * [1] : 필터막힘스위치(부스터펌프) 출력 설정
	 * [2] : 필터막힘스위치(윈치구동) 출력 설정
	 * [3] : 필터막힘스위치(투인양) 출력 설정
	 * [4] : 권선 근접센서(우측A_후방) 출력 설정
	 * [5] : 권선 근접센서(우측B_전방) 출력 설정
	 * [6] : 권선 근접센서(좌측A_후방) 출력 설정
	 * [7] : 권선 근접센서(좌측B_전방) 출력 설정
	 * [8] : 5회전 감지스위치 출력 설정
	 * [9] : 비례제어밸브 에러(윈치구동) 출력 설정
	 * [10] : 비례제어밸브 에러(권선구동) 출력 설정
	 * [11] : 비례제어밸브 에러(비상구동) 출력 설정
	 * [12] : 비례제어밸브 에러(우측주실린더) 출력 설정
	 * [13] : 비례제어밸브 에러(좌측주실린더) 출력 설정
	 * [14] : 비례제어밸브 에러(우측보조실린더) 출력 설정
	 * [15] : 비례제어밸브 에러(좌측보조실린더) 출력 설정
	 * [16] : 압력스위치(압력초과) 발생 출력 설정
	 * [17] : Spare
	 */
	for(uint8_t i = 0; i < 18; i++)
	{
		Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[i] = HILS.HILS_Input.LWS_C_HILS_OUTSET[i];
	}

	/*
	 * [0] : 윈치드럼 엔코더 초기 각도
	 * [1] : 권선정렬 엔코더 초기 각도
	 * [2] : 주실린더#1 초기 위치
	 * [3] : 주실린더#2 초기 위치
	 * [4] : 보조실린더#1 초기 위치
	 * [5] : 보조실린더#2 초기 위치
	 * [6] : 윈치동력 기준압력
	 * [7] : 투인양동력 기준압력
	 * [8] : 유량계 기준 유량
	 * [9] : 장력센서 설정장력
	 * [10] : 주실린더 팽창 기준압력
	 * [11] : 주실린더 수축 기준압력
	 * [12] : 보조실린더 팽창 기준압력
	 * [13] : 보조실린더 수축 기준압력
	 * [14] : Spare01
	 * [15] : Spare02
	 * [16] : Spare03
	 * [17] : Spare04
	 * [18] : Spare05
	 * [19] : Spare06
	 */
	for(uint8_t i = 0; i < 20; i++)
	{
		Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[i] = HILS.HILS_Input.LWS_C_HILS_PARA[i];
	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_HILS_Output_Routine(void)
{
	/*
	 *
	 */
	for(uint8_t i = 0; i < 19; i++)
	{
		HILS.HILS_Output.HILS_DO_Int[i] = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[i];
	}

	for(uint8_t i = 0; i < 27; i++)
	{
		HILS.HILS_Output.HILS_AO_Float[i] = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[i];
	}

	for(uint8_t i = 0; i < 15; i++)
	{
		HILS.HILS_Output.HILS_Monitoring[i] = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[i];
	}

	// 랠뷰 모니터링 변수 매칭
	Control.LWS_C_HILS[0] = HILS.HILS_Output.HILS_Monitoring[1];
	Control.LWS_C_HILS[1] = HILS.HILS_Output.HILS_Monitoring[3];
	Control.LWS_C_HILS[2] = HILS.HILS_Output.HILS_Monitoring[4];
	Control.LWS_C_HILS[3] = HILS.HILS_Output.HILS_Monitoring[5];
	Control.LWS_C_HILS[4] = HILS.HILS_Output.HILS_Monitoring[6];
	Control.LWS_C_HILS[5] = HILS.HILS_Output.HILS_Monitoring[7];
	Control.LWS_C_HILS[6] = HILS.HILS_Output.HILS_Monitoring[8];
	Control.LWS_C_HILS[7] = HILS.HILS_Output.HILS_Monitoring[9];
	Control.LWS_C_HILS[8] = HILS.HILS_Output.HILS_Monitoring[10];
	Control.LWS_C_HILS[9] = HILS.HILS_Output.HILS_Monitoring[11];

	HILS.HILS_Output.HILS_Mode = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMode;

	Control.Mode.LWS_C_Mode &= 0xff00;
	Control.Mode.LWS_C_Mode |= HILS.HILS_Output.HILS_Mode & 0xff;

	HILS.HILS_Output.HILS_Status = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsStatus;

	Control.Status_02.LWS_C_Status = HILS.HILS_Output.HILS_Status;

	HILS.HILS_Output.HILS_Error = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsError;

	HILS.HILS_Output.HILS_Alarm = Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAlarm;
}


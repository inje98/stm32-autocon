/*
 * RS485.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef RS485_RS485_H_
#define RS485_RS485_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define SEL_485_1_DE()			HAL_GPIO_WritePin(SEL_485_1_GPIO_Port, SEL_485_1_Pin, GPIO_PIN_SET)
#define SEL_485_1_RE()			HAL_GPIO_WritePin(SEL_485_1_GPIO_Port, SEL_485_1_Pin, GPIO_PIN_RESET)

#define RECEIVE_OK						(1)
#define RECEIVE_NONE					(0)

#define TX_BUF_LENGTH					(300)
#define RX_BUF_LENGTH					(300)

#define CHECK_NG						(0)
#define CHECK_OK						(1)

// FRAME
#define FRAME_STX						(0x7E)
#define FRAME_ETX						(0xE7)
#define FRAME_CONTROL					(0x80)
#define ENCODE_XOR						(0x80)

// MSG_ID
#define MSG_SYS_CMD						(0x01)			// GUI --> 제어기 동작명령
#define MSG_SYS_DATAREQ					(0x02)			// GUI --> 제어기 DATA(상태값, 온도, etc.) 요구 명령
#define MSG_SYS_PARAREQ					(0x03)			// GUI --> 제어기 PARA(게인, 설정, etc.) 요구 명령
#define MSG_CTRL_REP					(0x04)			// 제어기 --> GUI, 명령에 대한 응답
#define MSG_CTRL_DATA					(0x05)			// 제어기 --> GUI, 요청 DATA 응답
#define MSG_CTRL_PARA					(0x06)			// 제어기 --> GUI, 요청 PARA 응답

// TX_ID / RX_ID
#define LWS_GUI							(0x10)
#define LWS_CTLR_A						(0x20)
//#define LWS_CTLR_B					(0x30)
//#define MWS_GUI						(0x50)
//#define MWS_CTRL						(0x60)

// Protocol	FW -> GUI
#define F_HEAD_SIZE						(8)
#define F_STX							(0)
#define F_MSG_ID						(1)
#define F_TX_ID							(2)
#define F_RX_ID							(3)
#define F_CMD_CODE						(4)
#define F_DATA_LEN_0					(5)
#define F_DATA_LEN_1					(6)
#define F_SEQ_NO						(7)
#define F_DATA							(8)

// CMD CODE
// RX
#define DATA_RESPONSE					(100)
#define PARA_RESPONSE					(101)
#define CONTROL_ACK						(102)
#define HILS_INIT_RESPONSE				(103)

// TX
#define DATA_REQUEST					(1)
#define PARAMETER_REQUEST				(2)
#define PARAMETER_WRITE					(3)
#define HILS_START_STOP					(4)
#define HILS_INIT_READ					(5)
#define HILS_INIT_WRITE					(6)
#define HILS_OUTPUT_SET					(7)
#define GRIPPER_OUTPUT_SET				(8)
#define OIL_OUTPUT_SET					(9)
#define CUTTER_OUTPUT_SET				(10)
#define CLEANER_OUTPUT_SET				(11)
#define EMERGENCY_STOP_OUTPUT_SET		(12)

// DATA REQUEST //
//FW -> GUI
#define CR_DATA_SIZE	 				(118)		// 16Bit * 1 - MODE
													// 16Bit * 2 - STATUS 01
													// 16Bit * 2 - STATUS 02
													// 16Bit * 1 - ERROR
													// 16Bit * 2 - IN CH
													// 16Bit * 6 - OUT CH
													// 16Bit * (42 * 2) - Float - 32bit
													// 16Bit * (10 * 2) - Float - 32bit
// GUI -> FW
//#define RC_DATA_SIZE	 				(8)			// 16Bit *

// PARAMETER REQUEST //
#define CR_PARA_SIZE	 				(20)		// 16Bit * (65) - Float - 32bit

// GUI -> FW
//#define RC_PARA_SIZE	 				(8)			// 16Bit *

// HILS Init read //
#define CR_HINIT_SIZE	 				(14)		// 16Bit * (14) - Float - 32bit

// GUI -> FW
//#define RC_HINIT_SIZE	 				(8)			// 16Bit *

// ACK //
#define CR_CTR_ACK_SIZE	 				(2)			// 16Bit * (2) - 32bit

// GUI -> FW
//#define RC_CTR_ACK_SIZE	 			(8)			// 16Bit *

// HILS 시작 종료
#define HILS_STOP						(0)
#define HILS_START						(1)

// HILS 초기값 저장 버퍼
#define HILS_WRITE_LENGTH				(18)


#define HILS_OUTPUT_UC_Int_LENGTH		(19)		// HILS 출력 강제 설정
// [0]: 압력스위치(부스터)
// [1]: 압력스위치(투인양동력)
// [2]: 압력스위치(압력초과)
// [3]: 압력스위치(감김)
// [4]: 압력스위치(풀림)
// [5]: 압력스위치(권선)
// [6]: 필터막힘스위치(부스터펌프)
// [7]: 필터막힘스위치(윈치구동)
// [8]: 필터막힘스위치(윈치구동)
// [9]: 필터막힘스위치(투인양)
// [10]: 권선 근접센서(우측A)
// [11]: 권선 근접센서(우측B)
// [12]: 권선 근접센서(좌측A)
// [13]: 권선 근접센서(좌측B)
// [14]: 5회전 감지스위치
// [15]: 압력스위치(권서브레이크)
// [16]: 압력스위치(주브레이크)
// [17]: 압력스위치(보조브레이크)
// [18]: 비례밸브 에러(드럼구동)

#define HILS_OUTPUT_UC_Float_LENGTH		(27)		// HILS 출력 강제 설정
// [0]: 압력변환기(윈치동력)
// [1]: 압력변환기(투인양동력)
// [2]: 유량계(투인양동력)
// [3]: 비례밸브 에러(비상구동)
// [4]: 윈치드럼 각도(엔코더)
// [5]: 권선정렬 각도(엔코더)
// [6]: 비례밸브 에러(권선구동)
// [7]: 드럼 유압모터 A 속도
// [8]: 드럼 유압모터 B 속도
// [9]: 권선 유압모터 속도
// [10]: 장력센서 출력
// [11]: 압력변환기(메인실린더#1 팽창)
// [12]: 압력변환기(메인실린더#1 수축)
// [13]: LVDT(메인실린더#1)
// [14]: 비례밸브 에러(메인실린더#2)
// [15]: 압력변환기(메인실린더#2 팽창)
// [16]: 압력변환기(메인실린더#2 수축)
// [17]: LVDT(메인실린더#2)
// [18]: 비례밸브 에러(메인실린더#2)
// [19]: 압력변환기(보조실린더#1 팽창)
// [20]: 압력변환기(보조실린더#1 수축)
// [21]: LVDT(보조실린더#1)
// [22]: 비례밸브 에러(보조실린더#1)
// [23]: 압력변환기(보조실린더#2 팽창)
// [24]: 압력변환기(보조실린더#2 수축)
// [25]: LVDT(보조실린더#2)
// [26]: 비례밸브 에러(보조실린더#2)

//수신된 Data의 Parameter 저장
#define PARAMETER_WRITE_LENGTH			(20)
/* Private variables ---------------------------------------------------------*/
typedef struct
{
	float HILS_UC_Output_Float[HILS_OUTPUT_UC_Float_LENGTH];	//HILS 강제 출력
	uint8_t HILS_UC_Output_Int[HILS_OUTPUT_UC_Int_LENGTH];		//HILS 강제 출력
	float Gripper_Output_Float[3];						//그리퍼센서 출력설정
	uint8_t Gripper_Output_Int[6];						//그리퍼센서 출력설정
	float Oil_Output_Float;								//저유기센서 출력설정
	uint8_t Oil_Output_Int[4];							//저유기센서 출력설정
	float Cutter_Output_Float[8];						//절단기센서 출력설정
	uint8_t Cutter_Output_Int[8];						//절단기센서 출력설정
	uint8_t Cleaner_Output_Int[8];						//세척기센서 출력설정
	uint8_t Emergency_Output_Int[8];					//비상정지 출력설정

	uint8_t Uart7_Rx_Check_Flag;						//수신 완료 체크 플레그
	uint8_t Uart7_Rcv_Cplt_Flag;						//RS485 수신 완료 플레그

	uint8_t Uart7_Rx_IT_Buffer;							//RS485 인터럽트 수신 버퍼
	uint8_t Uart7_Rx_Buffer[RX_BUF_LENGTH];				//RS485 수신 버퍼
	uint8_t Uart7_Tx_Buffer[TX_BUF_LENGTH];				//RS485 송신 버퍼
	uint8_t Uart7_Data_Buffer[TX_BUF_LENGTH];			//RS485 Data 버퍼
	float LwsA_Parameter[PARAMETER_WRITE_LENGTH];		//Parameter 저장 버퍼
	uint8_t LwsA_HILS_Init_Value[HILS_WRITE_LENGTH];		//HILS 초기값 저장 버퍼

	uint16_t Uart7_Tx_Data_Length;						//수신된 데이터 길이
	uint16_t Uart7_Rx_Data_Length;						//수신된 데이터 길이
	uint16_t Uart7_Rx_Frame_Length;						//수신된 버퍼 길이

	uint8_t Uart7_Rx_Cnt;								//RS485 수신 버퍼 카운트
	uint16_t Uart7_Tx_Cnt;								//RS485 송신 버퍼 카운트

	//Data 요청
	uint8_t Uart7_Data_SEQ_Num;							// SEQ NO.
	uint8_t Uart7_Parameter_SEQ_Num;					// SEQ NO.
	uint8_t Uart7_HILS_Init_SEQ_Num;					// SEQ NO.
	uint8_t Uart7_Ack_SEQ_Num;							// SEQ NO.

	//HILS Start/Stop 결정 Cmd
	uint8_t HILS_Start_Stop_Cmd;
} _RS485;
extern _RS485 RS485;


/* Private function prototypes -----------------------------------------------*/
void FUN_RS485_Init(void);
void FUN_RS485_Rx_Data_Save(void);
uint8_t FUN_RS485_Ctrl_hils_action_U1(void);

#endif /* RS485_RS485_H_ */

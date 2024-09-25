/*
 * RS485.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/* Includes ------------------------------------------------------------------*/
#include "RS485.h"
#include "main.h"
#include "string.h"
#include "..\LED\LED.h"
#include "..\GPIO\GPO.h"
#include "..\DAC\DAC.h"
#include "..\ADC\ADC.h"
#include "..\TIM\TIM.h"
#include "..\Control\Control.h"
#include "..\HILS\HILS.h"
#include "..\EEPROM\EEPROM.h"

/* Private variables ---------------------------------------------------------*/
_RS485 RS485;
extern UART_HandleTypeDef huart7;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim7;

/* Private function prototypes -----------------------------------------------*/
void FUN_RS485_Rx_Data_Check(void);
void FUN_RS485_Rx_Buffer_Reset(void);
void FUN_RS485_Parameter_Reset(void);
void FUN_RS485_Rx_Data_Process(void);
void FUN_RS485_Process_Buffer_Init(void);
void Fun_RS485_Rx_Buffer_Init(void);
void Fun_RS485_Rx_Frame_Process(uint16_t Data_Size);
void Fun_RS485_Parameter_Write(uint8_t *Buffer);
void Fun_RS485_HILS_Start_Stop(uint8_t *Buffer);
void Fun_RS485_HILS_Init_Read(void);
void Fun_RS485_HILS_Init_Write(uint8_t *Buffer);
void Fun_RS485_HILS_Output_Set(uint8_t *Buffer);
void Fun_RS485_Gripper_Output_Set(uint8_t *Buffer);
void Fun_RS485_Oil_Output_Set(uint8_t *Buffer);
void Fun_RS485_Cutter_Output_Set(uint8_t *Buffer);
void Fun_RS485_Cleaner_Output_Set(uint8_t *Buffer);
void Fun_RS485_Emergency_Output_Set(uint8_t *Buffer);
void Fun_RS485_Response_ACK(void);
void Fun_RS485_Data_Response(void);
void Fun_RS485_Convert_Float_To_UC(uint8_t *Tx_Buffer ,uint8_t *Dummy_Int);
void Fun_RS485_Parameter_Read(void);
void Fun_RS485_Transmit_Await(uint8_t *Data, uint16_t Size);

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Init(void)
{
	//RS485 변수 초기화
	FUN_RS485_Parameter_Reset();

	SEL_485_1_RE();												// RS485 수신 모드
	HAL_UART_Receive_IT(&huart7, &RS485.Uart7_Rx_IT_Buffer, 1);	// Receive Interrupt 대기
}
/****************************************************************************/
/*	Overview	:	RS485 Parameter Reset									*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Parameter_Reset(void)
{
	for(uint8_t i = 0; i< HILS_OUTPUT_UC_Float_LENGTH; i++)
	{
		RS485.HILS_UC_Output_Float[i] = 0;
	}
	for(uint8_t i = 0; i< HILS_OUTPUT_UC_Int_LENGTH; i++)
	{
		RS485.HILS_UC_Output_Int[i] = 0;
	}
	for(uint8_t i = 0; i< 8; i++)
	{
		RS485.Cutter_Output_Float[i] = 0;
		RS485.Cutter_Output_Int[i] = 0;
		RS485.Cleaner_Output_Int[i] = 0;
		RS485.Gripper_Output_Float[i] = 0;
		RS485.Emergency_Output_Int[i] = 0;
	}
	for(uint8_t i = 0; i< 6; i++)
	{
		RS485.Gripper_Output_Int[i] = 0;
	}
	for(uint8_t i = 0; i< 4; i++)
	{
		RS485.Oil_Output_Int[i] = 0;
	}
	for(uint16_t i = 0; i< RX_BUF_LENGTH; i++)
	{
		RS485.Uart7_Rx_Buffer[i] = 0;
	}
	for(uint16_t i = 0; i< TX_BUF_LENGTH; i++)
	{
		RS485.Uart7_Tx_Buffer[i] = 0;
		RS485.Uart7_Data_Buffer[i] = 0;
	}
	for(uint8_t i = 0; i< PARAMETER_WRITE_LENGTH; i++)
	{
//		RS485.LwsA_Parameter[i] = 0;
	}
	for(uint8_t i = 0; i< HILS_WRITE_LENGTH; i++)
	{
		RS485.LwsA_HILS_Init_Value[i] = 0;
	}

	RS485.Oil_Output_Float = 0;
	RS485.Uart7_Rx_Check_Flag = 0;
	RS485.Uart7_Rcv_Cplt_Flag = 0;
	RS485.Uart7_Rx_IT_Buffer = 0;

	RS485.Uart7_Rx_Data_Length = 0;						//수신된 데이터 길이
	RS485.Uart7_Rx_Frame_Length = 0;					//수신된 버퍼 길이

	RS485.Uart7_Rx_Cnt = 0;								//RS485 수신 버퍼 카운트
	RS485.Uart7_Tx_Cnt = 0;								//RS485 송신 버퍼 카운트

	//Data 요청
	RS485.Uart7_Data_SEQ_Num = 0;						// SEQ NO.
	RS485.Uart7_Parameter_SEQ_Num = 0;					// SEQ NO.
	RS485.Uart7_HILS_Init_SEQ_Num = 0;					// SEQ NO.
	RS485.Uart7_Ack_SEQ_Num = 0;						// SEQ NO.

	//HILS Start/Stop 결정 Cmd
	RS485.HILS_Start_Stop_Cmd = HILS_STOP;
}
/****************************************************************************/
/*	Overview	:	Rx Call Back 함수											*/
/*	Return value:	void													*/
/****************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART7)
	{
		RS485.Uart7_Rx_Buffer[RS485.Uart7_Rx_Cnt++] = RS485.Uart7_Rx_IT_Buffer;

		FUN_RS485_Rx_Data_Check();

		HAL_UART_Receive_IT(&huart7, &RS485.Uart7_Rx_IT_Buffer, 1);	// 1byte 수신시 콜백
	}
}

/****************************************************************************/
/*	Overview	:	Tx Call Back 함수											*/
/*	Return value:	void													*/
/****************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART7)
	{
		//RS485 송신 완료 후 수신 모드로 전환
		SEL_485_1_RE();
	}
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Rx_Data_Check(void)
{
	// STX 체크
	if(RS485.Uart7_Rx_Buffer[F_STX] != FRAME_STX)
	{
		FUN_RS485_Rx_Buffer_Reset();
	}

	if(RS485.Uart7_Rx_Cnt > F_MSG_ID)
	{
		if(RS485.Uart7_Rx_Buffer[F_MSG_ID] > 0x06)
		{
			FUN_RS485_Rx_Buffer_Reset();
		}
	}

	// RX ID 체크
	if(RS485.Uart7_Rx_Cnt > F_RX_ID)
	{
		if(RS485.Uart7_Rx_Buffer[F_RX_ID] != LWS_CTLR_A)
		{
			FUN_RS485_Rx_Buffer_Reset();
		}
	}

	// LENGTH 계산
	if(RS485.Uart7_Rx_Cnt > F_DATA_LEN_1)
	{
		RS485.Uart7_Rx_Check_Flag = 1;
		RS485.Uart7_Rx_Data_Length = ((uint16_t)RS485.Uart7_Rx_Buffer[F_DATA_LEN_0]) << 8;
		RS485.Uart7_Rx_Data_Length |= ((uint16_t)RS485.Uart7_Rx_Buffer[F_DATA_LEN_1]);
		RS485.Uart7_Rx_Frame_Length = F_HEAD_SIZE + RS485.Uart7_Rx_Data_Length + 2;		// Head(8) + Data + Checksum + ETX
	}

	// ETX 체크
	if(RS485.Uart7_Rx_Check_Flag == 1)
	{
		if(RS485.Uart7_Rx_Cnt == RS485.Uart7_Rx_Frame_Length)
		{
			RS485.Uart7_Rx_Check_Flag = 0;
			if(RS485.Uart7_Rx_Buffer[RS485.Uart7_Rx_Cnt - 1] == FRAME_ETX)
			{
				RS485.Uart7_Rcv_Cplt_Flag = 1;
			}
		}

		if(RS485.Uart7_Rx_Cnt > RS485.Uart7_Rx_Frame_Length)
		{
			RS485.Uart7_Rx_Check_Flag = 0;
			FUN_RS485_Rx_Buffer_Reset();
		}
	}
}

/****************************************************************************/
/*	Overview	:	Rx Data Error시 Buffer Reset								*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Rx_Buffer_Reset(void)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		RS485.Uart7_Rx_Buffer[i] = 0;
	}
	RS485.Uart7_Rx_Cnt = 0;
}

/****************************************************************************/
/*	Overview	:	수신된 데이터 저장(FUN_Control_Routine 부분)					*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Rx_Data_Save(void)
{
	if(RS485.Uart7_Rcv_Cplt_Flag == 1)
	{
		RS485.Uart7_Rcv_Cplt_Flag = 0;

		FUN_RS485_Rx_Data_Process();
	}

	// Interrupt Error시에 강제 초기화, Uart Register참고
	if((huart7.Instance->CR3 & 0x0001) == 0x0001)
	{
		(huart7.Instance->CR3)^=1;
	}
}

/****************************************************************************/
/*	Overview	:	수신 데이터 처리												*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Rx_Data_Process(void)
{
	FUN_RS485_Process_Buffer_Init();

	memcpy(RS485.Uart7_Data_Buffer, RS485.Uart7_Rx_Buffer, RS485.Uart7_Rx_Frame_Length);

	Fun_RS485_Rx_Buffer_Init();

	Fun_RS485_Rx_Frame_Process(RS485.Uart7_Rx_Frame_Length);
}

/****************************************************************************/
/*	Overview	:	데이터 처리 버퍼 초기화										*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Process_Buffer_Init(void)
{
	for(volatile uint16_t i = 0; i < RX_BUF_LENGTH; i++)
	{
		RS485.Uart7_Data_Buffer[i] = 0;
	}
}

/****************************************************************************/
/*	Overview	:	수신 버퍼 초기화												*/
/*	Return value:	void													*/
/****************************************************************************/
void Fun_RS485_Rx_Buffer_Init(void)
{
	for(volatile uint16_t i = 0; i < RX_BUF_LENGTH; i++)
	{
		RS485.Uart7_Rx_Buffer[i] = 0;
	}
	RS485.Uart7_Rx_Cnt = 0;
}

/****************************************************************************/
/*	Overview	:	수신 데이터 처리												*/
/*	Return value:	void													*/
/****************************************************************************/
void Fun_RS485_Rx_Frame_Process(uint16_t Data_Size)
{
	uint8_t Check_Sum = 0;
	uint8_t MSG_Id = 0;
	uint8_t Cmd_Code = 0;

	LED.GUI_Check_Cnt = 0;

	// Send Checksum data = 1부터 size-2까지 (Sum, Frame 제외)
	// Received Checksum data = 1부터 size-2까지 Sum
	for(uint16_t i = 1; i < Data_Size - 2; i++)
	{
		Check_Sum = Check_Sum + RS485.Uart7_Data_Buffer[i];
	}

	// Check SUM OK
	if((Check_Sum & 0xFF) == RS485.Uart7_Data_Buffer[Data_Size - 2])
	{
		// MSG ID 체크
		MSG_Id = RS485.Uart7_Data_Buffer[F_MSG_ID];

		// Cmd Code 체크
		Cmd_Code = RS485.Uart7_Data_Buffer[F_CMD_CODE];

		switch(MSG_Id)
		{
			// HILS 연동
			case MSG_SYS_CMD:
				// CMD CODE로 구분
				switch(Cmd_Code)
				{
//					// 파라미터 읽기
//					case MSG_SYS_PARAREQ:
//						Fun_RS485_Parameter_Read();
//					break;
					// PARAMETER 쓰기
					case PARAMETER_WRITE:
						Fun_RS485_Parameter_Write(RS485.Uart7_Data_Buffer);
						break;
					// HILS 연동 시작 종료
					case HILS_START_STOP:
						Fun_RS485_HILS_Start_Stop(RS485.Uart7_Data_Buffer);
						break;
					// HILS 초기값 읽기
					case HILS_INIT_READ:
						Fun_RS485_HILS_Init_Read();
						break;
					// HILS 초기값 쓰기
					case HILS_INIT_WRITE:
						Fun_RS485_HILS_Init_Write(RS485.Uart7_Data_Buffer);
						break;
					// HILS 초기값 강제 출력
					case HILS_OUTPUT_SET:
						Fun_RS485_HILS_Output_Set(RS485.Uart7_Data_Buffer);
						break;
					// 그립퍼 센서 출력값 설정
					case GRIPPER_OUTPUT_SET:
						Fun_RS485_Gripper_Output_Set(RS485.Uart7_Data_Buffer);
						break;
					// 저유기센서 출력값 설정
					case OIL_OUTPUT_SET:
						Fun_RS485_Oil_Output_Set(RS485.Uart7_Data_Buffer);
						break;
					// 절단기센서 출력값 설정
					case CUTTER_OUTPUT_SET:
						Fun_RS485_Cutter_Output_Set(RS485.Uart7_Data_Buffer);
						break;
					// 세척기 센서 출력값 설정
					case CLEANER_OUTPUT_SET:
						Fun_RS485_Cleaner_Output_Set(RS485.Uart7_Data_Buffer);
						break;
					// 비상정지스위치 출력값 설정
					case EMERGENCY_STOP_OUTPUT_SET:
						Fun_RS485_Emergency_Output_Set(RS485.Uart7_Data_Buffer);
						break;
					default:
						break;
				}
			// 데이터 요청
			case MSG_SYS_DATAREQ:
				Fun_RS485_Data_Response();
				break;
			// 파라미터 읽기
			case MSG_SYS_PARAREQ:
				Fun_RS485_Parameter_Read();
				break;
			default:
				break;
		}
	}
}

/****************************************************************************/
/*	Overview	:	Parameter 쓰기											*/
/*	Return value:	HILS_INIT_WRITE											*/
/****************************************************************************/
void Fun_RS485_Parameter_Write(uint8_t *Buffer)
{
	uint32_t Dummy_Int = 0;
	float *Dummy_Float;

	for(uint8_t i = 0; i < PARAMETER_WRITE_LENGTH; i++)			// 65EA
	{
		Dummy_Int = ((uint32_t)Buffer[F_DATA+7 + (i * 4)] << 24) & 0xFF000000;
		Dummy_Int |= ((uint32_t)Buffer[F_DATA+7 + (i * 4) + 1] << 16) & 0x00FF0000;
		Dummy_Int |= ((uint32_t)Buffer[F_DATA+7 + (i * 4) + 2] << 8) & 0x0000FF00;
		Dummy_Int |= (uint32_t)Buffer[F_DATA+7 + (i * 4) + 3] & 0x000000FF;

		Dummy_Float = (float * ) & Dummy_Int;

		RS485.LwsA_Parameter[i] = *Dummy_Float;
	}

	EEPROM.EEPROM_Save_Flag = 1;

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	HILS 연동 시작 종료 결정 Cmd									*/
/*	Return value:	void													*/
/****************************************************************************/
void Fun_RS485_HILS_Start_Stop(uint8_t *Buffer)
{
	// HILS 초기 구동을 위해 강제 OFF
	FUN_GPO_Output(OUTPUT_PORT_NUM_4, 0);					// 비상정지신호 동력공급장치
	FUN_GPO_Output(OUTPUT_PORT_NUM_25, 0);					// 비상정지신호 윈치조립체
	FUN_GPO_Output(OUTPUT_PORT_NUM_43,	0);					// 투인양장치 : 압력스위치(세척기)
	FUN_GPO_Output(OUTPUT_PORT_NUM_10,	0);					// 동력공급장치 : 압력스위치(축압기 부족1)
	FUN_GPO_Output(OUTPUT_PORT_NUM_11,	0);					// 동력공급장치 : 압력스위치(축압기 부족2)
	FUN_GPO_Output(OUTPUT_PORT_NUM_12,	0);					// 동력공급장치 : 압력스위치(축압기 충전완료)
	FUN_GPO_Output(OUTPUT_PORT_NUM_8,	0);					// 동력공급장치 : 압력스위치(수냉식냉각기)
	FUN_GPO_Output(OUTPUT_PORT_NUM_1,	0);					// 동력공급장치 : 레벨스위치1(저유기조립체)
	FUN_GPO_Output(OUTPUT_PORT_NUM_2,	0);					// 동력공급장치 : 레벨스위치2(저유기조립체)
	FUN_GPO_Output(OUTPUT_PORT_NUM_3,	0);					// 동력공급장치 : 레벨스위치3(저유기조립체)
	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH7, 12);	//그림퍼 LVDT1
	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH2, 12);	//그림퍼 LVDT2
	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH4, 12);	//그림퍼 LVDT3
	FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH2, 6);	//저유기 온도센서
	RS485.HILS_Start_Stop_Cmd = (uint8_t)Buffer[8] & 0xFF;

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	HILS 초기값 읽기											*/
/*	Return value:	HILS_INIT_READ											*/
/****************************************************************************/
void Fun_RS485_HILS_Init_Read(void)
{
	//Checksum 이전까지 Tx Buffer 크기
	uint16_t Size = 0;
	//최종 Tx Buffer 크기
	uint16_t Count = 0;
	uint16_t Check_Sum = 0;
	uint8_t Tx_Buffer[TX_BUF_LENGTH];

	// SEQ_NO (1 ~ 100)
	if(RS485.Uart7_HILS_Init_SEQ_Num == 100)
	{
		RS485.Uart7_HILS_Init_SEQ_Num = 0;
	}
	Tx_Buffer[F_SEQ_NO] = ++RS485.Uart7_HILS_Init_SEQ_Num;

	// MSG_ID{
	Tx_Buffer[F_MSG_ID] = MSG_CTRL_REP;
	// TX ID
	Tx_Buffer[F_TX_ID] = LWS_CTLR_A;
	// RX_ID
	Tx_Buffer[F_RX_ID] = LWS_GUI;
	// CMD CODE
	Tx_Buffer[F_CMD_CODE] = HILS_INIT_RESPONSE;
	// DATA_LEN
	Tx_Buffer[F_DATA_LEN_0] = (uint8_t)((CR_HINIT_SIZE * 4) >> 8);
	Tx_Buffer[F_DATA_LEN_1] = (uint8_t)((CR_HINIT_SIZE * 4) & 0xFF);

	uint32_t *buf = (uint32_t *)&RS485.LwsA_HILS_Init_Value;

	for(uint16_t i = 0; i < CR_HINIT_SIZE; i++)
	{
		Tx_Buffer[F_HEAD_SIZE + i*4]	= (uint8_t)( (*(buf + i) >> 24) & 0xFF );
		Tx_Buffer[F_HEAD_SIZE + i*4 + 1]	= (uint8_t)( (*(buf + i) >> 16) & 0xFF );
		Tx_Buffer[F_HEAD_SIZE + i*4 + 2]	= (uint8_t)( (*(buf + i) >> 8) & 0xFF );
		Tx_Buffer[F_HEAD_SIZE + i*4 + 3]	= (uint8_t)( *(buf + i) & 0xFF );
	}
	//ETX, Checksum을 제외한 크기
	Size = CR_HINIT_SIZE * 4 + F_HEAD_SIZE;

	// CHECK SUM
	Count = 1;	//STX는 Checksum에서 건너뛰기
	for(uint16_t i = 1; i < Size; i++)
	{
		Check_Sum += Tx_Buffer[i];
		Count++;
	}
	Tx_Buffer[Count] = Check_Sum & 0xFF;
	Count++;

    // STX
	Tx_Buffer[F_STX] = FRAME_STX;

    // ETX
	Tx_Buffer[Count++] = FRAME_ETX;

	Size = Count;

	Fun_RS485_Transmit_Await(Tx_Buffer ,Count);
}

/****************************************************************************/
/*	Overview	:	데이터 전송 + 수신 대기										*/
/*	Return value:	void													*/
/****************************************************************************/
void Fun_RS485_Transmit_Await(uint8_t *Data, uint16_t Size)
{
	for(volatile uint16_t i = 0; i < TX_BUF_LENGTH; i++)
	{
		RS485.Uart7_Tx_Buffer[i] = Data[i];
	}

	//RS485 송신모드
	SEL_485_1_DE();

	HAL_UART_Transmit_DMA(&huart7, RS485.Uart7_Tx_Buffer, Size);

//	HAL_UART_Transmit(&huart7, RS485.Uart7_Tx_Buffer, Size, 100);
}

/****************************************************************************/
/*	Overview	:	HILS 초기값 쓰기											*/
/*	Return value:	HILS_INIT_WRITE											*/
/****************************************************************************/
void Fun_RS485_HILS_Init_Write(uint8_t *Buffer)
{
	for(uint8_t i = 0; i < HILS_WRITE_LENGTH; i++)				// 18EA
	{
		RS485.LwsA_HILS_Init_Value[i] = Buffer[F_DATA + i];
	}

	HILS.HILS_Input.HILS_Change_Flag = 1;

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	HILS 초기값 강제 출력										*/
/*	Return value:	HILS_OUTPUT_VALUE										*/
/****************************************************************************/
void Fun_RS485_HILS_Output_Set(uint8_t *Buffer)
{
	uint32_t Dummy_Int = 0;
	float *Dummy_Float;

	for(uint8_t i = 0; i < HILS_OUTPUT_UC_Int_LENGTH; i++)				// 19EA
	{
		RS485.HILS_UC_Output_Int[i] = Buffer[F_DATA + i];
	}

	for(uint8_t i = 0; i < HILS_OUTPUT_UC_Float_LENGTH; i++)				// 27EA
	{
		Dummy_Int = ((uint32_t)Buffer[F_DATA + HILS_OUTPUT_UC_Int_LENGTH + (i * 4)] << 24) & 0xFF000000;
		Dummy_Int |= ((uint32_t)Buffer[F_DATA + HILS_OUTPUT_UC_Int_LENGTH + (i * 4) + 1] << 16) & 0x00FF0000;
		Dummy_Int |= ((uint32_t)Buffer[F_DATA + HILS_OUTPUT_UC_Int_LENGTH + (i * 4) + 2] << 8) & 0x0000FF00;
		Dummy_Int |= (uint32_t)Buffer[F_DATA + HILS_OUTPUT_UC_Int_LENGTH + (i * 4) + 3] & 0x000000FF;

		Dummy_Float = (float * )&Dummy_Int;

		RS485.HILS_UC_Output_Float[i] = *Dummy_Float;
	}

	//Winch_A 출력 제어
	if(RS485.HILS_UC_Output_Float[7] > 0)		//A
	{
		OUTPUT_CH_31_LOW();						// 방향제어
		FUN_Frequency_Ctrl(Winch_A_SPEED, RS485.HILS_UC_Output_Float[7]*3.45);
	}
	else if(RS485.HILS_UC_Output_Float[7] == 0)
	{
		HAL_TIM_Base_DeInit(&htim4);
		OUTPUT_CH_31_HIGH();
		OUTPUT_CH_32_HIGH();
	}
	else if(RS485.HILS_UC_Output_Float[7] < 0)
	{
		OUTPUT_CH_31_HIGH();					// 방향제어
		FUN_Frequency_Ctrl(Winch_A_SPEED, -(RS485.HILS_UC_Output_Float[7]*3.45));
	}

	//Winch_B 출력 제어
	if(RS485.HILS_UC_Output_Float[8] > 0)		//B
	{
		OUTPUT_CH_33_LOW();						// 방향제어
		FUN_Frequency_Ctrl(Winch_B_SPEED, RS485.HILS_UC_Output_Float[8]*3.45);
	}
	else if(RS485.HILS_UC_Output_Float[8] == 0)
	{
		HAL_TIM_Base_DeInit(&htim5);
		OUTPUT_CH_33_HIGH();
		OUTPUT_CH_34_HIGH();
	}
	else if(RS485.HILS_UC_Output_Float[8] < 0)
	{
		OUTPUT_CH_33_HIGH();					// 방향제어
		FUN_Frequency_Ctrl(Winch_B_SPEED, -(RS485.HILS_UC_Output_Float[8]*3.45));
	}

	//Align 출력제어
	if(RS485.HILS_UC_Output_Float[9] > 0)		//권선
	{
		OUTPUT_CH_29_LOW();						// 방향제어
		FUN_Frequency_Ctrl(Align_SPEED, RS485.HILS_UC_Output_Float[9]);
	}
	else if(RS485.HILS_UC_Output_Float[9] == 0)
	{
		HAL_TIM_Base_DeInit(&htim7);
		OUTPUT_CH_29_HIGH();
		OUTPUT_CH_30_HIGH();
	}
	else if(RS485.HILS_UC_Output_Float[9] < 0)
	{
		OUTPUT_CH_29_HIGH();					// 방향제어
		FUN_Frequency_Ctrl(Align_SPEED, -(RS485.HILS_UC_Output_Float[9]));
	}

	Control.Float_Data.WinchDrumHydMotorASpeed =RS485.HILS_UC_Output_Float[7];
	Control.Float_Data.WinchDrumHydMotorBSpeed =RS485.HILS_UC_Output_Float[8];
	Control.Float_Data.AlignHydMotorSpeed =RS485.HILS_UC_Output_Float[9];

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	그립퍼 센서 출력값 설정										*/
/*	Return value:															*/
/****************************************************************************/
void Fun_RS485_Gripper_Output_Set(uint8_t *Buffer)
{
	uint32_t Dummy_Int = 0;
	float *Dummy_Float;

	for(uint8_t i = 0; i < 6; i++)
	{
		RS485.Gripper_Output_Int[i] = Buffer[F_DATA+i];
	}

	for(uint8_t i = 0; i < 3; i++)
	{
		Dummy_Int = ((uint32_t)Buffer[F_DATA + 6 + (i * 4)] << 24) & 0xFF000000;
		Dummy_Int |= ((uint32_t)Buffer[F_DATA + 6 + (i * 4) + 1] << 16) & 0x00FF0000;
		Dummy_Int |= ((uint32_t)Buffer[F_DATA + 6 + (i * 4) + 2] << 8) & 0x0000FF00;
		Dummy_Int |= (uint32_t)Buffer[F_DATA + 6 + (i * 4) + 3] & 0x000000FF;

		Dummy_Float = (float * )&Dummy_Int;

		RS485.Gripper_Output_Float[i] = *Dummy_Float;
	}
	FUN_GPO_Gripper();
	FUN_DAC_Converter_Gripper();

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	저유기센서 출력설정											*/
/*	Return value:															*/
/****************************************************************************/
void Fun_RS485_Oil_Output_Set(uint8_t *Buffer)				// 저유기센서 출력설정
{
	uint32_t Dummy_Int = 0;
	float *Dummy_Float;

	for(uint8_t i = 0; i < 4; i++)
	{
		RS485.Oil_Output_Int[i] = Buffer[F_DATA+i];
	}

	Dummy_Int = ((uint32_t)Buffer[F_DATA + 4 ] << 24) & 0xFF000000;
	Dummy_Int |= ((uint32_t)Buffer[F_DATA + 4 +1] << 16) & 0x00FF0000;
	Dummy_Int |= ((uint32_t)Buffer[F_DATA + 4 +2] << 8) & 0x0000FF00;
	Dummy_Int |= (uint32_t)Buffer[F_DATA + 4 +3] & 0x000000FF;

	Dummy_Float = (float * )&Dummy_Int;

	RS485.Oil_Output_Float = *Dummy_Float;

	FUN_GPO_Oil();
	FUN_DAC_Converter_Oil();

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	절단기센서 출력설정											*/
/*	Return value:															*/
/****************************************************************************/
void Fun_RS485_Cutter_Output_Set(uint8_t *Buffer)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		RS485.Cutter_Output_Int[i] = Buffer[F_DATA+i];
	}

	FUN_GPO_Cutter();

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	세척기센서 출력설정											*/
/*	Return value:															*/
/****************************************************************************/
void Fun_RS485_Cleaner_Output_Set(uint8_t *Buffer)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		RS485.Cleaner_Output_Int[i] = Buffer[F_DATA+i];
	}

	FUN_GPO_Cleaner();

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	비상정지스위치 출력설정										*/
/*	Return value:															*/
/****************************************************************************/
void Fun_RS485_Emergency_Output_Set(uint8_t *Buffer)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		RS485.Emergency_Output_Int[i] = Buffer[F_DATA+i];
	}

	FUN_GPO_Emergency();

	// ACK 응답
	Fun_RS485_Response_ACK();
}

/****************************************************************************/
/*	Overview	:	ACK 응답													*/
/*	Return value:															*/
/****************************************************************************/
void Fun_RS485_Response_ACK(void)
{
	uint16_t Size = 0;
	uint16_t Count = 0;
	uint16_t Check_Sum = 0;
	uint8_t Tx_Buffer[TX_BUF_LENGTH];

	Tx_Buffer[F_STX] = FRAME_STX;

	// SEQ_NO (1 ~ 100)
	if(RS485.Uart7_Ack_SEQ_Num == 100)
	{
		RS485.Uart7_Ack_SEQ_Num = 0;
	}
	Tx_Buffer[F_SEQ_NO] = ++RS485.Uart7_Ack_SEQ_Num;

	// DATA_LEN
	Tx_Buffer[F_DATA_LEN_0] = (uint8_t)((CR_CTR_ACK_SIZE * 4) >> 8);
	Tx_Buffer[F_DATA_LEN_1] = (uint8_t)((CR_CTR_ACK_SIZE * 4) & 0xFF);

	// MSG_ID{
	Tx_Buffer[F_MSG_ID] = MSG_CTRL_REP;
	// TX ID
	Tx_Buffer[F_TX_ID] = LWS_CTLR_A;
	// RX_ID
	Tx_Buffer[F_RX_ID] = LWS_GUI;
	// CMD CODE
	Tx_Buffer[F_CMD_CODE] = CONTROL_ACK;

	for(uint16_t i = 0; i < CR_CTR_ACK_SIZE; i++)
	{
		Tx_Buffer[F_HEAD_SIZE + i*4] 	 	= 0;
		Tx_Buffer[F_HEAD_SIZE + i*4 + 1] 	= 0;
		Tx_Buffer[F_HEAD_SIZE + i*4 + 2] 	= 0;
		Tx_Buffer[F_HEAD_SIZE + i*4 + 3] 	= 0;
	}

	Size = CR_CTR_ACK_SIZE * 4 + F_HEAD_SIZE;

	// CHECK SUM
	Count = 1;

	for(uint16_t i = 1; i < Size; i++)
	{
		Check_Sum += Tx_Buffer[i];
		Count++;
	}
	Tx_Buffer[Count] = Check_Sum & 0xff;
	Count++;

    // STX
	Tx_Buffer[F_STX] = FRAME_STX;

    // ETX
	Tx_Buffer[Count++] = FRAME_ETX;

    Size = Count;

    Fun_RS485_Transmit_Await(Tx_Buffer , Count);
}

/****************************************************************************/
/*	Overview	:	데이터 요청에 대한 응답										*/
/*	Return value:	void													*/
/****************************************************************************/
void Fun_RS485_Data_Response(void)
{
	uint16_t Size = 0;
	uint16_t Count = 0;
	uint16_t Check_Sum = 0;
	uint8_t Tx_Buffer[TX_BUF_LENGTH];
	uint8_t *Dummy_Int = 0;

	Tx_Buffer[F_STX] = FRAME_STX;

	// SEQ_NO (1 ~ 100)
	if(RS485.Uart7_Data_SEQ_Num == 100)
	{
		RS485.Uart7_Data_SEQ_Num = 0;
	}
	Tx_Buffer[F_SEQ_NO] = ++RS485.Uart7_Data_SEQ_Num;

	// DATA_LEN
	Tx_Buffer[F_DATA_LEN_0] = (uint8_t)((CR_DATA_SIZE * 2) >> 8);
	Tx_Buffer[F_DATA_LEN_1] = (uint8_t)((CR_DATA_SIZE * 2) & 0xFF);

	// MSG_ID{
	Tx_Buffer[F_MSG_ID] = MSG_CTRL_DATA;
	// TX ID
	Tx_Buffer[F_TX_ID] = LWS_CTLR_A;
	// RX_ID
	Tx_Buffer[F_RX_ID] = LWS_GUI;
	// CMD CODE
	Tx_Buffer[F_CMD_CODE] = DATA_RESPONSE;

	RS485.Uart7_Tx_Data_Length = F_HEAD_SIZE;

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Mode.LWS_C_Mode >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Mode.LWS_C_Mode;

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Status_01.LWS_C_Status >> 24);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Status_01.LWS_C_Status >> 16);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Status_01.LWS_C_Status >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Status_01.LWS_C_Status;

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Status_02.LWS_C_Status >> 24);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Status_02.LWS_C_Status >> 16);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Status_02.LWS_C_Status >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Status_02.LWS_C_Status;

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Error.LWS_C_Error >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Error.LWS_C_Error;

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Input_ch.Input_Alldata >> 24);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Input_ch.Input_Alldata >> 16);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Input_ch.Input_Alldata >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Input_ch.Input_Alldata;

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[0] >> 24);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[0] >> 16);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[0] >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Output_ch.Output_Alldata[0];

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[1] >> 24);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[1] >> 16);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[1] >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Output_ch.Output_Alldata[1];

	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[2] >> 24);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[2] >> 16);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)(Control.Output_ch.Output_Alldata[2] >> 8);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = (uint8_t)Control.Output_ch.Output_Alldata[2];

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In1_Ch2_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In1_Ch1_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In1_Ch3_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In2_Ch3_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In2_Ch4_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In2_Ch1_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In2_Ch2_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AI_ADC_In1_Ch4_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch2_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch5_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch4_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch3_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac3_Ch1_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Encoder_1;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Encoder_2;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac3_Ch0_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.WinchDrumHydMotorASpeed;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.WinchDrumHydMotorBSpeed;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AlignHydMotorSpeed;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch3_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch7_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch6_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch5_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac3_Ch2_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch9_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch8_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch0_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac3_Ch3_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch11_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch10_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch6_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac3_Ch4_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch13_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac4_Ch12_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch1_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac3_Ch5_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch7_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch2_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.Dac5_Ch4_Volt;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AO_Spare_01;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AO_Spare_02;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.Float_Data.AO_Spare_03;
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[0];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[1];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[2];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[3];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[4];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[5];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[6];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[7];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[8];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Dummy_Int = (uint8_t *)&Control.LWS_C_HILS[9];
	Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);

	Size = CR_DATA_SIZE * 2 + F_HEAD_SIZE;

	// CHECK SUM
	Count = 1;
	for(uint16_t i = 1; i < Size; i++)
	{
		Check_Sum += Tx_Buffer[i];
		Count++;
	}
	Tx_Buffer[Count] = Check_Sum & 0xff;
	Count++;

    // STX
	Tx_Buffer[F_STX] = FRAME_STX;

    // ETX
	Tx_Buffer[Count++] = FRAME_ETX;

    Size = Count;

    Fun_RS485_Transmit_Await(Tx_Buffer ,Size);

    FUN_ADC_AvgValueReset();
}

// HILS 시작, 정지 명령
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	HILS Action												*/
/****************************************************************************/
uint8_t FUN_RS485_Ctrl_hils_action_U1(void)
{
//	FUN_GPO_Output(OUTPUT_PORT_NUM_10,	1);		// 동력공급장치 : 압력스위치(축압기 부족1)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_11,	1);		// 동력공급장치 : 압력스위치(축압기 부족2)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_12,	1);		// 동력공급장치 : 압력스위치(축압기 충전완료)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_8,	1);				// 동력공급장치 : 압력스위치(수냉식냉각기)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_1,	0);				// 동력공급장치 : 레벨스위치1(저유기조립체)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_2,	0);				// 동력공급장치 : 레벨스위치2(저유기조립체)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_3,	0);				// 동력공급장치 : 레벨스위치3(저유기조립체)
//	FUN_GPO_Output(OUTPUT_PORT_NUM_43,	1);		// 투인양장치 : 압력스위치(세척기)
//	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH7, 0);
//	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH2, 0);
//	FUN_DAC_Converter_set_dac_code(DAC5_CH_SEL, DAC5_CH4, 0);
//	FUN_DAC_Converter_set_dac_code(DAC4_CH_SEL, DAC4_CH2, 10);// 동력공급장치: 온도센서(저유기조립체)
	return RS485.HILS_Start_Stop_Cmd;
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	float to UC												*/
/****************************************************************************/
void Fun_RS485_Convert_Float_To_UC(uint8_t *Tx_Buffer ,uint8_t *Dummy_Int)
{
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = *(Dummy_Int + 3);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = *(Dummy_Int + 2);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = *(Dummy_Int + 1);
	Tx_Buffer[RS485.Uart7_Tx_Data_Length++] = *(Dummy_Int + 0);
}

/****************************************************************************/
/*	Overview	:	Parameter Read											*/
/*	Return value:	void													*/
/****************************************************************************/
void Fun_RS485_Parameter_Read(void)
{
	uint16_t Size = 0;
	uint16_t Count = 0;
	uint16_t Check_Sum = 0;
	uint8_t *Dummy_Int = 0;
	uint8_t Tx_Buffer[TX_BUF_LENGTH];
//	uint32_t buf[80];

	Tx_Buffer[F_STX] = FRAME_STX;

	// SEQ_NO (1 ~ 100)
	if(RS485.Uart7_Parameter_SEQ_Num == 100)
	{
		RS485.Uart7_Parameter_SEQ_Num = 0;
	}
	Tx_Buffer[F_SEQ_NO] = ++RS485.Uart7_Parameter_SEQ_Num;

	// DATA_LEN
	Tx_Buffer[F_DATA_LEN_0] = (uint8_t)((CR_PARA_SIZE * 4) >> 8);
	Tx_Buffer[F_DATA_LEN_1] = (uint8_t)((CR_PARA_SIZE * 4) & 0xFF);

	// MSG_ID{
	Tx_Buffer[F_MSG_ID] = MSG_CTRL_PARA;
	// TX ID
	Tx_Buffer[F_TX_ID] = LWS_CTLR_A;
	// RX_ID
	Tx_Buffer[F_RX_ID] = LWS_GUI;
	// CMD CODE
	Tx_Buffer[F_CMD_CODE] = PARA_RESPONSE;

//	memcpy(buf, RS485.LwsA_Parameter, 80);
//	memcpy(buf, RS485.LwsA_Parameter, 80+156);
//	uint32_t *buf = (uint32_t *)&RS485.LwsA_Parameter;

	RS485.Uart7_Tx_Data_Length = F_HEAD_SIZE;

	// DATA
	for(uint16_t i = 0; i < CR_PARA_SIZE; i++)
	{
//		Tx_Buffer[F_HEAD_SIZE + i*4]		= (uint8_t)( ((buf[i*4]) >> 24) & 0xff000000 );
//		Tx_Buffer[F_HEAD_SIZE + i*4 + 1]	= (uint8_t)( ((buf[i*4 + 1]) >> 16) & 0x00ff0000 );
//		Tx_Buffer[F_HEAD_SIZE + i*4 + 2]	= (uint8_t)( ((buf[i*4 + 2]) >> 8) & 0x0000ff00 );
//		Tx_Buffer[F_HEAD_SIZE + i*4 + 3]	= (uint8_t)( (buf[i*4 + 3]) & 0x000000ff );

//		Tx_Buffer[F_HEAD_SIZE + ii++] = (uint8_t)(buf[i] >> 24);
//		Tx_Buffer[F_HEAD_SIZE + ii++] = (uint8_t)(buf[i] >> 16);
//		Tx_Buffer[F_HEAD_SIZE + ii++] = (uint8_t)(buf[i] >> 8);
//		Tx_Buffer[F_HEAD_SIZE + ii++] = (uint8_t)(buf[i]);

		if(i >= 16)
		{
			RS485.LwsA_Parameter[i] = 0;
		}
		Dummy_Int = (uint8_t *)&RS485.LwsA_Parameter[i];
		Fun_RS485_Convert_Float_To_UC(Tx_Buffer, Dummy_Int);
	}

	Size = CR_PARA_SIZE * 4 + F_HEAD_SIZE;

	// CHECK SUM
	Count = 1;
	for(uint16_t i = 1; i < Size; i++)
	{
		Check_Sum += Tx_Buffer[i];
		Count++;
	}
	Tx_Buffer[Count] = Check_Sum & 0xff;
	Count++;

    // STX
	Tx_Buffer[F_STX] = FRAME_STX;

    // ETX
	Tx_Buffer[Count++] = FRAME_ETX;

	Size = Count;

	Fun_RS485_Transmit_Await(Tx_Buffer, Size);
}

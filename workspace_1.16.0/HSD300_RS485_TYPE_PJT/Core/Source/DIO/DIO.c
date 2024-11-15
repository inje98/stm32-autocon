/*
 * DIO.c
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */


/* Includes ------------------------------------------------------------------*/
#include "..\Source\HSD300_FW.h"

_ID ID;

uint8_t EXT_RUN = 0;
uint8_t EXT_TEMP = 0;

void ID_Detecting(void);
void DIP_Read(void);

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPIO_Init()
{
	RUNNING_ON();
	SMOKE_DETECT_OFF();
	TEMP_WARRING_OFF();
	TEMP_ALARM_OFF();

}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_GPIO_Routine(void)
{
	ID_Detecting(); // 로터리 스위치 // 동그란 스위치 0~9
	DIP_Read();		// 딥 스위치 // 뒷면 왼쪽 스위치 4개

	// 밑엔 다 LED 부분인듯. RUNNING, RUNNING_OFF, 연기감지LED, 경고/알람LED
	if(ui.Status.Bit.SMOKE_DETECT == 1 || ui.temp_alarm_bit == 1 || Error.SHT30_Error == 1 || EEPROM.Error == 1)	// 넷 중 하나라도 문제 있으면
	{
		ui.Status.Bit.RUNNING = 0;																					// RUNNING 멈추고
		ui.Detection_Error = 1; 																					// Detection_Error = 1
	}
	else
	{
		ui.Status.Bit.RUNNING = 1;  // 저 4개 조건이 다 0이야 일로 오니까 --> 아무런 문제가 없다면 RUNNING = 1
	}
	if(ui.Status.Bit.RUNNING == 1){ // 아무 문제 없고 RUNNING == 1이면
		HAL_GPIO_TogglePin(LED_STT_GPIO_Port, LED_STT_Pin);
		//HAL_GPIO_WritePin(LED_STT_GPIO_Port, LED_STT_Pin, GPIO_PIN_RESET);
		RUNNING_ON(); // HAL_GPIO_WritePin(	EXT_RUN_GPIO_Port, EXT_RUN_Pin, GPIO_PIN_RESET)
	}
	else{
		HAL_GPIO_WritePin(LED_STT_GPIO_Port, LED_STT_Pin, GPIO_PIN_SET);
		RUNNING_OFF();
	}
	if(ui.Status.Bit.SMOKE_DETECT == 1){
		HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, GPIO_PIN_RESET);
		SMOKE_DETECT_ON();
	}
	else{
		HAL_GPIO_WritePin(LED_ERR_GPIO_Port, LED_ERR_Pin, GPIO_PIN_SET);
		SMOKE_DETECT_OFF();
	}
	if(ui.temp_alarm_bit == 1){
		TEMP_ALARM_ON();
	}
	else{
		TEMP_ALARM_OFF();
	}
	if(ui.temp_warring_bit == 1){
		TEMP_WARRING_ON();
	}
	else{
		TEMP_WARRING_OFF();
	}
}


void ID_Detecting(void)
{
	if(ID_11_Input_Check() == InputPort_LOW)  // HAL_GPIO_ReadPin(ADDR_RTY11_GPIO_Port,ADDR_RTY11_Pin) == InputPort_LOW
	{
		ID.ID_Check_1 |= InputPort_HIGH;
	}
	else
	{
		ID.ID_Check_1 = ID.ID_Check_1 & 0xFE;
	}

	if(ID_12_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_1 |= InputPort_HIGH << 1;
	}
	else
	{
		ID.ID_Check_1 = ID.ID_Check_1 & 0xFD;
	}

	if(ID_13_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_1 |= InputPort_HIGH << 2;
	}
	else
	{
		ID.ID_Check_1 = ID.ID_Check_1 & 0xFB;
	}


	if(ID_14_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_1 |= InputPort_HIGH << 3;
	}
	else
	{
		ID.ID_Check_1 = ID.ID_Check_1 & 0xF7;
	}
	// 왼쪽

	// 오른쪽이지 않을까
	if(ID_21_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_2 |= InputPort_HIGH;
	}
	else
	{
		ID.ID_Check_2 = ID.ID_Check_2 & 0xFE;
	}


	if(ID_22_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_2 |= InputPort_HIGH << 1;
	}
	else
	{
		ID.ID_Check_2 = ID.ID_Check_2 & 0xFD;
	}


	if(ID_23_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_2 |= InputPort_HIGH << 2;
	}
	else
	{
		ID.ID_Check_2 = ID.ID_Check_2 & 0xFB;
	}

	if(ID_24_Input_Check() == InputPort_LOW)
	{
		ID.ID_Check_2 |= InputPort_HIGH << 3;
	}
	else
	{
		ID.ID_Check_2 = ID.ID_Check_2 & 0xF7;
	}
	ui.ID = (ID.ID_Check_2 * 10) + ID.ID_Check_1;
}
void DIP_Read()
{
	uint8_t SMK_Level = ui.SMK_Level;
	uint8_t Protocol_Type = ui.Protocol_Type;
	uint8_t Baudrate = ui.Baudrate;
	uint8_t Baud = 0x00;
	if(DIP_1_Input_Check())  // HAL_GPIO_ReadPin(SET_DIP4_GPIO_Port,SET_DIP4_Pin)
	{
		ui.SMK_Level = RANK_1;
	}
	else{
		ui.SMK_Level = RANK_2;
	}
	if(DIP_2_Input_Check()==0)
	{
		ui.Protocol_Type = ONOFF_PROTOCOL; // 0x01
	}
	else{
		ui.Protocol_Type = MODBUS_PROTOCOL; // 0x00
	}
	Baud |= (!DIP_3_Input_Check() << 1) | (!DIP_4_Input_Check());
	ui.Baudrate = Baud;
	if(Baudrate != ui.Baudrate){
		RS485_Init();
	}
	if(SMK_Level != ui.SMK_Level || Protocol_Type != ui.Protocol_Type || Baudrate != ui.Baudrate)
	{
		EEPROM.SaveData_Flag = 1;
	}
}

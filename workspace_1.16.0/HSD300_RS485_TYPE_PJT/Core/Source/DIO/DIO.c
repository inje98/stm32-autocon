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
	ID_Detecting();
	DIP_Read();
	if(ui.Status.Bit.SMOKE_DETECT == 1 || ui.temp_alarm_bit == 1 || Error.SHT30_Error == 1 || EEPROM.Error == 1){
		ui.Status.Bit.RUNNING = 0;
		ui.Detection_Error = 1;
	}
	else{
		ui.Status.Bit.RUNNING = 1;
	}
	if(ui.Status.Bit.RUNNING == 1){
		HAL_GPIO_TogglePin(LED_STT_GPIO_Port, LED_STT_Pin);
		//HAL_GPIO_WritePin(LED_STT_GPIO_Port, LED_STT_Pin, GPIO_PIN_RESET);
		RUNNING_ON();
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
	if(ID_11_Input_Check() == InputPort_LOW)
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
	if(DIP_1_Input_Check())
	{
		ui.SMK_Level = RANK_1;
	}
	else{
		ui.SMK_Level = RANK_2;
	}
	if(DIP_2_Input_Check()==0)
	{
		ui.Protocol_Type = ONOFF_PROTOCOL;
	}
	else{
		ui.Protocol_Type = MODBUS_PROTOCOL;
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

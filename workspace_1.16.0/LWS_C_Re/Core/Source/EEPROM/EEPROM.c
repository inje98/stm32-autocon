/*
 * EEPROM.c
 *
 *  Created on: 2022. 9. 5.
 *      Author: hgson
 */

/*-------Include Header Files-----------------------------------------------*/
#include "main.h"
#include "string.h"
#include "EEPROM.h"
#include "../RS485/RS485.h"

/*-------Macro Declaration--------------------------------------------------*/
#define CAT24C256_ADDRESS_WRITE					(0xA0)
#define CAT24C256_ADDRESS_READ					(0xA1)

#define BYTE_ADDRESS_SIZE						(2)

/*-------Variable Declaration-----------------------------------------------*/
extern I2C_HandleTypeDef hi2c3;

_EEPROM EEPROM;

uint8_t I2C_Tx_Buffer[I2C_TX_BUFFER_LENGTH] = {0, };
uint8_t I2C_Rx_Buffer[I2C_RX_BUFFER_LENGTH] = {0, };

// test
uint8_t u1f_test_tx_buf[I2C_TX_BUFFER_LENGTH] = {0, };
uint8_t u1f_test_rx_buf[I2C_TX_BUFFER_LENGTH] = {0, };
/*-------Prototype Declaration----------------------------------------------*/



/* Private function prototypes ---------------------------------------------*/

/****************************************************************************/
/*	Overview	:	EEPROM Init												*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_EEPROM_Init(void)
{
	uint8_t ii = 0;
	HAL_I2C_Mem_Read(&hi2c3, CAT24C256_ADDRESS_READ, 64, BYTE_ADDRESS_SIZE, &I2C_Rx_Buffer[0], 64, 1000);

	HAL_I2C_Mem_Read(&hi2c3, CAT24C256_ADDRESS_READ, 128, BYTE_ADDRESS_SIZE, &I2C_Rx_Buffer[64], 16, 1000);

	for(uint8_t i = 0; i < 20; i++)
	{
		EEPROM.EEPROM_Save_U32_Buffer[i] = ((uint32_t)(I2C_Rx_Buffer[ii++])) << 24;
		EEPROM.EEPROM_Save_U32_Buffer[i] |= ((uint32_t)(I2C_Rx_Buffer[ii++])) << 16;
		EEPROM.EEPROM_Save_U32_Buffer[i] |= ((uint32_t)(I2C_Rx_Buffer[ii++])) << 8;
		EEPROM.EEPROM_Save_U32_Buffer[i] |= (uint32_t)(I2C_Rx_Buffer[ii++]);
	}

	memcpy(&EEPROM.EEPROM_Save_Float_Buffer[0], &EEPROM.EEPROM_Save_U32_Buffer[0], 80);

	memcpy(&RS485.LwsA_Parameter, &EEPROM.EEPROM_Save_U32_Buffer, 80);

	RS485.LwsA_Parameter[16] = -1;
	RS485.LwsA_Parameter[17] = 1.5;
}

/****************************************************************************/
/*	Overview	:	EEPROM Routine											*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_EEPROM_Routine(void)
{
	uint8_t i = 0;
	if(EEPROM.EEPROM_Save_Flag == 1)
	{
		EEPROM.EEPROM_Save_Flag = 0;

		memcpy(EEPROM.EEPROM_Save_U32_Buffer, RS485.LwsA_Parameter, 80);


		for(uint8_t ii = 0; ii < 20; ii++)
		{
			I2C_Tx_Buffer[i++] = (uint8_t)(EEPROM.EEPROM_Save_U32_Buffer[ii] >> 24);
			I2C_Tx_Buffer[i++] = (uint8_t)(EEPROM.EEPROM_Save_U32_Buffer[ii] >> 16);
			I2C_Tx_Buffer[i++] = (uint8_t)(EEPROM.EEPROM_Save_U32_Buffer[ii] >> 8);
			I2C_Tx_Buffer[i++] = (uint8_t)(EEPROM.EEPROM_Save_U32_Buffer[ii]);
		}

		HAL_I2C_Mem_Write(&hi2c3, CAT24C256_ADDRESS_WRITE, 64, BYTE_ADDRESS_SIZE, &I2C_Tx_Buffer[0], 64, 1000);

		HAL_I2C_Mem_Write(&hi2c3, CAT24C256_ADDRESS_WRITE, 128, BYTE_ADDRESS_SIZE, &I2C_Tx_Buffer[64], 16, 1000);

	}
}

//void FUN_EEPROM_write_test(void)
//{
//	for(uint8_t u1t_i = 0; u1t_i < I2C_TX_BUFFER_LENGTH; u1t_i++) {
//		u1f_i2c2_tx_buf[u1t_i] = u1t_i;
//	}
//
//	FUN_EEPROM_Write_data_page(0, u1f_i2c2_tx_buf, I2C_TX_BUFFER_LENGTH);
//}
//
//void FUN_EEPROM_read_test(void)
//{
//	FUN_EEPROM_Read_sqt_data(0, I2C_RX_BUFFER_LENGTH);
//}
//
//// Write 1BYTE
//void FUN_EEPROM_Write_data(uint16_t u2t_byte_address, uint8_t u1t_data)
//{
//	u1f_i2c2_tx_buf[0] = u1t_data;
//
//	HAL_I2C_Mem_Write(&hi2c3, CAT24C256_ADDRESS_WRITE, u2t_byte_address, BYTE_ADDRESS_SIZE, u1f_i2c2_tx_buf, 1, 10);
//}
//
//// Selective Read Timing
//uint8_t FUN_EEPROM_Read_data(uint16_t u2t_byte_address)
//{
//	HAL_I2C_Mem_Read(&hi2c3, CAT24C256_ADDRESS_READ, u2t_byte_address, BYTE_ADDRESS_SIZE, u1f_i2c2_rx_buf, 1, 10);
//
//	return u1f_i2c2_rx_buf[0];
//}
//
//// Write page
//void FUN_EEPROM_Write_data_page(uint16_t u2t_byte_address, uint8_t *u1t_data, uint8_t u1t_data_num)
//{
//	for(uint8_t u1t_i = 0; u1t_i < u1t_data_num; u1t_i++)
//	{
//		u1f_i2c2_tx_buf[u1t_i] = u1t_data[u1t_i];
//	}
//
//	HAL_I2C_Mem_Write(&hi2c3, CAT24C256_ADDRESS_WRITE, u2t_byte_address, BYTE_ADDRESS_SIZE, u1f_i2c2_tx_buf, u1t_data_num, 10);
//}
//
//// Sequential Read Timing
//void FUN_EEPROM_Read_sqt_data(uint16_t u2t_byte_address, uint8_t u1t_data_num)
//{
//	HAL_I2C_Mem_Read(&hi2c3, CAT24C256_ADDRESS_READ, u2t_byte_address, BYTE_ADDRESS_SIZE, u1f_i2c2_rx_buf, u1t_data_num, 10);
//}
//

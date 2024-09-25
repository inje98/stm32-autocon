/*
 * EEPROM.h
 *
 *  Created on: 2022. 9. 5.
 *      Author: hgson
 */

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_

/*-------Include Header Files-----------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "main.h"

/*-------Macro Declaration--------------------------------------------------*/
#define I2C_TX_BUFFER_LENGTH					(80)
#define I2C_RX_BUFFER_LENGTH					(80)

/*-------Type Declaration---------------------------------------------------*/
typedef struct
{
	uint8_t HILS_Parameter_Tx_Buffer[I2C_TX_BUFFER_LENGTH];
	uint8_t HILS_Parameter_Rx_Buffer[I2C_RX_BUFFER_LENGTH];

	uint32_t EEPROM_Save_U32_Buffer[I2C_TX_BUFFER_LENGTH];
	float EEPROM_Save_Float_Buffer[I2C_TX_BUFFER_LENGTH];
	uint8_t EEPROM_Save_Flag;
} _EEPROM;
extern _EEPROM EEPROM;

/*-------Prototype Declaration----------------------------------------------*/


/*-------Variable Declaration-----------------------------------------------*/
void FUN_EEPROM_Init(void);
void FUN_EEPROM_Routine(void);
//void FUN_EEPROM_Write_data(uint16_t u2t_byte_address, uint8_t u1t_data);
//uint8_t FUN_EEPROM_Read_data(uint16_t u2t_byte_address);
//void FUN_EEPROM_Write_data_page(uint16_t u2t_byte_address, uint8_t *u1t_data, uint8_t u1t_data_num);
//void FUN_EEPROM_Read_sqt_data(uint16_t u2t_byte_address, uint8_t u1t_data_num);
//
//void FUN_EEPROM_write_test(void);
//void FUN_EEPROM_read_test(void);

#endif /* EEPROM_EEPROM_H_ */

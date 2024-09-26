/*
 * Modbus.h
 *
 *  Created on: 2021. 2. 25.
 *      Author: dongho
 */

#ifndef MODBUS_MODBUS_H_
#define MODBUS_MODBUS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private define ------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
typedef struct {


} _Modbus;
extern _Modbus Modbus;


extern uint8_t Read_Data_Tx[37];
/* Private function prototypes -----------------------------------------------*/
extern void FUN_Modbus_init(void);
extern void FUN_Modbus_RxCallback_ReadData(uint8_t Addrs, uint8_t Lenth);
extern void FUN_Modbus_RxCallback_ReadWriteData(uint8_t Addrs, uint8_t Lenth, uint8_t Fun);
extern void FUN_Modbus_Read(void);
extern void FUN_Modbus_RxCallback_ERROR(uint8_t Fun, uint8_t Ex_Code);
#endif /* MODBUS_MODBUS_H_ */

/*
 * I2C.h
 *
 *  Created on: Nov 6, 2023
 *      Author: autocontech
 */

#ifndef SOURCE_I2C_I2C_H_
#define SOURCE_I2C_I2C_H_

#include "main.h"

#include "app_tof.h"
#include <stdio.h>
#include "vl53l3cx.h"
#include "custom_ranging_sensor.h"
#include "custom.h"

#define OBJ_SENSOR_ADDR 0x52
#define TEMP_SENSOR_ADDR ((0x44) << 1)

// SHT30
#define SENSOR_ERROR				(1)
#define SENSOR_NOT_ERROR			(0)

#define CMD_SINGLE_EN_HIGH			(0x2C06)
#define CMD_SINGLE_EN_MEDIUM		(0x2C0D)
#define CMD_SINGLE_EN_LOW			(0x2C10)
#define CMD_SINGLE_DI_HIGH			(0x2400)
#define CMD_SINGLE_DI_MEDIUM		(0x240B)
#define CMD_SINGLE_DI_LOW			(0x2416)


#define CMD_PERIODIC_HIGH_05		(0x2032)
#define CMD_PERIODIC_MIDIUM_05		(0x2024)
#define CMD_PERIODIC_LOW_05			(0x202F)

#define CMD_PERIODIC_HIGH_1			(0x2130)
#define CMD_PERIODIC_MIDIUM_1		(0x2126)
#define CMD_PERIODIC_LOW_1			(0x212D)

#define CMD_PERIODIC_HIGH_2			(0x2236)
#define CMD_PERIODIC_MIDIUM_2		(0x2220)
#define CMD_PERIODIC_LOW_2			(0x222B)

#define CMD_PERIODIC_HIGH_4			(0x2334)
#define CMD_PERIODIC_MIDIUM_4		(0x2322)
#define CMD_PERIODIC_LOW_4			(0x2329)

#define CMD_PERIODIC_HIGH_10		(0x2737)
#define CMD_PERIODIC_MIDIUM_10		(0x2721)
#define CMD_PERIODIC_LOW_10			(0x272A)


#define CMD_FETCH_DATA				(0xE000)


#define CMD_ART						(0x2B32)


#define CMD_PERIODIC_STOP			(0x3093)


#define CMD_SOFT_RESET				(0x30A2)
#define CMD_GENERAL_CALL_ADDRESS	(0x00)
#define CMD_GENERAL_CALL_SECOND_B	(0x06)


#define CMD_HEATER_ENABLE			(0x306D)
#define CMD_HEATER_DISABLE			(0x3066)


#define CMD_STATUS_REGISTER			(0xF32D)
#define CMD_CLEAR_STATUS_REGISTER	(0x3041)


typedef union{
	uint16_t monitor_all;
	struct {
		uint16_t Write_Date_Checksum_Status : 1;
		uint16_t Command_Status 			: 1;
		uint16_t Reserved4 					: 2;
		uint16_t System_Reset_Detected 		: 1;
		uint16_t Reserved3					: 5;
		uint16_t T_Tracking_Alert 			: 1;
		uint16_t RH_Tracking_Alert 			: 1;
		uint16_t Reserved2 					: 1;
		uint16_t Heater_Status 				: 1;
		uint16_t Reserved1				 	: 1;
		uint16_t Alert_Pending_Status 		: 1;

	}Bit;
}I2C_STATUS_REGISTER;

typedef struct{
	I2C_HandleTypeDef *I2C_Handle;
	uint8_t I2C_Addr;

	uint8_t i2c_write_buff[2];
	uint8_t i2c_read_buff[6];
	uint8_t i2c_read_state_buff[3];
	uint8_t i2c_period_cnt;
	uint8_t temp_acc_cnt;
	uint8_t humi_acc_cnt;
	int32_t temp_acc[20];
	int32_t humi_acc[20];
	uint32_t i2c_total_reset;

	uint32_t i2c_state;
	uint32_t i2c_error;
	uint32_t i2c_success;
	uint32_t i2c_error_cnt;
	uint8_t i2c_error_flag;

	uint8_t temp_crc_error_cnt;
	uint8_t humi_crc_error_cnt;
	uint8_t crc_error_flag;
	I2C_STATUS_REGISTER i2c_Status;

	uint8_t warring_cnt;
	uint8_t alarm_cnt;

	uint8_t sensor_error;
	float	temperature;
	float 	humidity;
	uint16_t temp_hex;
	uint16_t humi_hex;
}_SHT30_Dev;

/*-------Macro Declaration--------------------------------------------------*/
#define VL53LX_ERROR_NONE                              ((VL53LX_Error)  0)

typedef struct
{
	uint8_t Detect_Obj_Number;				// 관측할 물체의 갯수
	uint8_t Range_State;					// 0 : 정상 , others : 비정상
	int16_t Max_Distance;					// 관측된 물체의 최대 거리
	int16_t Min_Distance;					// 관츤된 물체의 최소 거리
	int16_t Distance;						// 실제 물체의 거리
	uint8_t Start_Flag;
} _VL53L3CX_Main;
extern _VL53L3CX_Main VL53L3CX_Main;

extern _SHT30_Dev Ext_SHT30;
extern _SHT30_Dev Int_SHT30;

extern int32_t Distance;

void FUN_I2C_SHT30_Init(void);
void FUN_I2C_SHT30_Routine(void);
void FUN_I2C_INT_SHT30_Routine(void);
void FUN_I2C_EXT_SHT30_Routine(void);
void I2C_SHT30_Task(void* argument);


void FUN_I2C_VL53L3CX_Init(void);
void FUN_I2C_VL53L3CX_Routine(void);
void I2C_VL53L3CX_Task(void* argument);

void I2C_Sensor_Task(void* argument);

#endif /* SOURCE_I2C_I2C_H_ */

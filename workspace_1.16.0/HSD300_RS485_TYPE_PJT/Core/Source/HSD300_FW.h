/*
 * HSD300_FW.h
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_HSD300_FW_H_
#define SOURCE_HSD300_FW_H_


#include "main.h"

#define HSD300
//#define	HSS300

#include "stm32G4xx_hal.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#include "app_tof.h"
#include "custom_ranging_sensor.h"
#include "custom.h"

#include "../Source/ADC/ADC.h"
#include "../Source/ADPD188BI/ADPD188BI.h"
#include "../Source/DIO/DIO.h"
#include "../Source/I2C/I2C.h"
#include "../Source/RS485/RS485.h"
#include "../Source/SMOKE_SENSOR/Smoke_Sensor.h"
#include "../Source/TIME_TASK/TIME_TASK.h"
#include "../Source/EEPROM/EEPROM.h"
#include "../Source/Modbus/Modbus.h"
#include "../Source/FLASH/FLASH.h"
#include "../Source/Bootloader/BOOTLOADER.h"



#endif /* SOURCE_HSD300_FW_H_ */

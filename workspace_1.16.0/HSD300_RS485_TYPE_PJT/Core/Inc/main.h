/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define EXT_TEMP1_Pin GPIO_PIN_14
#define EXT_TEMP1_GPIO_Port GPIOC
#define EXT_TEMP2_Pin GPIO_PIN_15
#define EXT_TEMP2_GPIO_Port GPIOC
#define SET_DIP1_Pin GPIO_PIN_0
#define SET_DIP1_GPIO_Port GPIOC
#define SET_DIP2_Pin GPIO_PIN_1
#define SET_DIP2_GPIO_Port GPIOC
#define SET_DIP3_Pin GPIO_PIN_2
#define SET_DIP3_GPIO_Port GPIOC
#define SET_DIP4_Pin GPIO_PIN_3
#define SET_DIP4_GPIO_Port GPIOC
#define ADDR_RTY11_Pin GPIO_PIN_0
#define ADDR_RTY11_GPIO_Port GPIOA
#define ADDR_RTY12_Pin GPIO_PIN_1
#define ADDR_RTY12_GPIO_Port GPIOA
#define ADDR_RTY13_Pin GPIO_PIN_2
#define ADDR_RTY13_GPIO_Port GPIOA
#define ADDR_RTY14_Pin GPIO_PIN_3
#define ADDR_RTY14_GPIO_Port GPIOA
#define ADDR_RTY21_Pin GPIO_PIN_4
#define ADDR_RTY21_GPIO_Port GPIOA
#define ADDR_RTY22_Pin GPIO_PIN_5
#define ADDR_RTY22_GPIO_Port GPIOA
#define ADDR_RTY23_Pin GPIO_PIN_6
#define ADDR_RTY23_GPIO_Port GPIOA
#define ADDR_RTY24_Pin GPIO_PIN_7
#define ADDR_RTY24_GPIO_Port GPIOA
#define CO_SENSOR_Pin GPIO_PIN_2
#define CO_SENSOR_GPIO_Port GPIOB
#define TOF_XSHUT_Pin GPIO_PIN_11
#define TOF_XSHUT_GPIO_Port GPIOB
#define EEPROM_CS_Pin GPIO_PIN_12
#define EEPROM_CS_GPIO_Port GPIOB
#define EEPROM_SCK_Pin GPIO_PIN_13
#define EEPROM_SCK_GPIO_Port GPIOB
#define EEPROM_MISO_Pin GPIO_PIN_14
#define EEPROM_MISO_GPIO_Port GPIOB
#define EEPROM_MOSI_Pin GPIO_PIN_15
#define EEPROM_MOSI_GPIO_Port GPIOB
#define EEPROM_HOLD_Pin GPIO_PIN_6
#define EEPROM_HOLD_GPIO_Port GPIOC
#define EEPROM_WP_Pin GPIO_PIN_7
#define EEPROM_WP_GPIO_Port GPIOC
#define TNH_SDA_Pin GPIO_PIN_8
#define TNH_SDA_GPIO_Port GPIOA
#define TNH_SCL_Pin GPIO_PIN_9
#define TNH_SCL_GPIO_Port GPIOA
#define LED_STT_Pin GPIO_PIN_10
#define LED_STT_GPIO_Port GPIOA
#define LED_ERR_Pin GPIO_PIN_11
#define LED_ERR_GPIO_Port GPIOA
#define HEAT_EN_Pin GPIO_PIN_12
#define HEAT_EN_GPIO_Port GPIOA
#define SMK_SCL_Pin GPIO_PIN_15
#define SMK_SCL_GPIO_Port GPIOA
#define SMK_SCLK_Pin GPIO_PIN_10
#define SMK_SCLK_GPIO_Port GPIOC
#define SMK_MISO_Pin GPIO_PIN_11
#define SMK_MISO_GPIO_Port GPIOC
#define RS485_TX_Pin GPIO_PIN_12
#define RS485_TX_GPIO_Port GPIOC
#define RS485_RX_Pin GPIO_PIN_2
#define RS485_RX_GPIO_Port GPIOD
#define SMK_CS__Pin GPIO_PIN_3
#define SMK_CS__GPIO_Port GPIOB
#define RS485_DE_Pin GPIO_PIN_4
#define RS485_DE_GPIO_Port GPIOB
#define SMK_MOSI_Pin GPIO_PIN_5
#define SMK_MOSI_GPIO_Port GPIOB
#define EXT_RUN_Pin GPIO_PIN_6
#define EXT_RUN_GPIO_Port GPIOB
#define EXT_SMK_Pin GPIO_PIN_7
#define EXT_SMK_GPIO_Port GPIOB
#define SMK_SDA_Pin GPIO_PIN_9
#define SMK_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

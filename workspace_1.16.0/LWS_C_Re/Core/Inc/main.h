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
#include "stm32f7xx_hal.h"

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
#define OUT_CH48_Pin GPIO_PIN_2
#define OUT_CH48_GPIO_Port GPIOE
#define IN_CH17_Pin GPIO_PIN_4
#define IN_CH17_GPIO_Port GPIOE
#define IN_CH18_Pin GPIO_PIN_5
#define IN_CH18_GPIO_Port GPIOE
#define NSS_5_Pin GPIO_PIN_2
#define NSS_5_GPIO_Port GPIOF
#define LDAC_5_Pin GPIO_PIN_12
#define LDAC_5_GPIO_Port GPIOI
#define CLR_5_Pin GPIO_PIN_13
#define CLR_5_GPIO_Port GPIOI
#define SCK_5_Pin GPIO_PIN_7
#define SCK_5_GPIO_Port GPIOF
#define MISO_5_Pin GPIO_PIN_8
#define MISO_5_GPIO_Port GPIOF
#define MOSI_5_Pin GPIO_PIN_9
#define MOSI_5_GPIO_Port GPIOF
#define CLR_3_Pin GPIO_PIN_4
#define CLR_3_GPIO_Port GPIOA
#define LDAC_3_Pin GPIO_PIN_5
#define LDAC_3_GPIO_Port GPIOA
#define NSS_3_Pin GPIO_PIN_6
#define NSS_3_GPIO_Port GPIOA
#define ADC_IN1_Pin GPIO_PIN_0
#define ADC_IN1_GPIO_Port GPIOB
#define ADC_IN2_Pin GPIO_PIN_1
#define ADC_IN2_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_1
#define LED_1_GPIO_Port GPIOJ
#define LED_2_Pin GPIO_PIN_2
#define LED_2_GPIO_Port GPIOJ
#define LED_3_Pin GPIO_PIN_3
#define LED_3_GPIO_Port GPIOJ
#define LED_4_Pin GPIO_PIN_4
#define LED_4_GPIO_Port GPIOJ
#define OUT_CH12_Pin GPIO_PIN_13
#define OUT_CH12_GPIO_Port GPIOF
#define OUT_CH32_Pin GPIO_PIN_15
#define OUT_CH32_GPIO_Port GPIOF
#define SCIRXDB_Pin GPIO_PIN_7
#define SCIRXDB_GPIO_Port GPIOE
#define SCITXDB_Pin GPIO_PIN_8
#define SCITXDB_GPIO_Port GPIOE
#define SEL_485_1_Pin GPIO_PIN_9
#define SEL_485_1_GPIO_Port GPIOE
#define LDAC_4_Pin GPIO_PIN_10
#define LDAC_4_GPIO_Port GPIOE
#define NSS_4_Pin GPIO_PIN_11
#define NSS_4_GPIO_Port GPIOE
#define SCK_4_Pin GPIO_PIN_12
#define SCK_4_GPIO_Port GPIOE
#define MISO_4_Pin GPIO_PIN_13
#define MISO_4_GPIO_Port GPIOE
#define MOSI_4_Pin GPIO_PIN_14
#define MOSI_4_GPIO_Port GPIOE
#define CLR_4_Pin GPIO_PIN_15
#define CLR_4_GPIO_Port GPIOE
#define CLK_1_Pin GPIO_PIN_10
#define CLK_1_GPIO_Port GPIOB
#define ADC2_SEL0_M_Pin GPIO_PIN_6
#define ADC2_SEL0_M_GPIO_Port GPIOH
#define ADC2_SEL1_M_Pin GPIO_PIN_7
#define ADC2_SEL1_M_GPIO_Port GPIOH
#define ER_SCA3_Pin GPIO_PIN_8
#define ER_SCA3_GPIO_Port GPIOH
#define ADC2_SEL2_M_Pin GPIO_PIN_9
#define ADC2_SEL2_M_GPIO_Port GPIOH
#define ADC1_SEL0_M_Pin GPIO_PIN_10
#define ADC1_SEL0_M_GPIO_Port GPIOH
#define ADC1_SEL1_M_Pin GPIO_PIN_11
#define ADC1_SEL1_M_GPIO_Port GPIOH
#define ADC1_SEL2_M_Pin GPIO_PIN_12
#define ADC1_SEL2_M_GPIO_Port GPIOH
#define MISO_1_Pin GPIO_PIN_14
#define MISO_1_GPIO_Port GPIOB
#define IN_CH1_Pin GPIO_PIN_11
#define IN_CH1_GPIO_Port GPIOD
#define IN_CH2_Pin GPIO_PIN_12
#define IN_CH2_GPIO_Port GPIOD
#define IN_CH3_Pin GPIO_PIN_13
#define IN_CH3_GPIO_Port GPIOD
#define IN_CH4_Pin GPIO_PIN_14
#define IN_CH4_GPIO_Port GPIOD
#define IN_CH5_Pin GPIO_PIN_15
#define IN_CH5_GPIO_Port GPIOD
#define IN_CH6_Pin GPIO_PIN_6
#define IN_CH6_GPIO_Port GPIOJ
#define IN_CH7_Pin GPIO_PIN_7
#define IN_CH7_GPIO_Port GPIOJ
#define IN_CH8_Pin GPIO_PIN_8
#define IN_CH8_GPIO_Port GPIOJ
#define IN_CH9_Pin GPIO_PIN_9
#define IN_CH9_GPIO_Port GPIOJ
#define IN_CH10_Pin GPIO_PIN_10
#define IN_CH10_GPIO_Port GPIOJ
#define IN_CH11_Pin GPIO_PIN_11
#define IN_CH11_GPIO_Port GPIOJ
#define IN_CH12_Pin GPIO_PIN_0
#define IN_CH12_GPIO_Port GPIOK
#define IN_CH13_Pin GPIO_PIN_1
#define IN_CH13_GPIO_Port GPIOK
#define IN_CH14_Pin GPIO_PIN_2
#define IN_CH14_GPIO_Port GPIOK
#define IN_CH15_Pin GPIO_PIN_2
#define IN_CH15_GPIO_Port GPIOG
#define IN_CH16_Pin GPIO_PIN_3
#define IN_CH16_GPIO_Port GPIOG
#define OUT_CH1_Pin GPIO_PIN_4
#define OUT_CH1_GPIO_Port GPIOG
#define OUT_CH2_Pin GPIO_PIN_5
#define OUT_CH2_GPIO_Port GPIOG
#define OUT_CH3_Pin GPIO_PIN_6
#define OUT_CH3_GPIO_Port GPIOG
#define OUT_CH4_Pin GPIO_PIN_7
#define OUT_CH4_GPIO_Port GPIOG
#define OUT_CH5_Pin GPIO_PIN_8
#define OUT_CH5_GPIO_Port GPIOG
#define OUT_CH6_Pin GPIO_PIN_6
#define OUT_CH6_GPIO_Port GPIOC
#define OUT_CH7_Pin GPIO_PIN_7
#define OUT_CH7_GPIO_Port GPIOC
#define OUT_CH8_Pin GPIO_PIN_8
#define OUT_CH8_GPIO_Port GPIOC
#define OUT_CH9_Pin GPIO_PIN_9
#define OUT_CH9_GPIO_Port GPIOC
#define ER_SCL3_Pin GPIO_PIN_8
#define ER_SCL3_GPIO_Port GPIOA
#define OUT_CH10_Pin GPIO_PIN_9
#define OUT_CH10_GPIO_Port GPIOA
#define OUT_CH11_Pin GPIO_PIN_10
#define OUT_CH11_GPIO_Port GPIOA
#define OUT_CH13_Pin GPIO_PIN_12
#define OUT_CH13_GPIO_Port GPIOA
#define OUT_CH14_Pin GPIO_PIN_13
#define OUT_CH14_GPIO_Port GPIOH
#define OUT_CH15_Pin GPIO_PIN_14
#define OUT_CH15_GPIO_Port GPIOH
#define OUT_CH16_Pin GPIO_PIN_15
#define OUT_CH16_GPIO_Port GPIOH
#define OUT_CH17_Pin GPIO_PIN_0
#define OUT_CH17_GPIO_Port GPIOI
#define OUT_CH18_Pin GPIO_PIN_1
#define OUT_CH18_GPIO_Port GPIOI
#define OUT_CH19_Pin GPIO_PIN_2
#define OUT_CH19_GPIO_Port GPIOI
#define OUT_CH20_Pin GPIO_PIN_3
#define OUT_CH20_GPIO_Port GPIOI
#define SCK_3_Pin GPIO_PIN_10
#define SCK_3_GPIO_Port GPIOC
#define MISO_3_Pin GPIO_PIN_11
#define MISO_3_GPIO_Port GPIOC
#define MOSI_3_Pin GPIO_PIN_12
#define MOSI_3_GPIO_Port GPIOC
#define OUT_CH21_Pin GPIO_PIN_0
#define OUT_CH21_GPIO_Port GPIOD
#define OUT_CH22_Pin GPIO_PIN_1
#define OUT_CH22_GPIO_Port GPIOD
#define OUT_CH23_Pin GPIO_PIN_2
#define OUT_CH23_GPIO_Port GPIOD
#define OUT_CH24_Pin GPIO_PIN_3
#define OUT_CH24_GPIO_Port GPIOD
#define OUT_CH25_Pin GPIO_PIN_4
#define OUT_CH25_GPIO_Port GPIOD
#define OUT_CH26_Pin GPIO_PIN_5
#define OUT_CH26_GPIO_Port GPIOD
#define OUT_CH27_Pin GPIO_PIN_6
#define OUT_CH27_GPIO_Port GPIOD
#define OUT_CH28_Pin GPIO_PIN_12
#define OUT_CH28_GPIO_Port GPIOJ
#define OUT_CH29_Pin GPIO_PIN_13
#define OUT_CH29_GPIO_Port GPIOJ
#define OUT_CH30_Pin GPIO_PIN_14
#define OUT_CH30_GPIO_Port GPIOJ
#define OUT_CH31_Pin GPIO_PIN_15
#define OUT_CH31_GPIO_Port GPIOJ
#define MISO_2_Pin GPIO_PIN_9
#define MISO_2_GPIO_Port GPIOG
#define CLK_2_Pin GPIO_PIN_11
#define CLK_2_GPIO_Port GPIOG
#define OUT_CH33_Pin GPIO_PIN_3
#define OUT_CH33_GPIO_Port GPIOK
#define OUT_CH34_Pin GPIO_PIN_4
#define OUT_CH34_GPIO_Port GPIOK
#define OUT_CH35_Pin GPIO_PIN_5
#define OUT_CH35_GPIO_Port GPIOK
#define OUT_CH36_Pin GPIO_PIN_6
#define OUT_CH36_GPIO_Port GPIOK
#define OUT_CH37_Pin GPIO_PIN_7
#define OUT_CH37_GPIO_Port GPIOK
#define OUT_CH38_Pin GPIO_PIN_15
#define OUT_CH38_GPIO_Port GPIOG
#define OUT_CH39_Pin GPIO_PIN_5
#define OUT_CH39_GPIO_Port GPIOB
#define OUT_CH40_Pin GPIO_PIN_8
#define OUT_CH40_GPIO_Port GPIOB
#define OUT_CH41_Pin GPIO_PIN_9
#define OUT_CH41_GPIO_Port GPIOB
#define OUT_CH42_Pin GPIO_PIN_0
#define OUT_CH42_GPIO_Port GPIOE
#define OUT_CH43_Pin GPIO_PIN_1
#define OUT_CH43_GPIO_Port GPIOE
#define OUT_CH44_Pin GPIO_PIN_4
#define OUT_CH44_GPIO_Port GPIOI
#define OUT_CH45_Pin GPIO_PIN_5
#define OUT_CH45_GPIO_Port GPIOI
#define OUT_CH46_Pin GPIO_PIN_6
#define OUT_CH46_GPIO_Port GPIOI
#define OUT_CH47_Pin GPIO_PIN_7
#define OUT_CH47_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

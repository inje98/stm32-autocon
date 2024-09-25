/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define CLCD_D0_Pin GPIO_PIN_2
#define CLCD_D0_GPIO_Port GPIOC
#define CLCD_D1_Pin GPIO_PIN_3
#define CLCD_D1_GPIO_Port GPIOC
#define CLCD_D2_Pin GPIO_PIN_4
#define CLCD_D2_GPIO_Port GPIOC
#define CLCD_D3_Pin GPIO_PIN_5
#define CLCD_D3_GPIO_Port GPIOC
#define SW_Pin GPIO_PIN_8
#define SW_GPIO_Port GPIOA
#define SW_EXTI_IRQn EXTI9_5_IRQn
#define B_SIG_Pin GPIO_PIN_15
#define B_SIG_GPIO_Port GPIOA
#define B_SIG_EXTI_IRQn EXTI15_10_IRQn
#define CLCD_EN_Pin GPIO_PIN_10
#define CLCD_EN_GPIO_Port GPIOC
#define CLCD_RS_Pin GPIO_PIN_11
#define CLCD_RS_GPIO_Port GPIOC
#define A_SIG_Pin GPIO_PIN_12
#define A_SIG_GPIO_Port GPIOC
#define A_SIG_EXTI_IRQn EXTI15_10_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

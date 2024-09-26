/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file  : custom.c
  * @brief : Source file for the BSP Common driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "custom.h"

/** @defgroup BSP BSP
 * @{
 */

/** @defgroup CUSTOM CUSTOM
 * @{
 */

/** @defgroup CUSTOM_LOW_LEVEL CUSTOM LOW LEVEL
 *  @brief This file provides set of firmware functions to manage Leds and push-button
 *         available on STM32F0xx-Nucleo Kit from STMicroelectronics.
 * @{
 */

/**
 * @}
 */

/** @defgroup CUSTOM_LOW_LEVEL_Private_Defines CUSTOM LOW LEVEL Private Defines
 * @{
 */

/** @defgroup CUSTOM_LOW_LEVEL_FunctionPrototypes CUSTOM LOW LEVEL Private Function Prototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup CUSTOM_LOW_LEVEL_Private_Variables CUSTOM LOW LEVEL Private Variables
 * @{
 */

USART_TypeDef* COM_USART[COMn] = {COM1_UART};
UART_HandleTypeDef hcom_uart[COMn];
#if (USE_COM_LOG > 0)
static COM_TypeDef COM_ActiveLogPort;
#endif
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1U)
static uint32_t IsUsart5MspCbValid = 0;
#endif
__weak HAL_StatusTypeDef MX_UART5_UART_Init(UART_HandleTypeDef* huart);
/**
 * @}
 */

/** @defgroup CUSTOM_LOW_LEVEL_Private_Functions CUSTOM LOW LEVEL Private Functions
 * @{
 */
#if (USE_BSP_COM_FEATURE > 0)
static void UART5_MspInit(UART_HandleTypeDef *huart);
static void UART5_MspDeInit(UART_HandleTypeDef *huart);
#endif
/**
 * @brief  This method returns the STM32F0xx NUCLEO BSP Driver revision
 * @retval version: 0xXYZR (8bits for each decimal, R for RC)
 */
int32_t BSP_GetVersion(void)
{
  return (int32_t)__CUSTOM_BSP_VERSION;
}

#if (USE_BSP_COM_FEATURE > 0)
/**
 * @brief  Configures COM port.
 * @param  COM: COM port to be configured.
 *              This parameter can be COM1
 * @param  UART_Init: Pointer to a UART_HandleTypeDef structure that contains the
 *                    configuration information for the specified USART peripheral.
 * @retval BSP error code
 */
int32_t BSP_COM_Init(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM > COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
     hcom_uart[COM].Instance = COM_USART[COM];
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0U)
    /* Init the UART Msp */
    UART5_MspInit(&hcom_uart[COM]);
#else
    if(IsUsart5MspCbValid == 0U)
    {
      if(BSP_COM_RegisterDefaultMspCallbacks(COM) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif

    if (MX_UART5_UART_Init(&hcom_uart[COM]))
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
 * @brief  DeInit COM port.
 * @param  COM COM port to be configured.
 *             This parameter can be COM1
 * @retval BSP status
 */
int32_t BSP_COM_DeInit(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM > COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* USART configuration */
    hcom_uart[COM].Instance = COM_USART[COM];

    #if (USE_HAL_UART_REGISTER_CALLBACKS == 0U)
      UART5_MspDeInit(&hcom_uart[COM]);
    #endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 0U) */

    if(HAL_UART_DeInit(&hcom_uart[COM]) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
 * @brief  Configures COM port.
 * @param  huart USART handle
 *               This parameter can be COM1
 * @param  COM_Init Pointer to a UART_HandleTypeDef structure that contains the
 *                  configuration information for the specified USART peripheral.
 * @retval HAL error code
 */

/* UART5 init function */

__weak HAL_StatusTypeDef MX_UART5_UART_Init(UART_HandleTypeDef* huart)
{
  HAL_StatusTypeDef ret = HAL_OK;

  huart->Instance = UART5;
  huart->Init.BaudRate = 115200;
  huart->Init.WordLength = UART_WORDLENGTH_8B;
  huart->Init.StopBits = UART_STOPBITS_1;
  huart->Init.Parity = UART_PARITY_NONE;
  huart->Init.Mode = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(huart) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  return ret;
}

#endif
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1U)
/**
 * @brief Register Default UART5 Bus Msp Callbacks
 * @retval BSP status
 */
int32_t BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {

    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register default MspInit/MspDeInit Callback */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, UART5_MspInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, UART5_MspDeInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsUsart5MspCbValid = 1U;
    }
  }

  /* BSP status */
  return ret;
}

/**
 * @brief Register UART5 Bus Msp Callback registering
 * @param Callbacks pointer to UART5 MspInit/MspDeInit callback functions
 * @retval BSP status
 */
int32_t BSP_COM_RegisterMspCallbacks (COM_TypeDef COM , BSP_COM_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register MspInit/MspDeInit Callbacks */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, Callback->pMspInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, Callback->pMspDeInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsUsart5MspCbValid = 1U;
    }
  }

  /* BSP status */
  return ret;
}
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

#if (USE_COM_LOG > 0)
/**
 * @brief  Select the active COM port.
 * @param  COM COM port to be activated.
 *             This parameter can be COM1
 * @retval BSP status
 */
int32_t BSP_COM_SelectLogPort(COM_TypeDef COM)
{
  if(COM_ActiveLogPort != COM)
  {
    COM_ActiveLogPort = COM;
  }
  return BSP_ERROR_NONE;
}

#if defined(__CC_ARM) /* For arm compiler 5 */
#if !defined(__MICROLIB) /* If not Microlib */

struct __FILE
{
  int dummyVar; //Just for the sake of redefining __FILE, we won't we using it anyways ;)
};

FILE __stdout;

#endif /* If not Microlib */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* For arm compiler 6 */
#if !defined(__MICROLIB) /* If not Microlib */

FILE __stdout;

#endif /* If not Microlib */
#endif /* For arm compiler 5 */

#if defined(__ICCARM__) || defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* For IAR and ARM Compiler 5 and 6*/
 int fputc (int ch, FILE *f)
#else /* For GCC Toolchains */
 int __io_putchar (int ch)
#endif /* For IAR and ARM Compiler 5 and 6 */
{
  (void)HAL_UART_Transmit(&hcom_uart[COM_ActiveLogPort], (uint8_t *)&ch, 1, COM_POLL_TIMEOUT);
  return ch;
}
#endif /* USE_COM_LOG */
/**
 * @brief  Initializes UART5 MSP.
 * @param  huart UART5 handle
 * @retval None
 */
#if (USE_BSP_COM_FEATURE>0)
static void UART5_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* USER CODE BEGIN UART5_MspInit 0 */

  /* USER CODE END UART5_MspInit 0 */
    /* Enable Peripheral clock */
    __HAL_RCC_UART5_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**UART5 GPIO Configuration
    PB3     ------> UART5_TX
    PB4     ------> UART5_RX
    */
    GPIO_InitStruct.Pin = BUS_UART5_TX_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = BUS_UART5_TX_GPIO_AF;
    HAL_GPIO_Init(BUS_UART5_TX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BUS_UART5_RX_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = BUS_UART5_RX_GPIO_AF;
    HAL_GPIO_Init(BUS_UART5_RX_GPIO_PORT, &GPIO_InitStruct);

  /* USER CODE BEGIN UART5_MspInit 1 */

  /* USER CODE END UART5_MspInit 1 */
}

static void UART5_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  /* USER CODE BEGIN UART5_MspDeInit 0 */

  /* USER CODE END UART5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART5_CLK_DISABLE();

    /**UART5 GPIO Configuration
    PB3     ------> UART5_TX
    PB4     ------> UART5_RX
    */
    HAL_GPIO_DeInit(BUS_UART5_TX_GPIO_PORT, BUS_UART5_TX_GPIO_PIN);

    HAL_GPIO_DeInit(BUS_UART5_RX_GPIO_PORT, BUS_UART5_RX_GPIO_PIN);

  /* USER CODE BEGIN UART5_MspDeInit 1 */

  /* USER CODE END UART5_MspDeInit 1 */
}
#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


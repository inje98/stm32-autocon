/**
  ******************************************************************************
  * @file          : app_tof.c
  * @author        : IMG SW Application Team
  * @brief         : This file provides code for the configuration
  *                  of the STMicroelectronics.X-CUBE-TOF1.3.1.0 instances.
  ******************************************************************************
  *
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

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "..\Source\HSD300_FW.h"

/* Private typedef -----------------------------------------------------------*/
extern int32_t Distance;
extern int32_t Distance1;
int32_t DistanceOffset = 20;
uint32_t status1;

/* Private define ------------------------------------------------------------*/
#define TIMING_BUDGET (32U)//(33U) /* 16 ms < TimingBudget < 500 ms */
#define POLLING_PERIOD (100U) /* refresh rate for polling mode (milliseconds, shall be consistent with TimingBudget value) */

/* Private variables ---------------------------------------------------------*/
static RANGING_SENSOR_Capabilities_t Cap;
static RANGING_SENSOR_ProfileConfig_t Profile;
static int32_t status = 0;
volatile uint8_t ToF_EventDetected = 0;

uint8_t tof_err_cnt = 0;
uint8_t err_flag = 0;

/* Private function prototypes -----------------------------------------------*/
static void MX_VL53L3CX_SimpleRanging_Init(void);
static void MX_VL53L3CX_SimpleRanging_Process(void);
//static void print_result(RANGING_SENSOR_Result_t *Result);
//static int32_t decimal_part(float_t x);

void MX_TOF_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN TOF_Init_PreTreatment */

  /* USER CODE END TOF_Init_PreTreatment */

  /* Initialize the peripherals and the TOF components */

  MX_VL53L3CX_SimpleRanging_Init();

  /* USER CODE BEGIN TOF_Init_PostTreatment */

  /* USER CODE END TOF_Init_PostTreatment */
}

/*
 * LM background task
 */
void MX_TOF_Process(void)
{
  /* USER CODE BEGIN TOF_Process_PreTreatment */

  /* USER CODE END TOF_Process_PreTreatment */

  MX_VL53L3CX_SimpleRanging_Process();

  /* USER CODE BEGIN TOF_Process_PostTreatment */

  /* USER CODE END TOF_Process_PostTreatment */
}

static void MX_VL53L3CX_SimpleRanging_Init(void)
{
  /* Initialize Virtual COM Port */
  //BSP_COM_Init(COM1);
  HAL_GPIO_WritePin(TOF_XSHUT_GPIO_Port, TOF_XSHUT_Pin, GPIO_PIN_SET);

  printf("VL53L3CX Simple Ranging demo application\n");
  status = CUSTOM_RANGING_SENSOR_Init(CUSTOM_VL53L3CX);

  if (status != BSP_ERROR_NONE)
  {
    printf("CUSTOM_RANGING_SENSOR_Init failed\n");
    while(1);
  }
}
uint8_t VL53L3CX_Check_Flag = 0;
static void MX_VL53L3CX_SimpleRanging_Process(void)
{
	uint32_t Id;
	RANGING_SENSOR_Result_t Result;
	if(VL53L3CX_Check_Flag == 0)
	{
		VL53L3CX_Check_Flag = 1;
		if(err_flag == 1){
			HAL_GPIO_WritePin(TOF_XSHUT_GPIO_Port, TOF_XSHUT_Pin, GPIO_PIN_SET);
			CUSTOM_RANGING_SENSOR_Init(CUSTOM_VL53L3CX);
			err_flag = 0;
		}

		CUSTOM_RANGING_SENSOR_ReadID(CUSTOM_VL53L3CX, &Id);
		CUSTOM_RANGING_SENSOR_GetCapabilities(CUSTOM_VL53L3CX, &Cap);

		Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
		Profile.TimingBudget = TIMING_BUDGET; /* 16 ms < TimingBudget < 500 ms */
		Profile.Frequency = 0; /* Induces intermeasurement period, set to ZERO for normal ranging */
		Profile.EnableAmbient = 1; /* Enable: 1, Disable: 0 */
		Profile.EnableSignal = 1; /* Enable: 1, Disable: 0 */

		/* set the profile if different from default one */
		CUSTOM_RANGING_SENSOR_ConfigProfile(CUSTOM_VL53L3CX, &Profile);

		status = CUSTOM_RANGING_SENSOR_Start(CUSTOM_VL53L3CX, RS_MODE_ASYNC_CONTINUOUS);
		if (status != BSP_ERROR_NONE)
		{
		//    printf("CUSTOM_RANGING_SENSOR_Start failed\n");
			while(1);
		}
	}


//  while (1)
// {
//    /* interrupt mode */
//    if (ToF_EventDetected != 0)
//    {
//      ToF_EventDetected = 0;
	status = CUSTOM_RANGING_SENSOR_GetDistance(CUSTOM_VL53L3CX, &Result);
	if(status == BSP_ERROR_NONE)
	{

		if(Result.ZoneResult[0].Distance[0] > 0 && Result.ZoneResult[0].Status[0] == 0){
			if(Result.ZoneResult[0].Distance[0] > 100000000)
			{
				tof_err_cnt++;
				if(tof_err_cnt > 10)
				{
					tof_err_cnt = 0;
					err_flag = 1;
				}
			}
			else
			{
				tof_err_cnt = 0;
				Distance = Result.ZoneResult[0].Distance[Result.ZoneResult[0].NumberOfTargets-1]+DistanceOffset;
				Distance1 = Result.ZoneResult[0].Distance[1];
				status1 = Result.ZoneResult[0].Status[1];
				if(Distance < 1100){
					ui.Status.Bit.OBJ_DETECT = 1;
					if(Distance > 900){
						ui.Status.Bit.DISTANCE_LEVEL = 3;
					}
					else if(Distance > 600){
						ui.Status.Bit.DISTANCE_LEVEL = 2;
					}
					else if(Distance > 300){
						ui.Status.Bit.DISTANCE_LEVEL = 1;
					}
					else{
						ui.Status.Bit.DISTANCE_LEVEL = 0;
					}
				}
				else{
					ui.Status.Bit.OBJ_DETECT = 0;
					ui.Status.Bit.DISTANCE_LEVEL = 3;
				}
			}
		}
	}
	else{
		tof_err_cnt++;
		if(tof_err_cnt > 10)
		{
			tof_err_cnt = 0;
			err_flag = 1;
		}
	}
	if(err_flag == 1){
		CUSTOM_RANGING_SENSOR_Stop(CUSTOM_VL53L3CX);
		VL53L3CX_Check_Flag = 0;
		CUSTOM_RANGING_SENSOR_DeInit(CUSTOM_VL53L3CX);
		HAL_GPIO_WritePin(TOF_XSHUT_GPIO_Port, TOF_XSHUT_Pin, GPIO_PIN_RESET);
		tof_err_cnt = 0;
	}
/*	else{
		CUSTOM_RANGING_SENSOR_Stop(CUSTOM_VL53L3CX);
		VL53L3CX_Check_Flag = 0;
	}
*/

/*

	*/
//	printf("\n1. Distance : %5ld , Status : %ld\n", (long)Result.ZoneResult[0].Distance[0], (long)Result.ZoneResult[0].Status[0]);

//	if (status == BSP_ERROR_NONE)
//	{
//	print_result(&Result);
//	}
//    }
//	HAL_Delay(POLLING_PERIOD);
//  }
}

//static void print_result(RANGING_SENSOR_Result_t *Result)
//{
//  uint8_t i, j;
//
//  for (i = 0; i < RANGING_SENSOR_MAX_NB_ZONES; i++)
//  {
//    printf("\nTargets = %lu", (unsigned long)Result->ZoneResult[i].NumberOfTargets);
//
//    for (j = 0; j < Result->ZoneResult[i].NumberOfTargets; j++)
//    {
//      printf("\n |---> ");
//
//      printf("Status = %ld, Distance = %5ld mm ",
//        (long)Result->ZoneResult[i].Status[j],
//        (long)Result->ZoneResult[i].Distance[j]);
//
//      if (Profile.EnableAmbient)
//        printf(", Ambient = %ld.%02ld kcps/spad",
//          (long)Result->ZoneResult[i].Ambient[j],
//          (long)decimal_part(Result->ZoneResult[i].Ambient[j]));
//
//      if (Profile.EnableSignal)
//        printf(", Signal = %ld.%02ld kcps/spad",
//          (long)Result->ZoneResult[i].Signal[j],
//          (long)decimal_part(Result->ZoneResult[i].Signal[j]));
//    }
//  }
//  printf ("\n");
//}
/*
static int32_t decimal_part(float_t x)
{
  int32_t int_part = (int32_t) x;
  return (int32_t)((x - int_part) * 100);
}
*/
#ifdef __cplusplus
}
#endif

/*
 * DIO.h
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_DIO_DIO_H_
#define SOURCE_DIO_DIO_H_



/* Private define ------------------------------------------------------------*/

#define InputPort_LOW			(0)
#define InputPort_HIGH			(1)

#define RUNNING_ON()				(HAL_GPIO_WritePin(	EXT_RUN_GPIO_Port, EXT_RUN_Pin, GPIO_PIN_RESET))
#define RUNNING_OFF()				(HAL_GPIO_WritePin(	EXT_RUN_GPIO_Port, EXT_RUN_Pin, GPIO_PIN_SET))
#define TEMP_WARRING_ON()			(HAL_GPIO_WritePin(	EXT_TEMP1_GPIO_Port, EXT_TEMP1_Pin, GPIO_PIN_RESET))
#define TEMP_WARRING_OFF()			(HAL_GPIO_WritePin(	EXT_TEMP1_GPIO_Port, EXT_TEMP1_Pin, GPIO_PIN_SET))
#define SMOKE_DETECT_ON()			(HAL_GPIO_WritePin(	EXT_SMK_GPIO_Port, EXT_SMK_Pin, GPIO_PIN_SET))
#define SMOKE_DETECT_OFF()			(HAL_GPIO_WritePin(	EXT_SMK_GPIO_Port, EXT_SMK_Pin, GPIO_PIN_RESET))
#define TEMP_ALARM_ON()				(HAL_GPIO_WritePin(	EXT_TEMP2_GPIO_Port, EXT_TEMP2_Pin, GPIO_PIN_SET))
#define TEMP_ALARM_OFF()			(HAL_GPIO_WritePin(	EXT_TEMP2_GPIO_Port, EXT_TEMP2_Pin, GPIO_PIN_RESET))


//Rotery Address
#define ID_11_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY11_GPIO_Port,ADDR_RTY11_Pin)
#define ID_12_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY12_GPIO_Port,ADDR_RTY12_Pin)
#define ID_13_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY13_GPIO_Port,ADDR_RTY13_Pin)
#define ID_14_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY14_GPIO_Port,ADDR_RTY14_Pin)
#define ID_21_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY21_GPIO_Port,ADDR_RTY21_Pin)
#define ID_22_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY22_GPIO_Port,ADDR_RTY22_Pin)
#define ID_23_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY23_GPIO_Port,ADDR_RTY23_Pin)
#define ID_24_Input_Check()		HAL_GPIO_ReadPin(ADDR_RTY24_GPIO_Port,ADDR_RTY24_Pin)

//DIP Switch
#define DIP_1_Input_Check()		HAL_GPIO_ReadPin(SET_DIP4_GPIO_Port,SET_DIP4_Pin)
#define DIP_2_Input_Check()		HAL_GPIO_ReadPin(SET_DIP3_GPIO_Port,SET_DIP3_Pin)
#define DIP_3_Input_Check()		HAL_GPIO_ReadPin(SET_DIP2_GPIO_Port,SET_DIP2_Pin)
#define DIP_4_Input_Check()		HAL_GPIO_ReadPin(SET_DIP1_GPIO_Port,SET_DIP1_Pin)
/* Private variables ---------------------------------------------------------*/
typedef struct
{
	uint8_t ID_Check_1;
	uint8_t ID_Check_2;
} _ID;
extern _ID ID;

/* Private function prototypes -----------------------------------------------*/
void FUN_GPIO_Init(void);
void FUN_GPIO_Routine(void);
#endif /* SOURCE_DIO_DIO_H_ */

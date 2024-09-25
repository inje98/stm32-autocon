/*
 * GPI.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef GPIO_GPI_H_
#define GPIO_GPI_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define InputPort_HIGH				(1)
#define InputPort_LOW				(0)


#define PORT_NUM_1					(1)				// 동력공급장치 : 무부하밸브(윈치동력)
#define PORT_NUM_2					(2)				// 동력공급장치 : 무부하밸브(투인양동력)
#define PORT_NUM_3					(3)				// 동력공급장치 : 방향전환밸브(수냉식냉각기)
#define PORT_NUM_4					(4)				// 동력공급장치 : 차단밸브(수냉식냉각기)
#define PORT_NUM_5					(5)				// 동력공급장치 : 차단밸브(축압기 충전)
#define PORT_NUM_6					(6)				// 동력공급장치 : 차단밸브(윈치동력)
#define PORT_NUM_7					(7)				// 윈치조립체 : 방향전환밸브(권선브레이크)
#define PORT_NUM_8					(8)				// 윈치조립체 : 방향전환밸브(보조브레이크)
#define PORT_NUM_9					(9)				// 윈치조립체 : 방향전환밸브(보조절단기)
#define PORT_NUM_10					(10)			// 윈치조립체 : 방향전환밸브(주브레이크)
#define PORT_NUM_11					(11)			// 윈치조립체 : 방향전환밸브(주절단기)
#define PORT_NUM_12					(12)			// 투인양장치 : 청수잠금밸브(세척기)
#define PORT_NUM_13					(13)			// 확성기
#define PORT_NUM_14					(14)			// SPARE
#define PORT_NUM_15					(15)			// SPARE
#define PORT_NUM_16					(16)			// SPARE
#define PORT_NUM_17					(17)			// 전원안정공급장치: 냉각기
#define PORT_NUM_18					(18)			// 전원안정공급장치: 히터


#define InputPort_CH_1				HAL_GPIO_ReadPin(IN_CH1_GPIO_Port,  IN_CH1_Pin)				// 동력공급장치 : 무부하밸브(윈치동력)
#define InputPort_CH_2				HAL_GPIO_ReadPin(IN_CH2_GPIO_Port,  IN_CH2_Pin)				// 동력공급장치 : 무부하밸브(투인양동력)
#define InputPort_CH_3				HAL_GPIO_ReadPin(IN_CH3_GPIO_Port,  IN_CH3_Pin)				// 동력공급장치 : 방향전환밸브(수냉식냉각기)
#define InputPort_CH_4				HAL_GPIO_ReadPin(IN_CH4_GPIO_Port,  IN_CH4_Pin)				// 동력공급장치 : 차단밸브(수냉식냉각기)
#define InputPort_CH_5				HAL_GPIO_ReadPin(IN_CH5_GPIO_Port,  IN_CH5_Pin)				// 동력공급장치 : 차단밸브(축압기 충전)
#define InputPort_CH_6				HAL_GPIO_ReadPin(IN_CH6_GPIO_Port,  IN_CH6_Pin)				// 동력공급장치 : 차단밸브(윈치동력)
#define InputPort_CH_7				HAL_GPIO_ReadPin(IN_CH7_GPIO_Port,  IN_CH7_Pin)				// 윈치조립체 : 방향전환밸브(권선브레이크)
#define InputPort_CH_8				HAL_GPIO_ReadPin(IN_CH8_GPIO_Port,  IN_CH8_Pin)				// 윈치조립체 : 방향전환밸브(보조브레이크)
#define InputPort_CH_9				HAL_GPIO_ReadPin(IN_CH9_GPIO_Port,  IN_CH9_Pin)				// 윈치조립체 : 방향전환밸브(보조절단기)
#define InputPort_CH_10				HAL_GPIO_ReadPin(IN_CH10_GPIO_Port, IN_CH10_Pin)			// 윈치조립체 : 방향전환밸브(주브레이크)
#define InputPort_CH_11				HAL_GPIO_ReadPin(IN_CH11_GPIO_Port, IN_CH11_Pin)			// 윈치조립체 : 방향전환밸브(주절단기)
#define InputPort_CH_12				HAL_GPIO_ReadPin(IN_CH12_GPIO_Port, IN_CH12_Pin)			// 투인양장치 : 청수잠금밸브(세척기)
#define InputPort_CH_13				HAL_GPIO_ReadPin(IN_CH13_GPIO_Port, IN_CH13_Pin)			// 확성기
#define InputPort_CH_14				HAL_GPIO_ReadPin(IN_CH14_GPIO_Port, IN_CH14_Pin)			// SPARE
#define InputPort_CH_15				HAL_GPIO_ReadPin(IN_CH15_GPIO_Port, IN_CH15_Pin)			// SPARE
#define InputPort_CH_16				HAL_GPIO_ReadPin(IN_CH16_GPIO_Port, IN_CH16_Pin)			// SPARE
#define InputPort_CH_17				HAL_GPIO_ReadPin(IN_CH17_GPIO_Port, IN_CH17_Pin)			// 전원안정공급장치: 냉각기
#define InputPort_CH_18				HAL_GPIO_ReadPin(IN_CH18_GPIO_Port, IN_CH18_Pin)			// 전원안정공급장치: 히터

/* Private variables ---------------------------------------------------------*/
typedef struct {

} _GPI;
extern _GPI GPI;


/* Private function prototypes -----------------------------------------------*/
void FUN_GPI_PortCheck(void);

#endif /* GPIO_GPI_H_ */

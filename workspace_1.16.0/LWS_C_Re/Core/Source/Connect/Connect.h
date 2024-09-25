/*
 * Connect.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef CONNECT_CONNECT_H_
#define CONNECT_CONNECT_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
typedef struct {

} _Connect;
extern _Connect Connect;


/* Private function prototypes -----------------------------------------------*/
void FUN_Connect_Init(void);
void FUN_Connect_Routine(void);

#endif /* CONNECT_CONNECT_H_ */

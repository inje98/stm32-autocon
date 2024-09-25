/*
 * Application.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
typedef struct {

} _Application;
extern _Application Application;


/* Private function prototypes -----------------------------------------------*/
void FUN_Application_Init(void);
void FUN_Application_Routine(void);

#endif /* APPLICATION_APPLICATION_H_ */

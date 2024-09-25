/*
 * DAC.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef DAC_DAC_H_
#define DAC_DAC_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
// DAC Channel Select
#define DAC3_CH_SEL				(0)
#define DAC4_CH_SEL				(1)
#define DAC5_CH_SEL				(2)
// 4mA
#define mA_4					(4)
// 0 ~ 10 V
// DAC3 Adresss n
#define DAC3_CH0				(uint8_t)(0x00)			//윈치조립체 권선구동 : 비례제어밸브 에러신호
#define DAC3_CH1				(uint8_t)(0x01)			//윈치조립체 비상구동 : 비례제어밸브 에러신호
#define DAC3_CH2				(uint8_t)(0x02)			//투인양장치 메인실린더1 : 비례제어밸브 에러신호
#define DAC3_CH3				(uint8_t)(0x03)			//투인양장치 메인실린더2 : 비례제어밸브 에러신호
#define DAC3_CH4				(uint8_t)(0x04)			//투인양장치 서보실린더1 : 비례제어밸브 에러신호
#define DAC3_CH5				(uint8_t)(0x05)			//투인양장치 서보실린더2 : 비례제어밸브 에러신호
#define DAC3_CH6				(uint8_t)(0x06)			//DAC_SPARE
#define DAC3_CH7				(uint8_t)(0x07)			//--

// 0 ~ 5 V
// DAC4 Adresss n
#define DAC4_CH0				(uint8_t)(0x00)			//DAC_20mA_SPARE1
#define DAC4_CH1				(uint8_t)(0x01)			//DAC_20mA_SPARE2
#define DAC4_CH2				(uint8_t)(0x02)			//동력공급장치 : 온도센서(저유기조립체)
#define DAC4_CH3				(uint8_t)(0x03)			//동력공급장치 : 유량계(투인양동력)
#define DAC4_CH4				(uint8_t)(0x04)			//동력공급장치 : 압력변환기(투인양동력)
#define DAC4_CH5				(uint8_t)(0x05)			//동력공급장치 : 압력변환기(윈치동력)
#define DAC4_CH6				(uint8_t)(0x06)			//투인양장치 : 실린더1(수축)압력변환기
#define DAC4_CH7				(uint8_t)(0x07)			//투인양장치 : 실린더1(팽창)압력변환기
#define DAC4_CH8				(uint8_t)(0x08)			//투인양장치 : 실린더2(수축)압력변환기
#define DAC4_CH9				(uint8_t)(0x09)			//투인양장치 : 실린더2(팽창)압력변환기
#define DAC4_CH10				(uint8_t)(0x0A)			//투인양장치 : 서보실린더1(수축)압력변환기
#define DAC4_CH11				(uint8_t)(0x0B)			//투인양장치 : 서보실린더1(팽창)압력변환기
#define DAC4_CH12				(uint8_t)(0x0C)			//투인양장치 : 서보실린더2(수축)압력변환기
#define DAC4_CH13				(uint8_t)(0x0D)			//투인양장치 : 서보실린더2(팽창)압력변환기

// 0 ~ 5 V
// DAC5 Adresss n
#define DAC5_CH0				(uint8_t)(0x00)			//투인양장치 : 메인실린더2 LVDT
#define DAC5_CH1				(uint8_t)(0x01)			//투인양장치 : 서보실린더2 LVDT
#define DAC5_CH2				(uint8_t)(0x02)			//투인양장치 : 그립퍼 LVDT2
#define DAC5_CH3				(uint8_t)(0x03)			//윈치조립체 : 장력센서
#define DAC5_CH4				(uint8_t)(0x04)			//투인양장치 : 그립퍼 LVDT3
#define DAC5_CH5				(uint8_t)(0x05)			//투인양장치 : 메인실린더1 LVDT
#define DAC5_CH6				(uint8_t)(0x06)			//투인양장치 : 메인실린더1 LVDT
#define DAC5_CH7				(uint8_t)(0x07)			//투인양장치 : 그립퍼 LVDT1
/* Private variables ---------------------------------------------------------*/
typedef struct
{

} _Dac;
extern _Dac Dac;


/* Private function prototypes -----------------------------------------------*/
void FUN_DAC_Init(void);
void FUN_DAC_Routine(void);
void FUN_DAC_Converter_set_dac_code(uint8_t u1t_ch_sel, uint8_t u1t_dac_address, float ft_dac_volt);
void FUN_DAC_Converter_Gripper(void);
void FUN_DAC_Converter_Oil(void);

#endif /* DAC_DAC_H_ */

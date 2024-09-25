/*
 * GPO.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef GPIO_GPO_H_
#define GPIO_GPO_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#ifndef OUTPUTPORT_H_
#define OUTPUTPORT_H_

/*-------Include Header Files-----------------------------------------------*/
#include "main.h"

/*-------Macro Declaration--------------------------------------------------*/

#define OUTPUT_PORT_HIGH			(1)
#define OUTPUT_PORT_LOW				(0)

// PORT NUM
#define OUTPUT_PORT_NUM_1			(1)		// 동력공급장치 : 레벨스위치1(저유기조립체)
#define OUTPUT_PORT_NUM_2			(2)		// 동력공급장치 : 레벨스위치2(저유기조립체)
#define OUTPUT_PORT_NUM_3			(3)		// 동력공급장치 : 레벨스위치3(저유기조립체)
#define OUTPUT_PORT_NUM_4			(4)		// 동력공급장치 : 비상정지스위치
#define OUTPUT_PORT_NUM_5			(5)		// 동력공급장치 : 압력스위치(감김)
#define OUTPUT_PORT_NUM_6			(6)		// 동력공급장치 : 압력스위치(권선)
#define OUTPUT_PORT_NUM_7			(7)		// 동력공급장치 : 압력스위치(부스터)
#define OUTPUT_PORT_NUM_8			(8)		// 동력공급장치 : 압력스위치(수냉식냉각기)
#define OUTPUT_PORT_NUM_9			(9)		// 동력공급장치 : 압력스위치(압력초과)
#define OUTPUT_PORT_NUM_10			(10)	// 동력공급장치 : 압력스위치(축압기 부족1)
#define OUTPUT_PORT_NUM_11			(11)	// 동력공급장치 : 압력스위치(축압기 부족2)
#define OUTPUT_PORT_NUM_12			(12)	// 동력공급장치 : 압력스위치(축압기 충전완료)
#define OUTPUT_PORT_NUM_13			(13)	// 동력공급장치 : 압력스위치(투인양동력)
#define OUTPUT_PORT_NUM_14			(14)	// 동력공급장치 : 압력스위치(풀림)
#define OUTPUT_PORT_NUM_15			(15)	// 동력공급장치 : 필터막힘스위치(리턴)
#define OUTPUT_PORT_NUM_16			(16)	// 동력공급장치 : 필터막힘스위치(부스터펌프)
#define OUTPUT_PORT_NUM_17			(17)	// 동력공급장치 : 필터막힘스위치(윈치구동)
#define OUTPUT_PORT_NUM_18			(18)	// 동력공급장치 : 필터막힘스위치(투인양)
#define OUTPUT_PORT_NUM_19			(19)	// 동력공급장치 윈치동력 : 비례제어밸브 에러신호
#define OUTPUT_PORT_NUM_20			(20)	// 윈치조립체 : 5회전 감지스위치
#define OUTPUT_PORT_NUM_21			(21)	// 윈치조립체 : 근접센서(우측A)
#define OUTPUT_PORT_NUM_22			(22)	// 윈치조립체 : 근접센서(우측B)
#define OUTPUT_PORT_NUM_23			(23)	// 윈치조립체 : 근접센서(좌측A)
#define OUTPUT_PORT_NUM_24			(24)	// 윈치조립체 : 근접센서(좌측B)
#define OUTPUT_PORT_NUM_25			(25)	// 윈치조립체 : 비상정지스위치
#define OUTPUT_PORT_NUM_26			(26)	// 윈치조립체 : 압력스위치(권선브레이크)
#define OUTPUT_PORT_NUM_27			(27)	// 윈치조립체 : 압력스위치(보조브레이크)
#define OUTPUT_PORT_NUM_28			(28)	// 윈치조립체 : 압력스위치(주브레이크)
#define OUTPUT_PORT_NUM_29			(29)	// 윈치조립체 : 권선유압모터(방향)
#define OUTPUT_PORT_NUM_30			(30)	// 윈치조립체 : 권선유압모터(속도)
#define OUTPUT_PORT_NUM_31			(31)	// 윈치조립체 : 유압모터A(방향)
#define OUTPUT_PORT_NUM_32			(32)	// 윈치조립체 : 유압모터A(속도)
#define OUTPUT_PORT_NUM_33			(33)	// 윈치조립체 : 유압모터B(방향)
#define OUTPUT_PORT_NUM_34			(34)	// 윈치조립체 : 유압모터B(속도)
#define OUTPUT_PORT_NUM_35			(35)	// 윈치조립체 : 칼날감지센서(보조절단기)
#define OUTPUT_PORT_NUM_36			(36)	// 윈치조립체 : 칼날감지센서(주절단기)
#define OUTPUT_PORT_NUM_37			(37)	// 투인양장치 : 근접스위치1
#define OUTPUT_PORT_NUM_38			(38)	// 투인양장치 : 근접스위치2
#define OUTPUT_PORT_NUM_39			(39)	// 투인양장치 : 근접스위치3
#define OUTPUT_PORT_NUM_40			(40)	// 투인양장치 : 근접스위치4
#define OUTPUT_PORT_NUM_41			(41)	// 투인양장치 : 근접스위치5
#define OUTPUT_PORT_NUM_42			(42)	// 투인양장치 : 근접스위치6
#define OUTPUT_PORT_NUM_43			(43)	// 투인양장치 : 압력스위치(세척기)
#define OUTPUT_PORT_NUM_44		(44)	// SPARE
#define OUTPUT_PORT_NUM_45		(45)	// SPARE
#define OUTPUT_PORT_NUM_46		(46)	// SPARE
#define OUTPUT_PORT_NUM_47		(47)	// SPARE
#define OUTPUT_PORT_NUM_48		(48)	// SPARE


// LO OUTPUT
#define OUTPUT_CH_1_LOW()			HAL_GPIO_WritePin(OUT_CH1_GPIO_Port,  OUT_CH1_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 레벨스위치1(저유기조립체)
#define OUTPUT_CH_2_LOW()			HAL_GPIO_WritePin(OUT_CH2_GPIO_Port,  OUT_CH2_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 레벨스위치2(저유기조립체)
#define OUTPUT_CH_3_LOW()			HAL_GPIO_WritePin(OUT_CH3_GPIO_Port,  OUT_CH3_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 레벨스위치3(저유기조립체)
#define OUTPUT_CH_4_LOW()			HAL_GPIO_WritePin(OUT_CH4_GPIO_Port,  OUT_CH4_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 비상정지스위치
#define OUTPUT_CH_5_LOW()			HAL_GPIO_WritePin(OUT_CH5_GPIO_Port,  OUT_CH5_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 압력스위치(감김)
#define OUTPUT_CH_6_LOW()			HAL_GPIO_WritePin(OUT_CH6_GPIO_Port,  OUT_CH6_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 압력스위치(권선)
#define OUTPUT_CH_7_LOW()			HAL_GPIO_WritePin(OUT_CH7_GPIO_Port,  OUT_CH7_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 압력스위치(부스터)
#define OUTPUT_CH_8_LOW()			HAL_GPIO_WritePin(OUT_CH8_GPIO_Port,  OUT_CH8_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 압력스위치(수냉식냉각기)
#define OUTPUT_CH_9_LOW()			HAL_GPIO_WritePin(OUT_CH9_GPIO_Port,  OUT_CH9_Pin, GPIO_PIN_RESET)		// 동력공급장치 : 압력스위치(압력초과)
#define OUTPUT_CH_10_LOW()			HAL_GPIO_WritePin(OUT_CH10_GPIO_Port,  OUT_CH10_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 압력스위치(축압기 부족1)
#define OUTPUT_CH_11_LOW()			HAL_GPIO_WritePin(OUT_CH11_GPIO_Port,  OUT_CH11_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 압력스위치(축압기 부족2)
#define OUTPUT_CH_12_LOW()			HAL_GPIO_WritePin(OUT_CH12_GPIO_Port,  OUT_CH12_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 압력스위치(축압기 충전완료)
#define OUTPUT_CH_13_LOW()			HAL_GPIO_WritePin(OUT_CH13_GPIO_Port,  OUT_CH13_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 압력스위치(투인양동력)
#define OUTPUT_CH_14_LOW()			HAL_GPIO_WritePin(OUT_CH14_GPIO_Port,  OUT_CH14_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 압력스위치(풀림)
#define OUTPUT_CH_15_LOW()			HAL_GPIO_WritePin(OUT_CH15_GPIO_Port,  OUT_CH15_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 필터막힘스위치(리턴)
#define OUTPUT_CH_16_LOW()			HAL_GPIO_WritePin(OUT_CH16_GPIO_Port,  OUT_CH16_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 필터막힘스위치(부스터펌프)
#define OUTPUT_CH_17_LOW()			HAL_GPIO_WritePin(OUT_CH17_GPIO_Port,  OUT_CH17_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 필터막힘스위치(윈치구동)
#define OUTPUT_CH_18_LOW()			HAL_GPIO_WritePin(OUT_CH18_GPIO_Port,  OUT_CH18_Pin, GPIO_PIN_RESET)	// 동력공급장치 : 필터막힘스위치(투인양)
#define OUTPUT_CH_19_LOW()			HAL_GPIO_WritePin(OUT_CH19_GPIO_Port,  OUT_CH19_Pin, GPIO_PIN_RESET)	// 동력공급장치 윈치동력 : 비례제어밸브 에러신호
#define OUTPUT_CH_20_LOW()			HAL_GPIO_WritePin(OUT_CH20_GPIO_Port,  OUT_CH20_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 5회전 감지스위치
#define OUTPUT_CH_21_LOW()			HAL_GPIO_WritePin(OUT_CH21_GPIO_Port,  OUT_CH21_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 근접센서(우측A)
#define OUTPUT_CH_22_LOW()			HAL_GPIO_WritePin(OUT_CH22_GPIO_Port,  OUT_CH22_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 근접센서(우측B)
#define OUTPUT_CH_23_LOW()			HAL_GPIO_WritePin(OUT_CH23_GPIO_Port,  OUT_CH23_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 근접센서(좌측A)
#define OUTPUT_CH_24_LOW()			HAL_GPIO_WritePin(OUT_CH24_GPIO_Port,  OUT_CH24_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 근접센서(좌측B)
#define OUTPUT_CH_25_LOW()			HAL_GPIO_WritePin(OUT_CH25_GPIO_Port,  OUT_CH25_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 비상정지스위치
#define OUTPUT_CH_26_LOW()			HAL_GPIO_WritePin(OUT_CH26_GPIO_Port,  OUT_CH26_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 압력스위치(권선브레이크)
#define OUTPUT_CH_27_LOW()			HAL_GPIO_WritePin(OUT_CH27_GPIO_Port,  OUT_CH27_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 압력스위치(보조브레이크)
#define OUTPUT_CH_28_LOW()			HAL_GPIO_WritePin(OUT_CH28_GPIO_Port,  OUT_CH28_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 압력스위치(주브레이크)
#define OUTPUT_CH_29_LOW()			HAL_GPIO_WritePin(OUT_CH29_GPIO_Port,  OUT_CH29_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 권선유압모터(방향)
#define OUTPUT_CH_30_LOW()			HAL_GPIO_WritePin(OUT_CH30_GPIO_Port,  OUT_CH30_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 권선유압모터(속도)
#define OUTPUT_CH_31_LOW()			HAL_GPIO_WritePin(OUT_CH31_GPIO_Port,  OUT_CH31_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 유압모터A(방향)
#define OUTPUT_CH_32_LOW()			HAL_GPIO_WritePin(OUT_CH32_GPIO_Port,  OUT_CH32_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 유압모터A(속도)
#define OUTPUT_CH_33_LOW()			HAL_GPIO_WritePin(OUT_CH33_GPIO_Port,  OUT_CH33_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 유압모터B(방향)
#define OUTPUT_CH_34_LOW()			HAL_GPIO_WritePin(OUT_CH34_GPIO_Port,  OUT_CH34_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 유압모터B(속도)
#define OUTPUT_CH_35_LOW()			HAL_GPIO_WritePin(OUT_CH35_GPIO_Port,  OUT_CH35_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 칼날감지센서(보조절단기)
#define OUTPUT_CH_36_LOW()			HAL_GPIO_WritePin(OUT_CH36_GPIO_Port,  OUT_CH36_Pin, GPIO_PIN_RESET)	// 윈치조립체 : 칼날감지센서(주절단기)
#define OUTPUT_CH_37_LOW()			HAL_GPIO_WritePin(OUT_CH37_GPIO_Port,  OUT_CH37_Pin, GPIO_PIN_RESET)	// 투인양장치 : 근접스위치1
#define OUTPUT_CH_38_LOW()			HAL_GPIO_WritePin(OUT_CH38_GPIO_Port,  OUT_CH38_Pin, GPIO_PIN_RESET)	// 투인양장치 : 근접스위치2
#define OUTPUT_CH_39_LOW()			HAL_GPIO_WritePin(OUT_CH39_GPIO_Port,  OUT_CH39_Pin, GPIO_PIN_RESET)	// 투인양장치 : 근접스위치3
#define OUTPUT_CH_40_LOW()			HAL_GPIO_WritePin(OUT_CH40_GPIO_Port,  OUT_CH40_Pin, GPIO_PIN_RESET)	// 투인양장치 : 근접스위치4
#define OUTPUT_CH_41_LOW()			HAL_GPIO_WritePin(OUT_CH41_GPIO_Port,  OUT_CH41_Pin, GPIO_PIN_RESET)	// 투인양장치 : 근접스위치5
#define OUTPUT_CH_42_LOW()			HAL_GPIO_WritePin(OUT_CH42_GPIO_Port,  OUT_CH42_Pin, GPIO_PIN_RESET)	// 투인양장치 : 근접스위치6
#define OUTPUT_CH_43_LOW()			HAL_GPIO_WritePin(OUT_CH43_GPIO_Port,  OUT_CH43_Pin, GPIO_PIN_RESET)	// 투인양장치 : 압력스위치(세척기)
#define OUTPUT_CH_44_LOW()			HAL_GPIO_WritePin(OUT_CH44_GPIO_Port,  OUT_CH44_Pin, GPIO_PIN_RESET)	// SPARE
#define OUTPUT_CH_45_LOW()			HAL_GPIO_WritePin(OUT_CH45_GPIO_Port,  OUT_CH45_Pin, GPIO_PIN_RESET)	// SPARE
#define OUTPUT_CH_46_LOW()			HAL_GPIO_WritePin(OUT_CH46_GPIO_Port,  OUT_CH46_Pin, GPIO_PIN_RESET)	// SPARE
#define OUTPUT_CH_47_LOW()			HAL_GPIO_WritePin(OUT_CH47_GPIO_Port,  OUT_CH47_Pin, GPIO_PIN_RESET)	// SPARE
#define OUTPUT_CH_48_LOW()			HAL_GPIO_WritePin(OUT_CH48_GPIO_Port,  OUT_CH48_Pin, GPIO_PIN_RESET)	// SPARE


// HI OUTPUT
#define OUTPUT_CH_1_HIGH()			HAL_GPIO_WritePin(OUT_CH1_GPIO_Port,  OUT_CH1_Pin, GPIO_PIN_SET)		// 동력공급장치 : 레벨스위치1(저유기조립체)
#define OUTPUT_CH_2_HIGH()			HAL_GPIO_WritePin(OUT_CH2_GPIO_Port,  OUT_CH2_Pin, GPIO_PIN_SET)		// 동력공급장치 : 레벨스위치2(저유기조립체)
#define OUTPUT_CH_3_HIGH()			HAL_GPIO_WritePin(OUT_CH3_GPIO_Port,  OUT_CH3_Pin, GPIO_PIN_SET)		// 동력공급장치 : 레벨스위치3(저유기조립체)
#define OUTPUT_CH_4_HIGH()			HAL_GPIO_WritePin(OUT_CH4_GPIO_Port,  OUT_CH4_Pin, GPIO_PIN_SET)		// 동력공급장치 : 비상정지스위치
#define OUTPUT_CH_5_HIGH()			HAL_GPIO_WritePin(OUT_CH5_GPIO_Port,  OUT_CH5_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(감김)
#define OUTPUT_CH_6_HIGH()			HAL_GPIO_WritePin(OUT_CH6_GPIO_Port,  OUT_CH6_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(권선)
#define OUTPUT_CH_7_HIGH()			HAL_GPIO_WritePin(OUT_CH7_GPIO_Port,  OUT_CH7_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(부스터)
#define OUTPUT_CH_8_HIGH()			HAL_GPIO_WritePin(OUT_CH8_GPIO_Port,  OUT_CH8_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(수냉식냉각기)
#define OUTPUT_CH_9_HIGH()			HAL_GPIO_WritePin(OUT_CH9_GPIO_Port,  OUT_CH9_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(압력초과)
#define OUTPUT_CH_10_HIGH()			HAL_GPIO_WritePin(OUT_CH10_GPIO_Port,  OUT_CH10_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(축압기 부족1)
#define OUTPUT_CH_11_HIGH()			HAL_GPIO_WritePin(OUT_CH11_GPIO_Port,  OUT_CH11_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(축압기 부족2)
#define OUTPUT_CH_12_HIGH()			HAL_GPIO_WritePin(OUT_CH12_GPIO_Port,  OUT_CH12_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(축압기 충전완료)
#define OUTPUT_CH_13_HIGH()			HAL_GPIO_WritePin(OUT_CH13_GPIO_Port,  OUT_CH13_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(투인양동력)
#define OUTPUT_CH_14_HIGH()			HAL_GPIO_WritePin(OUT_CH14_GPIO_Port,  OUT_CH14_Pin, GPIO_PIN_SET)		// 동력공급장치 : 압력스위치(풀림)
#define OUTPUT_CH_15_HIGH()			HAL_GPIO_WritePin(OUT_CH15_GPIO_Port,  OUT_CH15_Pin, GPIO_PIN_SET)		// 동력공급장치 : 필터막힘스위치(리턴)
#define OUTPUT_CH_16_HIGH()			HAL_GPIO_WritePin(OUT_CH16_GPIO_Port,  OUT_CH16_Pin, GPIO_PIN_SET)		// 동력공급장치 : 필터막힘스위치(부스터펌프)
#define OUTPUT_CH_17_HIGH()			HAL_GPIO_WritePin(OUT_CH17_GPIO_Port,  OUT_CH17_Pin, GPIO_PIN_SET)		// 동력공급장치 : 필터막힘스위치(윈치구동)
#define OUTPUT_CH_18_HIGH()			HAL_GPIO_WritePin(OUT_CH18_GPIO_Port,  OUT_CH18_Pin, GPIO_PIN_SET)		// 동력공급장치 : 필터막힘스위치(투인양)
#define OUTPUT_CH_19_HIGH()			HAL_GPIO_WritePin(OUT_CH19_GPIO_Port,  OUT_CH19_Pin, GPIO_PIN_SET)		// 동력공급장치 윈치동력 : 비례제어밸브 에러신호
#define OUTPUT_CH_20_HIGH()			HAL_GPIO_WritePin(OUT_CH20_GPIO_Port,  OUT_CH20_Pin, GPIO_PIN_SET)		// 윈치조립체 : 5회전 감지스위치
#define OUTPUT_CH_21_HIGH()			HAL_GPIO_WritePin(OUT_CH21_GPIO_Port,  OUT_CH21_Pin, GPIO_PIN_SET)		// 윈치조립체 : 근접센서(우측A)
#define OUTPUT_CH_22_HIGH()			HAL_GPIO_WritePin(OUT_CH22_GPIO_Port,  OUT_CH22_Pin, GPIO_PIN_SET)		// 윈치조립체 : 근접센서(우측B)
#define OUTPUT_CH_23_HIGH()			HAL_GPIO_WritePin(OUT_CH23_GPIO_Port,  OUT_CH23_Pin, GPIO_PIN_SET)		// 윈치조립체 : 근접센서(좌측A)
#define OUTPUT_CH_24_HIGH()			HAL_GPIO_WritePin(OUT_CH24_GPIO_Port,  OUT_CH24_Pin, GPIO_PIN_SET)		// 윈치조립체 : 근접센서(좌측B)
#define OUTPUT_CH_25_HIGH()			HAL_GPIO_WritePin(OUT_CH25_GPIO_Port,  OUT_CH25_Pin, GPIO_PIN_SET)		// 윈치조립체 : 비상정지스위치
#define OUTPUT_CH_26_HIGH()			HAL_GPIO_WritePin(OUT_CH26_GPIO_Port,  OUT_CH26_Pin, GPIO_PIN_SET)		// 윈치조립체 : 압력스위치(권선브레이크)
#define OUTPUT_CH_27_HIGH()			HAL_GPIO_WritePin(OUT_CH27_GPIO_Port,  OUT_CH27_Pin, GPIO_PIN_SET)		// 윈치조립체 : 압력스위치(보조브레이크)
#define OUTPUT_CH_28_HIGH()			HAL_GPIO_WritePin(OUT_CH28_GPIO_Port,  OUT_CH28_Pin, GPIO_PIN_SET)		// 윈치조립체 : 압력스위치(주브레이크)
#define OUTPUT_CH_29_HIGH()			HAL_GPIO_WritePin(OUT_CH29_GPIO_Port,  OUT_CH29_Pin, GPIO_PIN_SET)		// 윈치조립체 : 권선유압모터(방향)
#define OUTPUT_CH_30_HIGH()			HAL_GPIO_WritePin(OUT_CH30_GPIO_Port,  OUT_CH30_Pin, GPIO_PIN_SET)		// 윈치조립체 : 권선유압모터(속도)
#define OUTPUT_CH_31_HIGH()			HAL_GPIO_WritePin(OUT_CH31_GPIO_Port,  OUT_CH31_Pin, GPIO_PIN_SET)		// 윈치조립체 : 유압모터A(방향)
#define OUTPUT_CH_32_HIGH()			HAL_GPIO_WritePin(OUT_CH32_GPIO_Port,  OUT_CH32_Pin, GPIO_PIN_SET)		// 윈치조립체 : 유압모터A(속도)
#define OUTPUT_CH_33_HIGH()			HAL_GPIO_WritePin(OUT_CH33_GPIO_Port,  OUT_CH33_Pin, GPIO_PIN_SET)		// 윈치조립체 : 유압모터B(방향)
#define OUTPUT_CH_34_HIGH()			HAL_GPIO_WritePin(OUT_CH34_GPIO_Port,  OUT_CH34_Pin, GPIO_PIN_SET)		// 윈치조립체 : 유압모터B(속도)
#define OUTPUT_CH_35_HIGH()			HAL_GPIO_WritePin(OUT_CH35_GPIO_Port,  OUT_CH35_Pin, GPIO_PIN_SET)		// 윈치조립체 : 칼날감지센서(보조절단기)
#define OUTPUT_CH_36_HIGH()			HAL_GPIO_WritePin(OUT_CH36_GPIO_Port,  OUT_CH36_Pin, GPIO_PIN_SET)		// 윈치조립체 : 칼날감지센서(주절단기)
#define OUTPUT_CH_37_HIGH()			HAL_GPIO_WritePin(OUT_CH37_GPIO_Port,  OUT_CH37_Pin, GPIO_PIN_SET)		// 투인양장치 : 근접스위치1
#define OUTPUT_CH_38_HIGH()			HAL_GPIO_WritePin(OUT_CH38_GPIO_Port,  OUT_CH38_Pin, GPIO_PIN_SET)		// 투인양장치 : 근접스위치2
#define OUTPUT_CH_39_HIGH()			HAL_GPIO_WritePin(OUT_CH39_GPIO_Port,  OUT_CH39_Pin, GPIO_PIN_SET)		// 투인양장치 : 근접스위치3
#define OUTPUT_CH_40_HIGH()			HAL_GPIO_WritePin(OUT_CH40_GPIO_Port,  OUT_CH40_Pin, GPIO_PIN_SET)		// 투인양장치 : 근접스위치4
#define OUTPUT_CH_41_HIGH()			HAL_GPIO_WritePin(OUT_CH41_GPIO_Port,  OUT_CH41_Pin, GPIO_PIN_SET)		// 투인양장치 : 근접스위치5
#define OUTPUT_CH_42_HIGH()			HAL_GPIO_WritePin(OUT_CH42_GPIO_Port,  OUT_CH42_Pin, GPIO_PIN_SET)		// 투인양장치 : 근접스위치6
#define OUTPUT_CH_43_HIGH()			HAL_GPIO_WritePin(OUT_CH43_GPIO_Port,  OUT_CH43_Pin, GPIO_PIN_SET)		// 투인양장치 : 압력스위치(세척기)
#define OUTPUT_CH_44_HIGH()			HAL_GPIO_WritePin(OUT_CH44_GPIO_Port,  OUT_CH44_Pin, GPIO_PIN_SET)		// SPARE
#define OUTPUT_CH_45_HIGH()			HAL_GPIO_WritePin(OUT_CH45_GPIO_Port,  OUT_CH45_Pin, GPIO_PIN_SET)		// SPARE
#define OUTPUT_CH_46_HIGH()			HAL_GPIO_WritePin(OUT_CH46_GPIO_Port,  OUT_CH46_Pin, GPIO_PIN_SET)		// SPARE
#define OUTPUT_CH_47_HIGH()			HAL_GPIO_WritePin(OUT_CH47_GPIO_Port,  OUT_CH47_Pin, GPIO_PIN_SET)		// SPARE
#define OUTPUT_CH_48_HIGH()			HAL_GPIO_WritePin(OUT_CH48_GPIO_Port,  OUT_CH48_Pin, GPIO_PIN_SET)		// SPARE


// READ OUTPUT PORT
#define OUTPUT_CH_1_READ()			HAL_GPIO_ReadPin(OUT_CH1_GPIO_Port,		OUT_CH1_Pin)				// 동력공급장치 : 레벨스위치1(저유기조립체)
#define OUTPUT_CH_2_READ()			HAL_GPIO_ReadPin(OUT_CH2_GPIO_Port,		OUT_CH2_Pin)				// 동력공급장치 : 레벨스위치2(저유기조립체)
#define OUTPUT_CH_3_READ()			HAL_GPIO_ReadPin(OUT_CH3_GPIO_Port,		OUT_CH3_Pin)				// 동력공급장치 : 레벨스위치3(저유기조립체)
#define OUTPUT_CH_4_READ()			HAL_GPIO_ReadPin(OUT_CH4_GPIO_Port,		OUT_CH4_Pin)				// 동력공급장치 : 비상정지스위치
#define OUTPUT_CH_5_READ()			HAL_GPIO_ReadPin(OUT_CH5_GPIO_Port,		OUT_CH5_Pin)				// 동력공급장치 : 압력스위치(감김)
#define OUTPUT_CH_6_READ()			HAL_GPIO_ReadPin(OUT_CH6_GPIO_Port,		OUT_CH6_Pin)				// 동력공급장치 : 압력스위치(권선)
#define OUTPUT_CH_7_READ()			HAL_GPIO_ReadPin(OUT_CH7_GPIO_Port,		OUT_CH7_Pin)				// 동력공급장치 : 압력스위치(부스터)
#define OUTPUT_CH_8_READ()			HAL_GPIO_ReadPin(OUT_CH8_GPIO_Port,		OUT_CH8_Pin)				// 동력공급장치 : 압력스위치(수냉식냉각기)
#define OUTPUT_CH_9_READ()			HAL_GPIO_ReadPin(OUT_CH9_GPIO_Port,		OUT_CH9_Pin)				// 동력공급장치 : 압력스위치(압력초과)
#define OUTPUT_CH_10_READ()			HAL_GPIO_ReadPin(OUT_CH10_GPIO_Port,	OUT_CH10_Pin)				// 동력공급장치 : 압력스위치(축압기 부족1)
#define OUTPUT_CH_11_READ()			HAL_GPIO_ReadPin(OUT_CH11_GPIO_Port,	OUT_CH11_Pin)				// 동력공급장치 : 압력스위치(축압기 부족2)
#define OUTPUT_CH_12_READ()			HAL_GPIO_ReadPin(OUT_CH12_GPIO_Port,	OUT_CH12_Pin)				// 동력공급장치 : 압력스위치(축압기 충전완료)
#define OUTPUT_CH_13_READ()			HAL_GPIO_ReadPin(OUT_CH13_GPIO_Port,	OUT_CH13_Pin)				// 동력공급장치 : 압력스위치(투인양동력)
#define OUTPUT_CH_14_READ()			HAL_GPIO_ReadPin(OUT_CH14_GPIO_Port,	OUT_CH14_Pin)				// 동력공급장치 : 압력스위치(풀림)
#define OUTPUT_CH_15_READ()			HAL_GPIO_ReadPin(OUT_CH15_GPIO_Port,	OUT_CH15_Pin)				// 동력공급장치 : 필터막힘스위치(리턴)
#define OUTPUT_CH_16_READ()			HAL_GPIO_ReadPin(OUT_CH16_GPIO_Port,	OUT_CH16_Pin)				// 동력공급장치 : 필터막힘스위치(부스터펌프)
#define OUTPUT_CH_17_READ()			HAL_GPIO_ReadPin(OUT_CH17_GPIO_Port,	OUT_CH17_Pin)				// 동력공급장치 : 필터막힘스위치(윈치구동)
#define OUTPUT_CH_18_READ()			HAL_GPIO_ReadPin(OUT_CH18_GPIO_Port,	OUT_CH18_Pin)				// 동력공급장치 : 필터막힘스위치(투인양)
#define OUTPUT_CH_19_READ()			HAL_GPIO_ReadPin(OUT_CH19_GPIO_Port,	OUT_CH19_Pin)				// 동력공급장치 윈치동력 : 비례제어밸브 에러신호
#define OUTPUT_CH_20_READ()			HAL_GPIO_ReadPin(OUT_CH20_GPIO_Port,	OUT_CH20_Pin)				// 윈치조립체 : 5회전 감지스위치
#define OUTPUT_CH_21_READ()			HAL_GPIO_ReadPin(OUT_CH21_GPIO_Port,	OUT_CH21_Pin)				// 윈치조립체 : 근접센서(우측A)
#define OUTPUT_CH_22_READ()			HAL_GPIO_ReadPin(OUT_CH22_GPIO_Port,	OUT_CH22_Pin)				// 윈치조립체 : 근접센서(우측B)
#define OUTPUT_CH_23_READ()			HAL_GPIO_ReadPin(OUT_CH23_GPIO_Port,	OUT_CH23_Pin)				// 윈치조립체 : 근접센서(좌측A)
#define OUTPUT_CH_24_READ()			HAL_GPIO_ReadPin(OUT_CH24_GPIO_Port,	OUT_CH24_Pin)				// 윈치조립체 : 근접센서(좌측B)
#define OUTPUT_CH_25_READ()			HAL_GPIO_ReadPin(OUT_CH25_GPIO_Port,	OUT_CH25_Pin)				// 윈치조립체 : 비상정지스위치
#define OUTPUT_CH_26_READ()			HAL_GPIO_ReadPin(OUT_CH26_GPIO_Port,	OUT_CH26_Pin)				// 윈치조립체 : 압력스위치(권선브레이크)
#define OUTPUT_CH_27_READ()			HAL_GPIO_ReadPin(OUT_CH27_GPIO_Port,	OUT_CH27_Pin)				// 윈치조립체 : 압력스위치(보조브레이크)
#define OUTPUT_CH_28_READ()			HAL_GPIO_ReadPin(OUT_CH28_GPIO_Port,	OUT_CH28_Pin)				// 윈치조립체 : 압력스위치(주브레이크)
#define OUTPUT_CH_29_READ()			HAL_GPIO_ReadPin(OUT_CH29_GPIO_Port,	OUT_CH29_Pin)				// 윈치조립체 : 권선유압모터(방향)
#define OUTPUT_CH_30_READ()			HAL_GPIO_ReadPin(OUT_CH30_GPIO_Port,	OUT_CH30_Pin)				// 윈치조립체 : 권선유압모터(속도)
#define OUTPUT_CH_31_READ()			HAL_GPIO_ReadPin(OUT_CH31_GPIO_Port,	OUT_CH31_Pin)				// 윈치조립체 : 유압모터A(방향)
#define OUTPUT_CH_32_READ()			HAL_GPIO_ReadPin(OUT_CH32_GPIO_Port,	OUT_CH32_Pin)				// 윈치조립체 : 유압모터A(속도)
#define OUTPUT_CH_33_READ()			HAL_GPIO_ReadPin(OUT_CH33_GPIO_Port,	OUT_CH33_Pin)				// 윈치조립체 : 유압모터B(방향)
#define OUTPUT_CH_34_READ()			HAL_GPIO_ReadPin(OUT_CH34_GPIO_Port,	OUT_CH34_Pin)				// 윈치조립체 : 유압모터B(속도)
#define OUTPUT_CH_35_READ()			HAL_GPIO_ReadPin(OUT_CH35_GPIO_Port,	OUT_CH35_Pin)				// 윈치조립체 : 칼날감지센서(보조절단기)
#define OUTPUT_CH_36_READ()			HAL_GPIO_ReadPin(OUT_CH36_GPIO_Port,	OUT_CH36_Pin)				// 윈치조립체 : 칼날감지센서(주절단기)
#define OUTPUT_CH_37_READ()			HAL_GPIO_ReadPin(OUT_CH37_GPIO_Port,	OUT_CH37_Pin)				// 투인양장치 : 근접스위치1
#define OUTPUT_CH_38_READ()			HAL_GPIO_ReadPin(OUT_CH38_GPIO_Port,	OUT_CH38_Pin)				// 투인양장치 : 근접스위치2
#define OUTPUT_CH_39_READ()			HAL_GPIO_ReadPin(OUT_CH39_GPIO_Port,	OUT_CH39_Pin)				// 투인양장치 : 근접스위치3
#define OUTPUT_CH_40_READ()			HAL_GPIO_ReadPin(OUT_CH40_GPIO_Port,	OUT_CH40_Pin)				// 투인양장치 : 근접스위치4
#define OUTPUT_CH_41_READ()			HAL_GPIO_ReadPin(OUT_CH41_GPIO_Port,	OUT_CH41_Pin)				// 투인양장치 : 근접스위치5
#define OUTPUT_CH_42_READ()			HAL_GPIO_ReadPin(OUT_CH42_GPIO_Port,	OUT_CH42_Pin)				// 투인양장치 : 근접스위치6
#define OUTPUT_CH_43_READ()			HAL_GPIO_ReadPin(OUT_CH43_GPIO_Port,	OUT_CH43_Pin)				// 투인양장치 : 압력스위치(세척기)
#define OUTPUT_CH_44_READ()		HAL_GPIO_ReadPin(OUT_CH44_GPIO_Port,	OUT_CH44_Pin)				// SPARE
#define OUTPUT_CH_45_READ()		HAL_GPIO_ReadPin(OUT_CH45_GPIO_Port,	OUT_CH45_Pin)				// SPARE
#define OUTPUT_CH_46_READ()		HAL_GPIO_ReadPin(OUT_CH46_GPIO_Port,	OUT_CH46_Pin)				// SPARE
#define OUTPUT_CH_47_READ()		HAL_GPIO_ReadPin(OUT_CH47_GPIO_Port,	OUT_CH47_Pin)				// SPARE
#define OUTPUT_CH_48_READ()		HAL_GPIO_ReadPin(OUT_CH48_GPIO_Port,	OUT_CH48_Pin)				// SPARE


/*-------Prototype Declaration----------------------------------------------*/

#endif /* OUTPUTPORT_H_ */
/* Private variables ---------------------------------------------------------*/
typedef struct
{

} _GPO;
extern _GPO GPO;


/* Private function prototypes -----------------------------------------------*/
void FUN_GPO_Init(void);
void FUN_GPO_Routine(void);
void FUN_GPO_PortCheck(void);
void FUN_GPO_Output(uint8_t u1t_outport, uint8_t u1t_val);
void FUN_GPO_Gripper(void);
void FUN_GPO_Oil(void);
void FUN_GPO_Cutter(void);
void FUN_GPO_Cleaner(void);
void FUN_GPO_Emergency(void);

#endif /* GPIO_GPO_H_ */

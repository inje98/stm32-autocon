/*
 * Control.h
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
// Mode
typedef struct
{
	uint16_t LWS_C_Mode;
}Mode;

// Status
typedef union
{
	uint32_t LWS_C_Status;
	struct{
		uint8_t Status0		:	1;				// GUI(485통신) 연결 상태
		uint8_t Status1		:	1;				// 이더넷 연결상태
		uint8_t Status2		:	1;				// LwsWtuA 보드 전원투입 상태
		uint8_t Status3		:	1;				// 제어기 정상동작 상태

		uint8_t Status4		:	1;				// 제어장치 시험 명령수신 후 시험상태
		uint8_t Status5		:	1;				// HILS 연동 구동 상태(1: 연동중, 0: 연동종료)
		uint8_t Status6		:	1;				//
		uint8_t Status7		:	1;				//

		uint8_t Status8		:	1;				//
		uint8_t Status9		:	1;				//
		uint8_t Status10	:	1;				//
		uint8_t Status11	:	1;				//

		uint8_t Status12	:	1;				//
		uint8_t Status13	:	1;				//
		uint8_t Status14	:	1;				//
		uint8_t Status15	:	1;				//

		uint8_t Status16 	:	1;				//
		uint8_t Status17 	:	1;				//
		uint8_t Status18 	:	1;				//
		uint8_t Status19 	:	1;				//

		uint8_t Status20 	:	1;				//
		uint8_t Status21 	:	1;				//
		uint8_t Status22 	:	1;				//
		uint8_t Status23 	:	1;				//

		uint8_t Status24 	:	1;				//
		uint8_t Status25	:	1;				//
		uint8_t Status26	:	1;				//
		uint8_t Status27	:	1;				//

		uint8_t Status28	:	1;				//
		uint8_t Status29	:	1;				//
		uint8_t Status30	:	1;				//
		uint8_t Status31	:	1;				//
	}Bit;
}Status;

// Error
typedef union{
	uint16_t LWS_C_Error;
	struct{
		uint8_t Error1		:	1;			// 시험장치 BoradA 에러 상태

		uint8_t Error2		:	1;			//
		uint8_t Error3		:	1;			//
		uint8_t Error4		:	1;			//
		uint8_t Error5		:	1;			//
		uint8_t Error6		:	1;			//
		uint8_t Error7		:	1;			//
		uint8_t Error8		:	1;			//

		uint8_t Error9		:	1;			//
		uint8_t Error10		:	1;			//
		uint8_t Error11		:	1;			//
		uint8_t Error12		:	1;			//
		uint8_t Error13		:	1;			//
		uint8_t Error14		:	1;			//
		uint8_t Error15		:	1;			//
		uint8_t Error16		:	1;			//
	}Bit;
}LWS_Error;

// Input_CH
typedef union{
	uint32_t Input_Alldata;
	struct{
		uint8_t In_ch1		:	1;			// 무부하밸브(윈치동력)
		uint8_t In_ch2		:	1;			// 무부하밸브(투인양동력)
		uint8_t In_ch3		:	1;			// 방향전환밸브(수냉식냉각기)
		uint8_t In_ch4		:	1;			// 차단밸브(수냉식냉각기)
		uint8_t In_ch5		:	1;			// 차단밸브(축압기 충전)
		uint8_t In_ch6		:	1;			// 차단밸브(윈치동력)
		uint8_t In_ch17		:	1;			// 동력공급장치: 냉각기 구동명령
		uint8_t In_ch18		:	1;			// 동력공급장치: 히터 구동명령

		uint8_t In_ch7		:	1;			// 윈치조립체 : 방향전환밸브(권선브레이크)
		uint8_t In_ch10		:	1;			// 윈치조립체 : 방향전환밸브(주브레이크)
		uint8_t In_ch8		:	1;			// 윈치조립체 : 방향전환밸브(보조브레이크)
		uint8_t In_ch11		:	1;			// 윈치조립체 : 방향전환밸브(주절단기)
		uint8_t In_ch9		:	1;			// 윈치조립체 : 방향전환밸브(보조절단기)
		uint8_t In_ch12		:	1;			// 투인양장치 : 청수잠금밸브(세척기)
		uint8_t In_ch13		:	1;			// 확성기
		uint8_t Unused0		:	1;			// unused

		uint8_t Unused1		:	8;			//

		uint8_t Unused2		:	8;			//

//		uint8_t In_ch14		:	1;			// SPARE
//		uint8_t In_ch15		:	1;			// SPARE
//		uint8_t In_ch16		:	1;			// SPARE
	}Bit;
}Input_CH;

// Output_CH
typedef union{
	uint32_t Output_Alldata[3];
	struct{
		uint8_t Out_ch7		:	1;			// 동력공급장치 : 압력스위치(부스터)
		uint8_t Out_ch13	:	1;			// 동력공급장치 : 압력스위치(투인양동력)
		uint8_t Out_ch9		:	1;			// 동력공급장치 : 압력스위치(압력초과)
		uint8_t Out_ch5		:	1;			// 동력공급장치 : 압력스위치(감김)
		uint8_t Out_ch14	:	1;			// 동력공급장치 : 압력스위치(풀림)
		uint8_t Out_ch6		:	1;			// 동력공급장치 : 압력스위치(권선)
		uint8_t Out_ch15	:	1;			// 동력공급장치 : 필터막힘스위치(리턴)
		uint8_t Out_ch16	:	1;			// 동력공급장치 : 필터막힘스위치(부스터펌프)

		uint8_t Out_ch17	:	1;			// 동력공급장치 : 필터막힘스위치(윈치구동)
		uint8_t Out_ch18	:	1;			// 동력공급장치 : 필터막힘스위치(투인양)
		uint8_t Out_ch1		:	1;			// 동력공급장치 : 레벨스위치1(저유기조립체)
		uint8_t Out_ch2		:	1;			// 동력공급장치 : 레벨스위치2(저유기조립체)
		uint8_t Out_ch3		:	1;			// 동력공급장치 : 레벨스위치3(저유기조립체)
		uint8_t Out_ch8		:	1;			// 동력공급장치 : 압력스위치(수냉식냉각기)
		uint8_t Out_ch10	:	1;			// 동력공급장치 : 압력스위치(축압기 부족1)
		uint8_t Out_ch11	:	1;			// 동력공급장치 : 압력스위치(축압기 부족2)

		uint8_t Out_ch12	:	1;			// 동력공급장치 : 압력스위치(축압기 충전완료)
		uint8_t Out_ch4		:	1;			// 동력공급장치 : 비상정지스위치
		uint8_t	Unused0		:	6;			//

		uint8_t	Unused1		:	8;			//






		uint8_t Out_ch21	:	1;			// 윈치조립체 : 근접센서(우측A)
		uint8_t Out_ch22	:	1;			// 윈치조립체 : 근접센서(우측B)
		uint8_t Out_ch23	:	1;			// 윈치조립체 : 근접센서(좌측A)
		uint8_t Out_ch24	:	1;			// 윈치조립체 : 근접센서(좌측B)
		uint8_t Out_ch20	:	1;			// 윈치조립체 : 5회전 감지스위치
		uint8_t Out_ch26	:	1;			// 윈치조립체 : 압력스위치(권선브레이크)
		uint8_t Out_ch28	:	1;			// 윈치조립체 : 압력스위치(주브레이크)
		uint8_t Out_ch27	:	1;			// 윈치조립체 : 압력스위치(보조브레이크)

		uint8_t Out_ch19	:	1;			// 동력공급장치 윈치동력 : 비례제어밸브 에러신호
		uint8_t Out_ch35	:	1;			// 윈치조립체 : 칼날감지센서(보조절단기)
		uint8_t Out_ch36	:	1;			// 윈치조립체 : 칼날감지센서(주절단기)
		uint8_t Out_ch25	:	1;			// 윈치조립체 : 비상정지스위치
		uint8_t Out_ch29	:	1;			// 윈치조립체 : 권선유압모터(방향)
		uint8_t Out_ch30	:	1;			// 윈치조립체 : 권선유압모터(속도)
		uint8_t Out_ch31	:	1;			// 윈치조립체 : 유압모터A(방향)
		uint8_t Out_ch32	:	1;			// 윈치조립체 : 유압모터A(속도)

		uint8_t Out_ch33	:	1;			// 윈치조립체 : 유압모터B(방향)
		uint8_t Out_ch34	:	1;			// 윈치조립체 : 유압모터B(속도)
		uint8_t	Unused2		:	6;			//

		uint8_t	unused3		:	8;			//




		uint8_t Out_ch37	:	1;			// 투인양장치 : 근접스위치1
		uint8_t Out_ch38	:	1;			// 투인양장치 : 근접스위치2
		uint8_t Out_ch39	:	1;			// 투인양장치 : 근접스위치3
		uint8_t Out_ch40	:	1;			// 투인양장치 : 근접스위치4
		uint8_t Out_ch41	:	1;			// 투인양장치 : 근접스위치5
		uint8_t Out_ch42	:	1;			// 투인양장치 : 근접스위치6
		uint8_t Out_ch43	:	1;			// 투인양장치 : 압력스위치(세척기)
		uint8_t	Unused4		:	1;			//


		uint8_t	Unused5		:	8;			//

		uint8_t	Unused6		:	8;			//

		uint8_t	Unused7		:	8;			//

//		uint8_t Out_ch44	:	1;			// SPARE
//		uint8_t Out_ch45	:	1;			// SPARE
//		uint8_t Out_ch46	:	1;			// SPARE
//		uint8_t Out_ch47	:	1;			// SPARE
//		uint8_t Out_ch48	:	1;			// SPARE
	}Bit;
}Output_CH;

// Float�� Data
typedef struct
{

	// AI [8]
	float AI_ADC_In1_Ch1_Volt;				// 동력공급장치 윈치구동: 비례제어밸브
	float AI_ADC_In1_Ch2_Volt;				// 윈치조립체 비상구동 : 비례제어밸브
	float AI_ADC_In1_Ch3_Volt;				// 윈치조립체 권선구동 : 비례제어밸브
	float AI_ADC_In1_Ch4_Volt;				// Spare01
	float AI_ADC_In2_Ch1_Volt;				// 투인양장치 서보실린더1 : 비례제어밸브
	float AI_ADC_In2_Ch2_Volt;				// 투인양장치 서보실린더2 : 비례제어밸브
	float AI_ADC_In2_Ch3_Volt;				// 투인양장치 메인실린더1 : 비례제어밸브
	float AI_ADC_In2_Ch4_Volt;				// 투인양장치 메인실린더2 : 비례제어밸브


	// AO [34]
	float Encoder_1;							// 윈치드럼 각도(엔코더 01)
	float Encoder_2;							// 권선정렬 각도(엔코더 02)

	// ↓↓ 190305 ADD ↓↓
	float WinchDrumHydMotorASpeed;			// 윈치드럼 유압모터 A 속도(TA)
	float WinchDrumHydMotorBSpeed;			// 윈치드럼 유압모터 B 속도(TA)
	float AlignHydMotorSpeed;				// 권선정렬 유압모터 속도(TA)
	// ↑↑ 190305 ADD ↑↑

	float Dac3_Ch0_Volt;						// 윈치조립체 권선구동 : 비례제어밸브 에러신호
	float Dac3_Ch1_Volt;						// 동력공급장치 비상구동: 비례제어밸브 에러신호
	float Dac3_Ch2_Volt;						// 투인양장치 메인실린더1: 비례제어밸브 에러신호
	float Dac3_Ch3_Volt;						// 투인양장치 메인실린더2: 비례제어밸브 에러신호
	float Dac3_Ch4_Volt;						// 투인양장치 서보실린더1: 비례제어밸브 에러신호
	float Dac3_Ch5_Volt;						// 투인양장치 서보실린더2: 비례제어밸브 에러신호
	float DAC_Spare_0;							// Spare

	float DAC_Spare_1;							// Spare
	float DAC_Spare_2;							// Spare
	float Dac4_Ch2_Volt;						// 동력공급장치: 온도센서(저유기조립체)
	float Dac4_Ch3_Volt;						// 동력공급장치: 유량계(투인양동력)
	float Dac4_Ch4_Volt;						// 동력공급장치: 압력변환기(투인양동력)
	float Dac4_Ch5_Volt;						// 동력공급장치: 압력변환기(윈치동력)
	float Dac4_Ch6_Volt;						// 투인양장치: 실린더1(수축) 압력변환기
	float Dac4_Ch7_Volt;						// 투인양장치: 실린더1(팽창) 압력변환기
	float Dac4_Ch8_Volt;						// 투인양장치: 실린더2(수축) 압력변환기
	float Dac4_Ch9_Volt;						// 투인양장치: 실린더2(팽창) 압력변환기
	float Dac4_Ch10_Volt;					// 투인양장치: 서보실린더1(수축) 압력변환기
	float Dac4_Ch11_Volt;					// 투인양장치: 서보실린더1(팽창) 압력변환기
	float Dac4_Ch12_Volt;					// 투인양장치: 서보실린더2(수축) 압력변환기
	float Dac4_Ch13_Volt;					// 투인양장치: 서보실린더2(팽창) 압력변환기

	float Dac5_Ch0_Volt;						// 투인양장치: 메인실린더2 LVDT
	float Dac5_Ch1_Volt;						// 투인양장치: 서보실린더2 LVDT
	float Dac5_Ch2_Volt;						// 투인양장치: 그립퍼 LVDT2
	float Dac5_Ch3_Volt;						// 윈치조립체 : 장력센서
	float Dac5_Ch4_Volt;						// 투인양장치: 그립퍼 LVDT3
	float Dac5_Ch5_Volt;						// 투인양장치: 메인실린더1 LVDT
	float Dac5_Ch6_Volt;						// 투인양장치: 서보실린더1 LVDT
	float Dac5_Ch7_Volt;						// 투인양장치: 그립퍼 LVDT1

	float AO_Spare_01;						// Spare01
	float AO_Spare_02;						// Spare02
	float AO_Spare_03;						// Spare03

}Float_Data;
/*
typedef struct
{
	// LwsWtuA_HILS
	float ff_HilsOutputVar_01;					// HilsOutputVar_01
	float ff_HilsOutputVar_02;					// HilsOutputVar_02
	float ff_HilsOutputVar_03;					// HilsOutputVar_03
	float ff_HilsOutputVar_04;					// HilsOutputVar_04
	float ff_HilsOutputVar_05;					// HilsOutputVar_05
	float ff_HilsOutputVar_06;					// HilsOutputVar_06
	float ff_HilsOutputVar_07;					// HilsOutputVar_07
	float ff_HilsOutputVar_08;					// HilsOutputVar_08
	float ff_HilsOutputVar_09;					// HilsOutputVar_09
	float ff_HilsOutputVar_10;					// HilsOutputVar_10
}HILS_DATA;
*/
// ���� ������ ����� ����ü ���
typedef struct
{
	Mode 			Mode;				// MODE				// 16Bit
	Status 			Status_01;			// Status 01		// 32Bit
	Status 			Status_02;			// Status 02		// 32Bit
	LWS_Error		Error;				// EROROR			// 16Bit
	Input_CH 		Input_ch;				// Input CH			// 32Bit
	Output_CH 		Output_ch;				// Output CH		// 32Bit * 3
	Float_Data 		Float_Data;			// float �� 42 EA	// 32Bit * 42
	float LWS_C_HILS[10];				//22.09.06 float 형 10 EA	// 32Bit * 10
}_Control;
extern _Control Control;

/* Private function prototypes -----------------------------------------------*/
void FUN_Control_Init(void);
void FUN_Control_Routine(void);

#endif /* CONTROL_CONTROL_H_ */

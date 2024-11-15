/*
 * TIME_TASK.c
 *
 *  Created on: Oct 27, 2023
 *      Author: AutoconTech
 */
#include "../TCP_TEST_STM32F746_FW.h"


_TimeTask TimeTask;
_TimeTaskCnt TimeTaskCnt;

extern void FUN_RS485_Modbus_TxData();

//static void Task_1ms(void);
//static void Task_5ms(void);
static void Task_10ms(void);
static void Task_50ms(void);
static void Task_100ms(void);
static void Task_250ms(void);
static void Task_500ms(void);
static void Task_1000ms(void);





void FUN_TIM_Init(void)
{
//	HAL_TIM_Base_Start_IT(&htim7);   //1khz 인터럽트
}
//
//static void Task_1ms(void)
//{
//	TimeTaskCnt.Task_1msCnt++;
////	RS485_DATA_TASK();
//}
//
//static void Task_5ms(void)
//{
//	TimeTaskCnt.Task_5msCnt++;
//}

static void Task_10ms(void)
{
	TimeTaskCnt.Task_10msCnt++;
}

static void Task_50ms(void)
{
	TimeTaskCnt.Task_50msCnt++;
}


static void Task_100ms(void)
{
	TimeTaskCnt.Task_100msCnt++;
	if(Modbus.u.Header.Temperature++>15000)
	{
		Modbus.u.Header.Temperature = 0;
	}
}


static void Task_250ms(void)
{
	TimeTaskCnt.Task_250msCnt++;

}


static void Task_500ms(void)
{
	TimeTaskCnt.Task_500msCnt++;
	if(Modbus.u.Header.Humidity++>10000)
	{
		Modbus.u.Header.Humidity = 0;
	}
}



static void Task_1000ms(void)
{
	TimeTaskCnt.Task_1000msCnt++;
	if(Modbus.u.Header.WarningStandard-- <= 0)
	{
		Modbus.u.Header.WarningStandard = 10000;
	}

	if(Modbus.u.Header.GUI++>10000)
	{
		Modbus.u.Header.GUI = 0;
	}

	if(Modbus.u.Header.Alert == 0x00)
	{
		Modbus.u.Header.Alert = 0x01;
	}
	else if(Modbus.u.Header.Alert == 0x01)
	{
		Modbus.u.Header.Alert = 0x00;
	}
}




void Task_Schedule(void) // Task 스퀘줄링 함수
{

	TimeTaskCnt.TimeScheduleCnt++;

//	TimeTask.bit.Task_1ms = 1;


//	if((TimeTaskCnt.TimeScheduleCnt%5) == 0)     //5ms 카운터 체크
//	{
//		TimeTask.bit.Task_5ms = 1;
//	}
//
//
//	if((TimeTaskCnt.TimeScheduleCnt%1) == 0)    //10ms 카운터 체크
//	{
		TimeTask.bit.Task_10ms = 1;
//	}

	if((TimeTaskCnt.TimeScheduleCnt%5) == 0)    //50ms 카운터 체크
	{
		TimeTask.bit.Task_50ms = 1;
	}

	if((TimeTaskCnt.TimeScheduleCnt%10) == 0)    //100ms 카운터 체크
	{
		TimeTask.bit.Task_100ms = 1;
	}

	if((TimeTaskCnt.TimeScheduleCnt%25) == 0)    //250ms 카운터 체크
	{
		TimeTask.bit.Task_250ms = 1;
	}

	if((TimeTaskCnt.TimeScheduleCnt%50) == 0)    //500ms 카운터 체크
	{
		TimeTask.bit.Task_500ms = 1;
	}

	if(TimeTaskCnt.TimeScheduleCnt >= 100)       //1sec 카운터 체크
	{
		TimeTask.bit.Task_1000ms = 1;
		TimeTaskCnt.TimeScheduleCnt = 0;
	}

}




void Task_Schedule_FreeRun(void)
{
	/*if(TimeTask.bit.Task_1ms==1)                // 1ms  체크
	{
		Task_1ms();
		TimeTask.bit.Task_1ms = 0;
	}

	if(TimeTask.bit.Task_5ms==1)                // 5ms  체크
	{
		Task_5ms();
		TimeTask.bit.Task_5ms = 0;
	}*/

	if(TimeTask.bit.Task_10ms==1)                // 10ms  체크
	{
		Task_10ms();
		TimeTask.bit.Task_10ms = 0;
	}

	if(TimeTask.bit.Task_50ms==1)                // 10ms  체크
	{
		Task_50ms();
		TimeTask.bit.Task_50ms = 0;
	}

	if(TimeTask.bit.Task_100ms==1)               // 100ms 체크
	{
		Task_100ms();
		TimeTask.bit.Task_100ms = 0;
	}

	if(TimeTask.bit.Task_250ms==1)               // 250ms 체크
	{
		Task_250ms();
		TimeTask.bit.Task_250ms = 0;
	}

	if(TimeTask.bit.Task_500ms==1)               // 500ms 체크
	{
		Task_500ms();
		TimeTask.bit.Task_500ms = 0;
	}

	if(TimeTask.bit.Task_1000ms==1)              // 1sec  체크
	{
		Task_1000ms();
		TimeTask.bit.Task_1000ms = 0;
	}
}








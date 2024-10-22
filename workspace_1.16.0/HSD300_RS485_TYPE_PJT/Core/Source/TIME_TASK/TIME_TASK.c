/*
 * TIME_TASK.c
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#include "..\Source\HSD300_FW.h"

extern TIM_HandleTypeDef htim6;
//extern struct CsPin csPin;
extern UART_HandleTypeDef huart5;
extern SPI_HandleTypeDef hspi3;

/*-------Macro Declaration----------------------------------------------------*/
#define TIMER_1000ms			(999)
#define TIMER_250ms				(249)
#define TIMER_100ms				(99)
#define TIMER_10ms				(9)
#define TIMER_5ms				(4)


_TimeTask TimeTask;

_TimeTaskCnt TimeTaskCnt;

uint32_t u4f_tim_cnt = 0;
uint32_t u4f_tim_cnt1 = 0;
uint32_t u4f_tim_cnt2 = 0;
uint8_t u1f_tim_1000ms_trg = 0;
uint8_t u1f_tim_250ms_trg = 0;
//uint8_t u1f_tim_100ms_trg = 0;
uint8_t u1f_tim_10ms_trg = 0;
uint8_t u1f_tim_5ms_trg = 0;
uint8_t u1f_tim_1ms_trg = 0;
uint8_t Buzz_PWM;
uint8_t Tx_cnt;

bool DS_ActiveFlag = 0;


uint64_t CountCheck1ms    = 0;
uint64_t CountCheck5ms    = 0;
uint64_t CountCheck10ms   = 0;
uint64_t CountCheck100ms  = 0;
uint64_t CountCheck250ms  = 0;
uint64_t CountCheck500ms  = 0;
uint64_t CountCheck1000ms = 0;

uint64_t TimeFreeRunTaskCnt = 0; // main에 while안에 Task_Schedule_freerun() 이 함수 호출할때마다 ++되는데 어디다 쓰는지 모르겠음. 루프 돌때마다 1씩 증가

uint8_t count_200ms = 0;


_Error Error;

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_TIM_init(void)
{
	//HAL_TIM_Base_Init(&htim6);
	HAL_TIM_Base_Start_IT(&htim6);
}
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Tim6_1ms_routine(void)
{
        CountCheck1ms++; // 어디다 쓰이진 않는듯
#ifdef HSS300
        RS485_AnalyzePacket();
#endif
        //readData(hspi3, csPin);
}






void FUN_Tim6_5ms_routine(void)
{
        CountCheck5ms++;
        FUN_ADC_Routine();              // CO Sensor
        //readData(hspi3, csPin);
        Gas_Detecting(hspi3, csPin);    // IR 투과율 측정?
}




void FUN_Tim6_10ms_routine(void)
{
        CountCheck10ms++;
        //RS485_Make_Send_Packet();
        FUN_RS485_Rx_Timeout_Check();  // 타임아웃 250ms
}

void FUN_Tim6_100ms_routine(void)
{
        CountCheck100ms++;
        count_200ms++;
        //readData(hspi3, csPin);
        //tx_test(huart5);
        if(count_200ms > 1){
        	count_200ms = 0;
        	Gas_Sensor_Detect();       // 가스 누적값 계산 이라고만 알고 Pass
        }
}



void FUN_Tim6_250ms_routine(void)
{
        CountCheck250ms++;
        //swtich_test();

        FUN_I2C_INT_SHT30_Routine(); // 온습도값 sht30->temp_acc[]    sht30->humi_acc[]에 저장
    	FUN_I2C_EXT_SHT30_Routine(); // 온습도값 sht30->temp_acc[]    sht30->humi_acc[]에 저장 // 경고랑 알람 처리까지 하는거같음
    	//FUN_I2C_VL53L3CX_Routine();
        /*if(!DS_ActiveFlag){
        	FUN_I2C_INT_SHT30_Routine();
    		DS_ActiveFlag = !DS_ActiveFlag;
        }
        else{
        	FUN_I2C_VL53L3CX_Routine();
        	DS_ActiveFlag = !DS_ActiveFlag;
        }*/
}




void FUN_Tim6_500ms_routine(void)
{
        CountCheck500ms++;
        FUN_GPIO_Routine();        // 로터리/딥 스위치
        					       // if(ui.Status.Bit.SMOKE_DETECT == 1 || ui.temp_alarm_bit == 1 || Error.SHT30_Error == 1 || EEPROM.Error == 1)
        //readData(hspi3, csPin);
        //FUN_ADC_Routine();

}



void FUN_Tim6_1000ms_routine(void)
{
        CountCheck1000ms++;
        EEPROM_routine();
    	FUN_RS485_routine();   // HsdID = ui.ID --> 변경 ID 값 Update  //  FUN_RS485_Error_routine() -->  RS485 통신 에러 점검
        //readData(hspi3, csPin);


        if(CountCheck1000ms > 86400)  //하루 24시간
        {
                CountCheck1ms    = 0;
                CountCheck5ms    = 0;
                CountCheck10ms   = 0;
                CountCheck100ms  = 0;
                CountCheck250ms  = 0;
                CountCheck500ms  = 0;
                CountCheck1000ms = 0;

        }

}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)   // 1ms 마다 타이머(TIM6) 인터럽트 발생
{

	if(htim -> Instance == TIM6)
	{
		//If Main Loop is error for 1000ms, Watchdog Reset
		// If timer interrupt loop is error, Watchdog Reset
		TimeTaskCnt.TimeScheduleCnt++;


		TimeTask.bit.Task_1ms = 1;


		if((TimeTaskCnt.TimeScheduleCnt%5) == 0)     //5ms 카운터 체크
		{
				TimeTask.bit.Task_5ms = 1;
		}


		if((TimeTaskCnt.TimeScheduleCnt%10) == 0)     //10ms 카운터 체크
		{
				TimeTask.bit.Task_10ms = 1;
		}


		if((TimeTaskCnt.TimeScheduleCnt%100) == 0)    //100ms 카운터 체크
		{
				TimeTask.bit.Task_100ms = 1;
		}


		if((TimeTaskCnt.TimeScheduleCnt%250) == 0)    //100ms 카운터 체크
		{
				TimeTask.bit.Task_250ms = 1;
		}


		if((TimeTaskCnt.TimeScheduleCnt%500) == 0)    //500ms 카운터 체크
		{
				TimeTask.bit.Task_500ms = 1;
		}


		if(TimeTaskCnt.TimeScheduleCnt >= 1000)       //1sec 카운터 체크
		{
				TimeTask.bit.Task_1000ms = 1;

				TimeTaskCnt.TimeScheduleCnt = 0;
		}
	}
}


void Task_Schedule_freerun(void)
{
	TimeFreeRunTaskCnt++;
	if(TimeTask.bit.Task_1ms==1)                // 1ms  체크
	{
			FUN_Tim6_1ms_routine();

			TimeTask.bit.Task_1ms = 0;
	}


	if(TimeTask.bit.Task_5ms==1)                // 5ms  체크
	{
			FUN_Tim6_5ms_routine();

			TimeTask.bit.Task_5ms = 0;
	}


	if(TimeTask.bit.Task_10ms==1)                // 10ms  체크
	{
			FUN_Tim6_10ms_routine();

			TimeTask.bit.Task_10ms = 0;
	}

	if(TimeTask.bit.Task_100ms==1)               // 100ms 체크
	{
			FUN_Tim6_100ms_routine();

			TimeTask.bit.Task_100ms = 0;
	}


	if(TimeTask.bit.Task_250ms==1)               // 100ms 체크
	{
			FUN_Tim6_250ms_routine();

			TimeTask.bit.Task_250ms = 0;
	}


	if(TimeTask.bit.Task_500ms==1)               // 500ms 체크
	{
			FUN_Tim6_500ms_routine();

			TimeTask.bit.Task_500ms = 0;
	}


	if(TimeTask.bit.Task_1000ms==1)              // 1sec  체크
	{
			FUN_Tim6_1000ms_routine();

			TimeTask.bit.Task_1000ms = 0;
	}

}


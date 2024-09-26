/*
 * TIME_TASK.h
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_TIME_TASK_TIME_TASK_H_
#define SOURCE_TIME_TASK_TIME_TASK_H_


typedef struct {

	uint8_t    i2c1_Error_Cnt;
	uint16_t   i2c1_Error;

	uint8_t    SHT30_Error_Cnt;
	uint16_t   SHT30_Error;

	uint16_t   Smoke_error;
	uint32_t   RS485_error_chk;
	uint16_t   RS485_error_Cnt;
	uint16_t   RS485_error;
	uint32_t   RS485_State;
} _Error;
extern _Error Error;

//Timer Task 설정

typedef union {
	struct {

			uint16_t Task_1ms       : 1; // 0: 1ms Task

			uint16_t Task_5ms       : 1; // 0: 5ms Task

			uint16_t Task_10ms      : 1; // 2: 10ms Task

			uint16_t Task_100ms     : 1; // 3: 100ms Task

			uint16_t Task_250ms     : 1; // 4: 100ms Task

			uint16_t Task_500ms     : 1; // 5: 500ms Task

			uint16_t Task_1000ms    : 1; // 6: 1sec  Task

	} bit;
	uint16_t  all;
}_TimeTask;


extern  _TimeTask  TimeTask;               //TimeTask   구조체 변수



typedef struct {


        uint64_t TimeScheduleCnt;

        uint64_t Task_1msCnt;

        uint64_t Task_5msCnt;

        uint64_t Task_10msCnt;

        uint64_t Task_100msCnt;

        uint64_t Task_500msCnt;

        uint64_t Task_1000msCnt;


}_TimeTaskCnt;

extern _TimeTaskCnt TimeTaskCnt;    // TimeTaskCnt  구조체 변수
void FUN_TIM_init(void);
void Task_Schedule_freerun(void);


#endif /* SOURCE_TIME_TASK_TIME_TASK_H_ */

/*
 * TIME_TASK.h
 *
 *  Created on: Oct 27, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_TIME_TASK_TIME_TASK_H_
#define SOURCE_TIME_TASK_TIME_TASK_H_



typedef union
{
	struct
	{
		uint16_t Task_1ms       : 1; // 0: 1ms   Task
		uint16_t Task_5ms       : 1; // 1: 5ms   Task
		uint16_t Task_10ms      : 1; // 1: 10ms  Task
		uint16_t Task_50ms      : 1; // 1: 10ms  Task
		uint16_t Task_100ms     : 1; // 2: 100ms Task
		uint16_t Task_250ms     : 1; // 2: 100ms Task
		uint16_t Task_500ms     : 1; // 2: 500ms Task
		uint16_t Task_1000ms    : 1; // 3: 1sec  Task

    } bit;
      uint16_t  all;

}_TimeTask;



typedef struct
{
	uint64_t TimeScheduleCnt;
	uint64_t Task_1msCnt;
	uint64_t Task_5msCnt;
	uint64_t Task_10msCnt;
	uint64_t Task_50msCnt;
	uint64_t Task_100msCnt;
	uint64_t Task_250msCnt;
	uint64_t Task_500msCnt;
	uint64_t Task_1000msCnt;

}_TimeTaskCnt;


extern _TimeTask    TimeTask;    	//TimeTask   구조체 변수
extern _TimeTaskCnt TimeTaskCnt;    // TimeTaskCnt  구조체 변수

void FUN_TIM_Init(void);
void Task_Schedule(void);
void Task_Schedule_FreeRun(void);

void FUN_DevicePeripheral_Init(void);


#endif /* SOURCE_TIME_TASK_TIME_TASK_H_ */

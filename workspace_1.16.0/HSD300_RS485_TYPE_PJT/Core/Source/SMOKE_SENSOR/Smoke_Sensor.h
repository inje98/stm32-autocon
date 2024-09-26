/*
 * Smoke_Sensor.h
 *
 *  Created on: Jan 12, 2024
 *      Author: autocontech
 */

#ifndef SOURCE_SMOKE_SENSOR_SMOKE_SENSOR_H_
#define SOURCE_SMOKE_SENSOR_SMOKE_SENSOR_H_


#include "../Source/HSD300_FW.h"

typedef struct{
	float IR_Data;
	float Blue_IR_Data;
// 적분 오차 변수
	float IR_Cumulative;
	float Blue_IR_Cumulative;
	float IR_Cumulative_Int;
	float Blue_IR_Cumulative_Int;
	float IR_Cumulative_Error;
	float Blue_IR_Cumulative_Error;
	float IR_Cumulative_Error_Int;
	float Blue_IR_Cumulative_Error_Int;
	float IR_Cumulative_Error_Int_Limit;
	float Blue_IR_Cumulative_Error_Int_Limit;
	float IR_Cumulative_Error_Int_K;
	float Blue_IR_Cumulative_Error_Int_K;

	uint8_t Gas_Detect;
}Gas_Sensor_Data;

extern Gas_Sensor_Data Gas_Sensor;

void Gas_Sensor_Init();
void Gas_Sensor_Detect();
void Gas_Detecting(SPI_HandleTypeDef hspi, struct CsPin csPin);
float SMK_MovingAverageFilter(float f_data, float *f_buf);
#endif /* SOURCE_SMOKE_SENSOR_SMOKE_SENSOR_H_ */

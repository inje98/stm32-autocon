/*
 * Smoke_Sensor.c
 *
 *  Created on: Jan 12, 2024
 *      Author: autocontech
 */


#include "../Source/HSD300_FW.h"

#define SMK_Level 1

extern SPI_HandleTypeDef hspi3;

Gas_Sensor_Data Gas_Sensor;



#define IR_Limit 80
#define Blue_IR_Limit 80
#define Int_Error_Value 60


#define Moving_Average_Buff_Size 10
float  IR_MovBuff[Moving_Average_Buff_Size] ={0,};
float  Blue_IR_MovBuff[Moving_Average_Buff_Size] ={0,};


float SMK_MovingAverageFilter(float f_data, float *f_buf) // 버퍼 값 평균 // 버퍼 안에 값이 언제 들어가는지 모르겠음
{
    //버퍼가   5이라고 하면
   //카운트는 1부터 4까지 증가

   float Value_Sum = 0;
   float Value_Mov = 0;
   uint8_t i;

   for(i = 1; i <Moving_Average_Buff_Size; i++)
   {
      f_buf[i-1] = f_buf[i];
      Value_Sum += f_buf[i-1];
      //1일때  0번에  1번 값을 넣음
      //2일때  1번에  2번 값을 넣음
      //3일때  2번에  3번 값을 넣음
      //4일때  3번에  4번 값을 넣음
   }

   //4번 위치에 값을 계속 넣음

   f_buf[Moving_Average_Buff_Size-1] = f_data;
   Value_Sum += f_buf[Moving_Average_Buff_Size-1];

   Value_Mov = (float)(Value_Sum / Moving_Average_Buff_Size);
   return Value_Mov;
}


void Gas_Sensor_Init(){
	smokeSensorADPD188Init(hspi3, csPin);
	Gas_Sensor.Gas_Detect = 0;
#if SMK_Level == 1

	Gas_Sensor.IR_Cumulative = 4.25;

	Gas_Sensor.Blue_IR_Cumulative = 4.25;

	Gas_Sensor.IR_Cumulative_Error_Int_Limit = Gas_Sensor.IR_Cumulative * 0.5;           //튀는 값방지

	Gas_Sensor.Blue_IR_Cumulative_Error_Int_Limit = Gas_Sensor.Blue_IR_Cumulative * 0.5; //튀는 값방지


	Gas_Sensor.IR_Cumulative_Int = Gas_Sensor.IR_Cumulative_Error_Int_Limit * 0.5;  //감지 시간



	Gas_Sensor.Blue_IR_Cumulative_Int = Gas_Sensor.Blue_IR_Cumulative_Error_Int_Limit * 0.5;
#endif
}

void Gas_Detecting(SPI_HandleTypeDef hspi, struct CsPin csPin) // 5ms마다 호출
{
	_result_adp_data IR_Data = readData(hspi, csPin);		 // IR 투과율 측정 이부분인거 같음. 바닥에 있는거		// 뭔지 모르겠지만 구조체 변수 ADP_RESULT를 리턴 받아오는데	이게 IR값인가 싶기도
//	Gas_Sensor.IR_Data = SMK_MovingAverageFilter((float)IR_Data.result_IR_val * 0.1);
//	Gas_Sensor.Blue_IR_Data = SMK_MovingAverageFilter((float)IR_Data.result_Blue_val * 0.1);
	Gas_Sensor.IR_Data = SMK_MovingAverageFilter(IR_Data.result_IR_val, &IR_MovBuff[0]);                // 받아온 ADP_RESULT 구조체의 각각 멤버변수를 Gas_Sensor에 넣어준다. 5ms마다
	Gas_Sensor.Blue_IR_Data = SMK_MovingAverageFilter(IR_Data.result_Blue_val, &Blue_IR_MovBuff[0]);    // 근데 버퍼에 값이 언제 들어가는지.
	//Gas_Sensor_Detect();
}


void Gas_Sensor_Detect()    //  100ms마다 호출
{
	// 오차 누적값 계산
	Gas_Sensor.IR_Cumulative_Error = (Gas_Sensor.IR_Data * 0.1) - Gas_Sensor.IR_Cumulative;  			 // SMK_MovingAverageFilter() 리턴값 - 4.25(인듯? 다른데서 받는부분이 없음)
	Gas_Sensor.Blue_IR_Cumulative_Error = Gas_Sensor.Blue_IR_Data * 0.1 - Gas_Sensor.Blue_IR_Cumulative; // 이것도 똑같

	if(Gas_Sensor.IR_Cumulative_Error > Gas_Sensor.IR_Cumulative_Error_Int_Limit)
	{
		Gas_Sensor.IR_Cumulative_Error = Gas_Sensor.IR_Cumulative_Error_Int_Limit;
	}
	if(Gas_Sensor.Blue_IR_Cumulative_Error > Gas_Sensor.Blue_IR_Cumulative_Error_Int_Limit)
	{
		Gas_Sensor.Blue_IR_Cumulative_Error = Gas_Sensor.Blue_IR_Cumulative_Error_Int_Limit;
	}


	Gas_Sensor.IR_Cumulative_Error_Int = Gas_Sensor.IR_Cumulative_Error * 0.2 + Gas_Sensor.IR_Cumulative_Error_Int_K;

	if(Gas_Sensor.IR_Cumulative_Error_Int > 1.2)
	{
	   Gas_Sensor.IR_Cumulative_Error_Int = 1.2;
	}

	if(Gas_Sensor.IR_Cumulative_Error_Int < 0)
	{
		Gas_Sensor.IR_Cumulative_Error_Int = 0;
		Gas_Sensor.IR_Cumulative_Error_Int_K = 0;
	}
	else
	{
		Gas_Sensor.IR_Cumulative_Error_Int_K = Gas_Sensor.IR_Cumulative_Error_Int;
	}



	Gas_Sensor.Blue_IR_Cumulative_Error_Int = Gas_Sensor.Blue_IR_Cumulative_Error * 0.2 + Gas_Sensor.Blue_IR_Cumulative_Error_Int_K;


	if(Gas_Sensor.Blue_IR_Cumulative_Error_Int < 0)
	{
		Gas_Sensor.Blue_IR_Cumulative_Error_Int = 0;
		Gas_Sensor.Blue_IR_Cumulative_Error_Int_K = 0;
	}
	else
	{
		Gas_Sensor.Blue_IR_Cumulative_Error_Int_K = Gas_Sensor.Blue_IR_Cumulative_Error_Int;
	}


	if(Gas_Sensor.IR_Cumulative_Error_Int > Gas_Sensor.IR_Cumulative_Int)
	{
		Gas_Sensor.Gas_Detect = 1;
	}


	ui.Status.Bit.SMOKE_DETECT = Gas_Sensor.Gas_Detect;
}

void Gas_Detect_Bit_Reset()
{
	Gas_Sensor.Gas_Detect = 0;
	Gas_Sensor.IR_Cumulative_Error = 0;
	Gas_Sensor.IR_Cumulative_Error_Int = 0;
	Gas_Sensor.IR_Cumulative_Error_Int_K = 0;
	Gas_Sensor.Blue_IR_Cumulative_Error = 0;
	Gas_Sensor.Blue_IR_Cumulative_Error_Int = 0;
	Gas_Sensor.Blue_IR_Cumulative_Error_Int_K = 0;
}

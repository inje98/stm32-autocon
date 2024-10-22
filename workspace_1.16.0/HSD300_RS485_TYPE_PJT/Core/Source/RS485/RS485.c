/*
 * RS485.c
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#include "..\Source\HSD300_FW.h"


extern UART_HandleTypeDef huart5;
extern _result_adp_data ADP_RESULT;

UI_HSD300 ui;

#ifdef HSS300

uint8_t RS485_RX_Ring_Buf[DATA_RX_BUFFER_SIZE] = {0,};   //링버퍼
uint8_t RS485_RX_Ring_Head = 0;  // In
uint8_t RS485_RX_RingTail  = 0;  // Out

uint8_t RS485_RX_Data = 0;
uint8_t RS485_RX_Get_Buf[DATA_RX_BUFFER_SIZE]  = {0,};    //수신버퍼
uint8_t RS485_TX_Send_Buf[DATA_TX_BUFFER_SIZE] = {0,};    //송신버퍼

//UI_HSD300 ui;

_RS485_RxInfo RS485_RxInfo;

uint8_t RS485_RX_Result_Error = 0;


uint16_t RS485_RX_CheckSum_Cal = 0;
uint8_t  RS485_RX_CheckSum_Msb_Cal = 0;
uint8_t  RS485_RX_CheckSum_Lsb_Cal = 0;

uint8_t  RS485_RX_CheckSum_Msb_Org = 0;
uint8_t  RS485_RX_CheckSum_Lsb_Org = 0;

uint8_t RS485_RX_CheckSum_Error = 0;


//확인 변수

uint64_t RS485_RX_CheckSum_ErrorCnt = 0;

uint64_t RS485_CMD_HandlerCnt = 0;

uint64_t RS485_UART_ErrorCnt = 0;

uint8_t  Reset_Cmd = 0;

void RS485_Send_Packet(uint8_t *SendDataBuff, uint8_t DataLen);

void RS485_Init(void)
{
	ui.Status.Bit.RUNNING = 1;
	ui.Status.Bit.SMOKE_DETECT = 0;
	ui.Status.Bit.SHT30_SENSOR_ERROR = 0;
	ui.Status.Bit.ADC_ERROR = 0;
	ui.Status.Bit.OVER_TEMP_ERROR = 0;
	ui.Status.Bit.OBJ_DETECT = 0;
	ui.Status.Bit.DISTANCE_LEVEL = 3;

	ui.d_rank = RANK_1;
	ui.d_OverTemp_Range = 0;

	ui.temp_100times = 0;
	ui.humi_100times = 0;
	ui.ntc_100times = 0;

	RS485_RE();

	HAL_UART_Receive_IT(&huart5, &RS485_RX_Data, 1);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

 	if(huart->Instance==UART5)
 	{
 		RS485_RX_Ring_Head = (RS485_RX_Ring_Head + 1 ) & DATA_RX_BUFFER_MASK;

 		HAL_UART_Receive_IT(&huart5, &RS485_RX_Data, 1);

 		RS485_RX_Ring_Buf[RS485_RX_Ring_Head] = RS485_RX_Data;
 	}
 }


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

 	if(huart->Instance==UART5)
 	{
 	    RS485_RE();  // 송신하면 HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET) --> 바로 받을 준비
 	}
}



void RS485_AnalyzePacket(void)
{
   int Result = 0;

   Result = RS485_Parsing_Data();

   if(Result < 0 )
   {
	   return;
   }

   if(Result > 0)
   {
	   RS485_RX_CheckSum_Cal = RS485_Gen_CheckSum(RS485_RX_Get_Buf,(RS485_RxInfo.nLength + 2));

	   RS485_RX_CheckSum_Msb_Cal = (uint8_t)((RS485_RX_CheckSum_Cal >> 8) & 0xFF);
	   RS485_RX_CheckSum_Lsb_Cal = (uint8_t)(RS485_RX_CheckSum_Cal & 0xFF);


	   RS485_RX_CheckSum_Msb_Org = RS485_RX_Get_Buf[9];  //체크섬 위치
	   RS485_RX_CheckSum_Lsb_Org = RS485_RX_Get_Buf[10]; //체크섬 위치

		//체크섬 비교
		if((RS485_RX_CheckSum_Msb_Cal == RS485_RX_CheckSum_Msb_Org)&&(RS485_RX_CheckSum_Lsb_Cal == RS485_RX_CheckSum_Lsb_Org))
		{
			RS485_CMD_Handler(RS485_RX_Get_Buf[2]);
		}
		else
		{
			//체크섬이 맞지 않을 경우

			RS485_RX_CheckSum_ErrorCnt++;

			if(RS485_RX_CheckSum_ErrorCnt > 5)  //체크섬 에러가 5번이상 발생시
			{
				RS485_RX_CheckSum_Error = 1;

				RS485_RX_CheckSum_ErrorCnt = 0;
			}

		}
   }
}



void MoniteringApp_Make_Send_Packet(void)
{

   uint8_t Tx_Cnt = 0;

    //RS485_TX_Data++;


   RS485_TX_Send_Buf[Tx_Cnt++] = 0x02;  //STX
   RS485_TX_Send_Buf[Tx_Cnt++] = 0x01;  //ID
   RS485_TX_Send_Buf[Tx_Cnt++] = 0xAA;  //CMD

   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(ADP_RESULT.result_IR_val & 0xFF);
   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(ADP_RESULT.result_IR_val >> 8);

   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(ADP_RESULT.result_Blue_val & 0xFF);
   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(ADP_RESULT.result_Blue_val >> 8);

   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Co_Sensor & 0xFF);
   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Co_Sensor >> 8);

//   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Distance & 0xFF);
//   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Distance >> 8);

   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Ext_SHT30.temp_hex & 0xFF);
   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Ext_SHT30.temp_hex >> 8);


   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Ext_SHT30.humi_hex & 0xFF);
   RS485_TX_Send_Buf[Tx_Cnt++] = (uint8_t)(Ext_SHT30.humi_hex >> 8);

   RS485_TX_Send_Buf[Tx_Cnt++] = Gas_Sensor.Gas_Detect;

   RS485_TX_Send_Buf[Tx_Cnt++] = 0x03; //ETX


	RS485_Send_Packet(RS485_TX_Send_Buf, Tx_Cnt);

}



int RS485_Parsing_Data(void)
{
	  uint8_t RcvData = 0;
	  uint16_t nLoopLimit = 0;
	  int8_t Result = 0;


	 while(RS485_Ring_IsGetRxBuff() && (nLoopLimit++ < sizeof(RS485_RX_Get_Buf) * 2))
	 {
		 RcvData = RS485_Ring_GetByteBuff();

		switch(RS485_RxInfo.State)
		{
			case STX:

				RS485_RxInfo.nCnt = 0;

				if(RcvData == PACKET_STX)
				{
					RS485_RxInfo.State = LENGTH;
				}
				else
				{
					continue;
				}

				break;


			case LENGTH:

				if(RcvData == 0x07)
				{
					RS485_RxInfo.State = CMD_ID;

					RS485_RxInfo.nLength = RcvData; //길이정보 저장
				}
				else
				{
					RS485_RxInfo.State = STX;
					Result = -1;
					return Result;
				}

			break;



			case CMD_ID:

				if(RcvData != 0xB1)
				{
					RS485_RxInfo.State = CMD_CODE;
					RS485_RxInfo.Cmd_Id  = RcvData; //CMD 정보 저장
				}
				else
				{
					RS485_RxInfo.State = STX;
					Result = -1;
					return Result;
				}

			break;


			case CMD_CODE:


				RS485_RxInfo.Cmd_Code  = RcvData; //CMD 정보 저장

				RS485_RxInfo.State = DEVICE_ID;   //이동

			break;


			case DEVICE_ID:

				RS485_RxInfo.Device_Id = RcvData;

				if((ui.ID == RcvData)||(RcvData==0xFF)) //ID가 내 아이디랑 같거나 ID가 0xFF일 경우
				{
					RS485_RxInfo.State = DATA;
				}
				else
				{
					RS485_RxInfo.State = STX;
					Result = -1;
					return Result;
				}


			break;


			case DATA:


				if(RS485_RxInfo.nCnt < 8) //7번쨰 +1 DATA 마지막 까지 넣고 나감
				{

					RS485_RX_Get_Buf[RS485_RxInfo.nCnt] = RcvData;
				}
				else
				{
					RS485_RxInfo.State = CHECK_SUM_MSB;
				}

			break;


			case CHECK_SUM_MSB:


				RS485_RxInfo.State = CHECK_SUM_LSB;

			break;


			case CHECK_SUM_LSB:


				RS485_RxInfo.State = ETX;

			break;


			case ETX:


				if(RcvData == PACKET_ETX)
				{

					RS485_RX_Get_Buf[RS485_RxInfo.nCnt] = RcvData;

					RS485_RxInfo.State = STX;

					Result = 1;   //정상 확인
					return Result;

				}
				else
				{
					RS485_RxInfo.State = STX;
					Result = -1;
					return Result;
				}

			break;


			default :

			RS485_RxInfo.State = STX;
			Result = -1;
			return Result;

		}


			RS485_RX_Get_Buf[RS485_RxInfo.nCnt++] = RcvData;


			if(RS485_RxInfo.nCnt > sizeof(RS485_RX_Get_Buf))
			{
				RS485_RxInfo.State = STX;
				Result = -1;
				return Result;
			}

	 }

	 return Result;
}



void RS485_Send_Packet(uint8_t *SendDataBuff, uint8_t DataLen)
{

   //    //USART2 RX 인터럽트 비활성화 신규 추가

	RS485_DE();
    HAL_UART_Transmit_IT(&huart5, &SendDataBuff[0], DataLen);

//        //USART2 RX 인터럽트 활성화 신규 추가

}


void RS485_TX_INIT()
{
  HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET);

}

void RS485_RX_INIT()
{
  HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET);
}

//void tx_test(UART_HandleTypeDef huart)
//{
//  RS485_TX_INIT();
//
//
//  RS485_TX_Send_Buf[0] = (ADP_RESULT.result_IR_val >> 8) & 0xFFFF;
//  RS485_TX_Send_Buf[1] = ADP_RESULT.result_IR_val & 0xFFFF;
//
//  RS485_TX_Send_Buf[2] = (ADP_RESULT.result_Blue_val >> 8) & 0xFFFF;
//  RS485_TX_Send_Buf[3] = ADP_RESULT.result_Blue_val & 0xFFFF;
//
//
////  HAL_UART_Transmit(&huart5, (uint8_t*)tx_Data[0],8,10);
////  HAL_UART_Transmit(&huart5, (uint8_t*)tx_Data[1],8,10);
//  HAL_UART_Transmit(&huart5, RS485_TX_Send_Buf, 4, 10);
//  HAL_Delay(1);
//  for (uint8_t i; i<TX_BUFF_MAX;i++)
//  {
//    RS485_TX_Send_Buf[i]=0;
//  }
//}

void byteToHexStr(uint8_t byte, char *str)
{
    char hexChars[] = "0123456789ABCDEF";
    str[0] = hexChars[(byte >> 4) & 0x0F];  // 상위 4비트를 문자로 변환
    str[1] = hexChars[byte & 0x0F];         // 하위 4비트를 문자로 변환
}


uint16_t Parsing_Value = 0;
uint16_t Parsing_Count = 0;
uint64_t Handler_Count = 0;


int MoniteringApp_Parsing_Data(void)
{

	uint8_t RcvData = 0;
	uint8_t nLoopLimit = 0;
	int Result = 0;


    while(RS485_Ring_IsGetRxBuff()&&(nLoopLimit++ < sizeof(RS485_RX_Get_Buf) * 2))
    {
        RcvData = RS485_Ring_GetByteBuff();

       switch(Parsing_Value)
       {
           case 0:

        	   Parsing_Count = 0;

               if(RcvData == 0x02)  //STX
               {
            	   Parsing_Value = 1;
               }
               else
               {
                   continue;
               }

               break;


           case 1:

               if(RcvData == 0x01) //ID
               {
            	   Parsing_Value = 2;
               }
               else
               {
            	   Parsing_Value = 0;
                   Result = -1;
               }

           break;


           case 2:

               if(RcvData == 0xBB) //CMD
               {
                   Parsing_Value = 3;
               }
               else
               {
                   Parsing_Value = 0;
                   Result = -1;
               }

           break;


           case 3:

			    if(Parsing_Count >= 13)
		   		{
					Parsing_Value = 4;
			    }
				else
				{
				  Result = -1;
				}

           break;


           case 4:

			   if(RcvData == 0x03) //ETX
               {
               		Parsing_Value = 0;
			   		Result = 1;
			   }
			   else
			   {
				  Parsing_Value = 0;
                   Result = -1;
			   }

           break;


           default :

           Parsing_Value = 0;
           Result = -1;

		   break;
       }

       	   RS485_RX_Get_Buf[Parsing_Count++] = RcvData;

           if(Parsing_Count > sizeof(RS485_RX_Get_Buf))
           {
               Parsing_Value = 0;
               Result = -1;
           }
    }

    return Result;
}




void RS485_CMD_Handler(uint8_t CMD)
{
	Handler_Count++;
	uint16_t TX_CheckSum;

	switch(CMD) // CMD => RS485_RX_Get_Buf[2]
	{

		case 0xA1:

		 //열연갑지기 데이터 요청에 대한 응답

		 if(ui.Status.Bit.RUNNING == 1)
		 {
			 RS485_TX_Send_Buf[0]  = PACKET_STX; //STX // 0x53
			 RS485_TX_Send_Buf[1]  = 0x0D; //LENGTH
			 RS485_TX_Send_Buf[2]  = 0xB1; //CMD_ID
			 RS485_TX_Send_Buf[3]  = 0x01; //CMD_CODE
			 RS485_TX_Send_Buf[4]  = ui.ID;


			 RS485_TX_Send_Buf[5]  = ui.Status.u1t_bitfield;               // status
			 RS485_TX_Send_Buf[6]  = ui.d_rank;                            // d_rank


			 //LSB 부터 전송해야 할듯
			 RS485_TX_Send_Buf[7]  = (uint8_t)(ui.ntc_100times);           // ntc_100times(LSB)
			 RS485_TX_Send_Buf[8]  = (uint8_t)(ui.ntc_100times >> 8);      // ntc_100times(MSB)

			 RS485_TX_Send_Buf[9]  = (uint8_t)(ui.temp_100times);          // temp_100times(LSB)
			 RS485_TX_Send_Buf[10] = (uint8_t)(ui.temp_100times >> 8);     // temp_100times(MSB)

			 RS485_TX_Send_Buf[11] = (uint8_t)(ui.humi_100times);          // humi_100times(LSB)
			 RS485_TX_Send_Buf[12] = (uint8_t)(ui.humi_100times >> 8);     // humi_100times(MSB)

			 RS485_TX_Send_Buf[13] = (uint8_t)(ui.d_OverTemp_Range);       //DATA9   SPARE1(LSB)
			 RS485_TX_Send_Buf[14] = (uint8_t)(ui.d_OverTemp_Range >> 8);  //DATA10  SPARE1(MSB)


			 TX_CheckSum = RS485_Gen_CheckSum(RS485_TX_Send_Buf, (RS485_TX_Send_Buf[1] + 2));  //체크섬

			 RS485_TX_Send_Buf[15] = (uint8_t)((TX_CheckSum >> 8) & 0xFF); //CheckSum   MSB
			 RS485_TX_Send_Buf[16] = (uint8_t)(TX_CheckSum & 0xFF);        //CheckSum   LSB

			 RS485_TX_Send_Buf[17] = PACKET_ETX;  //ETX

			 RS485_Send_Packet(RS485_TX_Send_Buf, 18);
		 }
		 else
		 {
			 RS485_TX_Send_Buf[0]  = PACKET_STX; //STX
			 RS485_TX_Send_Buf[1]  = 0x0D; //LENGTH
			 RS485_TX_Send_Buf[2]  = 0xB1; //CMD_ID
			 RS485_TX_Send_Buf[3]  = 0x01; //CMD_CODE
			 RS485_TX_Send_Buf[4]  = ui.ID;

			 RS485_TX_Send_Buf[5]  = 0; //DATA1
			 RS485_TX_Send_Buf[6]  = 0; //DATA2
			 RS485_TX_Send_Buf[7]  = 0; //DATA3
			 RS485_TX_Send_Buf[8]  = 0; //DATA4
			 RS485_TX_Send_Buf[9]  = 0; //DATA5
			 RS485_TX_Send_Buf[10] = 0; //DATA6
			 RS485_TX_Send_Buf[11] = 0; //DATA7
			 RS485_TX_Send_Buf[12] = 0; //DATA8
			 RS485_TX_Send_Buf[13] = 0; //DATA9
			 RS485_TX_Send_Buf[14] = 0; //DATA10


			 TX_CheckSum = RS485_Gen_CheckSum(RS485_TX_Send_Buf, (RS485_TX_Send_Buf[1] + 2));   //체크섬

			 RS485_TX_Send_Buf[15] = (uint8_t)((TX_CheckSum >> 8) & 0xFF); //CheckSum   MSB
			 RS485_TX_Send_Buf[16] = (uint8_t)(TX_CheckSum & 0xFF);        //CheckSum   LSB

			 RS485_TX_Send_Buf[17] = PACKET_ETX;   //ETX

			 RS485_Send_Packet(RS485_TX_Send_Buf,18);
		 }

		break;


		case 0xA2:

		 //열연갑지기 설정값 요청에 대한 응답
		 //미사용

		break;

		case 0xA4:
			if(RS485_RX_Get_Buf[3] == 0x03){
				Gas_Sensor.Gas_Detect = 0;
				ui.Status.Bit.SMOKE_DETECT = 0;
			}
		break;
		case 0xA5:

		 //열연갑지기 버젼 정보에 대한 응답
		 RS485_TX_Send_Buf[0]  = PACKET_STX; //STX
		 RS485_TX_Send_Buf[1]  = 0x0D; //LENGTH
		 RS485_TX_Send_Buf[2]  = 0xB1; //CMD_ID
		 RS485_TX_Send_Buf[3]  = 0x02; //CMD_CODE
		 RS485_TX_Send_Buf[4]  = ui.ID;

		 RS485_TX_Send_Buf[5]  = 0;//My_Version_BUF[0]; //DATA1
		 RS485_TX_Send_Buf[6]  = 0;//My_Version_BUF[1]; //DATA2
		 RS485_TX_Send_Buf[7]  = 0;//My_Version_BUF[2]; //DATA3
		 RS485_TX_Send_Buf[8]  = 0;//My_Version_BUF[3]; //DATA4
		 RS485_TX_Send_Buf[9]  = 0; //DATA5
		 RS485_TX_Send_Buf[10] = 0; //DATA6
		 RS485_TX_Send_Buf[11] = 0; //DATA7
		 RS485_TX_Send_Buf[12] = 0; //DATA8
		 RS485_TX_Send_Buf[13] = 0; //DATA9
		 RS485_TX_Send_Buf[14] = 0; //DATA10


		 TX_CheckSum = RS485_Gen_CheckSum(RS485_TX_Send_Buf, (RS485_TX_Send_Buf[1] + 2));  //패킷 길이정보 확인

		 RS485_TX_Send_Buf[15] = (uint8_t)((TX_CheckSum >> 8) & 0xFF); //CheckSum   MSB
		 RS485_TX_Send_Buf[16] = (uint8_t)(TX_CheckSum & 0xFF);        //CheckSum   LSB

		 RS485_TX_Send_Buf[17] = PACKET_ETX;   //ETX

		 RS485_Send_Packet(RS485_TX_Send_Buf,18);

		break;

		case 0xBB:
			Reset_Cmd = RS485_RX_Get_Buf[3];
			if(Reset_Cmd)
			{
				Gas_Sensor.Gas_Detect = 0;
				ui.Status.Bit.SMOKE_DETECT = 0;
			}
			MoniteringApp_Make_Send_Packet();
		break;

		default :

		break;

	}
}



AddF_CmdReqToPC(0x0C,0x0504,0x66,0x00,cmd_Ack);
/* Example: Sensor --> PC : AddF_CmdReqToPC(0,18,0x05A1,0x01~); */
void AddF_CmdReqToPC(uint16_t size, uint16_t cmd, uint8_t code, uint8_t error, uint8_t cmdAck)
{
	uint8_t RS48502_TxBuf[20];
	uint16_t checksum;
	uint16_t ii;

	//프레임
	RS48502_TxBuf[0] = PACKET_STX;
	//Length 길이
	RS48502_TxBuf[1] = (uint8_t)(size>> 8);
	RS48502_TxBuf[2] = (uint8_t)(size & 0xFF);
	//CMD
	RS48502_TxBuf[3] = (uint8_t)(cmd>> 8);
	RS48502_TxBuf[4] = (uint8_t)(cmd & 0xFF);
	//code
	RS48502_TxBuf[5] = code;

	// Count
	 ui.TxCount ++;
	RS48502_TxBuf[6] = ui.TxCount;
	// ID
	RS48502_TxBuf[7] = HsdID;

	/* Data Range */
	RS48502_TxBuf[8] = error;	 // 에러 상태
	RS48502_TxBuf[9] = cmdAck;   // 수신 명령 확인 회신
	// Dummy Data
	RS48502_TxBuf[10] = 0;
	RS48502_TxBuf[11] = 0;
	RS48502_TxBuf[12] = 0;
	RS48502_TxBuf[13] = 0;
	RS48502_TxBuf[14] = 0;

	// 체크섬 계산
	checksum = 0;
	for (ii = 1; ii < 15 ; ii++)
	{
		checksum += RS48502_TxBuf[ii];
	}
	RS48502_TxBuf[15] = (uint8_t)(checksum >> 8);
	RS48502_TxBuf[16] = (uint8_t)(checksum & 0xFF);
	//프레임 끝
	RS48502_TxBuf[17] = PACKET_ETX;

	if(ui.End_Code == 1)
	{
		RS48502_TxBuf[18] = ECODE_CR;
		RS48502_TxBuf[19] = ECODE_LF;
		// Add Request Data Frame to RS485-1 SendFrame
		for (ii = 0; ii < 20 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48502_TxBuf[ii];
		}
	}
	else
	{
		// Add Data Request Frame to RS485-1 SendFrame
		for (ii = 0; ii < 18 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48502_TxBuf[ii];
		}
	}

	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
}



uint16_t RS485_Gen_CheckSum(uint8_t *tBuff, uint8_t nLen)
{
	 uint16_t Result, i;

 	//STX를 뺴고 계산하기 위해 1부터 증가

 	for (i = 1, Result = 0; i < nLen; i++)
 	{
 		Result += tBuff[i];
 	}

 	return Result;
 }




uint8_t RS485_Ring_IsGetRxBuff(void)
{

 	uint8_t Result;
 	uint8_t RxHead;
 	uint8_t RxTail;

     RxHead = RS485_RX_Ring_Head;
     RxTail = RS485_RX_RingTail;


     if(RxHead != RxTail)
     {
     	Result = 1;
     }
     else
     {
     	Result = 0;
     }
     return Result;
}



uint8_t RS485_Ring_GetByteBuff(void)
{
 	uint8_t Result;
 	uint8_t tmptail;

 	// Calculate Buffer Index
    tmptail = (RS485_RX_RingTail + 1) & DATA_RX_BUFFER_MASK;

    RS485_RX_RingTail = tmptail;        // store new index

 	Result = RS485_RX_Ring_Buf[tmptail]; // copy data into requested buffer

 	return Result;
}

#endif

#ifdef HSD300
/* Private macro -------------------------------------------------------------*/
uint8_t RS48501_TxPos, RS48501_TxEnd;

/* Private variables ---------------------------------------------------------*/
uint8_t RS48501_TxSendFrame[26];
//485 RX,TX데이터
uint8_t RS485Rx0Data[18];
uint8_t RS485RxMOData[25];

uint8_t data_tx;
uint16_t HsdID;

_RS485Rx RS485Rx;

uint8_t RS485RxA;
uint8_t RS485TxA;
// Bootloader 명령 체크 플래그
uint8_t u1f_bootjump_flag = 0;

/* Private function prototypes -----------------------------------------------*/
uint8_t FUN_Rx_data_check(void);
uint8_t FUN_Rx_data_Modbus_check(void);
void FUN_RS485_UART_Init(void);
/* Private function ----------------------------------------------------------*/
void AddF_ReqDataToPC(uint16_t size, uint16_t cmd, uint8_t code );
void AddF_CmdReqToPC(uint16_t size, uint16_t cmd, uint8_t code, uint8_t error, uint8_t cmdAck);
void AddF_CmdReqToPC_Val(uint16_t size, uint16_t cmd, uint8_t code, uint8_t error, int16_t data1, int16_t data2);

void RS485_Baudrate_Init(uint8_t baudrate);

// 초기화
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void RS485_Init(void)
{
	// Init ID
	HsdID = ui.ID;
	// Init Status
	//RS485Tx.running_bit = 1;
	ui.Status.Bit.RUNNING = 1;
	RS485Rx.detect_staet_reset_bit = 0;
	RS485Rx.smoke_detect_set_bit = 0;
	RS485Rx.smoke_detect_set_val = 0;
	ui.TxCount = 0;
	RS485Rx.Rx_cnt = 0;
	RS485Rx.Detection_Error = 0;
	EEPROM.SaveData_Flag = 0;
	//ui.temp_warring_bit = 0;
	//ui.SMK_Level = RANK_1;
	//ui.Protocol_Type = 1;
	RS485_Baudrate_Init(ui.Baudrate);
	HAL_UART_Receive_IT(&huart5, &RS485RxA, 1);
	RS485_RE();

	FUN_Modbus_init();
}

/****************************************************************************/
/*	Overview	:	변경 ID 값 Update, RS485 통신 에러 점검                                          */
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_routine(void)
{
	HsdID = ui.ID;
	FUN_RS485_Error_routine();
}

/****************************************************************************/
/*	Overview	:	RS485-01 - Make Frame and Send to 상위 제어기(PC or PLC) 	*/
/*	Return value:	void													*/
/****************************************************************************/
/* Example: Sensor --> PC : AddF_ReqDataToPC(0,18,0x05A1,0x01); */
void AddF_ReqDataToPC(uint16_t size, uint16_t cmd, uint8_t code )  // 데이터 송신을 위한 프레임 구성 / 전송 준비 인듯 // RxCallback
{
	uint8_t RS48501_TxBuf[26];
	uint16_t checksum, ii;
	int16_t intTmp;

	//프레임
	RS48501_TxBuf[0] = PACKET_STX;
	//Length 길이
	RS48501_TxBuf[1] = (uint8_t)(size>> 8);
	RS48501_TxBuf[2] = (uint8_t)(size & 0xFF);
	//CMD
	RS48501_TxBuf[3] = (uint8_t)(cmd>> 8);
	RS48501_TxBuf[4] = (uint8_t)(cmd & 0xFF);
	//Code
	RS48501_TxBuf[5] = code;

	// Tx Count
	ui.TxCount++;
	RS48501_TxBuf[6] = ui.TxCount;

	// HSD ID Update
	RS48501_TxBuf[7] = HsdID;

	/* Data Range */
	// Status(MSB)
	// 상태 추가에 대해서 고민 필요(Display Slip, Buzzer 설정, 연기감지농도 설정, End_Code 설정, HeartBit 설정)
	RS48501_TxBuf[8] = 0x00;
	//Disable slip
	RS48501_TxBuf[8] = 0x00;
	//부저
	RS48501_TxBuf[8] |= 0x00 << 1;
	//연기 감지 LEVEL
	RS48501_TxBuf[8] |= ui.SMK_Level << 2;
//	RS48501_TxBuf[8] |= Adc.SMK_Level << 2;
	//Heartbeat
	RS48501_TxBuf[8] |= ui.HeartBit << 4;
//	RS48501_TxBuf[8] |= Button.Heatbit << 4;
//	RS48501_TxBuf[8] |= Button.Heatbit << 4;

	// Status(LSB)
	// Update Error Status
	if((Error.SHT30_Error == 1) || (EEPROM.Error == 1) || (RS485Rx.Checksum_Error == 1))
	{
		ui.Detection_Error = 1;
		if(Error.SHT30_Error == 1){
			ui.ErrorCode = 0x01;
		}
		if(EEPROM.Error == 1){
			ui.ErrorCode = 0x02;
		}
		if(RS485Rx.Checksum_Error == 1){
			ui.ErrorCode = 0x03;
		}
	}
	else{
		ui.ErrorCode = 0x00;
		ui.Detection_Error = 0;
	}
	RS48501_TxBuf[9] = 0x00;	// Status byte init
    // Running
	RS48501_TxBuf[9] = ui.Status.Bit.RUNNING;
	//연기 감지
	RS48501_TxBuf[9] |= (ui.Status.Bit.SMOKE_DETECT << 1);//(RS485Tx.smoke_detect_on_bit << 1);
	//온도 경고
	RS48501_TxBuf[9] |= (ui.temp_warring_bit << 2);
	//온도 알람
	RS48501_TxBuf[9] |= (ui.temp_alarm_bit << 3);
	//감지기 에러
	RS48501_TxBuf[9] |= (ui.Detection_Error << 4);
	//온도 enable/disable
	RS48501_TxBuf[9] |= (ui.temp_alarm_enable << 5);
	//온도 경고 동작
	RS48501_TxBuf[9] |= (ui.temp_warring_maintain_bit << 6);
	//온도 알람 동작
	RS48501_TxBuf[9] |= (ui.temp_alarm_maintain_bit << 7);

	//ErrorCode
	RS48501_TxBuf[10] = ui.ErrorCode;

	// Update Analog Data
	// 온도/습도 값
	// 온도경고/알람 기준값, 편차 기준값
	RS485Rx.ff_cTemp_warring_R = ((int16_t)((ui.temp_warring+0.001) * 100));
	RS485Rx.ff_cTemp_alarm_R = ((int16_t)((ui.temp_alarm+0.001) * 100));
	//ui.co_100times = ((uint16_t)((ui.Warring_Deviation+0.001) * 100));

	//온도 값(소수점 첫째자리까지만 송신, 둘째자리는 버림)
	intTmp = (ui.temp_100times / 10) * 10;
	RS48501_TxBuf[11] = (uint8_t)(intTmp >> 8);
	RS48501_TxBuf[12] = (uint8_t)(intTmp & 0xFF);
	//습도 값(소수점 첫째자리까지만 송신, 둘째자리는 버림)
	intTmp = (ui.humi_100times / 10) * 10;
	RS48501_TxBuf[13] = (uint8_t)(intTmp >> 8);
	RS48501_TxBuf[14] = (uint8_t)(intTmp & 0xFF);

	/*if(RS485Rx.ADC_Offset_Flag == 1)
	{
		if(RS485Rx.ADC_Offset_Check_2 == 1)
		{
			RS485Rx.Max_MinValue = Adc.Max_MinValue * 100;
			RS485Rx.Zero_Offset = Adc.Zero_Offset * 100;
			//Max_MinValue
			intTmp = RS485Rx.Zero_Offset;
			RS48501_TxBuf[15] = (uint8_t)(intTmp >> 8);
			RS48501_TxBuf[16] = (uint8_t)(intTmp & 0xFF);
			//Zero_Offset
			intTmp = RS485Rx.Max_MinValue;
			RS48501_TxBuf[17] = (uint8_t)(intTmp >> 8);
			RS48501_TxBuf[18] = (uint8_t)(intTmp & 0xFF);
			//온도 경고 편차 값(소수점 첫째자리까지만 송신, 둘째자리는 버림)
			intTmp = (ui.co_100times / 10) * 10;
			RS48501_TxBuf[19] = (uint8_t)(intTmp >> 8);
			RS48501_TxBuf[20] = (uint8_t)(intTmp & 0xFF);
		}
		else
		{
			RS48501_TxBuf[15] = 0xFF;
			RS48501_TxBuf[16] = 0xFF;
			RS48501_TxBuf[17] = 0xFF;
			RS48501_TxBuf[18] = 0xFF;
			//온도 경고 편차 값(소수점 첫째자리까지만 송신, 둘째자리는 버림)
			intTmp = (ui.co_100times / 10) * 10;
			RS48501_TxBuf[19] = (uint8_t)(intTmp >> 8);
			RS48501_TxBuf[20] = (uint8_t)(intTmp & 0xFF);
		}
	}
	else
	{*/
		//온도 경고 기준(소수점 첫째자리까지만 송신, 둘째자리는 버림)
		intTmp = (RS485Rx.ff_cTemp_warring_R / 10) * 10;
		RS48501_TxBuf[15] = (uint8_t)(intTmp >> 8);
		RS48501_TxBuf[16] = (uint8_t)(intTmp & 0xFF);
		//온도 알람 기준(소수점 첫째자리까지만 송신, 둘째자리는 버림)
		intTmp = (RS485Rx.ff_cTemp_alarm_R / 10) * 10;
		RS48501_TxBuf[17] = (uint8_t)(intTmp >> 8);
		RS48501_TxBuf[18] = (uint8_t)(intTmp & 0xFF);
		//온도 경고 편차 값(소수점 첫째자리까지만 송신, 둘째자리는 버림)
		intTmp = (ui.co_100times / 10) * 10;
		RS48501_TxBuf[19] = (uint8_t)(intTmp >> 8);
		RS48501_TxBuf[20] = (uint8_t)(intTmp & 0xFF);
	//}

	// 체크섬 계산
	checksum = 0;
	for (ii = 1; ii < 21 ; ii++)
	{
		checksum += RS48501_TxBuf[ii];
	}
	RS48501_TxBuf[21] = (uint8_t)(checksum >> 8);
	RS48501_TxBuf[22] = (uint8_t)(checksum & 0xFF);
	//프레임 끝
	RS48501_TxBuf[23] = PACKET_ETX;

	if(ui.End_Code == 1)
	{
		RS48501_TxBuf[24] = ECODE_CR;
		RS48501_TxBuf[25] = ECODE_LF;
		// Add Request Data Frame to RS485-1 SendFrame
		for (ii = 0; ii < 26 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48501_TxBuf[ii];
		}
	}
	else
	{
		// Add Request Data Frame to RS485-1 SendFrame
		for (ii = 0; ii < 24 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48501_TxBuf[ii];
		}
	}

	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
}

/* Example: Sensor --> PC : AddF_CmdReqToPC(0,18,0x05A1,0x01~); */
void AddF_CmdReqToPC(uint16_t size, uint16_t cmd, uint8_t code, uint8_t error, uint8_t cmdAck)  // 일단 명령 요청을 위한 패킷 만드는거라고 생각해보자 //RxCallback
{
	uint8_t RS48502_TxBuf[20];
	uint16_t checksum;
	uint16_t ii;

	//프레임
	RS48502_TxBuf[0] = PACKET_STX;
	//Length 길이 // CMD ~ DATA 까지의 바이트 수
	RS48502_TxBuf[1] = (uint8_t)(size>> 8);
	RS48502_TxBuf[2] = (uint8_t)(size & 0xFF);
	//CMD		// 통신 명령
	RS48502_TxBuf[3] = (uint8_t)(cmd>> 8);
	RS48502_TxBuf[4] = (uint8_t)(cmd & 0xFF);
	//code		// 명령 구분
	RS48502_TxBuf[5] = code;

	// Count	// 송신 Count(0~255 반복)
	 ui.TxCount ++;
	RS48502_TxBuf[6] = ui.TxCount;
	// ID
	RS48502_TxBuf[7] = HsdID;

	// 온도 습도 등 데이터
	/* Data Range */
	RS48502_TxBuf[8] = error;	 // 에러 상태
	RS48502_TxBuf[9] = cmdAck;   // 수신 명령 확인 회신
	// Dummy Data
	RS48502_TxBuf[10] = 0;
	RS48502_TxBuf[11] = 0;
	RS48502_TxBuf[12] = 0;
	RS48502_TxBuf[13] = 0;
	RS48502_TxBuf[14] = 0;

	// 체크섬 계산 // length ~ Data 까지의 1Byte 씩 합한 값
	checksum = 0;
	for (ii = 1; ii < 15 ; ii++)
	{
		checksum += RS48502_TxBuf[ii];
	}
	RS48502_TxBuf[15] = (uint8_t)(checksum >> 8);
	RS48502_TxBuf[16] = (uint8_t)(checksum & 0xFF);
	//프레임 끝
	RS48502_TxBuf[17] = PACKET_ETX;

	if(ui.End_Code == 1)
	{
		RS48502_TxBuf[18] = ECODE_CR;
		RS48502_TxBuf[19] = ECODE_LF;
		// Add Request Data Frame to RS485-1 SendFrame
		for (ii = 0; ii < 20 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48502_TxBuf[ii];
		}
	}
	else
	{
		// Add Data Request Frame to RS485-1 SendFrame
		for (ii = 0; ii < 18 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48502_TxBuf[ii];
		}
	}

	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
}
void AddF_CmdReqToPC_Val(uint16_t size, uint16_t cmd, uint8_t code, uint8_t error, int16_t data1, int16_t data2) // RxCallback
{
	uint8_t RS48502_TxBuf[20];
	uint16_t checksum, ii;
	int16_t  intTmp;;

	//프레임
	RS48502_TxBuf[0] = PACKET_STX;
	//Length 길이
	RS48502_TxBuf[1] = (uint8_t)(size>> 8);
	RS48502_TxBuf[2] = (uint8_t)(size & 0xFF);
	//CMD
	RS48502_TxBuf[3] = (uint8_t)(cmd>> 8);
	RS48502_TxBuf[4] = (uint8_t)(cmd & 0xFF);
	//code
	RS48502_TxBuf[5] = code;
	// Count
	ui.TxCount ++;
	RS48502_TxBuf[6] = ui.TxCount;

	// ID
	RS48502_TxBuf[7] = HsdID; // ui.ID

	/* Data Range */
	RS48502_TxBuf[8] = error;	 // 에러 상태
	intTmp = (data1 / 10) * 10;	 // 소수점 둘째자리 제거
	RS48502_TxBuf[9] = (uint8_t)(intTmp >> 8);
	RS48502_TxBuf[10] = (uint8_t)(intTmp  & 0xFF);
	intTmp = (data2 / 10) * 10;  // 소수점 둘째자리 제거
	RS48502_TxBuf[11] = (uint8_t)(intTmp >> 8);
	RS48502_TxBuf[12] = (uint8_t)(intTmp  & 0xFF);
	// Dummy Data
	RS48502_TxBuf[13] = 0;
	RS48502_TxBuf[14] = 0;

	// 체크섬 계산
	checksum = 0;
	for (ii = 1; ii < 15 ; ii++)
	{
		checksum += RS48502_TxBuf[ii];
	}
	RS48502_TxBuf[15] = (uint8_t)(checksum >> 8);
	RS48502_TxBuf[16] = (uint8_t)(checksum & 0xFF);
	//프레임 끝
	RS48502_TxBuf[17] = PACKET_ETX;

	if(ui.End_Code == 1)
	{
		RS48502_TxBuf[18] = ECODE_CR;
		RS48502_TxBuf[19] = ECODE_LF;
		// Add Request Data Frame to RS485-1 SendFrame
		for (ii = 0; ii < 20 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48502_TxBuf[ii];
		}
	}
	else
	{
		// Add Data Request Frame to RS485-1 SendFrame
		for (ii = 0; ii < 18 ; ii++)
		{
			RS48501_TxSendFrame[ii] = RS48502_TxBuf[ii];
		}
	}
	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
}
/* Example: Sensor --> PC : AddF_CmdReqToPC(0,18,0x05A1,0x01); */


void RS48501_TxData(void)
{
	uint16_t dataSize = 0;
	// RS48501 TX Start
	if(RS48501_TxPos != RS48501_TxEnd)
	{

		RS485_DE(); // HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET)  // RS485핀을 데이터를 송신할 수 있게 활성화

		 if(ui.Protocol_Type == 0)
		 {
			 if(Read_Data_Tx[1] == 0x03)
			 {
				 dataSize = Read_Data_Tx[2];
				 HAL_UART_Transmit_IT(&huart5, &Read_Data_Tx[0], dataSize+5);
			 }
			 else if((Read_Data_Tx[1] == 0x06) || (Read_Data_Tx[1] == 0x10))
			 {
				 HAL_UART_Transmit_IT(&huart5, &Read_Data_Tx[0], 8);
			 }
			 else
			 {
				 HAL_UART_Transmit_IT(&huart5, &Read_Data_Tx[0], 5);
			 }
		 }
		 else   // ui.Protocol_Type == 0 이 아닌 경우
		 {
			dataSize = ((uint16_t)RS48501_TxSendFrame[1] << 8);
			dataSize |= ((uint16_t)RS48501_TxSendFrame[2] & 0xFF);

			// Request Data Frame size = 18, Ack Data Frame size = 12
			if(ui.End_Code == 1){
				HAL_UART_Transmit_IT(&huart5, &RS48501_TxSendFrame[0], dataSize+8);

			}
			else
			{
				HAL_UART_Transmit_IT(&huart5, &RS48501_TxSendFrame[0], dataSize+6);
			}
		 }
		RS485Rx.boot_send = 1;



		RS48501_TxEnd++;
		if(RS48501_TxEnd >= 20)	RS48501_TxEnd = 0;
	}

}
/****************************************************************************/
/*	Overview	:	Tx 데이터 송신 이후 RX 준비             							*/
/*	Return value:	void													*/
/****************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	 if(huart->Instance==UART5)
	 {	// RS485_DE : 송신
		RS485_RE(); // 송신이 완료되면 자동으로 GPIO 핀 활성화해서 수신모드로..
		if(RS485Rx.boot_send == 1){
			reboot_flag = 1;
		}
	 }
}

/****************************************************************************/
/*	Overview	:	RX 데이터 처리 통신 프레임										*/
/*	Return value:	void													*/
/****************************************************************************/
uint8_t FUN_Rx_data_check(void)  // 실패한 수신 0 리턴 / 성공 RS485Rx.result 리턴
{								 // 프레임 각 부분이 올바른지 확인 하는거 같음 --> RS485 통신의 안정성 확보 역할인듯
	//STX 체크
	if(RS485Rx0Data[0] != PACKET_STX) //'S')
	{
		RS485Rx.Rx_cnt = 0;
		// 실패한 수신
		return 0;
	}
	else
	{
		if(RS485Rx.Rx_cnt == 1){
			RS485Rx.Rx_Data_flag = 1;  //Frame start is received
		}
	}
	if(RS485Rx.Rx_cnt >= 3)
	{
		// Length 체크
		if((RS485Rx0Data[1] != 0x00) && (RS485Rx0Data[2] != 0x0C))
		{
			RS485Rx.Rx_cnt = 0;
			RS485Rx.Rx_Data_flag = 0;  //Frame start reset
			// 실패한 수신
			return 0;
		}
	}

	if(RS485Rx.Rx_cnt >= 4)
	{
		//TYPE 체크
		// 0x05: 판넬형 열연기감지기 제품군
		if(RS485Rx0Data[3] != 0x05)
		{
			RS485Rx.Rx_cnt = 0;
			RS485Rx.Rx_Data_flag = 0;  //Frame start reset
			// 실패한 수신
			return 0;
		}
	}

	if(RS485Rx.Rx_cnt >= 6)
	{
		// CMD 체크 result는 명령 순번을 나타냄
		if((RS485Rx0Data[4] == 0x01) && (RS485Rx0Data[5] == 0x01))
		{
			RS485Rx.result += 1;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x01))
		{
			RS485Rx.result += 2;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x02))
		{
			RS485Rx.result += 3;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x03))
		{
			RS485Rx.result += 4;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x04))
		{
			RS485Rx.result += 5;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x05))
		{
			RS485Rx.result += 6;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x06))
		{
			RS485Rx.result += 7;
		}
		else if((RS485Rx0Data[4] == 0x03) && (RS485Rx0Data[5] == 0x19))
		{
			RS485Rx.result += 8;
		}
		else if((RS485Rx0Data[4] == 0xE3) && (RS485Rx0Data[5] == 0x60))
		{
			RS485Rx.result += 9;
		}
		else
		{
			RS485Rx.Rx_cnt = 0;
			RS485Rx.Rx_Data_flag = 0;  //Frame start reset
			RS485Rx.result = 0;
			// 실패한 수신
			return 0;
		}
	}
	if(RS485Rx.Rx_cnt >= 18)
	{
		//ETX 체크
		if(RS485Rx0Data[17] != PACKET_ETX)
		{
			RS485Rx.Rx_cnt = 0;
			RS485Rx.Rx_Data_flag = 0;  //Frame start reset
			RS485Rx.result = 0;
			// 실패한 수신
			return 0;
		}
		else
		{
			// 성공적인 수신
			return RS485Rx.result;
		}
	}
	// 데이터가 더 남아있다
	return 0;
}
uint8_t FUN_Rx_data_Modbus_check(void)  // 얘도 패킷 검사하고 실패 0 리턴 같음. 근데 얘는 성공 리턴 1임
{
	static uint8_t writeLen = 0;

	//[0] = Device ID Check
	if(RS485RxMOData[0] != HsdID){
		RS485Rx.Rx_cnt = 0;
		// 실패한 수신
		return 0;
	}
	else{
		if(RS485Rx.Rx_cnt == 1){
			RS485Rx.Rx_Data_flag = 1;  //Frame start is received
		}
	}
	//[1] = Function Check
	if(RS485Rx.Rx_cnt >= 2)
	{
		// Function 체크
		if((RS485RxMOData[1] != 0x03) && (RS485RxMOData[1] != 0x06) && (RS485RxMOData[1] != 0x10)){
			RS485Rx.Rx_cnt = 0;
			RS485Rx.Rx_Data_flag = 0;  //Frame start reset
			// 실패한 수신
			return 0;
		}
	}
	//[2] = Address Register
	if(RS485Rx.Rx_cnt >= 3)
	{
		// Address 0x0A 체크
		if(RS485RxMOData[2] != 0xA0){
			RS485Rx.Rx_cnt = 0;
			RS485Rx.Rx_Data_flag = 0;  //Frame start reset
			// 실패한 수신
			return 0;
		}
	}
	//[6] = Length Check
	if(RS485Rx.Rx_cnt >= 8)
	{
		// Function Code is 0x10(Write Multiple Registers)
		if(RS485RxMOData[1] == 0x10){
			// 데이터가 더 남아있다
			writeLen = RS485RxMOData[6];
		}
		else{
			// 성공적인 수신
			return 1;
		}
	}
	//0x10: Write Multiple Registers Max Length Check <-- Modbus_Map(Max is 25 byte)
	if((RS485Rx.Rx_cnt >= (writeLen + 9)) || (RS485Rx.Rx_cnt >= 25))
	{
		// 성공적인 수신
		return 1;
	}
	// 데이터가 더 남아있다
	return 0;
}
/****************************************************************************/
/*	Overview	:	Rx 데이터 ICD 해석 부분										*/
/*	Return value:	void													*/
/****************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint16_t checkSumA;
    uint16_t rxCheckSumA;
	 if(huart->Instance==UART5)
	 {
		 if(ui.Protocol_Type == 0)
		 {
			 RS485RxMOData[RS485Rx.Rx_cnt++] = RS485RxA;

			 RS485Rx.result_MO = FUN_Rx_data_Modbus_check();

			 if(RS485Rx.result_MO == 1) {
				 RS485Rx.Rx_cnt = 0;
				 RS485Rx.Rx_Data_flag = 0;
				 FUN_Modbus_Read();
				 RS48501_TxData();
			 }
		 }
		 else
		 {
			 RS485Rx0Data[RS485Rx.Rx_cnt++] = RS485RxA;

			 RS485Rx.result = FUN_Rx_data_check();

			 uint8_t rsdCode;
			 // CheckSum Check after One Frame Receive and Id check OK
			 if(RS485Rx.result != 0)
			 {
				 RS485Rx.Rx_Data_flag = 0;
				 RS485Rx.Rx_cnt = 0;
				 // 수신데이터 처리하지 않음(목적지가 ID가 맞지 않음)
				 if(RS485Rx0Data[7] == HsdID)
				 {
					 // CheckSum
					 checkSumA = 0;
					 for (uint16_t i = 1; i < 15 ; i++)
					 {
						 checkSumA += RS485Rx0Data[i];
					 }
					 rxCheckSumA   = ((int16_t)RS485Rx0Data[15] << 8);
					 rxCheckSumA   |= ((int16_t)RS485Rx0Data[16] & 0xFF);

					 // CheckSum
					 if(checkSumA != rxCheckSumA){
						 RS485Rx.Checksum_Error_Cnt++;
					 	if(RS485Rx.Checksum_Error_Cnt >= 3)
					 	{
					 		// 3회 연속 발생시 내부 알람 발생, LCD에 에러 Display
							RS485Rx.Checksum_Error = 1;  // 하기 State를 활용하여 LCD 에러 Display 등 수행
							// Ack To PC or PLC
							rsdCode = (uint8_t)RS485Rx.result;
							if(rsdCode == 1){
								// 비정상 명령수신 에러응답 CMD: 0x05A1, Code: rsdCode
								AddF_CmdReqToPC(0x0C,0x05A3,rsdCode,0xFF,0x00);
							}
							else{
								// 비정상 명령수신 에러응답 CMD: 0x05A3, Code: (rsdCode-1)
								AddF_CmdReqToPC(0x0C,0x05A3,(rsdCode-1),0xFF,0x00);
							}
					 	}
					 	// CheckSum이 맞지 않으면 정상응답 하지 않음
					 	RS485Rx.result = 0;
					 }
					 else	//Pass, HsdData Update
					 {
						 // 정상 Packet 수신시 자동 리셋
						 // 정상 Packet 미 수신시 리셋 버튼에 의한 리셋 필요
						 RS485Rx.Checksum_Error = 0;
						 RS485Rx.Checksum_Error_Cnt = 0;
					 }

					 uint8_t cmd_Ack; //, Error_bit, reset_bit, MSG_SYS;
					 int16_t tempVal1, tempVal2; //, DEVVal;
					 // 정상명령 수신 후 응답
					 switch(RS485Rx.result){
						 case 1:
							 // Request a Data frame
							 AddF_ReqDataToPC(0x12, 0x05A1, 0x01);
							 break;
						 case 2:
							// 수신 명령 수행, 감지상태 RESET
							if(RS485Rx0Data[9] == 1){
								Gas_Sensor.Gas_Detect = 0;
								ui.Status.Bit.SMOKE_DETECT = 0;
								ui.temp_alarm_bit = 0;
								ui.temp_warring_bit = 0;
								cmd_Ack = 1;
							}
							else{
								cmd_Ack = 0;
							}
							AddF_CmdReqToPC(0x0C,0x05A3,0x01,0x00,cmd_Ack);
							 break;
						 case 3:
							 // 수신 명령 수행, 온도 경고/알람 기준값 변경
							// 온도 경고 발생 기준값
							RS485Rx.ff_cTemp_warring_R = ((int16_t)(ui.temp_warring * 100));
							RS485Rx.ff_cTemp_alarm_R = ((int16_t)(ui.temp_alarm * 100));

							RS485Rx.ff_cTemp_warring = ((int16_t)RS485Rx0Data[9] << 8);
							RS485Rx.ff_cTemp_warring |= ((int16_t)RS485Rx0Data[10] & 0xFF);
							// 온도 알람 발생 기준값
							RS485Rx.ff_cTemp_alarm   = ((int16_t)RS485Rx0Data[11] << 8);
							RS485Rx.ff_cTemp_alarm   |= ((int16_t)RS485Rx0Data[12] & 0xFF);
							// Limit
							if(RS485Rx.ff_cTemp_warring > 9999){
								RS485Rx.ff_cTemp_warring = 9999;
							}
							else if(RS485Rx.ff_cTemp_warring < 0){
								RS485Rx.ff_cTemp_warring = 0;
							}
							else;
							if(RS485Rx.ff_cTemp_alarm > 9999){
								RS485Rx.ff_cTemp_alarm = 9999;
							}
							else if(RS485Rx.ff_cTemp_alarm < 0){
								RS485Rx.ff_cTemp_alarm = 0;
							}
							else;
							// 온도값 경고 기준 Update
							ui.temp_warring    = (float)(RS485Rx.ff_cTemp_warring) / 100;
							// 온도값 알람 기준 Update
							ui.temp_alarm      = (float)(RS485Rx.ff_cTemp_alarm) / 100;

							if((RS485Rx.ff_cTemp_warring_R != RS485Rx.ff_cTemp_warring) || (RS485Rx.ff_cTemp_alarm_R != RS485Rx.ff_cTemp_alarm))
							{
								// 온도 경고/알람 기준값 EEPROM 저장
								EEPROM.SaveData_Flag = 1;
							}

							// 정상명령 응답 (소주점 둘째자리 제거)
							tempVal1 = RS485Rx.ff_cTemp_warring;
							tempVal2 = RS485Rx.ff_cTemp_alarm;
							AddF_CmdReqToPC_Val(0x0C, 0x05A3, 0x02, 0x00, tempVal1, tempVal2);
							break;
						 case 4:
							// 수신명령 수행: 온도 경고,알람 Enable / Disable
							uint8_t alarm_enable = ui.temp_alarm_enable;

							if(RS485Rx0Data[9] == 0){
								ui.temp_alarm_enable = 0;
							}
							else{
								ui.temp_alarm_enable = 1;
							}

							if(alarm_enable != ui.temp_alarm_enable)
							{
								// 온도 경고/알람 Enable/Disable EEPROM 저장
								EEPROM.SaveData_Flag = 1;
							}

							// 정상명령 응답
							cmd_Ack = ui.temp_alarm_enable;
							AddF_CmdReqToPC(0x0C,0x05A3,0x03,0x00,cmd_Ack);
							 break;
						 case 5:
							uint8_t warring_maintain_bit = ui.temp_warring_maintain_bit;
							// 수신명령 수행: 온도 경고 유지 Enable / Disable
							if(RS485Rx0Data[9] == 1){
								ui.temp_warring_maintain_bit = 1;
							}
							else{
								ui.temp_warring_maintain_bit = 0;
							}

							if(warring_maintain_bit != ui.temp_warring_maintain_bit)
							{
								// 온도 경고온도유지 설정 EEPROM 저장
								EEPROM.SaveData_Flag = 1;
							}

							// 정상명령 응답
							cmd_Ack = ui.temp_warring_maintain_bit;
							AddF_CmdReqToPC(0x0C,0x05A3,0x04,0x00,cmd_Ack);
							break;
						 case 6:
							uint8_t alarm_maintain_bit = ui.temp_alarm_maintain_bit;
							// 수신명령 수행: 온도 알람 유지 Enable/Disable
							if(RS485Rx0Data[9] == 1){
								ui.temp_alarm_maintain_bit = 1;
							}
							else{
								ui.temp_alarm_maintain_bit = 0;
							}
							if(alarm_maintain_bit != ui.temp_alarm_maintain_bit)
							{
								// 온도 경고알람유지 설정 EEPROM 저장
								EEPROM.SaveData_Flag = 1;
							}

							// 정상명령 응답
							cmd_Ack = ui.temp_alarm_maintain_bit;
							AddF_CmdReqToPC(0x0C,0x05A3,0x04,0x00,cmd_Ack);
							break;
						 case 7:
							/*ui.co_100times_R = ((uint16_t)(ui.Warring_Deviation * 100));
							// 수신명령 수행: 온도 경고 편차 값 설정
							ui.co_100times = ((uint16_t)RS485Rx0Data[9] << 8);
							ui.co_100times |= ((uint16_t)RS485Rx0Data[10] & 0xFF);
							if(ui.co_100times > 9999){
								ui.co_100times = 9999;
							}
							else if(ui.co_100times < 0){
								ui.co_100times = 0;
							}
							else;
							// 온도 경고 편차 값 Update
							ui.Warring_Deviation     = (float)(ui.co_100times) / 100;
							if(ui.co_100times_R != ui.co_100times)
							{
								// 온도 경고편차값 설정 EEPROM 저장
								EEPROM.SaveData_Flag = 1;
							}

							// 정상명령 응답
							tempVal1 = (int16_t)ui.co_100times;
							AddF_CmdReqToPC_Val(0x0C, 0x05A3, 0x06, 0x00, tempVal1,0x00);*/
							break;
						 case 8:
							 //부트로더 저장
							 u1f_bootjump_flag = 1;
							 cmd_Ack = RS485Rx0Data[7];
							 AddF_CmdReqToPC(0x0C,0x0504,0x66,0x00,cmd_Ack);
							 break;
						 case 9:
							 //ADC Offset Check Enable/Disable
							if(RS485Rx0Data[9] == 1)
							{
								 RS485Rx.ADC_Offset_Flag = 1;
								 RS485Rx.ADC_Offset_Check_1 = 1;
							}
							else
							{
								 RS485Rx.ADC_Offset_Flag = 0;
								 RS485Rx.ADC_Offset_Check_1 = 0;
								 RS485Rx.ADC_Offset_Check_2 = 0;
							}

							 cmd_Ack = RS485Rx0Data[9];
							AddF_CmdReqToPC(0x0C,0x05A3,0x60,0x00,cmd_Ack);
							 break;
						 default:  	 break;
					 }
				 }
				 else{
					 // 수신데이터 처리하지 않음(목적지가 ID가 맞지 않음)
					 RS485Rx.result = 0;
				 }
				 RS48501_TxData();
			 }
		 }
		 HAL_UART_Receive_IT(&huart5, &RS485RxA, 1);
	 }
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_RS485_Error_routine(void)
{
	Error.RS485_error_chk = HAL_UART_GetError(&huart5);
	Error.RS485_State = HAL_UART_GetState(&huart5);
	if(Error.RS485_error_chk != 0)
	{
		Error.RS485_error_Cnt  ++;
		// 5회 연속 에러 발생시
		if(Error.RS485_error_Cnt >= 5)
		{
			//
			HAL_UART_Receive_IT(&huart5, &RS485RxA, 1);
			RS485_RE();
			//
			Error.RS485_error = 1;
			Error.RS485_error_Cnt = 0;
		}
	}
	else{
		Error.RS485_error_Cnt = 0;
	}
}
void FUN_RS485_Rx_Timeout_Check(void)     	// 10ms마다 호출
{
	// Data Head 수신 이후 정상종료가 이루어지지 않았을 때 Time Out(Rx)
	if(RS485Rx.Rx_Data_flag == 1){  	// 데이터 수신이 시작되면 1이 되는거 같음
		RS485Rx.Rx_Data_cnt ++;
		// Time OUt : 250ms
		if(RS485Rx.Rx_Data_cnt > 25){   // 250ms(25번 호출) 지나면 전부 0으로.. 이게 타임아웃인거 같음
			RS485Rx.Rx_cnt = 0;	       //Buff Index Clear
			RS485Rx.Rx_Data_flag = 0;
			for (uint16_t i = 0; i < 25 ; i++){
				 RS485RxMOData[i] = 0x00;
				 if(i<18){
					 RS485Rx0Data[i] = 0x00;
				 }
			}
		}
	}
	else{
		RS485Rx.Rx_Data_cnt = 0;      // 수신중이 아니면 cnt = 0
	}
}
void RS485_Baudrate_Init(uint8_t baudrate)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  if(baudrate == BAUD_115200){
	  huart5.Init.BaudRate = 115200;
  }
  else if(baudrate == BAUD_38400){
	  huart5.Init.BaudRate = 38400;
  }
  else if(baudrate == BAUD_19200){
  	  huart5.Init.BaudRate = 19200;
  }
  else if(baudrate == BAUD_9600){
	  huart5.Init.BaudRate = 9600;
  }
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_RS485Ex_Init(&huart5, UART_DE_POLARITY_HIGH, 0, 0) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart5, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart5, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}
#endif



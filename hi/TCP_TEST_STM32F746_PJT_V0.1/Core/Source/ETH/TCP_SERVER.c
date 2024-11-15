/*
 * TCP_SERVER_01.c
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */


#include "../TCP_TEST_STM32F746_FW.h"




//extern struct netif gnetif;

struct netconn *conn_01, *newconn_01;


MODRD_Header MORD;
MODWR_Header MOWR;
Module_Header Modbus;

uint8_t MODWR_Flag = 0; // 0: none, 1: Write MODBUS
uint8_t MODWR_TCP_Flag = 0;
uint8_t PW_Flag = 0; // 0: none, 1: Write MODBUS



// TCP_IP Server Port
uint16_t TCP_Server_Port_01 = 4000;

// TCP_IP Server Buff
uint8_t u1f_eth_rx_buff_01[512];
uint8_t u1f_eth_tx_buff_01[2048];

uint16_t u1f_eth_rx_length_01 = 0;

uint16_t Tcp_Cmd_BootLoaderJump_Flag= 0;

uint64_t Check_TCP_01_RX_Cnt = 0;

uint16_t TCP_Checksum_Creat(uint16_t TX_Data_Cnt);
uint16_t TCP_Checksum_Check(uint16_t RX_Data_Cnt);


void TCP_RX_DATA_TASK(void *argument)
{
	  err_t err;

	  /*
	  struct netbuf *buf;
	  void *data;
	  u16_t len;
*/
	  LWIP_UNUSED_ARG(argument);

	  conn_01 = netconn_new(NETCONN_TCP);
	  netconn_bind(conn_01, IP_ADDR_ANY, TCP_Server_Port_01);

	  LWIP_ERROR("tcpecho: invalid conn", (conn_01 != NULL), return;);

	  netconn_listen(conn_01);



	  while(1)
	  {
	    err = netconn_accept(conn_01, &newconn_01);
	    if(err == ERR_OK)
	    {

	      struct netbuf *buf;
	      void *data;
	      u16_t len;

	      while((err = netconn_recv(newconn_01, &buf)) == ERR_OK)
	      {
	        do
	        {
				 netbuf_data(buf, &data, &len);       //receive data pointer & length

				 memcpy(&u1f_eth_rx_buff_01, data, len);
				 u1f_eth_rx_length_01 = len;
				 Check_TCP_01_RX_Cnt++;

				   TCP_Server_Modbus();

	        }

	        while(netbuf_next(buf) >= 0);  //check buffer empty
	        netbuf_delete(buf);      	   //clear buffer
	      }
	      netconn_close(newconn_01);
	      netconn_delete(newconn_01);         //clear buffer
	    }

	  }
}




//확인용  변수
uint64_t TCP_RX_COUNT  = 0;
uint64_t TCP_TX_COUNT_A = 0;
uint64_t TCP_TX_COUNT_B = 0;
uint64_t TCP_TX_COUNT_C = 0;
uint64_t TCP_TX_COUNT_D = 0;

uint64_t StandardCount = 0;


extern uint8_t MODWR_Flag; // 0: none, 1: Write MODBUS




uint32_t Check_ETH_ERR = 0;
uint8_t MODE_READ_FLAG = 0;
uint8_t MODE_WRITE_FLAG = 0;

uint16_t ETH_Check_Cnt = 0;
uint16_t Tcp_RX_Data_CheckSum_Ok_Flag = 0;

void TCP_Server_Modbus(void)
{
	uint16_t i, j;
	uint16_t Data_Cnt = 0;

	if((u1f_eth_rx_buff_01[6] == Modbus.u.Header.ID)||(u1f_eth_rx_buff_01[6] == 0x01))
	{
		//읽기 영억
		if(u1f_eth_rx_buff_01[7] == 0x03)
		{
			MORD.u.stream[0] = u1f_eth_rx_buff_01[6];  //Unit ID
			MORD.u.stream[1] = u1f_eth_rx_buff_01[7];  //Function code
			MORD.u.stream[2] = u1f_eth_rx_buff_01[9];  //Start Add
			MORD.u.stream[3] = u1f_eth_rx_buff_01[8];  //Start_Add
			MORD.u.stream[4] = u1f_eth_rx_buff_01[11]; //Length
			MORD.u.stream[5] = u1f_eth_rx_buff_01[10]; //Length
			if(MORD.u.Header.Add == 40976)
			{
				StandardCount++;
			}
			j = MORD.u.Header.Inx*2 + 3;

			u1f_eth_tx_buff_01[0] = u1f_eth_rx_buff_01[0];
			u1f_eth_tx_buff_01[1] = u1f_eth_rx_buff_01[1];
			u1f_eth_tx_buff_01[2] = u1f_eth_rx_buff_01[2];
			u1f_eth_tx_buff_01[3] = u1f_eth_rx_buff_01[3];
			u1f_eth_tx_buff_01[4] = (unsigned char)(j >> 8);
			u1f_eth_tx_buff_01[5] = (unsigned char)(j); //길이정보

			u1f_eth_tx_buff_01[6] = u1f_eth_rx_buff_01[6]; //ID
			u1f_eth_tx_buff_01[7] = 0x03;               //FunctionCode
			u1f_eth_tx_buff_01[8] = MORD.u.Header.Inx*2*2;
			for(i=0;i<MORD.u.Header.Inx;i++)
			{
				j = MORD.u.Header.Add+i;

				u1f_eth_tx_buff_01[9+i*2] = Modbus.u.stream[j*2+1];
				u1f_eth_tx_buff_01[9+i*2 + 1] = Modbus.u.stream[j*2];

			}

			Data_Cnt = (MORD.u.Header.Inx*2) + 9;
			TCP_TX_COUNT_A++;
		}
		else if(u1f_eth_rx_buff_01[7] == 0x10) // broadcast
		{
			MOWR.u.stream[0] = u1f_eth_rx_buff_01[6];   //Unit ID
			MOWR.u.stream[1] = u1f_eth_rx_buff_01[7];   //Function code
			MOWR.u.stream[2] = u1f_eth_rx_buff_01[9];   //Start Add
			MOWR.u.stream[3] = u1f_eth_rx_buff_01[8];   //Start_Add
			MOWR.u.stream[4] = u1f_eth_rx_buff_01[11];  //Length
			MOWR.u.stream[5] = u1f_eth_rx_buff_01[10];  //Length
			for(i=0; i < MOWR.u.Header.Inx; i++)   //2  -> 0, 1
			{
				j = MOWR.u.Header.Add+i;

				Modbus.u.stream[(j*2)+1] = u1f_eth_rx_buff_01[(i*2)+13];
				Modbus.u.stream[j*2]     = u1f_eth_rx_buff_01[(i*2)+14];
			}

			//Modbus-TCP Response

			u1f_eth_tx_buff_01[0] = u1f_eth_rx_buff_01[0];
			u1f_eth_tx_buff_01[1] = u1f_eth_rx_buff_01[1];
			u1f_eth_tx_buff_01[2] = u1f_eth_rx_buff_01[2];
			u1f_eth_tx_buff_01[3] = u1f_eth_rx_buff_01[3];
			u1f_eth_tx_buff_01[4]  = 0;
			u1f_eth_tx_buff_01[5]  = 0x06;
			u1f_eth_tx_buff_01[6]  = u1f_eth_rx_buff_01[6];
			u1f_eth_tx_buff_01[7]  = u1f_eth_rx_buff_01[7];
			u1f_eth_tx_buff_01[8]  = u1f_eth_rx_buff_01[8];
			u1f_eth_tx_buff_01[9]  = u1f_eth_rx_buff_01[9];
			u1f_eth_tx_buff_01[10] = u1f_eth_rx_buff_01[10];
			u1f_eth_tx_buff_01[11] = u1f_eth_rx_buff_01[11];

			Data_Cnt = 12;
			TCP_TX_COUNT_B++;
		}
		//읽기 영억
		else if(u1f_eth_rx_buff_01[7] == 0x01)
		{
			MORD.u.stream[0] = u1f_eth_rx_buff_01[6];  //Unit ID
			MORD.u.stream[1] = u1f_eth_rx_buff_01[7];  //Function code
			MORD.u.stream[2] = u1f_eth_rx_buff_01[9];  //Start Add
			MORD.u.stream[3] = u1f_eth_rx_buff_01[8];  //Start_Add
			MORD.u.stream[4] = u1f_eth_rx_buff_01[11]; //Length
			MORD.u.stream[5] = u1f_eth_rx_buff_01[10]; //Length
			MORD.u.Header.Inx = MORD.u.Header.Inx / 16;
			j = MORD.u.Header.Inx*2 + 3;

			u1f_eth_tx_buff_01[0] = u1f_eth_rx_buff_01[0];
			u1f_eth_tx_buff_01[1] = u1f_eth_rx_buff_01[1];
			u1f_eth_tx_buff_01[2] = u1f_eth_rx_buff_01[2];
			u1f_eth_tx_buff_01[3] = u1f_eth_rx_buff_01[3];
			u1f_eth_tx_buff_01[4] = (unsigned char)(j >> 8);
			u1f_eth_tx_buff_01[5] = (unsigned char)(j); //길이정보

			u1f_eth_tx_buff_01[6] = u1f_eth_rx_buff_01[6]; //ID
			u1f_eth_tx_buff_01[7] = 0x01;               //FunctionCode
			u1f_eth_tx_buff_01[8] = MORD.u.Header.Inx*2*2;  // 4 * 4byte
			for(i=0;i<MORD.u.Header.Inx;i++)
			{
				j = MORD.u.Header.Add+i;

				u1f_eth_tx_buff_01[9+i*2] = Modbus.u.stream[j*2+1]; // 11
				u1f_eth_tx_buff_01[9+i*2 + 1] = Modbus.u.stream[j*2]; // 10

			}

			Data_Cnt = (MORD.u.Header.Inx*2) + 9;
			TCP_TX_COUNT_C++;
		}
		//쓰기 영억
		else if(u1f_eth_rx_buff_01[7] == 0x0F) // broadcast
		{
			 MOWR.u.stream[0] = u1f_eth_rx_buff_01[6];   //Unit ID
			 MOWR.u.stream[1] = u1f_eth_rx_buff_01[7];   //Function code
			 MOWR.u.stream[2] = u1f_eth_rx_buff_01[9];   //Start Add
			 MOWR.u.stream[3] = u1f_eth_rx_buff_01[8];   //Start_Add
			 MOWR.u.stream[4] = u1f_eth_rx_buff_01[11];  //Length
			 MOWR.u.stream[5] = u1f_eth_rx_buff_01[10];  //Length

			 for(i=0; i < MOWR.u.Header.Inx; i++)   //2  -> 0, 1
			 {
				j = MOWR.u.Header.Add+i;
				Modbus.u.stream[(j*2)+1] = u1f_eth_rx_buff_01[(i*2)+13];
				Modbus.u.stream[j*2]     = 0x00;
			 }

			 //Modbus-TCP Response

			 u1f_eth_tx_buff_01[0] = u1f_eth_rx_buff_01[0];
			 u1f_eth_tx_buff_01[1] = u1f_eth_rx_buff_01[1];
			 u1f_eth_tx_buff_01[2] = u1f_eth_rx_buff_01[2];
			 u1f_eth_tx_buff_01[3] = u1f_eth_rx_buff_01[3];
			 u1f_eth_tx_buff_01[4]  = 0;
			 u1f_eth_tx_buff_01[5]  = 0x06;
			 u1f_eth_tx_buff_01[6]  = u1f_eth_rx_buff_01[6];
			 u1f_eth_tx_buff_01[7]  = u1f_eth_rx_buff_01[7];
			 u1f_eth_tx_buff_01[8]  = u1f_eth_rx_buff_01[8];
			 u1f_eth_tx_buff_01[9]  = u1f_eth_rx_buff_01[9];
			 u1f_eth_tx_buff_01[10] = u1f_eth_rx_buff_01[10];
			 u1f_eth_tx_buff_01[11] = u1f_eth_rx_buff_01[11];

			 Data_Cnt = 12;
			 TCP_TX_COUNT_D++;
		}


		netconn_write(newconn_01, u1f_eth_tx_buff_01, Data_Cnt, NETCONN_COPY);
	}
	else
	{
		Data_Cnt = 0;

		Check_ETH_ERR++;
	}
}

uint16_t TCP_Checksum_Creat(uint16_t TX_Data_Cnt)
{
	uint32_t u4t_sum_data = 0;
	uint16_t u2t_rtn = 0;

	//STX  : LENGTH ~ DATA
	for(uint16_t i = 1; i < TX_Data_Cnt; i++)
	{
		u4t_sum_data += (uint32_t)u1f_eth_tx_buff_01[i];
	}

	u2t_rtn = (uint16_t)u4t_sum_data;

	return u2t_rtn;
}

uint16_t TCP_Checksum_Check(uint16_t RX_Data_Cnt)
{
	uint32_t u4t_sum_data_r = 0;
	uint16_t u1t_chksum[2] = {0,0};
	uint16_t u2t_chksum = 0;

	//STX를 제외한 LENGTH 부터 DATA 까지 전체 길이까지 계산하며 -3은 전체 이더넷 패킷길이에서 체크섬과 ETX를 제외한것 까지
	for(uint16_t i = 1; i < (RX_Data_Cnt - 3); i++)
	{
		u4t_sum_data_r += (uint32_t)u1f_eth_rx_buff_01[i];
	}

	u2t_chksum = (uint16_t)u4t_sum_data_r;

	if(u2t_chksum > 0) //앞에서 데이터 체크시 잘못되면  모든데이터를 0으로 초기화 하며 모든데이터 0에대한 체크섬이 OK로 나와서 이것을 방지함
	{

		u1t_chksum[0] = (uint8_t)((u2t_chksum >> 8) & 0xFF);
		u1t_chksum[1] = (uint8_t)(u2t_chksum & 0xFF);

		if(u1t_chksum[0] != u1f_eth_rx_buff_01[RX_Data_Cnt-3])
		{
			return 0;  //CHECK_SUM_ERROR
		}

		if(u1t_chksum[1] != u1f_eth_rx_buff_01[RX_Data_Cnt-2])
		{
			return 0; //CHECK_SUM_ERROR
		}

		return 1;     //CHECK_SUM_OK
	}
	else
	{
		return 0;     //CHECK_SUM_ERROR
	}
}

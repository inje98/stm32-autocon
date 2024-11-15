/*
 * TCP_SERVER_01.h
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_ETH_TCP_SERVER_H_
#define SOURCE_ETH_TCP_SERVER_H_


typedef struct _MODRD_Header{
	union
	{
		struct
		{
			uint8_t  ID; // 1
			uint8_t  Fun;
			uint16_t Add;
			uint16_t Inx;
			uint16_t CRC16;
		}Header;
		uint8_t stream[8];
	}u;
}MODRD_Header;

typedef struct _MODWR_Header{
	union
	{
		struct
		{
			uint8_t  ID; // 1
			uint8_t  Fun;
			uint16_t Add;
			uint16_t Inx;
			uint8_t  Byte_Inx;
			uint16_t Data[100];
		}Header;
		uint8_t stream[207];
	}u;
}MODWR_Header;

typedef struct _Module_Header{
	union
	{
		struct
		{
			unsigned short Reserved[40000];
			unsigned short Alert; 			//40000
			//unsigned short Reserved1[3]; 				//40961~40963
			unsigned short Temperature; 	//40001
			//unsigned short Reserved2;							//40965
			unsigned short Humidity; 		//40002
			//unsigned short Reserved3[9];					//40967~40975
			unsigned short WarningStandard; //40003
			unsigned short GUI;             //40004
			//unsigned short Reserved4[9024];
			unsigned short ID; 			    //40005
			unsigned short Reset; 			//40006
			unsigned short Button3;
		}Header;
		unsigned char stream[80012];
	}u;
}Module_Header;

void TCP_Test_Respond_01(void);
void TCP_Server_Modbus(void);
void TCP_Server_PC_Mon(void);


uint16_t TCP_Checksum_Check(uint16_t RX_Data_Cnt);
uint16_t TCP_Checksum_Creat(uint16_t TX_Data_Cnt);


extern uint8_t MODWR_Flag;
extern uint8_t MODWR_TCP_Flag;
extern Module_Header Modbus;

#endif /* SOURCE_ETH_TCP_SERVER_H_ */

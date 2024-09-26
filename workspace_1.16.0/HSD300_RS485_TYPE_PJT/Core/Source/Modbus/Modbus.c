/*
 * Modbus.c
 *
 *  Created on: 2020. 8. 1.
 *      Author: dongho
 *      Vor.1.00
 */
/*-----------------------------Vor.1.10------------------------------------------*/

/* Includes ------------------------------------------------------------------*/

#include "..\Source\HSD300_FW.h"
/* Private define ------------------------------------------------------------*/
void FUN_Modbus_RxCallback_ReadData(uint8_t Addrs, uint8_t Lenth);
void FUN_Modbus_RxCallback_ReadWriteData(uint8_t Addrs, uint8_t Lenth, uint8_t Fun);
void FUN_Modbus_RxCallback_ERROR(uint8_t Fun, uint8_t Ex_Code);
void FUN_Modbus_RxCallback_Flag(void);
void FUN_Modbus_Write_save(void);

uint16_t CreateCRC16(uint32_t *buff, size_t len);
uint16_t CRC16(uint8_t* buf, size_t len);
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
uint8_t Read_Data_Tx[37];
uint8_t Data_Register_flag = 0;
uint8_t Data_Register[16];
uint8_t Exception_Code;

uint8_t Test[6];
uint16_t crc16 = 0xFFFF;
uint32_t* TESTS[6];
/* Private function prototypes -----------------------------------------------*/


uint16_t CRC16(uint8_t* buf, size_t len)
{
  uint16_t crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}

// �ʱ�ȭ
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Modbus_init(void)
{
	Data_Register_flag = 1;
	uint8_t Len;
	Len=0x06;

	Test[0]= 0xFF;
	Test[1]= 0x03;
	Test[2]= 0x00;
	Test[3]= 0x06;
	Test[4]= 0x00;
	Test[5]= 0x01;

	crc16 =CRC16((uint8_t*)&Test, Len);
}
/****************************************************************************/
/*	Overview	:	Read Data												*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Modbus_RxCallback_Flag(void)
{
	RS485Rx.ff_cTemp_warring_R = ((int16_t)(ui.temp_warring * 100));
	RS485Rx.ff_cTemp_alarm_R = ((int16_t)(ui.temp_alarm * 100));
	RS485Rx.Warring_Deviation_R = ((uint16_t)(ui.Warring_Deviation * 100));
	RS485Rx.TEnable_bit_R = ui.temp_alarm_enable;
	RS485Rx.Temp_Warring_Keep_R = ui.temp_warring_maintain_bit;
	RS485Rx.Temp_Alram_keep_R = ui.temp_alarm_maintain_bit;

	Data_Register[0] = (uint8_t)(RS485Rx.ff_cTemp_warring_R >> 8);
	Data_Register[1] = (uint8_t)(RS485Rx.ff_cTemp_warring_R  & 0xFF);
	Data_Register[2] = (uint8_t)(RS485Rx.ff_cTemp_alarm_R >> 8);
	Data_Register[3] = (uint8_t)(RS485Rx.ff_cTemp_alarm_R  & 0xFF);
	Data_Register[4] = (uint8_t)(RS485Rx.Warring_Deviation_R >> 8);
	Data_Register[5] = (uint8_t)(RS485Rx.Warring_Deviation_R  & 0xFF);
	Data_Register[6] = (uint8_t)(RS485Rx.TEnable_bit_R >> 8);
	Data_Register[7] = (uint8_t)(RS485Rx.TEnable_bit_R  & 0xFF);
	Data_Register[8] = (uint8_t)(RS485Rx.Temp_Warring_Keep_R >> 8);
	Data_Register[9] = (uint8_t)(RS485Rx.Temp_Warring_Keep_R  & 0xFF);
	Data_Register[10] = (uint8_t)(RS485Rx.Temp_Alram_keep_R >> 8);
	Data_Register[11] = (uint8_t)(RS485Rx.Temp_Alram_keep_R  & 0xFF);
}
void FUN_Modbus_Write_save(void)
{
	//��� �µ� ����
	ui.temp_warring_hex   = ((int16_t)Data_Register[0] << 8);
	ui.temp_warring_hex   |= ((int16_t)Data_Register[1] & 0xFF);
	//�˶� �µ� ����
	ui.temp_alarm_hex   	 = ((int16_t)Data_Register[2] << 8);
	ui.temp_alarm_hex  	 |= ((int16_t)Data_Register[3] & 0xFF);
	//���µ� ���� ����
	//�µ� ���/�˶� En/Dis
	ui.temp_alarm_enable  		 = Data_Register[7];
	//�µ� ��� ���� En/Dis`
	ui.temp_warring_maintain_bit 	 = Data_Register[9];
	//�µ� �˶� ���� En/Dis
	ui.temp_alarm_maintain_bit 	 = Data_Register[11];

	// �µ��� ��� ���� Update
	ui.temp_warring    = (float)(ui.temp_warring_hex) / 100;
	// �µ��� �˶� ���� Update
	ui.temp_alarm      = (float)(ui.temp_alarm_hex) / 100;
	// �µ� ��� ���� �� Update
	//ui.Warring_Deviation     = (float)(RS485Rx.Warring_Deviation) / 100;

	if((RS485Rx.ff_cTemp_warring_R != ui.temp_warring_hex) || (RS485Rx.ff_cTemp_alarm_R != ui.temp_alarm_hex) || (RS485Rx.Warring_Deviation_R != RS485Rx.Warring_Deviation)
			|| (RS485Rx.TEnable_bit_R != RS485Rx.TEnable_bit) || (RS485Rx.Temp_Warring_Keep_R != RS485Rx.Temp_Warring_Keep) || (RS485Rx.Temp_Alram_keep_R != RS485Rx.Temp_Alram_keep))
	{
		// EEPROM ����
		EEPROM.SaveData_Flag = 1;
	}

}


/****************************************************************************/
/*	Overview	:	Read Data												*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Modbus_RxCallback_ERROR(uint8_t Fun, uint8_t Ex_Code)
{
	Read_Data_Tx[0] = HsdID;
	Read_Data_Tx[1] = Fun + 0x80;

	Read_Data_Tx[2] = Ex_Code;

	//CRC
	crc16 =CRC16((uint8_t*)&Read_Data_Tx, 3);

	Read_Data_Tx[4] = (uint8_t)(crc16 >> 8);
	Read_Data_Tx[3] = (uint8_t)(crc16 & 0xFF);

	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;

}
/****************************************************************************/
/*	Overview	:	ReadWirte Data												*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Modbus_RxCallback_ReadWriteData(uint8_t Addrs, uint8_t Lenth, uint8_t Fun)
{
	uint8_t Modbus_ReadWirte[16];
	int16_t intTmp;
	uint8_t ii = 0, jj = 0;
	uint16_t crc16, Addrs_cnt;

	// �µ����/�˶� ���ذ�, ���� ���ذ�
	RS485Rx.ff_cTemp_warring_R = ((int16_t)(ui.temp_warring * 100));
	RS485Rx.ff_cTemp_alarm_R = ((int16_t)(ui.temp_alarm * 100));

	Addrs_cnt = Addrs - 0x10;

	//Temperature_Value
	//�µ� ��� ����(�Ҽ��� ù°�ڸ������� �۽�, ��°�ڸ��� ����)
	intTmp = (RS485Rx.ff_cTemp_warring_R / 10) * 10;
	Modbus_ReadWirte[0] = (uint8_t)(intTmp >> 8);
	Modbus_ReadWirte[1] = (uint8_t)(intTmp & 0xFF);

	//Humidity_value
	//�µ� �˶� ����(�Ҽ��� ù°�ڸ������� �۽�, ��°�ڸ��� ����)
	intTmp = (RS485Rx.ff_cTemp_alarm_R / 10) * 10;
	Modbus_ReadWirte[2] = (uint8_t)(intTmp >> 8);
	Modbus_ReadWirte[3] = (uint8_t)(intTmp & 0xFF);

	//Reserve
	//�µ� ��� ���� ��(�Ҽ��� ù°�ڸ������� �۽�, ��°�ڸ��� ����)
	Modbus_ReadWirte[4] = 0x00;
	Modbus_ReadWirte[5] = 0x00;

	//Temp Enable/Disable
	//�µ� enable/disable
	Modbus_ReadWirte[6] = 0x00;
	Modbus_ReadWirte[7] = ui.temp_alarm_enable;
	//�µ� ��� ����
	Modbus_ReadWirte[8] = 0x00;
	Modbus_ReadWirte[9] = ui.temp_warring_maintain_bit;
	//�µ� �˶� ����
	Modbus_ReadWirte[10] = 0x00;
	Modbus_ReadWirte[11] = ui.temp_alarm_maintain_bit;

	//Reserve
	Modbus_ReadWirte[12] = 0x00;
	Modbus_ReadWirte[13] = 0x00;
	Modbus_ReadWirte[14] = 0x00;
	Modbus_ReadWirte[15] = 0x00;

	Read_Data_Tx[0] = HsdID;
	Read_Data_Tx[1] = Fun;

	Read_Data_Tx[2] = 0x00;
	Read_Data_Tx[3] = Addrs;
	jj = 4;
	Lenth = 1;

	for(ii = Addrs_cnt; ii < Addrs_cnt+(Lenth*2); ii++)
	{
		Read_Data_Tx[jj++] = Modbus_ReadWirte[ii];
	}

	//CRC
	crc16 =CRC16((uint8_t*)&Read_Data_Tx, 6);

	Read_Data_Tx[7] = (uint8_t)(crc16 >> 8);
	Read_Data_Tx[6] = (uint8_t)(crc16 & 0xFF);

	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
}
/****************************************************************************/
/*	Overview	:	Read Data												*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Modbus_RxCallback_ReadData(uint8_t Addrs, uint8_t Lenth)
{
	uint8_t Modbus_Read[32];
	uint8_t ii, jj;
	uint16_t crc16;

	// Status(LSB)
	// Update Error Status
	if((Error.SHT30_Error == 1) || (EEPROM.Error == 1) || (RS485Rx.Checksum_Error == 1))
	{
		//ui.Detection_Error = 1;
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

	//   Opstatus
	//     MSB
	//Disable slip
	Modbus_Read[0] = 0x00;
	//����
	Modbus_Read[0] |= 0x00 << 1;
	//���� ���� LEVEL
	Modbus_Read[0] |= ui.SMK_Level << 2;
	//Heartbeat
	Modbus_Read[0] |= ui.HeartBit << 4;
	//Reserved

	//    LSB
    // Running
	Modbus_Read[1] = ui.Status.Bit.RUNNING;//RS485Tx.running_bit;
	//���� ����
	Modbus_Read[1] |= (ui.Status.Bit.SMOKE_DETECT << 1);//(RS485Tx.smoke_detect_on_bit << 1);
	//�µ� ���
	Modbus_Read[1] |= (ui.temp_warring_bit << 2);
	//�µ� �˶�
	Modbus_Read[1] |= (ui.temp_alarm_bit << 3);
	//������ ����
	Modbus_Read[1] |= (ui.Detection_Error << 4);
	//Reserved
	Modbus_Read[1] |= (0 << 5);
	//Reserved
	Modbus_Read[1] |= (0 << 6);
	//Reserved
	Modbus_Read[1] |= (0 << 7);

	//   Error Code
	//     MSB
	Modbus_Read[2] = 0x00;
	//     LSB
	Modbus_Read[3] = ui.ErrorCode;

	//Temperature_Value
	Modbus_Read[4] = (ui.temp_100times >> 8);
	Modbus_Read[5] = (ui.temp_100times & 0xFF);

	//Humidty_Value
	Modbus_Read[6] = (ui.humi_100times >> 8);
	Modbus_Read[7] = (ui.humi_100times & 0xFF);

	//Reserved
	Modbus_Read[8] = 0x00;
	Modbus_Read[9] = 0x00;

	//Reserved
	Modbus_Read[10] = 0x00;
	Modbus_Read[11] = 0x00;
	//Reserved
	Modbus_Read[12] = (ui.i_temp_100times >> 8);;
	Modbus_Read[13] = (ui.i_temp_100times & 0xFF);
	//Reserved
	Modbus_Read[14] = (ui.i_humi_100times >> 8);
	Modbus_Read[15] = (ui.i_humi_100times & 0xFF);

	//Temperature_warring
	//�µ� ��� ����(�Ҽ��� ù°�ڸ������� �۽�, ��°�ڸ��� ����)
	Modbus_Read[16] = (ui.temp_warring_hex >> 8);
	Modbus_Read[17] = (ui.temp_warring_hex & 0xFF);

	//Temperature_alarm
	//�µ� �˶� ����(�Ҽ��� ù°�ڸ������� �۽�, ��°�ڸ��� ����)
	Modbus_Read[18] = (ui.temp_alarm_hex >> 8);
	Modbus_Read[19] = (ui.temp_alarm_hex & 0xFF);

	//Deviation_value
	//�µ� ��� ���� ��(�Ҽ��� ù°�ڸ������� �۽�, ��°�ڸ��� ����)
	Modbus_Read[20] = (ui.co_100times >> 8);
	Modbus_Read[21] = (ui.co_100times & 0xFF);

	//Temp Enable/Disable
	//�µ� enable/disable
	Modbus_Read[22] = 0x00;
	Modbus_Read[23] = ui.temp_alarm_enable;
	//�µ� ��� ����
	Modbus_Read[24] = 0x00;
	Modbus_Read[25] = ui.temp_warring_maintain_bit;
	//�µ� �˶� ����
	Modbus_Read[26] = 0x00;
	Modbus_Read[27] = ui.temp_alarm_maintain_bit;

	//Reserve
	Modbus_Read[28] = 0x00;
	Modbus_Read[29] = 0x00;
	Modbus_Read[30] = 0x00;
	Modbus_Read[31] = 0x00;


	Read_Data_Tx[0] = HsdID;
	Read_Data_Tx[1] = 0x03;
	Read_Data_Tx[2] = Lenth * 2;

	jj = 3;
	for(ii = Addrs; ii < Addrs+(Lenth*2); ii++)
	{
		Read_Data_Tx[jj++] = Modbus_Read[ii];
	}

	crc16 =CRC16((uint8_t*)&Read_Data_Tx, (Lenth*2) +3);
	//CRC
	Read_Data_Tx[(Lenth*2) +4] = (uint8_t)(crc16 >> 8);
	Read_Data_Tx[(Lenth*2) +3] = (uint8_t)(crc16 & 0xFF);

	RS48501_TxPos++;
	if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
}
/****************************************************************************/
/*	Overview	:	RX ������ ó�� ��� ������										*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_Modbus_Read(void)
{
	uint8_t Addrs_Start, Data_Word, Function, ByteCount, Word_Max, byteCountTo;

	uint8_t Data_Register_cnt;
	uint8_t ii, jj;
	uint16_t CRCReq, CRCRes, CRCCal;
	uint8_t Len;

	//[0] = Device ID 1~99
	if(RS485RxMOData[0] == HsdID)
	{
		RS485Rx.Rx_cnt = 0;
		RS485Rx.result_MO = 0;

		if(RS485RxMOData[1] == 0x10)
		{
			Len = RS485RxMOData[6];

			CRCReq = (uint16_t)(RS485RxMOData[8+Len] << 8);
			CRCReq |= (uint16_t)(RS485RxMOData[7+Len] & 0xFF);

			CRCCal = CRC16((uint8_t*)&RS485RxMOData, 7+Len);
		}
		else
		{
			CRCReq = (uint16_t)(RS485RxMOData[7] << 8);
			CRCReq |= (uint16_t)(RS485RxMOData[6] & 0xFF);

			CRCCal = CRC16((uint8_t*)&RS485RxMOData, 6);
		}

		if(CRCReq == CRCCal)
		{
			Function = RS485RxMOData[1];

			//[1] = 0x03 = Read mode
			if(RS485RxMOData[1] == 0x03)
			{
				//Address Reguster ����
				Addrs_Start = RS485RxMOData[3];
				//Reading Register ����
				Data_Word	= RS485RxMOData[5];
				//data Register �ִ� ����
				Word_Max = 16 - (Addrs_Start / 2);

				if(Addrs_Start == 0)
				{
					Word_Max = 16;
				}
				else
				{
					Word_Max = 16 - (Addrs_Start / 2);
				}


				if(Addrs_Start <= 0x1E)
				{
					if(Addrs_Start %2 == 0)
					{
						if(Data_Word > Word_Max)
						{
							//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
							FUN_Modbus_RxCallback_ERROR(Function, 0x02);
						}
						else
						{
							if(Data_Word == 0)
							{
								FUN_Modbus_RxCallback_ERROR(Function, 0x03);
							}
							else
							{
								//Read  read data
								FUN_Modbus_RxCallback_ReadData(Addrs_Start, Data_Word);
							}
						}
					}
					else
					{
						//Ȧ���� ��û ��
						//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
						FUN_Modbus_RxCallback_ERROR(Function, 0x02);
					}

				}
				else
				{
					//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
					FUN_Modbus_RxCallback_ERROR(Function, 0x02);
				}
			}
			else if(RS485RxMOData[1] == 0x06)
			{
				FUN_Modbus_RxCallback_Flag();

				Data_Register_cnt = 0;
				//Address Reguster ����
				Addrs_Start = RS485RxMOData[3];
				//Reading Register ����
				Data_Word	= RS485RxMOData[5];

				if(Addrs_Start == 0x40)
				{
					if(Data_Word > 1)
					{
						//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
						FUN_Modbus_RxCallback_ERROR(Function, 0x02);
					}
					else
					{
						// ���� ��� ����, �������� RESET
						if(RS485RxMOData[5] == 1){
							Gas_Sensor.Gas_Detect = 0;
							ui.Status.Bit.SMOKE_DETECT = 0;
							ui.temp_alarm_bit = 0;
							ui.temp_warring_bit = 0;
						}
						Read_Data_Tx[0] = HsdID;
						Read_Data_Tx[1] = 0x06;
						Read_Data_Tx[2] = 0xA0;
						Read_Data_Tx[3] = Addrs_Start;
						Read_Data_Tx[4] = 0x00;
						Read_Data_Tx[5] = RS485RxMOData[5];

						CRCRes =CRC16((uint8_t*)&RS485RxMOData, 6);
						//CRC
						Read_Data_Tx[7] = (uint8_t)(CRCRes >> 8);
						Read_Data_Tx[6] = (uint8_t)(CRCRes & 0xFF);

						RS48501_TxPos++;
						if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
					}
				}
				else
				{
					if((Addrs_Start >= 0x10) && (Addrs_Start <= 0x1E))
					{
						if(Addrs_Start %2 == 0)
						{
							//Register ���� ��
							Data_Register_cnt = Addrs_Start - 0x10;
							Data_Register[Data_Register_cnt] 	= RS485RxMOData[4];
							Data_Register[Data_Register_cnt+1] 	= RS485RxMOData[5];

							FUN_Modbus_Write_save();
							//Read/Write Write data
							FUN_Modbus_RxCallback_ReadWriteData(Addrs_Start, 0x01, Function);
						}
						else
						{
							//Ȧ���� ��û ��
							//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
							FUN_Modbus_RxCallback_ERROR(Function, 0x02);
						}
					}
					else
					{
						//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
						FUN_Modbus_RxCallback_ERROR(Function, 0x02);
					}
				}
			}
			else if(RS485RxMOData[1] == 0x10)
			{
				FUN_Modbus_RxCallback_Flag();
				Data_Register_cnt = 0;
				//Address Reguster ����
				Addrs_Start = RS485RxMOData[3];
				//Reading Register ����
				Data_Word	= RS485RxMOData[5];
				ByteCount	= RS485RxMOData[6];
				byteCountTo = Data_Word * 2;
				Word_Max = 8 - ((Addrs_Start - 0x10) / 2);
				//Register ���� ��
				Data_Register_cnt = Addrs_Start - 0x10;

				if((Addrs_Start >= 0x10) && (Addrs_Start <= 0x1E))
				{
					if(Addrs_Start %2 == 0)
					{
						if(Data_Word < 9)
						{
							if(Data_Word > Word_Max)
							{
								FUN_Modbus_RxCallback_ERROR(Function, 0x02);
							}
							else
							{
								if(ByteCount == byteCountTo)
								{
									if(Data_Word == 0)
									{
										FUN_Modbus_RxCallback_ERROR(Function, 0x03);
									}
									else
									{
										jj = 7;
										for(ii = Data_Register_cnt; ii < Data_Register_cnt + ByteCount; ii++)
										{
											Data_Register[ii] = RS485RxMOData[jj++];
										}

										FUN_Modbus_Write_save();

										Read_Data_Tx[0] = HsdID;
										Read_Data_Tx[1] = 0x10;
										Read_Data_Tx[2] = 0xA0;
										Read_Data_Tx[3] = Addrs_Start;
										Read_Data_Tx[4] = 0x00;
										Read_Data_Tx[5] = Data_Word;

										CRCRes =CRC16((uint8_t*)&RS485RxMOData, 6);
										//CRC
										Read_Data_Tx[7] = (uint8_t)(CRCRes >> 8);
										Read_Data_Tx[6] = (uint8_t)(CRCRes & 0xFF);

										RS48501_TxPos++;
										if(RS48501_TxPos >= 20)	RS48501_TxPos = 0;
									}
								}
								else
								{
									FUN_Modbus_RxCallback_ERROR(Function, 0x02);
								}
							}
						}
						else
						{
							//���� word ���� �Ѿ��� ��
							//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
							FUN_Modbus_RxCallback_ERROR(Function, 0x02);
						}
					}
					else
					{
						//Ȧ���� ��û ��
						//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
						FUN_Modbus_RxCallback_ERROR(Function, 0x02);
					}
				}
				else
				{
					//Slave���� ���� ���� ���� Address�� register�� ��û�� �߻�
					FUN_Modbus_RxCallback_ERROR(Function, 0x02);
				}
			}
			else
			{
				//Slave���� �������� �ʴ� Function Code ��û�� �߻�
				FUN_Modbus_RxCallback_ERROR(Function, 0x01);
			}
		}
		else
		{
			Function = RS485RxMOData[1];
			//Slave���� �������� �ʴ� Function Code ��û�� �߻�
			FUN_Modbus_RxCallback_ERROR(Function, 0x03);
			RS485Rx.Rx_cnt = 0;
			RS485Rx.result_MO = 0;
		}
	}
	else{
		RS485Rx.Rx_cnt = 0;
		RS485Rx.result_MO = 0;
		 // Buff Clear
		for (uint16_t i = 0; i < 25 ; i++){
			 RS485RxMOData[i] = 0x00;
		}
	}

}

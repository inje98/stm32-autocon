/*
 * RS485.h
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_RS485_RS485_H_
#define SOURCE_RS485_RS485_H_

#include "../Source/HSD300_FW.h"

#define RS485_DE() HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET);
#define RS485_RE() HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET);

#define RANK_1				(0)
#define RANK_2				(1)
#define RANK_3				(2)

#ifdef HSS300

#define DATA_RX_BUFFER_SIZE 64  //16 32 64 128

#define DATA_TX_BUFFER_SIZE 36

#define DATA_RX_BUFFER_MASK (DATA_RX_BUFFER_SIZE - 1)



enum RS485_PACKET_STATE
{
    STX  = 0,
	LENGTH,
	CMD_ID,
	CMD_CODE,
	DEVICE_ID,
	DATA,
	CHECK_SUM_MSB,
	CHECK_SUM_LSB,
	ETX
};



typedef struct
{
	uint8_t nCnt;
	enum RS485_PACKET_STATE State;

	uint8_t nLength;
	uint8_t Cmd_Id;
	uint8_t Cmd_Code;
	uint8_t Device_Id;

} _RS485_RxInfo;


typedef union{
	uint8_t u1t_bitfield;
	struct {
		uint8_t RUNNING					:	1;			// ON(1) : 동작 중 / OFF(0) 정지
		uint8_t SMOKE_DETECT			:	1;			// ON(1) : 연기 감지 발생
		uint8_t SHT30_SENSOR_ERROR		:	1;			// ON(1) : 온습도 센서 에러
		uint8_t ADC_ERROR				:	1;			// ON(1) : ADC 에러
		uint8_t OVER_TEMP_ERROR			:	1;			// ON(1) : 과온 에러  //20221130 추가
		uint8_t OBJ_DETECT				:   1;
		uint8_t DISTANCE_LEVEL			:	2;
	}Bit;
}bit_field_Data;

typedef struct{
	uint8_t			 					ID;
	bit_field_Data 						Status;
	uint8_t								d_rank;			   // [1]   등급
	int16_t								ntc_100times; 	   // [2] ~ [3] NTC 온도
	int16_t								temp_100times;	   // [4] ~ [5] 센서 온도
	int16_t								humi_100times;	   // [6] ~ [7] 센서 습도
	int16_t								d_OverTemp_Range;  // [8] ~ [9] Spare1

	uint16_t							IR_Offset;
	uint16_t							Blue_IR_Offset;

}UI_HSD300;


extern  _RS485_RxInfo RS485_RxInfo;

extern UI_HSD300 ui;

void RS485_Init(void);
void RS485_Make_Send_Packet(void);
void RS485_Send_Packet(uint8_t *SendDataBuff, uint8_t DataLen);


void RS485_AnalyzePacket(void);
void RS485_CMD_Handler(uint8_t CMD);
int RS485_Parsing_Data(void);


uint8_t RS485_Ring_IsGetRxBuff(void);
uint8_t RS485_Ring_GetByteBuff(void);

uint16_t RS485_Gen_CheckSum(uint8_t *tBuff, uint8_t nLen);
#endif

#ifdef HSD300

#define MODBUS_PROTOCOL			0x00
#define	ONOFF_PROTOCOL			0x01

#define	BAUD_115200				0x00
#define BAUD_38400				0x01
#define BAUD_19200				0x02
#define	BAUD_9600				0x03

#define PACKET_STX 0x53
#define PACKET_ETX 0x45

#define ECODE_CR           		0x0D
#define ECODE_LF           		0x0A
/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

typedef union{
	uint8_t u1t_bitfield;
	struct {
		uint8_t RUNNING					:	1;			// ON(1) : 동작 중 / OFF(0) 정지
		uint8_t SMOKE_DETECT			:	1;			// ON(1) : 연기 감지 발생
		uint8_t SHT30_SENSOR_ERROR		:	1;			// ON(1) : 온습도 센서 에러
		uint8_t ADC_ERROR				:	1;			// ON(1) : ADC 에러
		uint8_t OVER_TEMP_ERROR			:	1;			// ON(1) : 과온 에러  //20221130 추가
		uint8_t OBJ_DETECT				:   1;
		uint8_t DISTANCE_LEVEL			:	2;
	}Bit;
}bit_field_Data;

typedef struct{
	uint8_t			 					ID;
	bit_field_Data 						Status;
	uint8_t								d_rank;			   // [1]   등급
	int16_t								co_100times; 	   // [2] ~ [3] NTC 온도
	int16_t								temp_100times;	   // [4] ~ [5] 센서 온도
	int16_t								humi_100times;	   // [6] ~ [7] 센서 습도

	int16_t								d_OverTemp_Range;  // [8] ~ [9] Spare1

	uint16_t							IR_Offset;
	uint16_t							Blue_IR_Offset;

	uint8_t								SMK_Level;
	int16_t								i_temp_100times;	   // 챔버 내부 센서 온도
	int16_t								i_humi_100times;	   // 챔버 내부 센서 습도

	uint8_t								temp_alarm_enable;
	uint8_t								temp_warring_bit;
	uint8_t 							temp_alarm_bit;
	uint8_t								temp_warring_maintain_bit;
	uint8_t								temp_alarm_maintain_bit;
	float								temp_warring;
	float								temp_alarm;
	uint16_t							temp_warring_hex;
	uint16_t							temp_alarm_hex;
	float								Warring_Deviation;
	uint8_t								Detection_Error;
	uint8_t								ErrorCode;

	uint8_t								TxCount;

	uint8_t 							HeartBit;
	uint8_t								Protocol_Type;
	uint8_t								End_Code;
	uint8_t								Baudrate;
}UI_HSD300;
extern UI_HSD300 ui;

typedef struct {
	uint16_t detect_staet_reset_bit;    // 감지상태 RESET
	uint8_t smoke_detect_set_bit;      // 농도 값 설정 변경
	int16_t smoke_detect_set_val;     // 연기감지 농도 설정 값
	uint8_t rxdataSave_Flag;
	int16_t ff_cTemp_alarm_R;
	int16_t ff_cTemp_warring_R;
	int16_t ff_cTemp_alarm;
	int16_t ff_cTemp_warring;
	uint16_t ff_humidity_alarm_R;
	uint16_t ff_humidity_warring_R;
	uint16_t Rx_cnt;
	uint8_t  result;
	uint8_t  result_MO;
	int16_t ff_cTemp_ReVal;
	int16_t ff_humidity_ReVal;
	uint8_t TEnable_bit;               // Enable / Disable 명령
	uint8_t TEnable_bit_R;
	uint8_t HEable_bit;
	uint16_t Detection_Error;
	uint16_t SensingCumulative;
	uint8_t ErrorCode;
	uint8_t Checksum_Error;
	int16_t Checksum_Error_Cnt;
	uint16_t SensingCumulative_Error_Int;
	uint8_t Temp_Warring_Keep;
	uint8_t Temp_Alram_keep;
	uint8_t Temp_Warring_Keep_R;
	uint8_t Temp_Alram_keep_R;
	uint8_t Smoke_keep;
	uint16_t Warring_Deviation;
	uint16_t Warring_Deviation_R;
	uint32_t BPS_SET;
	uint32_t BPS_SET_R;
	uint32_t BPS_SET_cnt;
	uint8_t Rx_Data_flag;
	uint8_t ID_Data_flag;
	uint16_t Rx_Data_cnt;
	uint16_t ID_Data_cnt;
	uint8_t boot_send;
	uint8_t ADC_Offset_Flag;
	uint8_t ADC_Offset_Check_1;
	uint8_t ADC_Offset_Check_2;
	int16_t Max_MinValue;
	int16_t Zero_Offset;
} _RS485Rx;
extern _RS485Rx RS485Rx;

typedef struct{
	uint8_t				temp_alarm_enable;
	uint16_t			temp_warring;
	uint16_t			temp_alarm;

	uint8_t				temp_warring_maintain_bit;
	uint8_t				temp_alarm_maintain_bit;

}_Register;
/*
typedef struct {
	uint8_t Count;
	uint16_t running_bit;               // Enable / Disable 명령
	uint8_t staet_error_bit;           // 감지상태 RESET
	uint32_t staet_error;              //i2c error
	uint16_t smoke_detect_on_bit;       // 연기 감지 ON / OFF
	int16_t smoke_detect_val;          // 연기감지 농도 값
	int16_t temp_val;                  // 온도(열) 값
	int16_t humi_val;                  // 습도 값
	uint8_t END_CODE;
	uint8_t Modbus_Code;
} _RS485Tx;
extern _RS485Tx RS485Tx;
*/
extern uint8_t RS485Rx0Data[18];
extern uint16_t HsdID;
extern uint8_t Modbus_485;
extern uint8_t RS485RxMOData[25];
extern uint8_t RS48501_TxPos, RS48501_TxEnd;

extern uint8_t u1f_bootjump_flag;
/* Private function prototypes -----------------------------------------------*/
void RS485_Init(void);
void FUN_RS485_routine(void);
void RS48501_TxData(void);
void FUN_RS485_Error_routine(void);
void FUN_RS485_Rx_Timeout_Check(void);
void RS485_Baudrate_Init(uint8_t baudrate);
#endif

#endif /* SOURCE_RS485_RS485_H_ */

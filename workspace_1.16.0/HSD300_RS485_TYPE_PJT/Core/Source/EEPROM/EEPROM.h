/*
 * EEPROM.h
 *
 *  Created on: Dec 13, 2023
 *      Author: AutoconTech
 */

#ifndef SOURCE_EEPROM_EEPROM_H_
#define SOURCE_EEPROM_EEPROM_H_

/* Private define ------------------------------------------------------------*/

#define EEPROM_BUF_MAX 32

#define EEPROM_CS_ON()    HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET)
#define EEPROM_CS_OFF()     HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET)

#define EEPROM_WP_ON()			(HAL_GPIO_WritePin(	EEPROM_WP_GPIO_Port,	EEPROM_WP_Pin,	GPIO_PIN_SET))
#define EEPROM_WP_OFF()		    (HAL_GPIO_WritePin(	EEPROM_WP_GPIO_Port,	EEPROM_WP_Pin,	GPIO_PIN_RESET))

#define EEPROM_HOLD_ON()		(HAL_GPIO_WritePin(	EEPROM_HOLD_GPIO_Port,	EEPROM_HOLD_Pin,	GPIO_PIN_SET))
#define EEPROM_HOLD_OFF()		(HAL_GPIO_WritePin(	EEPROM_HOLD_GPIO_Port,	EEPROM_HOLD_Pin,	GPIO_PIN_RESET))

#define EEPROM_WIP_FLAG        0x01  /*!< Write In Progress (WIP) flag */

#define EEPROM_PAGESIZE        64    /*!< Pagesize according to documentation */
#define EEPROM_BUFFER_SIZE     64    /*!< EEPROM Buffer size. Setup to your needs */

/* M95256 SPI EEPROM defines */
#define EEPROM_WREN  0x06  /*!< Write Enable 				0000 0110 */
#define EEPROM_WRDI  0x04  /*!< Write Disable 				0000 0100 */
#define EEPROM_RDSR  0x05  /*!< Read Status Register 		0000 0101 */
#define EEPROM_WRSR  0x01  /*!< Write Status Register 		0000 0001 */
#define EEPROM_READ  0x03  /*!< Read from Memory Array 		0000 0011 */
#define EEPROM_WRITE 0x02  /*!< Write to Memory Array 		0000 0010 */
#define EEPROM_RDID  0x83  /*!< Read Identification Page 	1000 0011 */
#define EEPROM_WRID  0x82  /*!< Write Identification Page 	1000 0010 */


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

typedef enum {
    EEPROM_STATUS_PENDING,
    EEPROM_STATUS_COMPLETE,
    EEPROM_STATUS_ERROR
} EEPROM_Operations;

typedef struct {
	uint8_t SaveData_Flag;
	uint8_t status;
	uint8_t TxBuff[EEPROM_BUF_MAX];
	uint8_t RxBuff[EEPROM_BUF_MAX];
	uint16_t Result;

	uint8_t Error;
	uint8_t Error_cnt;
	uint16_t	Checksum;
} _EEPROM;
extern _EEPROM EEPROM;

extern uint8_t offset_Flag;
extern uint8_t Save_Flag;


/* Private function prototypes -----------------------------------------------*/
void EEPROM_SPI_INIT(SPI_HandleTypeDef * hspi);
EEPROM_Operations EEPROM_SPI_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
EEPROM_Operations EEPROM_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
EEPROM_Operations EEPROM_SPI_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead);
uint8_t EEPROM_SPI_WaitStandbyState(void);

/* Low layer functions */
uint8_t EEPROM_SendByte(uint8_t byte);
void EEPROM_WriteEnable(void);
void EEPROM_WriteDisable(void);
void EEPROM_WriteStatusRegister(uint8_t regval);
uint8_t EEPROM_ReadStatusRegister(void);

void  EEPROM_SPI_SendInstruction(uint8_t *instruction, uint8_t size);
void  EEPROM_SPI_ReadStatusByte(SPI_HandleTypeDef SPIe, uint8_t *statusByte );

extern void EEPROM_init(void);
extern void EEPROM_routine(void);

#endif /* SOURCE_EEPROM_EEPROM_H_ */

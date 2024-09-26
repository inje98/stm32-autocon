/*
 * bootloader.c
 *
 *  Created on: 2020. 6. 2.
 *      Author: New
 */

/* Private includes ----------------------------------------------------------*/
#include "..\Source\HSD300_FW.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
typedef  void (*pFunction)(void);
pFunction JumpToApplication;
uint32_t JumpAddress;

uint8_t reboot_flag = 0;

static FLASH_EraseInitTypeDef EraseInitStruct;
volatile uint32_t u4f_application_flag_address = ADDR_FLASH_PAGE_15;

extern UART_HandleTypeDef huart5;
HAL_StatusTypeDef status = HAL_OK;
/* Private function prototypes -----------------------------------------------*/
static void FUN_Flash_event(uint32_t u4f_flash_address, uint32_t u4f_flag);

/* Private user code ---------------------------------------------------------*/

// Application Flag ���⿡ ��� (1byte�� ���� �����ϰ� ���� �Լ�) (������ ���� ������ HAL_FLASH_Program �Լ� �ø��� ��)
// 1. Flash Unlock ����
// 2. Flash Clear flag ����
// 3. ����ϰ��� �ϴ� Flash �ּҷ� ���� ���
// 4. �ش� ������ ���� �����
// 5. �ش� �ּҿ� �� ����
// 6. �ٽ� Flash Lock ����
/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
static void FUN_Flash_event(uint32_t u4f_flash_address, uint32_t u4f_flag)
{
	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

	//uint32_t u4f_sector = FUN_Flash_GetSector(u4f_flash_address);

	//FLASH_If_Erase(u4f_flash_address);

	uint32_t PageError = 0;


	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page = (u4f_flash_address - ADDR_FLASH_PAGE_0)/FLASH_PAGE_SIZE;
	EraseInitStruct.NbPages = 1;
	status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, u4f_flash_address, u4f_flag);

	HAL_FLASH_Lock();
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_bootloader_init()
{
	FUN_Flash_event(u4f_application_flag_address, 1);
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_bootloader_freerun()
{
	if(reboot_flag == 1)
	{
		// boot �δ� ��� OK
		if(u1f_bootjump_flag == 1)
		{
			HAL_UART_Abort_IT(&huart5);
			FUN_Flash_event(u4f_application_flag_address, 0);

			HAL_Delay(100);

			__disable_irq();


			for(volatile uint8_t i = 0; i < 8; i ++)
			{
				  NVIC->ICER[i] = 0xFFFFFFFF;
			}
			for(volatile uint8_t i = 0; i < 8; i ++)
			{
				  NVIC->ICPR[i] = 0xFFFFFFFF;
			}
			__enable_irq();

			NVIC_SystemReset();

			/* execute the new program */
	/*		  if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
			  {
			    JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
			    JumpToApplication = (pFunction) JumpAddress;
			    __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
			    JumpToApplication();
			  }*/
		}
	}

}


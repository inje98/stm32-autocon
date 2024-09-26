/*
 * FLASH.c
 *
 *  Created on: Jan 3, 2024
 *      Author: autocontech
 */

#include "../Source/HSD300_FW.h"

uint8_t buf[512];
/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_Init(void)
{
  /* Unlock the Program memory */
  HAL_FLASH_Unlock();

  /* Clear all FLASH flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
  for(int i = 0; i < 512; i++){
	  buf[i] = i;
  }
  /* Unlock the Program memory */
  HAL_FLASH_Lock();
}

bool flashInSector(uint16_t sector_num, uint32_t addr, uint32_t length)
{
  bool ret = false;

  uint32_t sector_start;
  uint32_t sector_end;
  uint32_t flash_start;
  uint32_t flash_end;


  sector_start = FLASH_BASE + (sector_num * FLASH_SECTOR_SIZE);
  sector_end   = sector_start + FLASH_SECTOR_SIZE - 1;
  flash_start  = addr;
  flash_end    = addr + length - 1;


  if (sector_start >= flash_start && sector_start <= flash_end)
  {
    ret = true;
  }

  if (sector_end >= flash_start && sector_end <= flash_end)
  {
    ret = true;
  }

  if (flash_start >= sector_start && flash_start <= sector_end)
  {
    ret = true;
  }

  if (flash_end >= sector_start && flash_end <= sector_end)
  {
    ret = true;
  }

  return ret;
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  start: start of user flash area
  * @retval FLASHIF_OK : user flash area successfully erased
  *         FLASHIF_ERASEKO : error occurred
  */
uint32_t FLASH_Erase(uint32_t start)
{
  uint32_t NbrOfPages = 0;
  uint32_t PageError = 0;
  int32_t start_sector = -1;
  int32_t end_sector = -1;
  uint32_t length = USER_FLASH_END_ADDRESS - APPLICATION_ADDRESS;

  FLASH_EraseInitTypeDef pEraseInit;
  HAL_StatusTypeDef status = HAL_OK;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

  /* Get the sector where start the user flash area */

  start_sector = -1;
  end_sector = -1;

  for (int i=0; i<FLASH_MAX_SECTOR; i++)
  {
    if (flashInSector(i, start, length) == true)
    {
      if (start_sector < 0)
      {
        start_sector = i;
      }
      end_sector = i;
    }
  }

  NbrOfPages = (end_sector - start_sector) + 1;

  pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
  pEraseInit.Page = start_sector;
  pEraseInit.NbPages = NbrOfPages;
  pEraseInit.Banks = FLASH_BANK_1;
  status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  if (status != HAL_OK)
  {
    /* Error occurred while page erase */
    return FLASHIF_ERASEKO;
  }

  return FLASHIF_OK;
}

uint32_t FLASH_Erase_FLA(uint32_t start)
{
  uint32_t NbrOfPages = 0;
  uint32_t PageError = 0;
  FLASH_EraseInitTypeDef pEraseInit;
  HAL_StatusTypeDef status = HAL_OK;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Get the sector where start the user flash area */
  NbrOfPages = (start - ADDR_FLASH_PAGE_0)/FLASH_PAGE_SIZE;

  pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
  pEraseInit.Page = NbrOfPages;
  pEraseInit.NbPages = 1;
  status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  if (status != HAL_OK)
  {
    /* Error occurred while page erase */
    return FLASHIF_ERASEKO;
  }

  return FLASHIF_OK;
}


/* Public functions ---------------------------------------------------------*/
/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  destination: start address for target location
  * @param  p_source: pointer on buffer with data to write
  * @param  length: length of data buffer (unit is 32-bit word)
  * @retval uint32_t 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_Write(uint32_t destination, uint8_t *p_source, uint32_t length)
{
  uint32_t i = 0;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  for (i = 0; i < length; i+=8)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, destination + i, *(uint64_t*)(p_source+i)) == HAL_OK)
    {
     /* Check the written value */
      /*if (*(uint64_t*)destination != *(uint64_t*)(p_source+i))
      {
        *//* Flash content doesn't match SRAM content */
        /*return(FLASHIF_WRITINGCTRL_ERROR);
      }*/
      /* Increment FLASH destination address */
      //destination += 8;

    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (FLASHIF_WRITING_ERROR);
    }
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  return (FLASHIF_OK);
}

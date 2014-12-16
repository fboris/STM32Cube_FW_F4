/**
  ******************************************************************************
  * @file    LwIP/LwIP_IAP/Src/flash_if.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file provides high level routines to manage internal Flash 
  *          programming (erase and write). 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{ 
   HAL_FLASH_Unlock(); 
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occured 
  */
int8_t FLASH_If_Erase(uint32_t StartSector)
{
  uint32_t FlashAddress;
 
  FlashAddress = StartSector;

  /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
     be done by word */ 
 
  if (FlashAddress <= (uint32_t) USER_FLASH_LAST_PAGE_ADDRESS)
  {
    FLASH_EraseInitTypeDef FLASH_EraseInitStruct;
    uint32_t sectornb = 0;
    
    FLASH_EraseInitStruct.TypeErase = TYPEERASE_SECTORS;
    FLASH_EraseInitStruct.Sector = FLASH_SECTOR_5;
    FLASH_EraseInitStruct.NbSectors = 19;
    FLASH_EraseInitStruct.VoltageRange = VOLTAGE_RANGE_3;
    
    if (HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &sectornb) != HAL_OK)
      return (1);
  }
  else
  {
    return (1);
  }

  return (0);
}
/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)   
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(__IO uint32_t* FlashAddress, uint32_t* Data ,uint16_t DataLength)
{
  uint32_t i = 0;

  for (i = 0; (i < DataLength) && (*FlashAddress <= (USER_FLASH_END_ADDRESS-4)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (HAL_FLASH_Program(TYPEPROGRAM_WORD, *FlashAddress, *(uint32_t*)(Data+i)) == HAL_OK)
    {
     /* Check the written value */
      if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data+i))
      {
        /* Flash content doesn't match SRAM content */
        return(2);
      }
      /* Increment FLASH destination address */
      *FlashAddress += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (1);
    }
  }

  return (0);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

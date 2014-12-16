/**
  ******************************************************************************
  * @file    LwIP/LwIP_IAP/Inc/flash_if.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for flash_if.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - USER_FLASH_FIRST_PAGE_ADDRESS)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t FLASH_If_Write(__IO uint32_t* Address, uint32_t* Data, uint16_t DataLength);
int8_t FLASH_If_Erase(uint32_t StartSector);
void FLASH_If_Init(void);

#endif /* __FLASH_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

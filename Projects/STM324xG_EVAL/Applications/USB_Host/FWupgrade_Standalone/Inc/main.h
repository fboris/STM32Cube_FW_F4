/**
  ******************************************************************************
  * @file    USB_Host/FWupgrade_Standalone/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for main.c module
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
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usbh_msc.h" 
#include "ff.h"
#include "stm324xg_eval.h" 
#include "flash_if.h"
#include "command.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  APPLICATION_IDLE = 0,  
  APPLICATION_READY, 
  APPLICATION_CONNECT,  
  APPLICATION_DISCONNECT,
}FW_ApplicationTypeDef;

extern USBH_HandleTypeDef hUSBHost;
extern FATFS USBH_fatfs;
extern FW_ApplicationTypeDef Appli_state;
extern __IO uint32_t UploadCondition;

/* Exported constants --------------------------------------------------------*/
/* This value can be equal to (512 * x) according to RAM size availability with x=[1, 128]
   In this project x is fixed to 64 => 512 * 64 = 32768bytes = 32 Kbytes */   
#define BUFFER_SIZE        ((uint16_t)512*64) 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FW_UPGRADE_Process(void);
void Fail_Handler(void);
void FatFs_Fail_Handler(void);
void Erase_Fail_Handler(void);

#endif /* __MAIN_H */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

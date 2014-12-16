/**
  ******************************************************************************
  * @file    usbd_app.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014   
  * @brief   Header for usbd_app.c file
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
#ifndef __USBD_APP_H
#define __USBD_APP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h"
#include "stm324x9i_eval.h" 
#include "stm324x9i_eval_sd.h"
   
/* Exported constants --------------------------------------------------------*/   
#define CONNECTED                  0x00
#define DISCONNECTED               0x01
   
/* Exported types ------------------------------------------------------------*/

typedef enum
{
  USBD_ERROR_NONE = 0, 
  USBD_ERROR_IO,
  USBD_ERROR_HW, 
  USBD_ERROR_UNKNOWN, 
  
}USBD_ErrorTypdef;


/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
USBD_ErrorTypdef  USBDSTOR_Start(void);
USBD_ErrorTypdef  USBDSTOR_Connect(void);
USBD_ErrorTypdef  USBDSTOR_Refrech(void);
USBD_ErrorTypdef  USBDSTOR_Stop(void);
USBD_ErrorTypdef  USBDSTOR_Disconnect(void);

#ifdef __cplusplus
}
#endif

#endif /*__USBD_APP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

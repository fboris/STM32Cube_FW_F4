/**
  ******************************************************************************
  * @file    PolarSSL/SSL_Client/Inc/ssl_client.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file contains the functions prototype for SSL client file.
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
#ifndef __SSL_CLIENT_H
#define __SSL_CLIENT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t State;
}rng_state;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ssl_client(void const * argument);
int RandVal(void* arg, unsigned char *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __SSL_CLIENT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    PolarSSL/SSL_Client/Inc/main.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file contains all the functions prototypes for the main.c 
  *          file.
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

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm324xg_eval.h"
#include "stm324xg_eval_lcd.h"
   
#include "cmsis_os.h"

/* Demo application includes */
#include "ssl_client.h"

/* Standard includes */
#include <stdio.h>
#include <string.h>

/* LwIP includes */
#include "lwip/tcpip.h"
#include "lwip/api.h"

/* PolarSSL includes */
#include "polarssl/net.h"
#include "polarssl/ssl.h"
#include "polarssl/havege.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USE_LCD        /* enable LCD  */  
//#define USE_DHCP       /* enable DHCP, if disabled static address is used*/
 
/* Static IP ADDRESS */
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10
   
/* NETMASK */
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* Gateway Address */
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1  

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
/* Exported function prototypes ----------------------------------------------*/
int RandVal(void* arg, unsigned char *output, size_t output_len);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


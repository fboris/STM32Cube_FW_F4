/**
  ******************************************************************************
  * @file    LwIP/LwIP_IAP/Inc/main.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file contains all the functions prototypes for the main.c 
  *          file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* IAP options selection ******************************************************/
#define USE_IAP_TFTP   /* enable IAP using TFTP */
#define USE_IAP_HTTP   /* enable IAP using HTTP */
#define USE_LCD        /* enable LCD  */  
//#define USE_DHCP       /* enable DHCP, if disabled static address is used */

/* Flash user area definition *************************************************/   
/* 
   IMPORTANT NOTE:
   ==============
   Be sure that USER_FLASH_FIRST_PAGE_ADDRESS do not overlap with IAP code.
   For example, with all option enabled the total readonly memory size using TrueSTUDIO
   compiler v4.30, with high optimization for size, is 69840 bytes.
   Based on this result four sectors of 16 Kbytes and a sector of 64 Kbytes will be used to store
   the IAP code, so the user Flash address will start from Sector5.

   In this example the define USER_FLASH_FIRST_PAGE_ADDRESS is set to 128K boundary,
   but it can be changed to any other address outside the 1st 128 Kbytes of the Flash.
   */
#define USER_FLASH_FIRST_PAGE_ADDRESS 0x08020000 /* Only as example see comment */
#define USER_FLASH_LAST_PAGE_ADDRESS  0x080E0000
#define USER_FLASH_END_ADDRESS        0x080FFFFF  
   
/* UserID and Password definition *********************************************/
#define USERID       "user"
#define PASSWORD     "stm32"
#define LOGIN_SIZE   (15+ sizeof(USERID) + sizeof(PASSWORD))
 
/* Static IP Address definition ***********************************************/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10

/* NETMASK definition *********************************************************/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* Gateway Address definition *************************************************/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
/* Exported function prototypes ----------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


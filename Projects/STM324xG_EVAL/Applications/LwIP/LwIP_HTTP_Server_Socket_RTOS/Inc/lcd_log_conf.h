/**
  ******************************************************************************
  * @file    LwIP/LwIP_HTTP_Server_Socket_RTOS/Inc/lcd_log_conf.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   lcd_log configuration file.
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

#ifndef  __LCD_LOG_CONF_H__
#define  __LCD_LOG_CONF_H__

/* Includes ------------------------------------------------------------------*/
#include "stm324xg_eval_lcd.h" 
#include <stdio.h>


/** @addtogroup LCD_LOG
  * @{
  */
  
/** @defgroup LCD_LOG
  * @brief This file is the 
  * @{
  */ 


/** @defgroup LCD_LOG_CONF_Exported_Defines
  * @{
  */ 

/* Comment the line below to disable the scroll back and forward features */
#define     LCD_SCROLL_ENABLED      1 

/* Define the Fonts  */
#define     LCD_LOG_HEADER_FONT                   Font16
#define     LCD_LOG_FOOTER_FONT                   Font12
#define     LCD_LOG_TEXT_FONT                     Font12
            
/* Define the LCD LOG Color  */
#define     LCD_LOG_BACKGROUND_COLOR              LCD_COLOR_WHITE
#define     LCD_LOG_TEXT_COLOR                    LCD_COLOR_DARKBLUE
#define     LCD_LOG_DEFAULT_COLOR                 LCD_COLOR_DARKBLUE

#define     LCD_LOG_SOLID_BACKGROUND_COLOR        LCD_COLOR_BLUE
#define     LCD_LOG_SOLID_TEXT_COLOR              LCD_COLOR_WHITE

/* Define the cache depth */
#define     CACHE_SIZE              100
#define     YWINDOW_SIZE            17

#if (YWINDOW_SIZE > 17)
  #error "Wrong YWINDOW SIZE"
#endif

/* Redirect the printf to the LCD */
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define LCD_LOG_PUTCHAR int __io_putchar(int ch)
#else
#define LCD_LOG_PUTCHAR int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/** @defgroup LCD_LOG_CONF_Exported_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup LCD_LOG_Exported_Macros
  * @{
  */ 


/**
  * @}
  */ 

/** @defgroup LCD_LOG_CONF_Exported_Variables
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup LCD_LOG_CONF_Exported_FunctionsPrototype
  * @{
  */ 

/**
  * @}
  */ 


#endif //__LCD_LOG_CONF_H__

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    Demonstrations/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
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
#include "stm32f4xx_nucleo.h"
#include "stm32_adafruit_sd.h"
#include "stm32_adafruit_lcd.h"
#include <stdio.h>
#include <stdlib.h>

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "fatfs_storage.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define  MAX_BMP_FILES  25
#define  MAX_BMP_FILE_NAME 11

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

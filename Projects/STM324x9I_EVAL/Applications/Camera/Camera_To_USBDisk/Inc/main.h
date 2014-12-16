/**
  ******************************************************************************
  * @file    Camera/Camera_To_USBDisk/Inc/main.h 
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
#include "stm324x9i_eval.h"
#include "stm324x9i_eval_lcd.h"
#include "stm324x9i_eval_camera.h"
#include "fatfs_storage.h"
#include "stm324x9i_eval_ts.h"
#include "stm324x9i_eval_audio.h"

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "usbh_diskio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* LCD Frame Buffer address */
#define CAMERA_FRAME_BUFFER               0xC0260000
#define LCD_FRAME_BUFFER                  0xC0130000
#define LCD_FRAME_BUFFER_LAYER1           0xC0000000
#define CONVERTED_FRAME_BUFFER            0xC0390000
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Touchscreen_Calibration (void);
uint16_t Calibration_GetX(uint16_t x);
uint16_t Calibration_GetY(uint16_t y);
uint8_t IsCalibrationDone(void);
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

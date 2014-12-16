/**
  ******************************************************************************
  * @file    camera_app.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014   
  * @brief   Camera application header file
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
#ifndef __CAMERA_APP_H
#define __CAMERA_APP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported constants --------------------------------------------------------*/
#define CAMERA_FRAME_BUFFER 0xC0000000
#define CAMERA_CVRT_BUFFER  0xC0025800

#define RGB_HEADER_SIZE      54
#define IMAGE_BUFFER_SIZE   (320*240*2)     /* Size of RGB16 image */
#define MAX_IMAGE_SIZE      (320*240*3)      /* Size of RGB24 image  */
#define IMAGE_COLUMN_SIZE   240
#define IMAGE_LINE_SIZE     320
   
/* Exported types ------------------------------------------------------------*/
typedef union
{
  uint32_t d32;
  struct
  {
    uint32_t brightness     : 3;
    uint32_t contrast       : 3;    
  }b;
} CameraSettingsTypeDef;

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void    CAMERA_Init(void);
void    CAMERA_Suspend(void);
void    CAMERA_Resume(void);
void    CAMERA_Stop(void);
void    CAMERA_Set_ContrastBrightness(uint32_t contrast_Level, uint32_t brightness_level);
void    CAMERA_SelectEffect(uint32_t effect);
uint8_t CAMERA_SaveToFile(uint8_t *path);
uint8_t CAMERA_GetState(void);
#ifdef __cplusplus
}
#endif

#endif /*__CAMERA_APP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

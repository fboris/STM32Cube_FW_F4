/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Inc/waverecorder.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for waverecorder.c module.
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
#ifndef __WAVERECORDER_H
#define __WAVERECORDER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

/* Exported Defines ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Defines for the Audio recording process */

#define DEFAULT_TIME_REC                      30  /* Recording time in second (default: 30s) */

#define WR_BUFFER_SIZE                        4*2304 /* buffer size in half-word */

#define REC_WAVE_NAME "Wave.wav"
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
AUDIO_ErrorTypeDef AUDIO_REC_Process(void);
AUDIO_ErrorTypeDef AUDIO_REC_Start(void);
#endif /* __WAVERECORDER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

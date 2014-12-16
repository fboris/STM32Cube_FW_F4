/**
  ******************************************************************************
  * @file    Audio_playback_and_record/inc/waverecorder.h
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


/* Exported types ------------------------------------------------------------*/
/* Exported Defines ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Defines for the Audio recording process */
#define WR_BUFFER_SIZE           4096  /*  More the size is higher, the recorded quality is better */ 
#define DEFAULT_TIME_REC         30000  /* Recording time in millisecond (Systick Time Base*TIME_REC= 1ms*30000)
                                        (default: 30s) */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t  WaveRecorderInit(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr);
uint8_t   WaveRecorderStart(uint16_t* pBuf, uint32_t wSize);
uint32_t  WaveRecorderStop(void);
void      WaveRecorderProcess(void);
void      WaveRecorderProcessingAudioBuffer(void);
#endif /* __WAVERECORDER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Inc/main.h 
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
#include "stdio.h"
#include "usbh_core.h"
#include "stm324x9i_eval_io.h"
#include "stm324x9i_eval_audio.h"
#include "lcd_log.h"
#include "ff.h"    
#include "ff_gen_drv.h"
#include "usbh_diskio.h"
#include "waveplayer.h"
#include "waverecorder.h" 

/* Exported Defines ----------------------------------------------------------*/
#define AUDIO_BUFFER_SIZE   8192
/* Exported types ------------------------------------------------------------*/
/* Application State Machine Structure */
typedef enum {
  APPLICATION_IDLE = 0,  
  APPLICATION_START,   
  APPLICATION_READY,
  APPLICATION_DISCONNECT,
}AUDIO_ApplicationTypeDef;
    
/* Audio Demo State Structure */    
typedef enum {
  AUDIO_DEMO_IDLE = 0,
  AUDIO_DEMO_WAIT,  
  AUDIO_DEMO_EXPLORE,
  AUDIO_DEMO_PLAYBACK,
  AUDIO_DEMO_IN,  
}AUDIO_Demo_State;

/* Audio Demo State Machine Structure */
typedef struct _DemoStateMachine {
  __IO AUDIO_Demo_State            state;
  __IO uint8_t                     select;  
}AUDIO_DEMO_StateMachine;

typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_WAIT,    
  AUDIO_STATE_INIT,    
  AUDIO_STATE_CONFIG,    
  AUDIO_STATE_PLAY,  
  AUDIO_STATE_NEXT,  
  AUDIO_STATE_PREVIOUS,
  AUDIO_STATE_FORWARD,   
  AUDIO_STATE_BACKWARD,
  AUDIO_STATE_STOP,   
  AUDIO_STATE_PAUSE,
  AUDIO_STATE_RESUME,
  AUDIO_STATE_VOLUME_UP,
  AUDIO_STATE_VOLUME_DOWN,
  AUDIO_STATE_ERROR,  
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  AUDIO_SELECT_MENU = 0,
  AUDIO_PLAYBACK_CONTROL ,  
}AUDIO_DEMO_SelectMode;

/* Audio buffer control struct*/
typedef struct {
  uint8_t buff[AUDIO_BUFFER_SIZE];
  int32_t offset;
  uint32_t fptr;
}Audio_BufferTypeDef;

extern USBH_HandleTypeDef hUSBHost;
extern AUDIO_ApplicationTypeDef AppliState;
extern AUDIO_PLAYBACK_StateTypeDef AudioState;

extern FATFS USBH_fatfs;
extern FIL WavFile;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Toggle_Leds(void);
void AUDIO_MenuInit(void);
void AUDIO_MenuProcess(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

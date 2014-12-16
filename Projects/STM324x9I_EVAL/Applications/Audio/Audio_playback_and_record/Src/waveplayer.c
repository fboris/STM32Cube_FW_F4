/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Src/audio.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file provides the Audio Out (playback) interface API
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Audio_BufferTypeDef  BufferCtl;
static int16_t FilePos = 0;
static __IO uint32_t uwVolume = 70;

WAVE_FormatTypeDef WaveFormat;
FIL WavFile;
extern FILELIST_FileTypeDef FileList;

/* Private function prototypes -----------------------------------------------*/
static AUDIO_ErrorTypeDef AUDIO_GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info);
static uint8_t AUDIO_WavePlayerInit(uint32_t AudioFreq);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes Audio Interface.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Init(void)
{
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, uwVolume, I2S_AUDIOFREQ_48K) == 0)
  {
    return AUDIO_ERROR_NONE;
  }
  else
  {
    return AUDIO_ERROR_IO;
  }
}

/**
  * @brief  Starts Audio streaming.    
  * @param  idx: File index
  * @retval Audio error
  */ 
AUDIO_ErrorTypeDef AUDIO_Start(uint8_t idx)
{
  uint32_t bytesread;
  
  f_close(&WavFile);
  if(AUDIO_GetWavObjectNumber() > idx)
  { 
    AUDIO_GetFileInfo(idx, &WaveFormat);
    
    /*Adjust the Audio frequency */
    AUDIO_WavePlayerInit(WaveFormat.SampleRate); 
    
    BufferCtl.offset = BUFFER_OFFSET_NONE;
    
    /* Get Data from USB Flash Disk */
    f_lseek(&WavFile, 0);
    /* Fill whole buffer at first time */
    if(f_read(&WavFile, 
              &BufferCtl.buff[0], 
              AUDIO_BUFFER_SIZE, 
              (void *)&bytesread) == FR_OK)
    {
      AudioState = AUDIO_STATE_PLAY;
      BSP_LCD_DisplayStringAt(250, LINE(14), (uint8_t *)"  [PLAY ]", LEFT_MODE);
      { 
        if(bytesread != 0)
        {
          BSP_AUDIO_OUT_Play((uint16_t*)&BufferCtl.buff[0], AUDIO_BUFFER_SIZE);
          BufferCtl.fptr = bytesread;
          return AUDIO_ERROR_NONE;
        }
      }
    }
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process. 
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Process(void)
{
  uint32_t bytesread, elapsed_time;
  AUDIO_ErrorTypeDef audio_error = AUDIO_ERROR_NONE;
  static uint32_t prev_elapsed_time = 0xFFFFFFFF;
  uint8_t str[10];  
  
  switch(AudioState)
  {
  case AUDIO_STATE_PLAY:
    if(BufferCtl.fptr >= WaveFormat.FileSize)
    {
      BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
      AudioState = AUDIO_STATE_NEXT;
    }
    
    if(BufferCtl.offset == BUFFER_OFFSET_HALF)
    {
      if(f_read(&WavFile, 
                &BufferCtl.buff[0], 
                AUDIO_BUFFER_SIZE/2, 
                (void *)&bytesread) != FR_OK)
      { 
        BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW); 
        return AUDIO_ERROR_IO;       
      } 
      BufferCtl.offset = BUFFER_OFFSET_NONE;
      BufferCtl.fptr += bytesread; 
    }
    
    if(BufferCtl.offset == BUFFER_OFFSET_FULL)
    {
      if(f_read(&WavFile, 
                &BufferCtl.buff[AUDIO_BUFFER_SIZE /2], 
                AUDIO_BUFFER_SIZE/2, 
                (void *)&bytesread) != FR_OK)
      { 
        BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW); 
        return AUDIO_ERROR_IO;       
      } 
 
      BufferCtl.offset = BUFFER_OFFSET_NONE;
      BufferCtl.fptr += bytesread; 
    }
    
    /* Display elapsed time */
    elapsed_time = BufferCtl.fptr / WaveFormat.ByteRate; 
    if(prev_elapsed_time != elapsed_time)
    {
      prev_elapsed_time = elapsed_time;
      sprintf((char *)str, "[%02d:%02d]", (int)(elapsed_time /60), (int)(elapsed_time%60));
      BSP_LCD_SetTextColor(LCD_COLOR_CYAN); 
      BSP_LCD_DisplayStringAt(263, LINE(8), str, LEFT_MODE);
      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
    }
    break;
    
  case AUDIO_STATE_STOP:
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AudioState = AUDIO_STATE_IDLE; 
    audio_error = AUDIO_ERROR_IO;
    break;
    
  case AUDIO_STATE_NEXT:
    if(++FilePos >= AUDIO_GetWavObjectNumber())
    {
      FilePos = 0; 
    }
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_Start(FilePos);
    break;    
    
  case AUDIO_STATE_PREVIOUS:
    if(--FilePos < 0)
    {
      FilePos = AUDIO_GetWavObjectNumber() - 1; 
    }
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_Start(FilePos);
    break;   
    
  case AUDIO_STATE_PAUSE:
    BSP_LCD_DisplayStringAt(250, LINE(14), (uint8_t *)"  [PAUSE]", LEFT_MODE);
    BSP_AUDIO_OUT_Pause();
    AudioState = AUDIO_STATE_WAIT;
    break;
    
  case AUDIO_STATE_RESUME:
    BSP_LCD_DisplayStringAt(250, LINE(14), (uint8_t *)"  [PLAY ]", LEFT_MODE);
    BSP_AUDIO_OUT_Resume();
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_VOLUME_UP: 
    if( uwVolume <= 90)
    {
      uwVolume += 10;
    }
    BSP_AUDIO_OUT_SetVolume(uwVolume);
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_VOLUME_DOWN:    
    if( uwVolume >= 10)
    {
      uwVolume -= 10;
    }
    BSP_AUDIO_OUT_SetVolume(uwVolume);
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_WAIT:
  case AUDIO_STATE_CONFIG:    
  case AUDIO_STATE_IDLE:
  case AUDIO_STATE_INIT:    
  default:
    /* Do Nothing */
    break;
  }
  return audio_error;
}

/**
  * @brief  Stops Audio streaming.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Stop(void)
{
  AudioState = AUDIO_STATE_STOP;
  FilePos = 0;
  
  BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
  f_close(&WavFile);
  return AUDIO_ERROR_NONE;
}

/**
  * @brief  Probes the play back joystick state.
  * @param  state: Joystick state
  * @retval None
  */
void AUDIO_PlaybackProbeKey(JOYState_TypeDef state)
{
  /* Handle File List Selection */ 
  if(state == JOY_UP)
  {
    if(AudioState == AUDIO_STATE_PLAY)
    {
      AudioState = AUDIO_STATE_VOLUME_UP;
    }
  }
  else if(state == JOY_DOWN)
  {
    if(AudioState == AUDIO_STATE_PLAY)
    {
      AudioState = AUDIO_STATE_VOLUME_DOWN;
    }
  }
  else if(state == JOY_RIGHT)
  {
    AudioState = AUDIO_STATE_NEXT;
  }  
  else if(state == JOY_LEFT)
  {
    AudioState = AUDIO_STATE_PREVIOUS;
  }    
  else if(state == JOY_SEL)
  {
    AudioState = (AudioState == AUDIO_STATE_WAIT) ? AUDIO_STATE_RESUME : AUDIO_STATE_PAUSE;
  } 
}

/**
  * @brief  Shows audio file (*.wav) on the root
  * @param  None
  * @retval None
  */
uint8_t AUDIO_ShowWavFiles(void)
{
  uint8_t i = 0;
  uint8_t line_idx = 0;
  if(AUDIO_StorageInit() == FR_OK)
  {
    if(AUDIO_StorageParse() ==  FR_OK)
    {
      if(FileList.ptr > 0)
      {
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        LCD_UsrLog("audio file(s) [ROOT]:\n\n");
        
        for(i = 0; i < FileList.ptr; i++)
        {
          line_idx++;
          if(line_idx > 9)
          {
            line_idx = 0;
            LCD_UsrLog("> Press [Key] To Continue.\n");
            
            /* KEY Button in polling */
            while(BSP_PB_GetState(BUTTON_KEY) != RESET)
            {
              /* Wait for User Input */
            }
          } 
          LCD_DbgLog("   |__");
          LCD_DbgLog((char *)FileList.file[i].name);
          LCD_DbgLog("\n");
        }
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        LCD_UsrLog("\nEnd of files list.\n");
        return 0;
      }
      return 1;
    }
    return 2;
  }
  else
  {
    return 3;
  }
}

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
  if(AudioState == AUDIO_STATE_PLAY)
  {
    BufferCtl.offset = BUFFER_OFFSET_FULL;
    BSP_AUDIO_OUT_ChangeBuffer((uint16_t*)&BufferCtl.buff[0], AUDIO_BUFFER_SIZE /2);
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{ 
  if(AudioState == AUDIO_STATE_PLAY)
  {
    BufferCtl.offset = BUFFER_OFFSET_HALF;
    BSP_AUDIO_OUT_ChangeBuffer((uint16_t*)&BufferCtl.buff[AUDIO_BUFFER_SIZE /2], AUDIO_BUFFER_SIZE /2);
  }
}

/**
  * @brief  Manages the DMA FIFO error interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_Error_CallBack(void)
{
}

/******************************************************************************
                            Static Function
*******************************************************************************/

/**
  * @brief  Gets the file info.
  * @param  file_idx: File index
  * @param  info: Pointer to WAV file info
  * @retval Audio error
  */
static AUDIO_ErrorTypeDef AUDIO_GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info)
{
  uint32_t bytesread;
  uint32_t duration;
  uint8_t str[FILEMGR_FILE_NAME_SIZE + 20];  
  
  if(f_open(&WavFile, (char *)FileList.file[file_idx].name, FA_OPEN_EXISTING | FA_READ) == FR_OK) 
  {
    /* Fill the buffer to Send */
    if(f_read(&WavFile, info, sizeof(WaveFormat), (void *)&bytesread) == FR_OK)
    {
      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
      sprintf((char *)str, "Playing file (%d/%d): %s", 
              file_idx + 1, FileList.ptr,
              (char *)FileList.file[file_idx].name);
      BSP_LCD_ClearStringLine(4);
      BSP_LCD_DisplayStringAtLine(4, str);
      
      BSP_LCD_SetTextColor(LCD_COLOR_CYAN); 
      sprintf((char *)str,  "Sample rate : %d Hz", (int)(info->SampleRate));
      BSP_LCD_ClearStringLine(6);
      BSP_LCD_DisplayStringAtLine(6, str);
      
      sprintf((char *)str,  "Channels number : %d", info->NbrChannels);
      BSP_LCD_ClearStringLine(7);      
      BSP_LCD_DisplayStringAtLine(7, str);
      
      duration = info->FileSize / info->ByteRate; 
      sprintf((char *)str, "File Size : %d KB [%02d:%02d]", (int)(info->FileSize/1024), (int)(duration/60), (int)(duration%60));
      BSP_LCD_ClearStringLine(8);
      BSP_LCD_DisplayStringAtLine(8, str);
      BSP_LCD_DisplayStringAt(263, LINE(8), (uint8_t *)"[00:00]", LEFT_MODE);
      BSP_LCD_SetTextColor(LCD_COLOR_WHITE); 
      return AUDIO_ERROR_NONE;
    }
    f_close(&WavFile);
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Initializes the Wave player.
  * @param  AudioFreq: Audio sampling frequency
  * @retval None
  */
static uint8_t AUDIO_WavePlayerInit(uint32_t AudioFreq)
{ 
  /* Initialize the Audio codec and all related peripherals (I2S, I2C, IOExpander, IOs...) */  
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, uwVolume, AudioFreq) != 0)
  {
    return 1;
  }
  else
  {
    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
    return 0;
  } 
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

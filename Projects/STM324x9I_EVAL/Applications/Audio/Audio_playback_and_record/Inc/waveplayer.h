/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Inc/waveplayer.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for waveplayer.c module.
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
#ifndef __WAVEPLAYER_H
#define __WAVEPLAYER_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported constants --------------------------------------------------------*/
#define FILEMGR_LIST_DEPDTH                     24
#define FILEMGR_FILE_NAME_SIZE                  40
#define FILEMGR_FULL_PATH_SIZE                 256
#define FILEMGR_MAX_LEVEL                        4    
#define FILETYPE_DIR                             0
#define FILETYPE_FILE                            1

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  LittleEndian,
  BigEndian
}Endianness;

typedef enum
{
  BUFFER_OFFSET_NONE = 0,  
  BUFFER_OFFSET_HALF,  
  BUFFER_OFFSET_FULL,     
}BUFFER_StateTypeDef;

typedef struct 
{
  uint32_t   ChunkID;       /* 0 */ 
  uint32_t   FileSize;      /* 4 */
  uint32_t   FileFormat;    /* 8 */
  uint32_t   SubChunk1ID;   /* 12 */
  uint32_t   SubChunk1Size; /* 16*/  
  uint16_t   AudioFormat;   /* 20 */ 
  uint16_t   NbrChannels;   /* 22 */   
  uint32_t   SampleRate;    /* 24 */
  
  uint32_t   ByteRate;      /* 28 */
  uint16_t   BlockAlign;    /* 32 */  
  uint16_t   BitPerSample;  /* 34 */  
  uint32_t   SubChunk2ID;   /* 36 */   
  uint32_t   SubChunk2Size; /* 40 */    
}WAVE_FormatTypeDef;

typedef enum
{
  Valid_WAVE_File = 0,
  Unvalid_RIFF_ID,
  Unvalid_WAVE_Format,
  Unvalid_FormatChunk_ID,
  Unsupporetd_FormatTag,
  Unsupporetd_Number_Of_Channel,
  Unsupporetd_Sample_Rate,
  Unsupporetd_Bits_Per_Sample,
  Unvalid_DataChunk_ID,
  Unsupporetd_ExtraFormatBytes,
  Unvalid_FactChunk_ID
}ErrorCode;

typedef struct _FILELIST_LineTypeDef {
  uint8_t type;
  uint8_t name[FILEMGR_FILE_NAME_SIZE];
}FILELIST_LineTypeDef;

typedef struct _FILELIST_FileTypeDef {
  FILELIST_LineTypeDef  file[FILEMGR_LIST_DEPDTH] ;
  uint16_t              ptr; 
}FILELIST_FileTypeDef;

typedef enum {
  AUDIO_ERROR_NONE = 0,  
  AUDIO_ERROR_IO,  
  AUDIO_ERROR_INVALID_VALUE,     
}AUDIO_ErrorTypeDef;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
AUDIO_ErrorTypeDef AUDIO_Init(void);
AUDIO_ErrorTypeDef AUDIO_Start(uint8_t idx);
AUDIO_ErrorTypeDef AUDIO_Process(void);
AUDIO_ErrorTypeDef AUDIO_Stop(void);
void AUDIO_PlaybackProbeKey(JOYState_TypeDef state);
uint8_t AUDIO_ShowWavFiles(void);

/* Disk Explorer API*/
uint8_t AUDIO_StorageInit(void);
FRESULT AUDIO_StorageParse(void);
uint16_t AUDIO_GetWavObjectNumber(void);

#endif /* __WAVEPLAYER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

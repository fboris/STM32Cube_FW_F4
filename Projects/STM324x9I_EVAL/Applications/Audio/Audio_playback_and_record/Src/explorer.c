/**
  ******************************************************************************
  * @file    Audio/Audio_playback_and_record/Src/explorer.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file provides USB Key drive configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
FATFS USBH_FatFs;
char USBKey_Path[4] = "0:/"; 
FILELIST_FileTypeDef FileList;
uint16_t NumObs = 0;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the USB KEY Storage.
  * @param  None
  * @retval Status
  */
uint8_t AUDIO_StorageInit(void)
{
  /* Link the USB Key disk I/O driver */
  if((f_mount(&USBH_FatFs, (TCHAR const*)USBKey_Path, 0) != FR_OK))
  {
    /* FatFs Initialization Error */
    LCD_ErrLog("Cannot Initialize FatFs! \n");
    return 1;
  }
  else
  {
    LCD_DbgLog ("INFO : FatFs Initialized! \n");
    return 0;
  }
}

/**
  * @brief  Copies disk content in the explorer list.
  * @param  None
  * @retval Operation result
  */
FRESULT AUDIO_StorageParse(void)
{
  FRESULT res;
  FILINFO fno;
  DIR dir;
  char *fn;
  
#if _USE_LFN
  static char lfn[_MAX_LFN];
  fno.lfname = lfn;
  fno.lfsize = sizeof(lfn);
#endif
  
  res = f_opendir(&dir, USBKey_Path);
  FileList.ptr = 0;
  
  if(res == FR_OK)
  {
    while (1)
    {
      res = f_readdir(&dir, &fno);
      
      if(res != FR_OK || fno.fname[0] == 0)
      {
        break;
      }
      if(fno.fname[0] == '.')
      {
        continue;
      }
#if _USE_LFN
      fn = *fno.lfname ? fno.lfname : fno.fname;
#else
      fn = fno.fname;
#endif
      
      if(FileList.ptr < FILEMGR_LIST_DEPDTH)
      {
        if((fno.fattrib & AM_DIR) == 0)
        {
          if((strstr(fn, "wav")) || (strstr(fn, "WAV")))
          {
            strncpy((char *)FileList.file[FileList.ptr].name, (char *)fn, FILEMGR_FILE_NAME_SIZE);
            FileList.file[FileList.ptr].type = FILETYPE_FILE;
            FileList.ptr++;
          }
        }
      }   
    }
  }
  NumObs = FileList.ptr;
  f_closedir(&dir);
  return res;
}

/**
  * @brief  Gets Wav Object Number.
  * @param  None
  * @retval None
  */
uint16_t AUDIO_GetWavObjectNumber(void)
{
  return NumObs;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    filebrowser_app.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Utilities for file handling
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
#include "filebrowser_app.h"
#include <string.h>

/** @addtogroup FILE_BROWSER_MODULE
  * @{
  */

/** @defgroup FILE_BROWSER
 * @brief file browser routines
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Copy disk content in the explorer list
  * @param  path: pointer to root path
  * @param  list: pointer to file list
  * @retval Status
  */
uint8_t  FILEMGR_ParseDisks (char *path, FILELIST_FileTypeDef *list)
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
  
  res = f_opendir(&dir, path);
  list->ptr = 0;
  
  if (res == FR_OK)
  {
    
    while (1)
    {
      res = f_readdir(&dir, &fno);
      
      if (res != FR_OK || fno.fname[0] == 0)
      {
        break;
      }
      if (fno.fname[0] == '.')
      {
        continue;
      }
#if _USE_LFN
      fn = *fno.lfname ? fno.lfname : fno.fname;
#else
      fn = fno.fname;
#endif
      
      if (list->ptr < FILEMGR_LIST_DEPDTH)
      {
        if ((fno.fattrib & AM_DIR) == AM_DIR)
        {
          strncpy((char *)list->file[list->ptr].name, (char *)fn, FILEMGR_FILE_NAME_SIZE);
          list->file[list->ptr].type = FILETYPE_DIR;
          list->ptr++;
        }
        else
        {
          strncpy((char *)list->file[list->ptr].name, (char *)fn, FILEMGR_FILE_NAME_SIZE);
          list->file[list->ptr].type = FILETYPE_FILE;
          list->ptr++;
        }
      }   
    }
  }
  f_closedir(&dir);
  return res;
}

/**
  * @brief  Retrieve the parent directory from full file path
  * @param  dir: pointer to parent directory
  * @retval None
*/
void FILEMGR_GetParentDir (char *dir)
{
  uint16_t idx = FILEMGR_FULL_PATH_SIZE;
  
  for (  ; idx > 0 ; idx --)
  {
    
    if (dir [idx] == '/')
    {
      dir [idx + 1] = 0;
      break;
    }
    dir [idx + 1] = 0;
  }
}


/**
  * @brief  Retrieve the file name from a full file path
  * @param  file: pointer to base path
  * @param  path: pointer to full path
  * @retval None
*/
void FILEMGR_GetFileOnly (char *file, char *path)
{
  char *baseName1, *baseName2;
  baseName1 = strrchr(path,'/');
  baseName2 = strrchr(path,':');
  
  if(baseName1++) 
  { 
    strcpy(file, baseName1);
  }
  else 
  {
    if (baseName2++) 
    {
      
      strcpy(file, baseName2);
    }
    else
    {
      strcpy(file, path);
    }
  }
}

/**
* @}
*/ 

/**
* @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

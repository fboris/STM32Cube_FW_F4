/**
  ******************************************************************************
  * @file    USB_Host/MSC_Standalone/Src/explorer.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Explore the USB flash disk content
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Displays disk content.
  * @param  path: Pointer to root path
  * @param  recu_level: Disk content level 
  * @retval Operation result
  */
FRESULT Explore_Disk(char *path, uint8_t recu_level)
{
  FRESULT res = FR_OK;
  FILINFO fno;
  DIR dir;
  char *fn;
  char tmp[14];
  uint8_t line_idx = 0;
  
#if _USE_LFN
  static char lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
  fno.lfname = lfn;
  fno.lfsize = sizeof lfn;
#endif
  
  res = f_opendir(&dir, path);
  if(res == FR_OK) 
  {
    while(USBH_MSC_IsReady(&hUSBHost))
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
      strcpy(tmp, fn); 
      
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
      
      if(recu_level == 1)
      {
        LCD_DbgLog("   |__");
      }
      else if(recu_level == 2)
      {
        LCD_DbgLog("   |   |__");
      }
      if((fno.fattrib & AM_MASK) == AM_DIR)
      {
        strcat(tmp, "\n"); 
        LCD_UsrLog((void *)tmp);
        Explore_Disk(fn, 2);
      }
      else
      {
        strcat(tmp, "\n"); 
        LCD_DbgLog((void *)tmp);
      }
      
      if(((fno.fattrib & AM_MASK) == AM_DIR)&&(recu_level == 2))
      {
        Explore_Disk(fn, 2);
      }
    }
    f_closedir(&dir);
	LCD_UsrLog("> Select an operation to Continue.\n" );
  }
  return res;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

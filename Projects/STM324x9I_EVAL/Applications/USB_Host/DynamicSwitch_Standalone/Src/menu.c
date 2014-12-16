/**
  ******************************************************************************
  * @file    USB_Host/DynamicSwitch_Standalone/Src/menu.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This file implements Menu Functions
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
extern char SD_Path[4];  /* SD logical drive path */
char USBDISKPath[4];     /* USB Host logical drive path */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Demo state machine.
  * @param  None
  * @retval None
  */
void Menu_Init(void)
{
  msc_demo.state = MSC_DEMO_IDLE;
  hid_demo.state = HID_DEMO_IDLE;
  audio_demo.state = AUDIO_DEMO_IDLE;
}

/**
  * @brief  Manages DS Menu Process.
  * @param  None
  * @retval None
  */
void DS_MenuProcess(void)
{       
  switch(Appli_state)
  {
  case APPLICATION_IDLE:
    break;
    
  case APPLICATION_MSC:
    MSC_MenuProcess();
    break;
    
  case APPLICATION_AUDIO:
    AUDIO_MenuProcess();
    break;
    
  case APPLICATION_HID:
    HID_MenuProcess();
    break;

  default:
	break;
  }
  if(Appli_state == APPLICATION_DISCONNECT)
  {
    Appli_state = APPLICATION_IDLE; 
    Menu_Init();
    /* Unlink the micro SD disk I/O driver */
    FATFS_UnLinkDriver(SD_Path);
    /* Unlink the USB disk I/O driver */
    FATFS_UnLinkDriver(USBDISKPath);
  }
} 

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static JOYState_TypeDef JoyState = JOY_NONE;
  static uint32_t debounce_time = 0;
  
  if(GPIO_Pin == GPIO_PIN_8)
  {    
    /* Get the Joystick State */
    JoyState = BSP_JOY_GetState();
    
    /* Clear joystick interrupt pending bits */
    BSP_IO_ITClear();
    
    if(Appli_state == APPLICATION_MSC)
    {
      MSC_DEMO_ProbeKey(JoyState); 
    }
    else if(Appli_state == APPLICATION_HID)
    {
      HID_DEMO_ProbeKey(JoyState); 
    }
    else if(Appli_state == APPLICATION_AUDIO)
    {
      if(audio_select_mode == AUDIO_SELECT_MENU)
      {  
        AUDIO_MenuProbeKey(JoyState); 
      }
      else if(audio_select_mode == AUDIO_PLAYBACK_CONTROL)
      {
        AUDIO_PlaybackProbeKey(JoyState);
      }
    }
    switch(JoyState)
    {
    case JOY_LEFT:
      LCD_LOG_ScrollBack();
      break;
           
    case JOY_RIGHT:
      LCD_LOG_ScrollForward();
      break;          
      
    default:
      break;           
    }
  }
  
  if(audio_demo.state == AUDIO_DEMO_PLAYBACK)
  {
    if(GPIO_Pin == KEY_BUTTON_PIN)
    { 
      /* Prevent debounce effect for user key */
      if((HAL_GetTick() - debounce_time) > 50)
      {
        debounce_time = HAL_GetTick();
      }
      else
      {
        return;
      }
      
      /* Change the selection type */
      if(audio_select_mode == AUDIO_SELECT_MENU)
      {
        Audio_ChangeSelectMode(AUDIO_PLAYBACK_CONTROL); 
      }
      else if(audio_select_mode == AUDIO_PLAYBACK_CONTROL)
      {       
        Audio_ChangeSelectMode(AUDIO_SELECT_MENU);
      }
    }
  }
} 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

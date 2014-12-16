/**
  @page STemWin_HelloWorld Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    STemWin_HelloWorld/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014    
  * @brief   
  ******************************************************************************
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
   @endverbatim

@par Description

This directory contains a set of source files that implement a simple "Hello
Wolrd" example based on STemWin for STM32F4xx devices.

The example allows also to run the different Segger samples that can be
downloaded from here:
http://www.segger.com/emwin-samples.html
To do this, user has only to replace the file "Basic_HelloWorld.c" into the
project workspace by the downloaded one.
As example, two sample source files are provided (but not linked to the project):
	STemWin/HelloWorld/Src/MEMDEV_WM_Ticker.c
	STemWin/HelloWorld/Src/MOVIE_ShowFeatures.c

Note that the following user files may need to be updated:
  LCDConf_stm3240g_eval.c
  GUIConf_stm3240g_eval.c
(if for example more GUI allocated memory is needed)

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - STemWin/STemWin_HelloWorld/Inc/GUIConf.h                Header for GUIConf_stm3240g_eval.c
  - STemWin/STemWin_HelloWorld/Inc/LCDConf_stm3240g_eval.h  Header for LCDConf_stm3240g_eval.c
  - STemWin/STemWin_HelloWorld/Inc/main.h                   Main program header file
  - STemWin/STemWin_HelloWorld/Inc/stm32f4xx_hal_conf.h     Library Configuration file
  - STemWin/STemWin_HelloWorld/Inc/stm32f4xx_it.h           Interrupt handlers header file
  - STemWin/STemWin_HelloWorld/Src/BASIC_HelloWorld.c       Simple demo drawing "Hello world"
  - STemWin/STemWin_HelloWorld/Src/GUIConf_stm3240g_eval.c  Display controller initialization
  - STemWin/STemWin_HelloWorld/Src/LCDConf_stm3240g_eval.c  Configuration file for the GUI library
  - STemWin/STemWin_HelloWorld/Src/main.c                   Main program file
  - STemWin/STemWin_HelloWorld/Src/stm32f4xx_it.c           STM32F4xx Interrupt handlers
  - STemWin/STemWin_HelloWorld/Src/system_stm32f4xx.c       STM32F4xx system file
 
@par Hardware and Software environment 

  - This example runs on STM32F42xxx/STM32F43xxx devices.
    
  - This example has been tested with STM324xG-EVAL evaluation board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

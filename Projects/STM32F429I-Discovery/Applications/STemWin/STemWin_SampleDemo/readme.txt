/**
  @page SampleDemo  STemWin SampleDemo Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    readme.txt 
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

This directory contains a set of source files that implement demo based on STemWin 
for STM32F4xx devices.

Note that the following user files may need to be updated:
  LCDConf_stm32f429i_disco_MB1075.c
  GUIConf.c
(if for example more GUI allocated memory is needed)

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
	  
@note Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select the RTC clock source; in this 
      case the Backup domain will be reset in order to modify the RTC Clock source, as consequence RTC  
      registers (including the backup registers) and RCC_BDCR register are set to their reset values.
	   
     
@par Directory contents 

  - STemWin/STemWin_SampleDemo/Inc/GUIConf.h                        Header for GUIConf.c
  - STemWin/STemWin_SampleDemo/Inc/LCDConf.h                        Header for LCDConf*.c
  - STemWin/STemWin_SampleDemo/Inc/rtc.h                            Header for rtc.c
  - STemWin/STemWin_SampleDemo/Inc/calibration.h                    Header for calibration.c
  - STemWin/STemWin_SampleDemo/Inc/main.h                           Main program header file
  - STemWin/STemWin_SampleDemo/Inc/stm32f4xx_hal_conf.h             Library Configuration file
  - STemWin/STemWin_SampleDemo/Inc/stm32f4xx_it.h                   Interrupt handlers header file
  - STemWin/STemWin_SampleDemo/Src/rtc.c                            Main file to configure RTC clock
  - STemWin/STemWin_SampleDemo/Src/calibration.c                    Main file to calibrate TS
  - STemWin/STemWin_SampleDemo/Src/GUIConf.c                        Display controller initialization file
  - STemWin/STemWin_SampleDemo/Src/LCDConf_stm32f429i_disco_MB1075.c  Configuration file for the GUI library (MB1075 LCD)
  - STemWin/STemWin_SampleDemo/Src/main.c                           Main program file
  - STemWin/STemWin_SampleDemo/Src/stm32f4xx_it.c                   STM32F4xx Interrupt handlers
  - STemWin/STemWin_SampleDemo/Src/system_stm32f4xx.c               STM32F4xx system file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_*.c                     All the sources files provided for SEGGER DEMO

@par Hardware and Software environment  

  - This example runs on STM32F429xx devices.

  - This example has been tested with STMicroelectronics STM32F429I-Discovery RevB 
    boards and can be easily tailored to any other supported device 
    and development board.
	
  
@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

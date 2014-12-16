/**
  @page STemWin_SampleDemo Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    STemWin_SampleDemo/readme.txt 
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

This directory contains a set of source files that implement a sample
demonstration example allowing to show some of the STemWin Library capabilities 
on STM32F4xx devices.

The list of modules to be used is configured into the file Demo/GUIDEMO.h

At the first run, after power OFF/ON, a touch screen calibration is needed: in
order to to this, user is just requested to follow the displayed instructions.
Then all the demo modules are run sequentially. Throughout the demonstration, a
control frame window is displayed at the bottom right of the touch screen: it
includes a progress bar and two control buttons (Next + Halt) allowing to skip
or pause the currently running module.

LEDs 1 to 4 are continuously toggling to indicate that the Demo runs properly.

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

  - STemWin/SampleDemo/Inc/GUIConf.h                        Header for GUIConf.c
  - STemWin/SampleDemo/Inc/LCDConf.h                        Header for LCDConf*.c
  - STemWin/SampleDemo/Inc/rtc.h                            Header for rtc.c
  - STemWin/SampleDemo/Inc/calibration.h                    Header for calibration.c
  - STemWin/SampleDemo/Inc/main.h                           Main program header file
  - STemWin/SampleDemo/Inc/stm32f4xx_hal_conf.h             Library Configuration file
  - STemWin/SampleDemo/Inc/stm32f4xx_it.h                   Interrupt handlers header file
  - STemWin/SampleDemo/Src/rtc.c                            Main file to configure RTC clock
  - STemWin/SampleDemo/Src/calibration.c                    Main file to calibrate TS
  - STemWin/SampleDemo/Src/GUIConf.c                        Display controller initialization file
  - STemWin/SampleDemo/Src/LCDConf_stm324x9i_eval_MB1046.c  Configuration file for the GUI library (MB1046 LCD)
  - STemWin/SampleDemo/Src/LCDConf_stm324x9i_eval_MB1063.c  Configuration file for the GUI library (MB1063 LCD)
  - STemWin/SampleDemo/Src/main.c                           Main program file
  - STemWin/SampleDemo/Src/stm32f4xx_it.c                   STM32F4xx Interrupt handlers
  - STemWin/SampleDemo/Src/system_stm32f4xx.c               STM32F4xx system file
  - STemWin/SampleDemo/Demo/GUIDEMO_*.c                     All the sources files provided for SEGGER DEMO
  - STemWin/SampleDemo/Demo/GUIDEMO.h                       DEMO modules configuration file


@par Hardware and Software environment 

  - This example runs on STM32F429xx/439xx devices.
    
  - This example has been tested with STMicroelectronics STM324x9I-EVAL RevB
    (STM32F429xx/STM32F439xx Devices) evaluation boards and can be easily 
    tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

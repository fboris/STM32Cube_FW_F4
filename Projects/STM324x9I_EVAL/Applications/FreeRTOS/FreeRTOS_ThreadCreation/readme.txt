/**
  @page FreeRTOS_ThreadCreation FreeRTOS Thread Creation example
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    FreeRTOS/FreeRTOS_ThreadCreation/readme.txt
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014 
  * @brief   Description of the FreeRTOS Thread Creation example.
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

This directory contains a set of sources files that implement a thread creation 
example using CMSIS RTOS API 

This example creates two threads with the same priority, which executes in 
a periodic cycle of 15 seconds. 

In the first 5 seconds, the thread 1 toggles LED1 each 200 ms and the 
thread 2 toggles LED2 each 500 ms
In the second 5 seconds, the thread 1 suspend itself and the thread 2
continue toggling LED2
In the last 5 seconds, the thread 2 resume execution of thread 1 then 
suspend itself, the thread 1 toggles the LED1 each 400 ms    


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about FreeRTOS implementation on STM32Cube, please refer to UM1722 "Developing Applications 
on STM32Cube with RTOS".


@par Directory contents

    - FreeRTOS/FreeRTOS_ThreadCreation/Inc/main.h                Main program header file
    - FreeRTOS/FreeRTOS_ThreadCreation/Inc/stm32f4xx_hal_conf.h  HAL Library Configuration file
    - FreeRTOS/FreeRTOS_ThreadCreation/Inc/stm32f4xx_it.h        Interrupt handlers header file
    - FreeRTOS/FreeRTOS_ThreadCreation/Inc/FreeRTOSConfig.h      FreeRTOS Configuration file
    - FreeRTOS/FreeRTOS_ThreadCreation/Src/main.c                Main program
    - FreeRTOS/FreeRTOS_ThreadCreation/Src/stm32f4xx_it.c        Interrupt handlers


@par Hardware and Software environment

  - This example runs on STM32F42xxx/STM32F43xxx devices
    
  - This example has been tested with STM324x9I-EVAL RevB evaluation board and can be
    easily tailored to any other supported device and development board.
    
    
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

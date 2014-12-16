/**
  @page FreeRTOS_Queues FreeRTOS Queues example
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    FreeRTOS/FreeRTOS_Queues/readme.txt
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the FreeRTOS Queues example.
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

This directory contains a set of sources files that implement an example
that uses message queues with CMSIS RTOS API

This example creates two threads that send and receive an incrementing number 
to/from a queue.
One thread acts as a producer and the other as the consumer.  The consumer 
is a higher priority than the producer and is set to block on queue reads. 
The queue only has space for one item - as soon as the producer posts a
message on the queue the consumer will unblock, preempt the producer, 
and remove the item.  

Add the following variables to LiveWatch, these variables must remain equals all the time:
 - ProducerValue
 - ConsumerValue

STM32 Eval board's LEDs can be used to monitor the example status:
  - LED1 should toggle when the example runs successfully.
  - LED3 is ON when any error occurs.

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

    - FreeRTOS/FreeRTOS_Queues/Inc/main.h                Main program header file
    - FreeRTOS/FreeRTOS_Queues/Inc/stm32f4xx_hal_conf.h  HAL Library Configuration file
    - FreeRTOS/FreeRTOS_Queues/Inc/stm32f4xx_it.h        Interrupt handlers header file
    - FreeRTOS/FreeRTOS_Queues/Inc/FreeRTOSConfig.h      FreeRTOS Configuration file
    - FreeRTOS/FreeRTOS_Queues/Src/main.c                Main program
    - FreeRTOS/FreeRTOS_Queues/Src/stm32f4xx_it.c        Interrupt handlers


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

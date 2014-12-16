/**
  @page LTDC_Paint LTDC Paint example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    TouchPanel/Paint/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the LTDC Paint example.
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
   @endverbatim

@par Example Description

 This example describe how to configure LCD touch screen and attribute 
 an action related to configured touch zone.
 
 At the beginning of the main program the HAL_Init() function is called to reset 
 all the peripherals, initialize the Flash interface and the systick.
 Then the SystemClock_Config() function is used to configure the system
 clock (SYSCLK) to run at 180 MHz. 

 After LCD and touch screen initialization, a menu is displayed on the screen 
 
 The menu contains a palette of colors, clear icon, save icon, different kind 
 of draw size, the current selected size and color and a working rectangle. 

 The user can select the color, the size draw inside the rectangle and save 
 the picture in USB mass storage. 
 Link the the USB mass storage disk I/O driver.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents

    - TouchPanel/Paint/Inc/main.h                 Main configuration file
    - TouchPanel/Paint/Inc/stm32f4xx_it.h         Interrupt handlers header file
    - TouchPanel/Paint/Inc/stm32f4xx_hal_conf.h   HAL Configuration file 
    - TouchPanel/Paint/Inc/ffconf.h               Configuration file for FatFs module.
    - TouchPanel/Paint/Inc/usbh_conf.h            Configuration file for USB module.
    - TouchPanel/Paint/Inc/color2.h               Image used to display colored pens
    - TouchPanel/Paint/Inc/save.h                 Image used to display save icon
    - TouchPanel/Paint/Src/main.c                 Main program 
    - TouchPanel/Paint/Src/stm32f4xx_it.c         Interrupt handlers
    - TouchPanel/Paint/Src/usbh_conf.c            Main function to configure USB
    - TouchPanel/Paint/Src/ts_calibration.c       Main function used to calibrate TS
    - TouchPanel/Paint/Src/system_stm32f4xx.c     STM32F4xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F429xx Devices.
    
  - This example has been tested with STM32F429I-Discovery RevB board and can be
    easily tailored to any other supported device and development board.  

  - STM32F429I-DISCO RevB Set-up
    - Plug the USB key into the STM32F429I-DISCO board through 'USB micro A-Male 
      to A-Female' cable.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
                                   
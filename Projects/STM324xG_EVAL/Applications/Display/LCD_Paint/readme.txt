/**
  @page LCD_Paint LCD Paint example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the LCD Paint example.
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

@par Example Description

 This example describe how to configure LCD touch screen and attribute 
 an action related to configured touch zone and how to save BMP picture in SDCard.
 
 At the beginning of the main program the HAL_Init() function is called to reset 
 all the peripherals, initialize the Flash interface and the systick.
 Then the SystemClock_Config() function is used to configure the system
 clock (SYSCLK) to run at 168 MHz. 

 After LCD and touch screen initialization, touchscreen calibration is requested
 for better accuracy, then, menu is displayed on the screen. 
 
 The menu contains palette of colors, clear icon, save icon, different kind 
 of draw size, the current selected size, selected color and working rectangle. 

 Select one of proposed colors and select the size of brush to draw 
 inside the working rectangle.
 
 Clear the working window by pressing the clear icon or/and save the picture 
 in SDCard by pressing the save icon.

                                          LCD Menu
               ____________________________________________________________
          /   |______|---------------------------------------------------- |
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
palette   |   |______||               Working Rectangle                   ||
   of   __|   |______||                                                   ||
 Colors   |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||                                                   ||
          |   |______||___________________________________________________|| 
          \   |______|__________________ _________        __               | 
              |clear |  choose the brush|   Save  |      |__|         O    | 
              |______|________size______|__SDCard_|__selected color__size__|


  - LED1 is on to indicate the end of saving operation.
  - LED3 is ON when any error occurs.

Note: After save operation, the touch positions are not cleared from STMPE811 FIFO 
      and the next touch in any positions of the LCD screen leads second save 
      operation.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents

    - Display/LCD_Paint/Inc/main.h                      Main program header file
    - Display/LCD_Paint/Inc/stm32f4xx_it.h              Interrupt handlers header file
    - Display/LCD_Paint/Inc/stm32f4xx_hal_conf.h        HAL Configuration file 
    - Display/LCD_Paint/Inc/color.h                     Image used for LCD Validation
    - Display/LCD_Paint/Inc/save.h                      Image used for LCD Validation 
    - Display/LCD_Paint/Inc/fatfs_storage.h             Header for fatfs_storage.c
    - Display/LCD_Paint/Inc/ffconf.h                    Configuration file for FatFs module.
    - Display/LCD_Paint/Src/main.c                      Main program  
    - Display/LCD_Paint/Src/stm32f4xx_it.c              Interrupt handlers
    - Display/LCD_Paint/Src/system_stm32f4xx.c          STM32F4xx system clock configuration file
    - Display/LCD_Paint/Src/ts_calibration.c            Touchscreen calibration driver
    - Display/LCD_Paint/Src/fatfs_storage.c             Storage (FatFs) driver


@par Hardware and Software environment

  - This example runs on STM32F40xxx/STM32F41xxx devices.

  - This example has been tested with STM324xG-EVAL evaluation board 
    and can be easily tailored to any other supported device and development board.

  - STM324xG-EVAL RevC Set-up
   - Connect a uSD Card to the MSD connector (CN6). 
   - Please ensure that jumpers JP16 and JP22 are in position 1-2.


@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
                                   

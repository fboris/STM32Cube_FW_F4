/**
  @page Demo   Demo STM32F401_Discovery 
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    Demonstrations/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description STM32F401 Discovery Demo 
  ******************************************************************************
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Example Description

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 84 MHz.
           
- Connect the STM32F401-Discovery RevB board to a PC with a 'USB type A to Mini-B' cable
through USB connector CN1 to power the board. Then red led LD1 (COM) and
LD2 (PWR) light up.
- All 4 leds between B1 and B2 are blinking as chenillard.
- Press User Button B1 (User) then MEMS sensor (LSM303DLHC) is enabled, move the
board and observe the four Leds blinking according to the motion direction.
- Connect the board to a PC with a second USB'type A to micro-B cable through USB 
connector CN5, this convert it to a standard mouse. Move the STM32F401-Discovery 
board and see the mouse moves according to the motion direction.
- Press B1 or B2 to restart demonstration.



@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents
 
  - FatFs/Demo/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - FatFs/Demo/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - FatFs/Demo/Inc/main.h                  Main program header file
  - FatFs/Demo/Inc/ffconf.h                FAT file system module configuration file   
  - FatFs/Demo/Src/stm32f4xx_it.c          Interrupt handlers
  - FatFs/Demo/Src/main.c                  Main program
  - FatFs/Demo/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file


@par Hardware and Software environment

  - This Demo runs on STM32F401xCx Devices.
  
  - This example has been tested with STMicroelectronics STM32F401-Discovery RevB (MB1115B) 
    and can be easily tailored to any other supported device and development board.

  - STM32F401-Discovery RevB Set-up
    - Plug the USB key into the STM32F401C-DISCO board through 'USB micro A-Male 
      to A-Female' cable (FS mode: connector CN5).


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
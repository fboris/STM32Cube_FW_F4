/**
  @page FatFs_USBDisk_MultipleAccess_RTOS   FatFs with USB disk drive multiple access in RTOS mode example
 
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the FatFs with USB disk drive multiple access in 
  *          RTOS mode example
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

This example provides a description on how to use STM32Cube firmware with FatFs 
middleware component as a generic FAT file system module, FreeRTOS as an RTOS
module based on using CMSIS-OS wrapping layer common APIs, and also STM32 USB 
On-The-Go (OTG) host library, in Full Speed (FS), High Speed (HS) and High Speed
in Full Speed (HS-IN-FS) modes, in order to develop an application exploiting 
FatFs offered features with USB disk drive in RTOS mode configuration.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 168 MHz, to provide 48 MHz clock needed for the USB operation. 
Please note that the USB is not functional if the system clock is set to 180 MHz.
           
The application is based on writing two text files to a drive. Two threads, with
different priorities, are created to manage mutliple access to the FAT volumeus
through FatFs APIs as described in the following steps:  

 - StartThread with a normal priority executing steps below:           
   - Link the USB Host disk I/O driver;
   - Register the file system object (mount) to the FatFs module for the USB drive;
   - Create and Open new text file object with write access;
   - Write data to the text file;
   - Close the open text file.
 
 - ConcurrentThread with a high priority executing steps below:  
   - Create and Open new text file object with write access;
   - Write data to the text file;
   - Close the open text file;
   - Unlink the USB Host disk I/O driver.
 
It is worth noting that the application manages any error occurred during the 
access to FAT volume, when using FatFs APIs. Otherwise, user can check if the
written text files are available on the USB disk.

It is possible to fine tune needed FatFs features by modifying defines values 
in FatFs configuration file “ffconf.h” available under the project includes 
directory, in a way to fit the application requirements. 

STM32 Eval board's LEDs can be used to monitor the example status:
  - LED1 and LED4 are ON when the example runs successfully.
  - LED3 is ON when any error occurs.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about FatFs implementation on STM32Cube, please refer to UM1721 "Developing Applications 
on STM32Cube with FatFs".


@par Directory contents
 
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Inc/main.h                  Main program header file
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Inc/ffconf.h                FAT file system module configuration file   
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Src/stm32f4xx_it.c          Interrupt handlers
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Src/main.c                  Main program
  - FatFs/FatFs_USBDisk_MultipleAccess_RTOS/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file        
 
 
@par Hardware and Software environment

  - This example runs on STM32F429xx/STM32F439xx devices.
    
  - This example has been tested with STMicroelectronics STM324x9I-EVAL RevB 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM324x9I-EVAL RevB Set-up
    - Plug the USB key into the STM324x9I-EVAL board through 'USB micro A-Male 
      to A-Female' cable to the connector:
      - CN9 : to use USB High Speed (HS) 
      - CN14: to use USB Full Speed (FS) with embedded PHY(U7)
              Please ensure that jumper JP16 is not fitted.
      - CN15: to use USB HS-IN-FS.
              Note that some FS signals are shared with the HS ULPI bus, so some PCB rework is needed.
              For more details, refer to section 2.8 USB OTG2 HS & FS in UM1667


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
   - STM324x9I-EVAL_USBH-HS: to configure the project for STM32F4xx devices using USB OTG HS peripheral
   - STM324x9I-EVAL_USBH-FS: to configure the project for STM32F4xx devices using USB OTG FS peripheral
   - STM324x9I-EVAL_USBH-HS-IN-FS: to configure the project for STM32F4xx devices and use USB OTG HS 
                                   peripheral In FS (using embedded PHY).
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
/**
  @page HID_Standalone USB Device Humain Interface (HID) example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    USB_Device/HID_Standalone/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the USB HID example.
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

This example is a part of the USB Device Library package using STM32Cube firmware. It describes how to 
use USB device application based on the Humain Interface (HID) on the STM32F4xx devices.

This is a typical example on how to use the STM32F4xx USB OTG Device peripheral where the STM32 MCU is
enumerated as a HID device using the native PC Host HID driver to which the STM324xG-EVAL
board is connected, in order to emulate the Mouse directions using Joystick buttons mounted on the 
STM324xG-EVAL board.

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 168 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock, which is generated from an integrated PLL. In the High Speed (HS) mode the
USB clock (60 MHz) is driven by the ULPI.

It's worth noting that the system clock (SYSCLK) can be configured, depending on the used USB Core:
 - SYSCLK is set to 168 MHz: for FS Core because used embedded PHY requires 48 MHz clock,
                             achieved only when system clock is set to 168 MHz.                             
 - SYSCLK is set to 180 MHz: for only HS Core, since no embedded PHY is used.
 
This example supports remote wakeup (which is the ability of a USB device to bring a suspended bus back
to the active condition), and the Key button is used as the remote wakeup source. 
   
By default, in Windows powered PC the Power Management feature of USB mouse devices is turned off.
This setting is different from classic PS/2 computer functionality. Therefore, to enable the Wake from 
standby option, user must manually turn on the Power Management feature for the USB mouse.

To manually enable the wake from standby option for the USB mouse, proceed as follows: 
 - Start "Device Manager",
 - Select "Mice and other pointing devices",
 - Select the "HID-compliant mouse" device (make sure that PID &VID are equal to 0x5710 & 0x0483 respectively) 
 - Right click and select "Properties", 
 - Select "Power Management" tab,
 - Finally click to select "Allow this device to wake the computer" check box.
 
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
For more details about the STM32Cube USB Device library, please refer to UM1734 
"STM32Cube USB Device library".
      

@par USB Library Configuration

To select the appropriate USB Core to work with, user must add the following macro defines within the
compiler preprocessor (already done in the preconfigured projects provided with this example):
      - "USE_USB_HS" when using USB High Speed (HS) Core
      - "USE_USB_FS" when using USB Full Speed (FS) Core 
      - "USE_USB_HS" and "USE_USB_HS_IN_FS" when using USB High Speed (HS) Core in FS mode


@par Directory contents

  - USB_Device/HID_Standalone/Src/main.c                  Main program
  - USB_Device/HID_Standalone/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file
  - USB_Device/HID_Standalone/Src/stm32f4xx_it.c          Interrupt handlers
  - USB_Device/HID_Standalone/Src/usbd_conf.c             General low level driver configuration
  - USB_Device/HID_Standalone/Src/usbd_desc.c             USB device HID descriptor
  - USB_Device/HID_Standalone/Inc/main.h                  Main program header file
  - USB_Device/HID_Standalone/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - USB_Device/HID_Standalone/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - USB_Device/HID_Standalone/Inc/usbd_conf.h             USB device driver Configuration file
  - USB_Device/HID_Standalone/Inc/usbd_desc.h             USB device HID descriptor header file  

	
@par Hardware and Software environment

  - This example runs on STM32F407xx/STM32F417xx devices.
    
  - This example has been tested with STMicroelectronics STM324xG-EVAL RevC 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.

  - STM324xG-EVAL RevC Set-up
    - Connect the STM324xG-EVAL board to the PC through 'USB micro A-Male 
      to A-Male' cable to the connector:
      - CN9 : to use USB High Speed (HS) 
      - CN8 : to use USB Full Speed (FS)
              

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
   - STM324xG-EVAL_USBH-HS: to configure the project for STM32F4xx devices using USB OTG HS peripheral
   - STM324xG-EVAL_USBH-FS: to configure the project for STM32F4xx devices using USB OTG FS peripheral
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
  
/**
  @page LwIP_HTTP_Server_Netconn_RTOS LwIP HTTP Server Netconn Application
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    LwIP/LwIP_HTTP_Server_Netconn_RTOS/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the LwIP http server Netconn API.
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

This example guides STM32Cube HAL API users to run a http server application 
based on Netconn API of LwIP TCP/IP stack
The communication is done with a web browser application in a remote PC.

this HTTP server contains two html pages:
  + the first page (home page) is static, it gives information about STM32F4
    and LwIP stack.
  + the second page is dynamically refreshed (every 1 s), it shows the RTOS 
    statistics in runtime

If the LCD is used (#define USE_LCD in main.h), log messages will be displayed 
to inform user about ethernet cable status and the IP address value, else this 
will be ensured by LEDs:
  + LED1: ethernet cable is connected.
  + LED2: ethernet cable is not connected.

If a DHCP server is available, a dynamic IP address can be allocated by enabling 
the DHCP process (#define USE_DHCP in main.h)

Note: In this application the Ethernet Link ISR need the System tick interrupt 
to configure the Ethernet MAC, so the Ethernet Link interrupt priority must be 
set lower (numerically greater) than the Systick interrupt priority to ensure 
that the System tick increments while executing the Ethernet Link ISR.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
For more details about this application, refer to UM1713 "STM32Cube interfacing with LwIP and examples"


@par Directory contents

  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/app_ethernet.h          header of app_ethernet.c file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/ethernetif.h            header for ethernetif.c file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/lcd_log_conf.h          lcd_log configuration file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/stm32f4xx_it.h          STM32 interrupt handlers header file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/main.h                  Main program header file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/lwipopts.h              LwIP stack configuration options
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/FreeRTOSConfig.h        FreeRTOS configuration options
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/httpserver-netconn.h    header for httpserver-netconn.c
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/fs.h                    header for fs.c
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Inc/fsdata.h                header for fsdata.c
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/app_ethernet.c          Ethernet specefic module
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/stm32f4xx_it.c          STM32 interrupt handlers
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/main.c                  Main program
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/ethernetif.c            Interfacing LwIP to ETH driver
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/httpserver-netconn.c    httpserver netconn main thread
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/fs.c                    file system functions
  - LwIP/LwIP_HTTP_Server_Netconn_RTOS/Src/fsdata.c                ROM filesystem data (html pages)
            

@par Hardware and Software environment

  - This example runs on STM32F407xx/STM32F417xx Devices.
    
  - This example has been tested with the following environments:
     - STM324xG-EVAL board
     - Http clients: Firefox Mozilla (v24) or Microsoft Internet Explorer (v8 and later)
     - DHCP server:  PC utility TFTPD32 (http://tftpd32.jounin.net/) is used as a DHCP server    
      
  - STM324xG-EVAL RevC Set-up
    - Connect the eval board to remote PC (through a crossover ethernet cable)
      or to your local network (through a straight ethernet cable)
  
  - Remote PC Set-up
    - Configure a static IP address for your remote PC 
      for example 192.168.0.11 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
            
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

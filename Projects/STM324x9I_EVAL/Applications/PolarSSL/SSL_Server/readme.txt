/**
  @page SSL_Server SSL Server example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    PolarSSL/SSL_Server/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of SSL Server example.
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

This example guides STM32Cube HAL API users to run an SSL Server application 
based on PolarSSL crypto library and LwIP TCP/IP stack

To off-load the CPU from encryption/decryption, hash and RNG, all these 
algorithms are implemented using the hardware acceleration AES 128/192/256, 
Triple DES, MD5, SHA-1, SHA2-2 and analog RNG through the STM32Cube HAL APIs

the HTTP server (STM32439I-EVAL) contains a html page dynamically refreshed 
(every 1 s), it shows the RTOS statistics in runtime

The HyperTerminal can be used to debug messages exchanged between client and 
server.

Note: In this application the Ethernet Link ISR need the System tick interrupt 
to configure the Ethernet MAC, so the Ethernet Link interrupt priority must be 
set lower (numerically greater) than the Systick interrupt priority to ensure 
that the System tick increments while executing the Ethernet Link ISR.

Note: By default, the Ethernet Half duplex mode is not supported in the 
STM324x9I-EVAL board, for more information refer to the HAL_ETH_MspInit() 
function in the ethernetif.c file 

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

For more details about this application, refer to UM1723 "STM32Cube PolarSSL example".


@par Directory contents 

    - PolarSSL/SSL_Server/Inc/app_ethernet.h           header of app_ethernet.c file
    - PolarSSL/SSL_Server/Inc/ethernetif.h             header for ethernetif.c file
    - PolarSSL/SSL_Server/Inc/main.h                   Main program header file 
    - PolarSSL/SSL_Server/Inc/config.h                 PolarSSL library configuration options
    - PolarSSL/SSL_Server/Inc/FreeRTOSConfig.h         FreeRTOS configuration options
    - PolarSSL/SSL_Server/Inc/lwipopts.h               LwIP stack configuration options
    - PolarSSL/SSL_Server/Inc/stm32f4xx_it.h           Interrupt handlers header file 
    - PolarSSL/SSL_Server/Inc/stm32f4xx_hal_conf.h     Library Configuration file
    - PolarSSL/SSL_Server/Inc/ssl_server.h             header for ssl_server.c
    - PolarSSL/SSL_Server/Src/app_ethernet.c           Ethernet specific module
    - PolarSSL/SSL_Server/Src/main.c                   Main program
    - PolarSSL/SSL_Server/Src/ssl_server.c             SSL Server main thread
    - PolarSSL/SSL_Server/Src/ethernetif.c             Interfacing the LwIP stack to ETH driver
    - PolarSSL/SSL_Server/Src/stm32f4xx_hal_msp.c      HAL MSP module
    - PolarSSL/SSL_Server/Src/stm32f4xx_it.c           Interrupt handlers 
    - PolarSSL/SSL_Server/Src/system_stm32f4xx.c       STM32 system clock configuration file


@par Hardware and Software environment  

  - This example runs on STM32F439xx Devices.
  
  - This example has been tested with the following environments: 
     - STM32439I-EVAL board
     - Http clients: Firefox Mozilla v24
     - DHCP server:  PC utility TFTPD32 (http://tftpd32.jounin.net/)
                     is used as a DHCP server 
     - HyperTerminal: used to display debug messages 
  
  - STM32439I-EVAL Set-up 
    - Connect STM32439I-EVAL board to remote PC (through a crossover ethernet cable)
      or to your local network (through a straight ethernet cable)
    - RS232 link (used with HyperTerminal like application to display debug messages):
      connect a null-modem female/female RS232 cable between the DB9 connector 
      CN8 (USART1) and PC serial port.
  
  - Remote PC Set-up
    - Configure a static IP address for your remote PC 
      for example 192.168.0.1 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
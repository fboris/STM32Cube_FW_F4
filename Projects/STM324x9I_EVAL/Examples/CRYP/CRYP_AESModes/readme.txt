/**
  @page CRYP_AESModes  Encrypt and Decrypt data using AES Algo in ECB/CBC/CTR
  chaining modes with all possible key sizes.
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    CRYP/CRYP_AESModes/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the CRYP AES Algorithm in all modes and all key sizes
             Example
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

This example provides a short description of how to use the CRYPTO peripheral to
encrypt and decrypt data using AES in chaining modes (ECB, CBC, CTR) and all key
sizes (128, 192, 256) Algorithm.

For this example, a firmware is used to interface with the Crypto peripheral
in polling mode.

This program behaves as follows:

1. ECB mode:
   - AES128 ECB Encryption
   - AES192 ECB Encryption
   - AES256 ECB Encryption

   - AES128 ECB Decryption
   - AES192 ECB Decryption
   - AES256 ECB Decryption

2. CBC mode:
   - AES128 CBC Encryption
   - AES192 CBC Encryption
   - AES256 CBC Encryption

   - AES128 CBC Decryption
   - AES192 CBC Decryption
   - AES256 CBC Decryption

3. CTR mode:
   - AES128 CTR Encryption
   - AES192 CTR Encryption
   - AES256 CTR Encryption

   - AES128 CTR Decryption
   - AES192 CTR Decryption
   - AES256 CTR Decryption

 @note The data to decrypt(aCiphertext) is different from the encryption 
       result of  aPlaintext, so the result of decryption will not be the 
       Plain Data. 

The Plain data, encrypted data and decrypted data can be displayed on a PC
Hyperterminal using the UART.

The USARTx is configured as follows:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - CRYP/CRYP_AESModes/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_AESModes/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_AESModes/Inc/main.h                  Main program header file  
  - CRYP/CRYP_AESModes/Src/stm32f4xx_it.c          Interrupt handlers
  - CRYP/CRYP_AESModes/Src/main.c                  Main program
  - CRYP/CRYP_AESModes/Src/stm32f4xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_AESModes/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F439xx devices.
  
  - This example has been tested with STMicroelectronics STM32439I-EVAL RevB 
    evaluation boards and can be easily tailored to any other supported device 
    and development board. 
    
  - STM324x9I-EVAL RevB Set-up
    - Connect a null-modem female/female RS232 cable between the DB9 connector 
      CN8 (USART1) and PC serial port if you want to display data on the HyperTerminal.
      Please ensure that jumper JP7 is in position RS232_RX
     
  - Hyperterminal configuration:
    - BaudRate = 115200 baud  
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled     

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
/**
  @page CRYP_AES_GCM  Encrypt and Decrypt data using AES Algo using GCM chaining mode
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    CRYP/CRYP_AES_GCM/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the CRYP AES Algorithm using GCM chaining mode example
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

This example provides a description of how to use the CRYPTO peripheral to
encrypt and decrypt data using AES with Galois/Counter Mode (GCM).
The AES-GCM mode requires:
1. Plain text which will be authenticated and encrypted. Its size must be a
   multiple of 16 bytes. So if the original plain text size is not a multiple
   of 16 bytes, it must be padded.
2. Header that will be authenticated but not encrypted. The header size must be
   multiple of 16 bytes whatever the key size.
3. Initialization vector a value that is used only once within a specified
   context. It must be padded to 16-byte length with LSB set to 2. 
4. Key is the parameter which determines the cipher text. In this example the
   key size is 128 bits =16 bytes but it can be tailored to 192 bits or 256 bits.

The AES-GCM provides:
1. Cipher text which is the encryption result of the Plaint text. In this
   example, the cipher text is available in "EncryptedText".
   Its size is the same as the plain text.
2. Plain text which is the decryption result of the Cipher text. In this
   example, the plain text is available in "DecryptedText".
   Its size is the same as the plain text. 
3. TAG: The Message Authentication Code which is used for both message
   authentication and message tampering detection. It's size is always 16 bytes.
   
The Plain data, encrypted data, authentication TAG (MAC) and decrypted data can
be displayed on a PC HyperTerminal using the UART.

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

  - CRYP/CRYP_AES_GCM/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_AES_GCM/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_AES_GCM/Inc/main.h                  Main program header file  
  - CRYP/CRYP_AES_GCM/Src/stm32f4xx_it.c          Interrupt handlers
  - CRYP/CRYP_AES_GCM/Src/main.c                  Main program
  - CRYP/CRYP_AES_GCM/Src/stm32f4xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_AES_GCM/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file


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
 
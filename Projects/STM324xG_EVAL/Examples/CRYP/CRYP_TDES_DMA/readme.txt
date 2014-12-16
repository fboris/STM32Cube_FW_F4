/**
  @page CRYP_TDES_DMA  Encrypt data using TDES Algo in ECB mode, with DMA example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    CRYP/CRYP_TDES_DMA/readme.txt 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the CRYP TDES DMA example.
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
encrypt data using TDES Algorithm.

For this example, DMA is used to transfer data from memory to the CRYPTO processor
IN FIFO and also to transfer data from CRYPTO processor OUT FIFO to memory.

The data to be encrypted is a 384 bit data, which correspond to 6 TDES Blocks.

This program behaves as follows:
- TDES Encryption   (PlainData --> EncryptedData)

STM32 Eval board's LEDs can be used to monitor the transfer status:
 - LED1 is ON when encryption is right.
 - LED2 is ON when encryption is wrong.
 - LED3 is ON when there is an initialization error occurred.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 

  - CRYP/CRYP_TDES_DMA/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_TDES_DMA/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_TDES_DMA/Inc/main.h                  Main program header file  
  - CRYP/CRYP_TDES_DMA/Src/stm32f4xx_it.c          Interrupt handlers
  - CRYP/CRYP_TDES_DMA/Src/main.c                  Main program
  - CRYP/CRYP_TDES_DMA/Src/stm32f4xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_TDES_DMA/Src/system_stm32f4xx.c      STM32F4xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32F417xx devices.  
    
  - This example has been tested with STMicroelectronics STM32417G-EVAL RevC 
    evaluation boards and can be easily tailored to any other supported device 
    and development board.   


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
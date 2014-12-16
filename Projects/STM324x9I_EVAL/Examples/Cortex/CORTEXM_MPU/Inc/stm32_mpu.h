/**
  ******************************************************************************
  * @file    CORTEXM/CORTEXM_MPU/Inc/stm32_mpu.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for stm32_mpu.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_MPU_H
#define __STM32_MPU_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define RAM_ADDRESS_START                        (0x20000000UL)
#define RAM_SIZE                                 (0x19UL << 0UL)
#define PERIPH_ADDRESS_START                     (0x40000000)
#define PERIPH_SIZE                              (0x39UL << 0UL)
#define FLASH_ADDRESS_START                      (0x08000000)
#define FLASH_SIZE                               (0x27UL << 0UL)
#define portMPU_REGION_READ_WRITE                (0x03UL << MPU_RASR_AP_Pos)
#define portMPU_REGION_PRIVILEGED_READ_ONLY      (0x05UL << MPU_RASR_AP_Pos)
#define portMPU_REGION_READ_ONLY                 (0x06UL << MPU_RASR_AP_Pos)
#define portMPU_REGION_PRIVILEGED_READ_WRITE     (0x01UL << MPU_RASR_AP_Pos)
#define RAM_REGION_NUMBER                        (0x00UL << MPU_RNR_REGION_Pos)
#define FLASH_REGION_NUMBER                      (0x01UL << MPU_RNR_REGION_Pos)
#define PERIPH_REGION_NUMBER                     (0x02UL << MPU_RNR_REGION_Pos)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MPU_Config(void);
void MPU_AccessPermConfig(void);

#endif /* __STM32_MPU_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    CRYP/CRYP_AES_CCM/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This example provides a short description of how to use the CRYPTO
  *          peripheral to encrypt data using AES with Combined Cypher Machine (CCM).
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup CRYP_AES_CCM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Key size in bits */
#define KEY_SIZE           128

#define NONCE_SIZE         8
#define HEADER_SIZE        16
#define PLAINTEXT_SIZE     16
#define MAC_SIZE           6

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* CRYP handler declaration */
CRYP_HandleTypeDef     CrypHandle;

uint8_t aAES128Key[KEY_SIZE/8] = {0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,
                                  0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f};
                                   
uint8_t aNonce[NONCE_SIZE] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17};
                                        
uint32_t uwNonceSize = NONCE_SIZE;

uint8_t aHeaderMessage[HEADER_SIZE] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                                       0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};

/* Temporary buffer used to append the header. aHBuffer size must be equal to HEADER_SIZE + 21 */
uint8_t aHBuffer[HEADER_SIZE + 21]; 
                                      

uint8_t aPlaintext[PLAINTEXT_SIZE] = {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
                                      0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f};
                                       

uint8_t aExpectedCyphertext[PLAINTEXT_SIZE] = {0xd2,0xa1,0xf0,0xe0,
                                               0x51,0xea,0x5f,0x62,
                                               0x08,0x1a,0x77,0x92,
                                               0x07,0x3d,0x59,0x3d};

/* Used for storing either encrypted or decrypted text */
uint8_t aOutputText[PLAINTEXT_SIZE];

/* Used for storing computed aMAC (TAG) */
uint8_t aMAC[MAC_SIZE];

uint8_t aExpectedMAC[6] = {0x1F,0xC6,0x4F,0xBF,0xAC,0xCD};

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();
  
  /* Configure the system clock to 180 Mhz */
  SystemClock_Config();
  
  /* Initialize LED1, LED2 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  
  /*##-1- Configure the CRYP peripheral ######################################*/
  /* Set the CRYP parameters */
  CrypHandle.Init.DataType   = CRYP_DATATYPE_8B;
  CrypHandle.Init.KeySize    = CRYP_KEYSIZE_128B;
  CrypHandle.Init.pKey       = aAES128Key;
  CrypHandle.Init.pInitVect  = aNonce;
  CrypHandle.Init.IVSize     = uwNonceSize;
  CrypHandle.Init.Header     = aHeaderMessage;
  CrypHandle.Init.HeaderSize = 16;
  CrypHandle.Init.TagSize    = 6;
  CrypHandle.Init.pScratch   = aHBuffer;

  if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /*##-2- Start the AES Encryption in CCM chaining mode ######################*/
  if(HAL_CRYPEx_AESCCM_Encrypt(&CrypHandle, aPlaintext, PLAINTEXT_SIZE, aOutputText, 0xFF) != HAL_OK)
  {
    /* Encryption Error */
    Error_Handler(); 
  }
  
  /*##-3- Compute the authentication TAG for AES CCM mode ####################*/ 
  if(HAL_CRYPEx_AESCCM_Finish(&CrypHandle, aMAC, 0xFF) != HAL_OK)
  {
    /* TAG Error */
    Error_Handler(); 
  }
  
  /*##-4- Compare the encrypted text and the aMAC with the expected ones #####*/
  if( (memcmp(aOutputText, aExpectedCyphertext, PLAINTEXT_SIZE) != 0) ||  (memcmp(aMAC, aExpectedMAC, MAC_SIZE) != 0))
  {
    /* Wrong encryption: Turn LED2 on */
    BSP_LED_On(LED2);
  }
  else
  {
    /* Right encryption: Turn LED1 on */
    BSP_LED_On(LED1);
  }
  
  /* Infinite loop */
  while(1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_ActivateOverDrive();
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

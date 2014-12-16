/**
  ******************************************************************************
  * @file    CRYP/CRYP_DESTDESmodes/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This example provides a short description of how to use the CRYPTO
  *          peripheral to encrypt and decrypt data using DES and TDES in all
  *          modes (ECB, CBC) Algorithm.
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

/** @addtogroup CRYP_DESTDESmodes
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PLAINTEXT_SIZE             16
#define ECB                        1
#define CBC                        2
#define DES                        ' '
#define TDES                       'T'

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* CRYP handler declaration */
CRYP_HandleTypeDef     CrypHandle;

/* UART handler declaration */
UART_HandleTypeDef     UartHandle;

/* Initialization vector */
uint8_t aInitVector[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};

/* Key size 8 bytes */
uint8_t aDESKey[8] = {0x75,0x28,0x78,0x39,0x74,0x93,0xCB,0x70}; 

uint8_t aTDESKey[24] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,  /* Key 1 */
                        0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,  /* Key 2 */
                        0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67}; /* Key 3 */
/* Plaintext */
uint8_t aPlaintext[16] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,
                          0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00}; 
/* Cyphertext */
uint8_t aCyphertext[16] = {0xB5,0x21,0x9E,0xE8,0x1A,0xA7,0x49,0x9D,
                           0x21,0x96,0x68,0x7E,0x13,0x97,0x38,0x56};

/* Used for storing the encrypted text */
uint8_t aEncryptedText[PLAINTEXT_SIZE]; 

/* Used for storing the decrypted text */
uint8_t aDecryptedText[PLAINTEXT_SIZE]; 

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

static void SystemClock_Config(void);
static void Error_Handler(void);
static void Display_PlainData(uint32_t datalength);
static void Display_EncryptedData(uint32_t algo, uint32_t mode, uint32_t datalength);
static void Display_DecryptedData(uint32_t algo, uint32_t mode, uint32_t datalength);

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
  
  /* Configure the COM port */
  UartHandle.Init.BaudRate = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;
  BSP_COM_Init(COM1, &UartHandle);
  
  /*##-1- Configure the CRYP peripheral ######################################*/
  /* Set the common CRYP parameters */
  CrypHandle.Init.DataType = CRYP_DATATYPE_8B;
  CrypHandle.Init.KeySize  = CRYP_KEYSIZE_128B;
  CrypHandle.Init.pKey     = aDESKey;
 
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Display Plain Data */
  Display_PlainData(PLAINTEXT_SIZE);
  
  /*##-2- Start Encryption ###################################################*/
  
  /****************************************************************************/
  /*                             DES mode ECB                                 */
  /****************************************************************************/
  
  /*=====================================================
  Encryption ECB mode                                        
  ======================================================*/
  /* Encrypt the plaintext message */
  if (HAL_CRYP_DESECB_Encrypt(&CrypHandle, aPlaintext, 16, aEncryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display encrypted data */
    Display_EncryptedData(DES, ECB, PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  /*=====================================================
  Decryption ECB mode                                        
  ======================================================*/
  /* ReInitialize the DES Key */
  CrypHandle.Init.pKey = aDESKey;
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Decrypt the Encrypted message */
  if (HAL_CRYP_DESECB_Decrypt(&CrypHandle, aEncryptedText, 16, aDecryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display decrypted data */
    Display_DecryptedData(DES, ECB, PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  
  /****************************************************************************/
  /*                             DES mode CBC                                 */
  /****************************************************************************/
  /* Insert the Initialization Vector & reInitialize the DES Key */
  CrypHandle.Init.pKey      = aDESKey;
  CrypHandle.Init.pInitVect = aInitVector;
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }  
  /*=====================================================
  Encryption CBC mode                                        
  ======================================================*/
  /* Encrypt the plaintext message */
  if (HAL_CRYP_DESCBC_Encrypt(&CrypHandle, aPlaintext, 16, aEncryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display encrypted data */
    Display_EncryptedData(DES,CBC,PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  /*=====================================================
  Decryption CBC mode                                        
  ======================================================*/
  /* ReInitialize the DES Key */
  CrypHandle.Init.pKey = aDESKey;
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /* Decrypt the Encrypted message */
  if (HAL_CRYP_DESCBC_Decrypt(&CrypHandle, aEncryptedText, 16, aDecryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display decrypted data */
    Display_DecryptedData(DES, CBC, PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  
  /****************************************************************************/
  /*                             TDES mode ECB                                */
  /****************************************************************************/
  /* ReInitialize the DES Key */
  CrypHandle.Init.pKey = aTDESKey; 
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /*=====================================================
  Encryption ECB mode                                        
  ======================================================*/
  /* Encrypt the plaintext message */
  if (HAL_CRYP_TDESECB_Encrypt(&CrypHandle, aPlaintext, 16, aEncryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display encrypted data */
    Display_EncryptedData(TDES,ECB,PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  /*=====================================================
  Decryption ECB mode                                        
  ======================================================*/
  /* ReInitialize the DES Key */
  CrypHandle.Init.pKey = aTDESKey;
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /* Decrypt the Encrypted message */
  if (HAL_CRYP_TDESECB_Decrypt(&CrypHandle, aEncryptedText, 16, aDecryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display decrypted data*/
    Display_DecryptedData(TDES, ECB, PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  
  /****************************************************************************/
  /*                             TDES mode CBC                                */
  /****************************************************************************/
  /* Insert the Initialization Vector & reInitialize the DES Key */
  CrypHandle.Init.pKey      = aTDESKey;
  CrypHandle.Init.pInitVect = aInitVector;
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }  
  /*=====================================================
  Encryption CBC mode                                        
  ======================================================*/
  
  /* Encrypt the plaintext message */
  if (HAL_CRYP_TDESCBC_Encrypt(&CrypHandle, aPlaintext, 16, aEncryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display encrypted data */
    Display_EncryptedData(TDES,CBC,PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
  }
  /*=====================================================
  Decryption CBC mode                                        
  ======================================================*/
  /* Insert the Initialization Vector & reInitialize the TDES Key */
  CrypHandle.Init.pKey      = aTDESKey;
  CrypHandle.Init.pInitVect = aInitVector;
  
  if (HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }  
  /* Decrypt the Encrypted message */
  if (HAL_CRYP_TDESCBC_Decrypt(&CrypHandle, aEncryptedText, 16, aDecryptedText, TIMEOUT_VALUE) == HAL_OK)
  {
    /* Display decrypted data */
    Display_DecryptedData(TDES, CBC, PLAINTEXT_SIZE);
  }
  else
  {
    /* Processing Error */
    Error_Handler();
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

/**
  * @brief  Display Plain Data 
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_PlainData(uint32_t datalength)
{
  uint32_t BufferCounter =0;
  uint32_t count = 0;
  
  printf("\n\r=============================================================\n\r");
  printf("================= Crypt Using HW Crypto  ====================\n\r");
  printf("=============================================================\n\r");
  printf("---------------------------------------\n\r");
  printf("Plain Data :\n\r");
  printf("---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aPlaintext[BufferCounter]);
    count++;

    if(count == 8)
    { 
      count = 0;
      printf("  Block %d \n\r", (int)BufferCounter/8);
    }
  }
}


/**
  * @brief  Display Decrypted Data 
  * @param  algo: Algorithm used (DES or TDES)
  * @param  mode: chaining mode
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_DecryptedData(uint32_t algo, uint32_t mode, uint32_t datalength)
{
  uint32_t BufferCounter = 0;
  uint32_t count = 0;

  printf("\n\r ======================================\n\r");
  printf("  Decrypted Data %cDES Mode ",(int)algo);

  if(mode == ECB)
  {
    printf("ECB\n\r");
  } 
  else   /* if(mode == CBC)*/
  {
    printf("CBC\n\r");
  }
   
  printf(" --------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aDecryptedText[BufferCounter]);
    count++;

    if(count == 8)
    { 
      count = 0;
      printf(" Block %d \n\r", (int)BufferCounter/8);
    }
  }
}

/**
  * @brief  Display Encrypted Data 
  * @param  algo: Algorithm used (DES or TDES)
  * @param  mode: chaining mode
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_EncryptedData(uint32_t algo, uint32_t mode, uint32_t datalength)
{
  uint32_t BufferCounter = 0;
  uint32_t count = 0;

  printf("\n\r=======================================\n\r");
  printf("  Encrypted Data %cDES Mode ",(int)algo);

  if(mode == ECB)
  {
    printf("ECB\n\r");
  } 
  else  /* if(mode == CBC) */
  {
    printf("CBC\n\r");
  }
     
  printf("---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aEncryptedText[BufferCounter]);
    count++;

    if(count == 8)
    { 
      count = 0;
      printf(" Block %d \n\r", (int)BufferCounter/8);
    }
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 5); 

  return ch;
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

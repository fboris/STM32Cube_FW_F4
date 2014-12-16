/**
  ******************************************************************************
  * @file    CRYP/CRYP_AES_GCM/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Description of the CRYP AES Algorithm using GCM chaining mode
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

/** @addtogroup CRYP_AES_GCM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* The size of the plaintext in bytes. It must be a multiple of 16.
   AES is a block cypher algorithm. The plaintext must be multiple of 128 bits = 16 bytes */
#define PLAINTEXT_SIZE    16

/* The key size must be 128 bits (16 bytes), 192 bits (24 bytes) or 256 bits (32 bytes) */
#define KEY_SIZE          128

/* The header size must be multiple of 16 bytes whatever the key size */
#define HEADER_SIZE       16
#define AES_MODE_GCM      1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* CRYP handler declaration */
CRYP_HandleTypeDef     CrypHandle;

/* UART handler declaration */
UART_HandleTypeDef     UartHandle;

/* AES Key size is 128-bit (16 bytes) */
uint8_t aAES128Key[KEY_SIZE] = {0xc9,0x39,0xcc,0x13,0x39,0x7c,0x1d,0x37,
                                0xde,0x6a,0xe0,0xe1,0xcb,0x7c,0x42,0x3c};

uint8_t aInitVector[16] = {0xb3,0xd8,0xcc,0x01,0x7c,0xbb,0x89,0xb3,
                           0x9e,0x0f,0x67,0xe2,0x00,0x00,0x00,0x02};

uint8_t aHeaderMessage[HEADER_SIZE] = {0x24,0x82,0x56,0x02,0xbd,0x12,0xa9,0x84, 
                                       0xe0,0x09,0x2d,0x3e,0x44,0x8e,0xda, 0x5f}; 
                                       
uint8_t aPlaintext[PLAINTEXT_SIZE] = {0xc3,0xb3,0xc4,0x1f,0x11,0x3a,0x31,0xb7,
                                      0x3d,0x9a,0x5c,0xd4,0x32,0x10,0x30,0x69};

uint8_t aCyphertext[PLAINTEXT_SIZE] = {0x93,0xfe,0x7d,0x9e,0x9b,0xfd,0x10,0x34, 
                                       0x8a,0x56,0x06,0xe5,0xca,0xfa,0x73,0x54}; 
                                       
/* Used for storing the encrypted text */
uint8_t aEncryptedText[PLAINTEXT_SIZE]; 

/* Used for storing the decrypted text */
uint8_t aDecryptedText[PLAINTEXT_SIZE]; 

/* Used for storing the computed MAC (aTAG) */
uint8_t aTAG[16];

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
static void Display_Plaintext(uint32_t datalength);
static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength);
static void Display_TAG(uint8_t* aTAG);
static void PressToContinue(void);

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
  
  /* Configure LED3 */
  BSP_LED_Init(LED3);  
  
  /* Configure the COM port */
  UartHandle.Init.BaudRate = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;
  BSP_COM_Init(COM1, &UartHandle);
  
  /*##-1- Configure the CRYP peripheral ######################################*/
  /* Set the CRYP parameters */
  CrypHandle.Init.DataType   = CRYP_DATATYPE_8B;
  CrypHandle.Init.KeySize    = CRYP_KEYSIZE_128B;
  CrypHandle.Init.pKey       = aAES128Key;
  CrypHandle.Init.pInitVect  = aInitVector;
  CrypHandle.Init.Header     = aHeaderMessage;
  CrypHandle.Init.HeaderSize = sizeof(aHeaderMessage);
  
  if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Infinite loop */
  while(1)
  {
    /* Display Plaintext */
    Display_Plaintext(PLAINTEXT_SIZE);
    
    /*##-2- Encryption Phase #################################################*/
    /* Set the Initialization vector */
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }
  
    /* Encrypt the plaintext message */
    if(HAL_CRYPEx_AESGCM_Encrypt(&CrypHandle, aPlaintext, 16, aEncryptedText, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(AES_MODE_GCM, KEY_SIZE, PLAINTEXT_SIZE);
    }
    else 
    {
      /* Processing Error */
      Error_Handler();
    }
    
    /* Compute the authentication aTAG */
    if(HAL_CRYPEx_AESGCM_Finish(&CrypHandle, 16, aTAG, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display the computed aTAG, aTAG size is 16 bytes */
      Display_TAG(aTAG);
    }
    else 
    {
      /* Processing Error */
      Error_Handler();
    }

    /*##-3- Decryption Phase #################################################*/    
    /* Set the Initialization vector */
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }
  
    /* Encrypt the plaintext message */
    if(HAL_CRYPEx_AESGCM_Decrypt(&CrypHandle, aCyphertext, 16, aDecryptedText, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_DecryptedData(AES_MODE_GCM, KEY_SIZE, PLAINTEXT_SIZE);
    }
    else 
    {
      /* Processing Error */
      Error_Handler();
    }
       
    /* Compute the authentication aTAG */
    if(HAL_CRYPEx_AESGCM_Finish(&CrypHandle, 16, aTAG, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display the computed aTAG, aTAG size is 16 bytes */
      Display_TAG(aTAG);
    }
    else 
    {
      /* Processing Error */
      Error_Handler();
    }    
    
    PressToContinue();
    printf("\n\r Example restarted...\n ");   
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
static void Display_Plaintext(uint32_t datalength)
{
  uint32_t BufferCounter =0;
  uint32_t count = 0;
  
  printf("\n\r =============================================================\n\r");
  printf(" =================== AES using GCM mode  =====================\n\r");
  printf(" =============================================================\n\r");
  printf(" ---------------------------------------\n\r");
  printf(" Plain Data :\n\r");
  printf(" ---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aPlaintext[BufferCounter]);
    count++;

    if(count == 16)
    { 
      count = 0;
      printf("  Block %d \n\r", (int)BufferCounter/16);
    }
  }
}

/**
  * @brief  Display Encrypted Data 
  * @param  mode: chaining mode
  * @param  keysize: AES key size used
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_EncryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength)
{
  uint32_t BufferCounter = 0;
  uint32_t count = 0;

  printf("\n\r =======================================\n\r");
  printf(" Encrypted Data with AES %d  mode  ",keysize );
  if(mode == AES_MODE_GCM)
  {
    printf("GCM\n\r");
  }
  printf(" ---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aEncryptedText[BufferCounter]);

    count++;
    if(count == 16)
    { 
      count = 0;
      printf(" Block %d \n\r", (int)BufferCounter/16);
    }
  }
}

/**
  * @brief  Display Decrypted Data 
  * @param  mode: chaining mode
  * @param  keysize: AES key size used
  * @param  datalength: length of the data to display
  * @retval None
  */
static void Display_DecryptedData(uint8_t mode, uint16_t keysize, uint32_t datalength)
{
  uint32_t BufferCounter = 0;
  uint32_t count = 0;

  printf("\n\r =======================================\n\r");
  printf(" Decrypted Data with AES %d  mode  ",keysize ); 
  if(mode == AES_MODE_GCM)
  {
    printf("GCM\n\r");
  }
  printf(" ---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aDecryptedText[BufferCounter]);
    count++;

    if(count == 16)
    { 
      count = 0;
      printf(" Block %d \n\r", (int)BufferCounter/16);
    }
  }
}


/**
  * @brief  Display the aTAG
  * @param  aTAG: the computed aTAG
  * @retval None
  */
static void Display_TAG(uint8_t* aTAG)
{
  uint32_t BufferCounter = 0;
  
  printf("\n\r =======================================\n\r");
  printf(" Message Authentication Code (aTAG):\n\r  "); 
  printf("---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < 16; BufferCounter++)
  {
    printf("[0x%02X]", aTAG[BufferCounter]);
  }
}

/**
  * @brief  Wait till a character is received by the USART
  * @param  None
  * @retval None
  */
static void PressToContinue(void)
{
  uint8_t data = 0;
  
  printf("\n\r Press any key to continue...\n\r ");  
  
  while (data == 0)
  {
    /* Read a character from the EVAL_COM1 */
    HAL_UART_Receive(&UartHandle, (uint8_t *)&data, 1, TIMEOUT_VALUE);
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

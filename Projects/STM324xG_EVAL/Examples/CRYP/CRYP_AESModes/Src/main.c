/**
  ******************************************************************************
  * @file    CRYP/CRYP_AESModes/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This example provides a short description of how to use the CRYPTO
  *          peripheral to encrypt and decrypt data using AES in chaining modes
  *         (ECB, CBC, CTR) and all key sizes (128, 192, 256) Algorithm.
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

/** @addtogroup CRYP_AESModes
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define KEY_SIZE          128 /* Key size in bits */
#define PLAINTEXT_SIZE    16
#define AES_TEXT_SIZE     64 /* 16 x 4 */

#define ECB               1
#define CBC               2
#define CTR               3

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* CRYP handler declaration */
CRYP_HandleTypeDef     CrypHandle;

/* UART handler declaration */
UART_HandleTypeDef     UartHandle;

/* Key size 128 bytes */
uint8_t aAES128key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,
                          0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c}; 

/* Key size 192 bytes */  
uint8_t aAES192key[24] = {0x8e,0x73,0xb0,0xf7,0xda,0x0e,0x64,0x52,
                          0xc8,0x10,0xf3,0x2b,0x80,0x90,0x79,0xe5,
                          0x62,0xf8,0xea,0xd2,0x52,0x2c,0x6b,0x7b}; 

/* Key size 256 bytes */
uint8_t aAES256key[32] = {0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,
                          0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
                          0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,
                          0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4}; 

/* Initialization vector */
uint8_t aInitVector[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                           0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}; 

/* Plaintext */
uint8_t aPlaintext[AES_TEXT_SIZE] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,
                                     0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,
                                     0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,
                                     0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,
                                     0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,
                                     0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,
                                     0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,
                                     0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10};

/* Cyphertext */
uint8_t aCyphertext[AES_TEXT_SIZE] = {0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,
                                      0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d,
                                      0x50,0x86,0xcb,0x9b,0x50,0x72,0x19,0xee,
                                      0x95,0xdb,0x11,0x3a,0x91,0x76,0x78,0xb2,
                                      0x73,0xbe,0xd6,0xb8,0xe3,0xc1,0x74,0x3b,
                                      0x71,0x16,0xe6,0x9e,0x22,0x22,0x95,0x16,
                                      0x3f,0xf1,0xca,0xa1,0x68,0x1f,0xac,0x09,
                                      0x12,0x0e,0xca,0x30,0x75,0x86,0xe1,0xa7};

/* Used for storing the encrypted text */
uint8_t aEncryptedtext[AES_TEXT_SIZE];

/* Used for storing the decrypted text */
uint8_t aDecryptedtext[AES_TEXT_SIZE];

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
static void Display_EncryptedData(uint8_t mode,uint16_t keysize,uint32_t datalength);
static void Display_DecryptedData(uint8_t mode,uint16_t keysize,uint32_t datalength);
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
  
  /* Configure the system clock to 168 Mhz */
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

  if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Infinite loop */ 
  while(1)
  {
    /* Display Plain Data*/
    Display_PlainData(AES_TEXT_SIZE);
    
    PressToContinue();
    
/******************************************************************************/
/*                             AES mode ECB                                   */
/******************************************************************************/

/*=====================================================
    Encryption ECB mode                                        
======================================================*/

/*****************  AES 128   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize = CRYP_KEYSIZE_128B;
    CrypHandle.Init.pKey    = aAES128key;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESECB_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(ECB, 128, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }     
/*****************  AES 192   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize = CRYP_KEYSIZE_192B;
    CrypHandle.Init.pKey    = aAES192key;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESECB_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(ECB, 192, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }    
/*****************  AES 256   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize = CRYP_KEYSIZE_256B;
    CrypHandle.Init.pKey    = aAES256key;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }
    
    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESECB_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(ECB, 256, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }    
    
    PressToContinue();
/*=====================================================
    Decryption ECB mode                                        
======================================================*/

/*****************  AES 128   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize = CRYP_KEYSIZE_128B;
    CrypHandle.Init.pKey    = aAES128key;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESECB_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(ECB,128,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }   
/*****************  AES 192   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize = CRYP_KEYSIZE_192B;
    CrypHandle.Init.pKey    = aAES192key;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESECB_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(ECB,192,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }  
/*****************  AES 256   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize = CRYP_KEYSIZE_256B;
    CrypHandle.Init.pKey    = aAES256key;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESECB_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(ECB,256,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }
  
    PressToContinue();
    
/******************************************************************************/
/*                             AES mode CBC                                   */
/******************************************************************************/
    
/*=====================================================
    Encryption CBC mode                                        
======================================================*/
    
/*****************  AES 128   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_128B;
    CrypHandle.Init.pKey      = aAES128key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESCBC_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(CBC, 128, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }   
/*****************  AES 192   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_192B;
    CrypHandle.Init.pKey      = aAES192key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESCBC_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(CBC, 192, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }   
/*****************  AES 256   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_256B;
    CrypHandle.Init.pKey      = aAES256key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESCBC_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(CBC, 256, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }
    
    PressToContinue();
/*=====================================================
    Decryption CBC mode                                        
======================================================*/
    
/*****************  AES 128   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_128B;
    CrypHandle.Init.pKey      = aAES128key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESCBC_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(CBC,128,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }   
/*****************  AES 192   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_192B;
    CrypHandle.Init.pKey      = aAES192key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }
    
    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESCBC_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(CBC,192,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    } 
/*****************  AES 256   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_256B;
    CrypHandle.Init.pKey      = aAES256key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESCBC_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(CBC,256,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }

    PressToContinue();
/******************************************************************************/
/*                             AES mode CTR                                   */
/******************************************************************************/

/*=====================================================
    Encryption CTR mode                                        
======================================================*/
    
/*****************  AES 128   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_128B;
    CrypHandle.Init.pKey      = aAES128key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESCTR_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(CTR, 128, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }
/*****************  AES 192   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_192B;
    CrypHandle.Init.pKey      = aAES192key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESCTR_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(CTR, 192, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }   
/*****************  AES 256   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_256B;
    CrypHandle.Init.pKey      = aAES256key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start encrypting aPlaintext, the cypher data is available in aEncryptedtext */
    if(HAL_CRYP_AESCTR_Encrypt(&CrypHandle, aPlaintext, AES_TEXT_SIZE, aEncryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display encrypted Data */
      Display_EncryptedData(CTR, 256, AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }
    
    PressToContinue();
/*=====================================================
    Decryption CTR mode                                        
======================================================*/
    
/*****************  AES 128   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_128B;
    CrypHandle.Init.pKey      = aAES128key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESCTR_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(CTR,128,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }
/*****************  AES 192   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_192B;
    CrypHandle.Init.pKey      = aAES192key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESCTR_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(CTR,192,AES_TEXT_SIZE);
    }
    else
    {
      /* Processing Error */
      Error_Handler(); 
    }
/*****************  AES 256   ****************/
    /* Initialize the CRYP peripheral */
    CrypHandle.Init.KeySize   = CRYP_KEYSIZE_256B;
    CrypHandle.Init.pKey      = aAES256key;
    CrypHandle.Init.pInitVect = aInitVector;
    
    if(HAL_CRYP_Init(&CrypHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }

    /* Start decrypting aCyphertext, the decrypted data is available in aDecryptedtext */
    if(HAL_CRYP_AESCTR_Decrypt(&CrypHandle, aCyphertext, AES_TEXT_SIZE, aDecryptedtext, TIMEOUT_VALUE) == HAL_OK)
    {
      /* Display decrypted Data */
      Display_DecryptedData(CTR, 256, AES_TEXT_SIZE);
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
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 336
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
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
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
  
  printf("\n\r =============================================================\n\r");
  printf(" ================= Crypt Using HW Crypto  ====================\n\r");
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
  printf(" Encrypted Data with AES %d  Mode  ",keysize );

  if(mode == ECB)
  {
    printf("ECB\n\r");
  }    
  else if(mode == CBC)     
  {
    printf("CBC\n\r");
  }      
  else /* if(mode == CTR)*/ 
  {
    printf("CTR\n\r");
  }   

  printf(" ---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aEncryptedtext[BufferCounter]);

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
  printf(" Decrypted Data with AES %d  Mode  ",keysize );

  if(mode == ECB)
  {
    printf("ECB\n\r");
  }    
  else if(mode == CBC)     
  {
    printf("CBC\n\r");
  }      
  else /* if(mode == CTR)*/ 
  {
    printf("CTR\n\r");
  }   
 
  printf(" ---------------------------------------\n\r");
  
  for(BufferCounter = 0; BufferCounter < datalength; BufferCounter++)
  {
    printf("[0x%02X]", aDecryptedtext[BufferCounter]);
    count++;

    if(count == 16)
    { 
      count = 0;
      printf(" Block %d \n\r", (int)BufferCounter/16);
    }
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

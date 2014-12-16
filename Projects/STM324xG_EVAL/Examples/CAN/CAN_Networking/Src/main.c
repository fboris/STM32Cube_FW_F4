/**
  ******************************************************************************
  * @file    CAN/CAN_Networking/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This example shows how to configure the CAN peripheral 
  *          to send and receive CAN frames in normal mode. The sent frames 
  *          are used to control LEDs by pressing Key push button.
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

/** @addtogroup CAN_Networking
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define KEY_PRESSED     0x00
#define KEY_NOT_PRESSED 0x01

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t ubKeyNumber = 0x0;
CAN_HandleTypeDef    CanHandle;

/* Private function prototypes -----------------------------------------------*/
static void CAN_Config(void);
static void SystemClock_Config(void);
static void Error_Handler(void);
static void LED_Display(uint8_t Ledstatus);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
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
  
  /* Configure LED1, LED2, LED3 and LED4 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  /* Configure Push button key */  
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
  
  /*##-1- Configure the CAN peripheral #######################################*/
  CAN_Config();
  
  /*##-2- Start the Reception process and enable reception interrupt #########*/
  if(HAL_CAN_Receive_IT(&CanHandle, CAN_FIFO0) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }
    
  /* Infinite loop */
  while(1)
  {
    while(BSP_PB_GetState(BUTTON_KEY) == KEY_PRESSED)
    {
      if(ubKeyNumber == 0x4) 
      {
        ubKeyNumber = 0x00;
      }
      else
      {
        LED_Display(++ubKeyNumber);
        /* Set the data to be tranmitted */
        CanHandle.pTxMsg->Data[0] = ubKeyNumber;
        CanHandle.pTxMsg->Data[1] = 0xAD;
        /*##-3- Start the Transmission process ###############################*/
        if(HAL_CAN_Transmit(&CanHandle, 10) != HAL_OK)
        {
          /* Transmition Error */
          Error_Handler();
        }
        HAL_Delay(10);
        while(BSP_PB_GetState(BUTTON_KEY) != KEY_NOT_PRESSED)
        {
        }
      }
    }
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
  while(1)
  {
  }
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
static void CAN_Config(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  static CanTxMsgTypeDef        TxMessage;
  static CanRxMsgTypeDef        RxMessage;
  
  /*##-1- Configure the CAN peripheral #######################################*/
  CanHandle.Instance = CAN1;
  CanHandle.pTxMsg = &TxMessage;
  CanHandle.pRxMsg = &RxMessage;
    
  CanHandle.Init.TTCM = DISABLE;
  CanHandle.Init.ABOM = DISABLE;
  CanHandle.Init.AWUM = DISABLE;
  CanHandle.Init.NART = DISABLE;
  CanHandle.Init.RFLM = DISABLE;
  CanHandle.Init.TXFP = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_NORMAL;
  CanHandle.Init.SJW = CAN_SJW_1TQ;
  CanHandle.Init.BS1 = CAN_BS1_6TQ;
  CanHandle.Init.BS2 = CAN_BS2_8TQ;
  CanHandle.Init.Prescaler = 2;
  
  if(HAL_CAN_Init(&CanHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure the CAN Filter ###########################################*/
  sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;
  
  if(HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
      
  /*##-3- Configure Transmission process #####################################*/
  CanHandle.pTxMsg->StdId = 0x321;
  CanHandle.pTxMsg->ExtId = 0x01;
  CanHandle.pTxMsg->RTR = CAN_RTR_DATA;
  CanHandle.pTxMsg->IDE = CAN_ID_STD;
  CanHandle.pTxMsg->DLC = 2;
}

/**
  * @brief  Transmission  complete callback in non blocking mode 
  * @param  CanHandle: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle)
{
  if ((CanHandle->pRxMsg->StdId == 0x321)&&(CanHandle->pRxMsg->IDE == CAN_ID_STD) && (CanHandle->pRxMsg->DLC == 2))
  {
    LED_Display(CanHandle->pRxMsg->Data[0]);
    ubKeyNumber = CanHandle->pRxMsg->Data[0];
  }
  
  /* Receive */
  if(HAL_CAN_Receive_IT(CanHandle, CAN_FIFO0) != HAL_OK)
  {
    /* Reception Error */
    Error_Handler();
  }
}

/**
  * @brief  Turn ON/OFF the dedicated LED.
  * @param  Ledstatus: Led number from 0 to 3.
  * @retval None
  */
void LED_Display(uint8_t Ledstatus)
{
  /* Turn off all LEDs */
  BSP_LED_Off(LED1);
  BSP_LED_Off(LED2);
  BSP_LED_Off(LED3);
  BSP_LED_Off(LED4);
  
  switch(Ledstatus)
  {
    case(1): 
      BSP_LED_On(LED1);
      break;
   
    case(2): 
      BSP_LED_On(LED2);
      break;
 
    case(3): 
      BSP_LED_On(LED3);
      break;

    case(4): 
      BSP_LED_On(LED4);
      break;
      
    default:
      break;
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

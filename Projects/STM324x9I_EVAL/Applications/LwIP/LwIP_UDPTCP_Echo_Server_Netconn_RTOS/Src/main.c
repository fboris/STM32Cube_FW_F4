/**
  ******************************************************************************
  * @file    LwIP/LwIP_UDPTCP_Echo_Server_Netconn_RTOS/Src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   This sample code implements a UDP and TCP Echo Client application 
  *          based on Netconn API of LwIP stack and FreeRTOS. 
  *          This application uses STM32F4xx the ETH HAL API to transmit and 
  *          receive data. 
  *          The communication is done with a web browser of a remote PC.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "cmsis_os.h"
#include "ethernetif.h"
#include "app_ethernet.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct netif gnetif; /* network interface structure */
/* Semaphore to signal Ethernet Link state update */
osSemaphoreId Netif_LinkSemaphore = NULL;
/* Ethernet link thread Argument */
struct link_str link_arg;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void StartThread(void const * argument);
static void ToggleLed4(void const * argument);
static void BSP_Config(void);
static void Netif_Config(void);
extern void tcpecho_init(void);
extern void udpecho_init(void);

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
  
  /* Configure the system clock to 180 Mhz */
  SystemClock_Config();
  
  /* Init task */
  osThreadDef(Start, StartThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE * 2);
  osThreadCreate (osThread(Start), NULL);
  
  /* Start scheduler */
  osKernelStart (NULL, NULL);
  
  /* We should never get here as control is now taken by the scheduler */
  for( ;; );
}

/**
  * @brief  Main task
  * @param  pvParameters not used
  * @retval None
  */
static void StartThread(void const * argument)
{
  /* Initialize LCD and LEDs */
  BSP_Config();
  
  /* Create tcp_ip stack thread */
  tcpip_init( NULL, NULL );
  
  /* Initilaize the LwIP stack */
  Netif_Config();
  
  /* Initialize tcp echo server */
  tcpecho_init();

  /* Initialize udp echo server */
  udpecho_init();
  
  /* Notify user about the netwoek interface config */
  User_notification(&gnetif);
  
   /* Start toogleLed4 task : Toggle LED4  every 250ms */
  osThreadDef(LED4, ToggleLed4, osPriorityLow, 0, configMINIMAL_STACK_SIZE);
  osThreadCreate (osThread(LED4), NULL);

  for( ;; )
  {
    /* Delete the Init Thread*/ 
    osThreadTerminate(NULL);
  }
}

/**
  * @brief  Initializes the lwIP stack
  * @param  None
  * @retval None
  */
static void Netif_Config(void)
{
  struct ip_addr ipaddr;
  struct ip_addr netmask;
  struct ip_addr gw;	
  
  /* IP address setting */
  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
  
  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
  struct ip_addr *netmask, struct ip_addr *gw,
  void *state, err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))
  
  Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.
  
  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
  
  /*  Registers the default network interface. */
  netif_set_default(&gnetif);
  
  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called.*/
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }

  /* Set the link callback function, this function is called on change of link status*/
  netif_set_link_callback(&gnetif, ethernetif_update_config);
  
  /* create a binary semaphore used for informing ethernetif of frame reception */
  osSemaphoreDef(Netif_SEM);
  Netif_LinkSemaphore = osSemaphoreCreate(osSemaphore(Netif_SEM) , 1 );
  
  link_arg.netif = &gnetif;
  link_arg.semaphore = Netif_LinkSemaphore;
  /* Create the Ethernet link handler thread */
  osThreadDef(LinkThr, ethernetif_set_link, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  osThreadCreate (osThread(LinkThr), &link_arg);
}

/**
  * @brief  Initializes the STM324x9I-EVAL's LCD and LEDs resources.
  * @param  None
  * @retval None
  */
static void BSP_Config(void)
{
  /* Initialize STM324x9I-EVAL's LEDs */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  /* Init IO Expander */
  BSP_IO_Init();
  /* Enable IO Expander interrupt for ETH MII pin */
  BSP_IO_ConfigPin(MII_INT_PIN, IO_MODE_IT_FALLING_EDGE);
}

/**
  * @brief  Toggle Led4 task
  * @param  pvParameters not used
  * @retval None
  */
static void ToggleLed4(void const * argument)
{
  for( ;; )
  {
    /* toggle LED4 each 250ms */
    BSP_LED_Toggle(LED4);
    osDelay(250);
  }
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_8)
  {
    /* Get the IT status register value */
    if(BSP_IO_ITGetStatus(MII_INT_PIN))
    {
      osSemaphoreRelease(Netif_LinkSemaphore);
    }
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

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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
  {}
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

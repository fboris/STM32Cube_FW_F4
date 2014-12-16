/**
  ******************************************************************************
  * @file    k_mem.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for k_mem.c file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _K_MEM_H
#define _K_MEM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
   
/* Exported types ------------------------------------------------------------*/
#define SIZE_OF_PAGE    1024   /* 1 KBytes pages */
#define MAX_PAGE_NUMBER   64    /* Maximum of 64 pages */


typedef struct
{
  uint32_t mallocBase;                    /* Memory pool base address */
  uint32_t size[MAX_PAGE_NUMBER];         /* Sizes Table to allow safe deallocation */
  uint8_t PageTable[MAX_PAGE_NUMBER];     /* Memory page state table '1'-> Allocated '0' -> Free */
}
mem_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void k_MemInit(void);
void * k_malloc(size_t s);
void k_free(void * p);

#ifdef __cplusplus
}
#endif

#endif /* _K_MEM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    CALIBRATION.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for CALIBRATION.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT YYYY STMicroelectronics</center></h2>
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
#ifndef __CALIBRATION_H
#define __CALIBRATION_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void CALIBRATION_Check(void);
uint8_t  CALIBRATION_IsDone(void);
uint16_t CALIBRATION_GetX(uint16_t x);
uint16_t CALIBRATION_GetY(uint16_t y);

#ifdef __cplusplus
}
#endif

#endif /*__CALIBRATION_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


  @verbatim
  ******************************************************************************
  *  
  *           Portions COPYRIGHT 2014 STMicroelectronics                       
  *           Portions Copyright (C) 2013 Real Time Engineers Ltd, all right reserved
  *  
  * @file    st_readme.txt 
  * @author  MCD Application Team
  * @brief   This file lists the main modification done by STMicroelectronics on
  *          FreeRTOS V7.6.0 for integration with STM32Cube solution.
  *          For more details on FreeRTOS implementation on STM32Cube, please refer 
  *          to UM1722 "Developing Applications on STM32Cube with FreeRTOS"  
  ******************************************************************************
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
  @endverbatim

### V1.1.2/13-June-2014 ###
===========================
  + FreeRTOSConfig_template.h: add this definition #define INCLUDE_xTaskGetSchedulerState 1
                               to enable the use of xTaskGetSchedulerState() API in the 
                               application code. 


### V1.1.1/30-April-2014 ###
============================
  + cmsis_os.c: add preprocessor compilation condition when calling some FreeRTOS APIs, to avoid link
                errors with MDK-ARM when some FreeRTOS features are not enabled in FreeRTOSConfig.h


### V1.1.0/22-April-2014 ###
============================
  + Add Tickles mode for CM0 port (IAR, GCC, RVDS).


### V1.0.0/18-February-2014 ###
===============================
   + First customized version for STM32Cube solution.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

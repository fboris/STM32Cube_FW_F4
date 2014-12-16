
  @verbatim
  ******************************************************************************
  *  
  *           Portions COPYRIGHT 2014 STMicroelectronics                       
  *           Portions Copyright (C) 2012, ChaN, all right reserved            
  *  
  * @file    st_readme.txt 
  * @author  MCD Application Team
  * @brief   This file lists the main modification done by STMicroelectronics on
  *          FatFs R.10 for integration with STM32Cube solution.
  *          For more details on FatFs implementation on STM32Cube, please refer 
  *          to UM1721 "Developing Applications on STM32Cube with FatFs"  
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


### V1.1.0/22-April-2014 ###
============================
  + Update sd_diskio to use SD BSP in polling mode instead of DMA mode (the scratch
    buffer needed for DMA alignment is removed as well).
  + diskio.c and ff_gen_drv.c/.h: update to prevent multiple initialization.


### V1.0.0/18-February-2014 ###
===============================
   + First customized version for STM32Cube solution.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

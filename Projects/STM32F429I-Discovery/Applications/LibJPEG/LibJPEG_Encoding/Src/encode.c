/**
  ******************************************************************************
  * @file    LibJPEG/LibJPEG_Encoding/Src/encode.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014 
  * @brief   This file contain the compress method.
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
#include "encode.h"

/* Private typedef -----------------------------------------------------------*/
   /* This struct contains the JPEG compression parameters */
   static struct jpeg_compress_struct cinfo; 
   /* This struct represents a JPEG error handler */
   static struct jpeg_error_mgr jerr; 
  
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Decode
  * @param  file:          pointer to the bmp file
  * @param  file1:         pointer to the jpg file  
  * @param  width:         image width
  * @param  height:        image height
  * @param  image_quality: image quality
  * @param  buff:          pointer to the image line
  * @retval None
  */
void jpeg_encode(FIL *file, FIL *file1, uint32_t width, uint32_t height, uint32_t image_quality, uint8_t * buff)
{ 
    
  /* Encode BMP Image to JPEG */  
  JSAMPROW row_pointer;    /* Pointer to a single row */
  uint32_t bytesread;
            
  /* Step 1: allocate and initialize JPEG compression object */
  /* Set up the error handler */
  cinfo.err = jpeg_std_error(&jerr);
  
  /* Initialize the JPEG compression object */  
  jpeg_create_compress(&cinfo);
  
  /* Step 2: specify data destination */
  jpeg_stdio_dest(&cinfo, file1);
  
  /* Step 3: set parameters for compression */
  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  
  /* Set default compression parameters */
  jpeg_set_defaults(&cinfo);
  
  cinfo.dct_method  = JDCT_FLOAT;    
  
  jpeg_set_quality(&cinfo, image_quality, TRUE);
  
  /* Step 4: start compressor */
  jpeg_start_compress(&cinfo, TRUE);
  
  f_read(file, buff, 54, (UINT*)&bytesread);
  
  while (cinfo.next_scanline < cinfo.image_height)
  {          
    
    if(f_read(file, buff, width*3, (UINT*)&bytesread) == FR_OK)
    {
      row_pointer = (JSAMPROW)buff;
      jpeg_write_scanlines(&cinfo, &row_pointer, 1);          
    }
  }
  /* Step 5: finish compression */
  jpeg_finish_compress(&cinfo);
  
  /* Step 6: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);
    
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

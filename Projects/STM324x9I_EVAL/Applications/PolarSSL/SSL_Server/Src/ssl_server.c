/**
  ******************************************************************************
  * @file    PolarSSL/SSL_Server/Src/ssl_server.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   SSL Server main task
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
#include <stdlib.h>

#include "config.h"
#include "polarssl/entropy.h"
#include "polarssl/ctr_drbg.h"
#include "polarssl/certs.h"
#include "polarssl/x509.h"
#include "polarssl/ssl.h"
#include "polarssl/net.h"
#include "polarssl/error.h"

#if defined(POLARSSL_SSL_CACHE_C)
#include "polarssl/ssl_cache.h"
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DEBUG_LEVEL 1   /* Set DEBUG_LEVEL if you want to enable SSL debug
option, this should be set to 2, 3, 4 or 5 */

#define HTTP_RESPONSE \
"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n" \
"<h2>PolarSSL Test Server</h2>\r\n" \
"<p>Successful connection using: %s</p>\r\n"
      
      /* Format of dynamic web page */
#define PAGE_START \
"<html>\
<head>\
</head>\
<BODY onLoad=\"window.setTimeout(&quot;location.href='index.html'&quot;,1000)\" bgcolor=\"#FFFFFF\" text=\"#000000\">\
<font size=\"4\" color=\"#0000FF\"><b>STM32Cube : SSL server Demo using STM32F439xx HW Crypto</font></b></i>\
<br><br><pre>\r\nPage Hits = "
                  
#define PAGE_END \
" \r\n</pre><br><br><hr>\
<font size=\"3\" color=\"#808080\">All rights reserved STMicroelectronics\
\r\n</font></BODY>\
 </html>"
                          
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* SSL structures */
uint32_t nPageHits = 0;

/* Private functions ---------------------------------------------------------*/
void my_debug(void *ctx, int level, const char *str)
{
  if(level < DEBUG_LEVEL)
  {
    printf("%s", str);  
  }
}

/**
  * @brief  SSL Server task.
  * @param  pvParameters not used
  * @retval None
  */
void ssl_server(void const * argument)
{
  int ret, len;
  int listen_fd;
  int client_fd = -1;
  unsigned char buf[1524];
  ssl_context ssl;
  x509_cert srvcert;
  rsa_context rsa;
#if defined(POLARSSL_SSL_CACHE_C)
  ssl_cache_context cache;
  
  ssl_cache_init( &cache );
#endif
  
  /*
  * Load the certificates and private RSA key
  */
  printf( "\n  . Loading the server cert. and key..." );
  
  memset( &srvcert, 0, sizeof( x509_cert ) );
  
  /*
  * This demonstration program uses embedded test certificates.
  * Instead, you may want to use x509parse_crtfile() to read the
  * server and CA certificates, as well as x509parse_keyfile().
  */
  ret = x509parse_crt( &srvcert, (const unsigned char *) test_srv_crt,
                      strlen( test_srv_crt ) );
  if( ret != 0 )
  {
    printf( " failed\n  !  x509parse_crt returned %d\n\n", ret );
    goto exit;
  }
  
  ret = x509parse_crt( &srvcert, (const unsigned char *) test_ca_crt,
                      strlen( test_ca_crt ) );
  if( ret != 0 )
  {
    printf( " failed\n  !  x509parse_crt returned %d\n\n", ret );
    goto exit;
  }
  
  rsa_init( &rsa, RSA_PKCS_V15, 0 );
  ret =  x509parse_key( &rsa, (const unsigned char *) test_srv_key,
                       strlen( test_srv_key ), NULL, 0 );
  if( ret != 0 )
  {
    printf( " failed\n  !  x509parse_key returned %d\n\n", ret );
    goto exit;
  }
  
  printf( " ok\n\r" );
  
  /*
  * Setup the listening TCP socket
  */
  printf( "  . Bind on https://localhost:443/ ..." );
  
  if( ( ret = net_bind( &listen_fd, NULL, 443) ) != 0 )
  {
    printf( " failed\n  ! net_bind returned %d\n\n", ret );
    goto exit;
  }
  
  printf( " ok\n\r" );
    
    /*
    * Setup stuff
    */
    printf( "  . Setting up the SSL data...." );
    
    if( ( ret = ssl_init( &ssl ) ) != 0 )
    {
      printf( " failed\n  ! ssl_init returned %d\n\n", ret );
      goto reset;
    }
    
    ssl_set_endpoint( &ssl, SSL_IS_SERVER );
    ssl_set_authmode( &ssl, SSL_VERIFY_NONE );
    
    ssl_set_rng( &ssl, RandVal , NULL );
    ssl_set_dbg( &ssl, my_debug, stdout );
    
#if defined(POLARSSL_SSL_CACHE_C)
    ssl_set_session_cache( &ssl, ssl_cache_get, &cache,
                          ssl_cache_set, &cache );
#endif

    ssl_set_ca_chain( &ssl, srvcert.next, NULL, NULL );
    ssl_set_own_cert( &ssl, &srvcert, &rsa );
    
    ssl_set_bio( &ssl, net_recv, &client_fd, net_send, &client_fd );
    
    printf( " ok\n\r" );

  for(;;)
  {   
    /*
    * Wait until a client connects
    */
    client_fd = -1;
    
    printf( "  . Waiting for a remote connection ..." );
    
    if( ( ret = net_accept( listen_fd, &client_fd, NULL ) ) != 0 )
    {
      printf( " failed\n  ! net_accept returned %d\n\n", ret );
      goto exit;
    }
    
    printf( " ok\n\r" );
    
    /*
    * Handshake
    */
    printf( "  . Performing the SSL/TLS handshake..." );
    
    while( ( ret = ssl_handshake( &ssl ) ) != 0 )
    {
      if( ret != POLARSSL_ERR_NET_WANT_READ && ret != POLARSSL_ERR_NET_WANT_WRITE )
      {
        printf( " failed\n  ! ssl_handshake returned -0x%x\n\n", -ret );
        goto reset;
      }
    }
    
    printf( " ok\n\r" );
    
    /*
    * Read the HTTP Request
    */
    printf( "  < Read from client:" );
    memset( buf, 0, sizeof( buf ) );
    len = 0;
    do
    {
      ret = ssl_read( &ssl, buf + len, 1523 - len);
      
      if( ret == POLARSSL_ERR_NET_WANT_READ || ret == POLARSSL_ERR_NET_WANT_WRITE )
        continue;
      
      if( ret <= 0 )
      {
        switch( ret )
        {
        case POLARSSL_ERR_SSL_PEER_CLOSE_NOTIFY:
          printf( " connection was closed gracefully\n" );
          break;
          
        case POLARSSL_ERR_NET_CONN_RESET:
          printf( " connection was reset by peer\n" );
          break;
          
        default:
          printf( " ssl_read returned -0x%x\n", -ret );
          break;
        }
        
        break;
      }
      
        len += ret;
        

        if( ret > 1 )
            break;
    }
    while( 1 );
    
    printf( " %d bytes read\n\r", len);
    
    /*
    * Write the 200 Response
    */
    printf( "  > Write to client:" );
    
    /* Send the dynamic html page */    
    ssl_DynPage(&ssl);
    goto reset;
    
  exit:
    
#ifdef POLARSSL_ERROR_C
    if( ret != 0 )
    {
      char error_buf[100];
      error_strerror( ret, error_buf, 100 );
      printf("Last error was: %d - %s\n\n", ret, error_buf );
    }
#endif
    
    x509_free( &srvcert );
    rsa_free( &rsa );
    ssl_free( &ssl );
#if defined(POLARSSL_SSL_CACHE_C)
    ssl_cache_free( &cache );
#endif
    
  reset:
    
    if (client_fd != -1)
      net_close(client_fd);
    ssl_session_reset( &ssl );
  }
}           

/**
  * @brief  Create and send a dynamic Web Page.  This page contains the list of 
  *         running tasks and the number of page hits. 
  * @param  ssl the SSL context
  * @retval None
  */
void ssl_DynPage(ssl_context *ssl)
{
  portCHAR buf[2048];
  portCHAR pagehits[10];
  portCHAR getcipher[200];
  uint32_t len = 0;

  memset(buf, 0, 2048);

  /* Update the hit count */
  nPageHits++;
  sprintf( pagehits, "%d", (int)nPageHits );
  sprintf( (char *) getcipher, HTTP_RESPONSE, ssl_get_ciphersuite(ssl));   
  
  /* Generate the dynamic page */
  strcpy(buf, PAGE_START);

  /* Page header */
  strcat(buf, pagehits);
  strcat((char *) buf, "<br><pre>** The list of tasks and their status **");
  strcat((char *) buf, "<br><pre>---------------------------------------------"); 
  strcat((char *) buf, "<br>Name          State  Priority  Stack   Num" );
  strcat((char *) buf, "<br>---------------------------------------------<br>"); 
    
  /* The list of tasks and their status */
  vTaskList((signed char *)buf + strlen(buf));
  strcat((char *) buf, "<br>---------------------------------------------"); 
  strcat((char *) buf, "<br>B : Blocked, R : Ready, D : Deleted, S : Suspended<br><br>");

  /* The current cipher used */
  strcat(buf, getcipher);

  /* Page footer */
  strcat(buf, PAGE_END);
  
  /* Send the dynamically generated page */
  len = ssl_write(ssl, (unsigned char *)buf, strlen(buf));

  /* Display the length of application data */
  printf( "Successfully write %d bytes to client\n\n\r", (int)len);
}

/**
  * @brief  This function is used to send messages with size upper 16k bytes.
  * @param  ssl  SSL context
  * @param  data buffer holding the data
  * @param  len  how many bytes must be written
  * @retval None
  */
void ssl_sendframes( ssl_context *ssl, char *data, int datalen )
{
  int index = 0;
  int k = 0;
  int lastframe, nbrframes;
  
  /* Calculate the number of frames */
  nbrframes = datalen / 16000; 
  
  /* Send nbrframes frames */
  while(nbrframes > 0)
  {
    index = k * 16000;
    ssl_write( ssl, (unsigned char *)(data + index), 16000 );
    nbrframes--;
    k++;
  }
  /* Send the last frame */
  index = k * 16000;
  lastframe = datalen % 16000 ;
  ssl_write( ssl, (unsigned char *)(data + index), lastframe );
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

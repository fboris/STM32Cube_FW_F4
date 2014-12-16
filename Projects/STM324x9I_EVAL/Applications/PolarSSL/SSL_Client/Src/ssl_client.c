/**
  ******************************************************************************
  * @file    PolarSSL/SSL_Client/Src/ssl_client.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   SSL Client main task
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
#include "config.h"
#include "polarssl/net.h"
#include "polarssl/ssl.h"
#include "polarssl/rsa.h"
#include "polarssl/ctr_drbg.h"
#include "polarssl/error.h"
#include "polarssl/certs.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SSL_SERVER_PORT 443 /* Server port number */
#define SSL_SERVER_NAME "192.168.0.1" /* Server address */
#define GET_REQUEST "GET / HTTP/1.0\r\n\r\n" /* HTTP request */

#define DEBUG_LEVEL   1   /* Set DEBUG_LEVEL if you want to enable SSL debug
option, this should be set to 2, 3, 4 or 5 */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* SSL structures */
rng_state rngs;
ssl_context ssl;
ssl_session ssn;

/* Private functions ---------------------------------------------------------*/
void my_debug(void *ctx, int level, const char *str)
{
  if(level < DEBUG_LEVEL)
  {
    printf("%s", str); 
  }
}

/**
  * @brief  SSL client task.
  * @param  pvParameters not used
  * @retval None
  */
void ssl_client(void const * argument)
{
  int ret, len, server_fd;
  unsigned char buf[1024];
  ssl_context ssl;
  x509_cert cacert;
  
  memset( &ssl, 0, sizeof( ssl_context ) );
  memset( &cacert, 0, sizeof( x509_cert ) );
  
  /*
  *  Initialize certificates
  */
  printf( "  . Loading the CA root certificate ..." );
  
#if defined(POLARSSL_CERTS_C)
  ret = x509parse_crt( &cacert, (const unsigned char *) test_ca_crt,
                      strlen( test_ca_crt ) );
#else
  ret = 1;
  printf("POLARSSL_CERTS_C not defined.");
#endif
  
  if( ret < 0 )
  {
    printf( " failed\n  !  x509parse_crt returned -0x%x\n\n", -ret );
    goto exit;
  }
  
  printf( " ok (%d skipped)\n", ret );
  
  /* Start the connection */
  do
  {
    printf(( "\n\rSSL : Start the connection \n\r"));
    printf("\n\rConnecting to tcp/%s/ Port:%4d...", SSL_SERVER_NAME, SSL_SERVER_PORT); 
    
    /* Bint the connection to SSL server port */
    ret = net_connect(&server_fd, SSL_SERVER_NAME, SSL_SERVER_PORT);
    if(ret != 0)
    {
      /* Connection to SSL server failed */
      printf(" failed \n\r ! net_connect returned %d\n\r", -ret);
      
      /* Wait 500 ms until next retry */
      vTaskDelay(500);
    } 
  }while(ret!=0);
  
  printf( " ok\n\r" );
  
  /*
  * 2. Setup stuff
  */
  printf( "  . Setting up the SSL/TLS structure..." );
  
  if( ( ret = ssl_init( &ssl ) ) != 0 )
  {
    printf( " failed\n  ! ssl_init returned %d\n\n\r", ret );
    goto exit;
  }
  
  printf( " ok\n\r" );
  
  ssl_set_endpoint( &ssl, SSL_IS_CLIENT );
  ssl_set_authmode( &ssl, SSL_VERIFY_OPTIONAL );
  ssl_set_ca_chain( &ssl, &cacert, NULL, "PolarSSL Server 1" );
  
  ssl_set_rng( &ssl, RandVal , NULL );
  ssl_set_dbg( &ssl, my_debug, NULL);
  ssl_set_bio( &ssl, net_recv, &server_fd,
              net_send, &server_fd );
  
  /*
  * Handshake
  */
  printf( "  . Performing the SSL/TLS handshake..." );
  
  while( ( ret = ssl_handshake( &ssl ) ) != 0 )
  {
    if( ret != POLARSSL_ERR_NET_WANT_READ && ret != POLARSSL_ERR_NET_WANT_WRITE )
    {
      printf( " failed\n  ! ssl_handshake returned -0x%x\n\n\r", -ret );
      goto exit;
    }
  }
  
  printf( " ok\n\r" );
  
  /*
  * Verify the server certificate
  */
  printf( "\n\r  . Verifying peer X.509 certificate..." );
  
  if( ( ret = ssl_get_verify_result( &ssl ) ) != 0 )
  {
    printf( " failed\n\r" );
    
    if( ( ret & BADCERT_EXPIRED ) != 0 )
      printf( "  ! server certificate has expired\n" );
    
    if( ( ret & BADCERT_REVOKED ) != 0 )
      printf( "  ! server certificate has been revoked\n" );
    
    if( ( ret & BADCERT_CN_MISMATCH ) != 0 )
      printf( "  ! CN mismatch (expected CN=%s)\n", "PolarSSL Server 1" );
    
    if( ( ret & BADCERT_NOT_TRUSTED ) != 0 )
      printf( "  ! self-signed or not signed by a trusted CA\n" );
    
    printf( "\n\r" );
  }
  else
    printf( " ok\n\r" );
  
  /*
  * Write the GET request
  */
  printf( "  > Write to server:" );
  
  len = sprintf( (char *) buf, GET_REQUEST );
  
  while( ( ret = ssl_write( &ssl, buf, len ) ) <= 0 )
  {
    if( ret != POLARSSL_ERR_NET_WANT_READ && ret != POLARSSL_ERR_NET_WANT_WRITE )
    {
      printf( " failed\n  ! ssl_write returned %d\n\n\r", ret );
      goto exit;
    }
  }
  
  len = ret;
  printf( " %d bytes written\n\n\r%s", len, (char *) buf );
  
  /*
  * Read the HTTP response
  */
  printf( "  < Read from server:" );
  
  do
  {
    len = sizeof( buf ) - 1;
    memset( buf, 0, sizeof( buf ) );
    ret = ssl_read( &ssl, buf, len );
    
    if( ret == POLARSSL_ERR_NET_WANT_READ || ret == POLARSSL_ERR_NET_WANT_WRITE )
      continue;
    
    if( ret == POLARSSL_ERR_SSL_PEER_CLOSE_NOTIFY )
      break;
    
    if( ret < 0 )
    {
      printf( "failed\n\r  ! ssl_read returned %d\n\n\r", ret );
      break;
    }
    
    if( ret == 0 )
    {
      printf( "\n\nEOF\n\n\r" );
      break;
    }
    
    len = ret;
    printf( " %d bytes read\n\n\r%s", len, (char *) buf );
  }
  while( 1 );
  
exit:

#ifdef POLARSSL_ERROR_C
  if( ret != 0 )
  {
    char error_buf[100];
    error_strerror( ret, error_buf, 100 );
    printf("Last error was: %d - %s\n\n\r", ret, error_buf );
  }
#endif
  
  x509_free( &cacert );
  net_close( server_fd );
  ssl_free( &ssl );
  
  memset( &ssl, 0, sizeof( ssl ) );
  
  /* Infinite loop */
  for( ;; ) 
  {
    /* Toggle LD1 */
    BSP_LED_Toggle(LED1);
    
    /* Insert 400 ms delay */
    osDelay(400);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


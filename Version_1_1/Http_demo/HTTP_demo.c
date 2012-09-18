/**********************************************************************
* $Id$		main.c					2012-07-02
*//**
* @file		main.c
* @brief	
* @MCU		STM32f107VC
* @version	1.0
* @date		6. Sept. 2012
* @Company   VBEB Corp,.Ltd
* @Website    http://www.vbeb.vn
* @author	Sang Mai - IT Training Assistance - sang.mai@vbeb.vn 
*
* @References:
*
* All rights reserved.
*
***********************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "usart.h"
#include "usart_int.h"
#include "logo_RGB565.h"
#include "GLCD.h"
#include <string.h>
#include <stdio.h>
#include <RTL.h>
#include <Net_Config.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

BOOL tick;
U8 tcp_soc;
U8 soc_state;
BOOL wait_ack;
/* Private macro -------------------------------------------------------------*/
#define RFID_Debug 1;
/* Private variables ---------------------------------------------------------*/
uint8_t SmartCardDataBuffer[12];
/* Private function prototypes -----------------------------------------------*/
void init_display (void);
void delay (unsigned int cnt); 
void send_data (U8 *data_buf, U8 data_length); 
U16 tcp_callback (U8 soc, U8 event, U8 *ptr, U16 par);
/* Private functions ---------------------------------------------------------*/


/************************************************************************
 * @brief 	main function	
 * @param[in]	None
 * @return		None
 ***********************************************************************/
int main(void)
{
	uint16_t i;
	uint16_t ReData;
	SystemInit();
	USART_Config();
	init_display ();

	USART1_Puts("This msg from USART1\n\r");
	USART2_Puts("This msg from USART2\n\r");
	
	tcp_soc = tcp_get_socket (TCP_TYPE_CLIENT, 0, 120, tcp_callback);
  soc_state = 0;
	
	while(1)
	{
#if 0	
		
		ReData = USART2_GetChar();
		//USART2_Puts((unsigned char*)ReData);
		USART_SendData(USART2, ReData);
		
#endif
		
#if 1
		
		
		USART2_Puts("*STS#");
		delay(100);
		GLCD_displayStringLn(Line7, "Sending: *STS#");
		//USART2_SmartCardGet(4); //updating data
		if (USART2_BufferCompare((uint8_t *)"*CP#", 4))
		{
			USART2_Puts("*R0802#");
			
			GLCD_displayStringLn(Line8, "Sending: *R0802#");
			//USART2_SmartCardGet(12); //updating data
			delay(100);
			if (USART2_BufferCompare((uint8_t *)"*RD08024344#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 1");
					break;
				}
			
			if (USART2_BufferCompare((uint8_t *)"*RD08024142#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 2");
					break;
				}
			
			if (USART2_BufferCompare((uint8_t *)"*RD08024143#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 3");
					break;
				}
			
					
			}
#endif		
		}
}
void init_display (void) 
{
  /* LCD Module init */

  GLCD_init();

  GLCD_clear(Navy);
  GLCD_setBackColor(Navy);
  GLCD_setTextColor(White);
    
  GLCD_displayStringLn(Line0, "       VBEB Co.,Ltd");
	GLCD_displayStringLn(Line1, "           -=*=-");
  GLCD_displayStringLn(Line3, "Libarary Management");
	GLCD_displayStringLn(Line4, "      Center");
	GLCD_displayStringLn(Line6, "    Version 1.0");

  GLCD_bitmap (5, 10, 95, 35, VBEBLogo); 

//  upd_display ();

}
void delay (unsigned int cnt) 
{

  unsigned int i,j;  

  for (i=1;i<=cnt; i++)
  	for (j=1;j<10000;j++);
}
void send_data (U8 *data_buf, U8 data_length) 
{
  
  static int bcount;
	//int i;
	U32 max;
  U8 *sendbuf;

  switch (soc_state) {
    case 0:
      //tcp_connect (tcp_soc, rem_IP, 2020, 0);
      bcount    = 0;
      wait_ack  = __FALSE;
      soc_state = 1;
			GLCD_clearLn (Line8);
			GLCD_displayStringLn(Line8, "Connecting...");
      return;
		case 2:
      
			if (wait_ack == __TRUE) 
				{
					return;
				}
			
			if (tcp_check_send (tcp_soc))
				{
      
					sendbuf = tcp_get_buf (data_length);
      
			
					memcpy (sendbuf, data_buf, data_length);
					tcp_send (tcp_soc, sendbuf, data_length);
			
					GLCD_clearLn (Line8);
					GLCD_displayStringLn(Line8, "Message Sent");
					wait_ack = __TRUE;
					return;
				}
			case 3:
      if (wait_ack == __TRUE) {
        return;
      }
      tcp_close (tcp_soc);
      soc_state = 4;
      return;
  }
}
U16 tcp_callback (U8 soc, U8 event, U8 *ptr, U16 par) 
{
  /* This function is called on TCP event */
	U8 data_get,i;
	unsigned char databuff[8];
	
  switch (event) {
     
    case TCP_EVT_CONNECT:
      /* Socket is now connected and ready to send data. */
      soc_state = 2;
      break;
    case TCP_EVT_ACK:
      /* Our sent data has been acknowledged by remote peer */
      wait_ack = __FALSE;
      break;
		case TCP_EVT_DATA:
      /* TCP data frame has been received, 'ptr' points to data */
      /* Data length is 'par' bytes */
      data_get = *ptr;
			
			for ( i=0; i <=8; i++)
				{
					databuff[i] = data_get++;
				}
			GLCD_clearLn (Line9);
			GLCD_displayStringLn(Line9, (unsigned char *) databuff);
		
      break;
       
		
  }
  return (0);
}
	
/*----------------------------------------------------
*-------------------End of Code-----------------------
*----------------------------------------------------*/

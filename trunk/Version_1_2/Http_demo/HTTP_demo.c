/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    HTTP_DEMO.C
 *      Purpose: HTTP Server demo example
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <RTL.h>
#include <Net_Config.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "usart.h"
#include "usart_int.h"
#include "GLCD.h"
#include "logo_RGB565.h"
#include <string.h>

BOOL LEDrun;
BOOL LCDupdate;
BOOL tick;
U32  dhcp_tout;
U8 tcp_soc;
U8 soc_state;
BOOL wait_ack;
U8   lcd_text[2][16+1] = {" ",                /* Buffer for LCD text         */
                          "Waiting for DHCP"};

#define CONNECTED 1
#define DISCONNECTED 0
#define NOT_YET 0
#define FINISHED 1
#define YES 1
#define NO 0

uint8_t connection_Flag,DATA_SENT, CARD_INSERT,time;

char *data1_buf = "Hello The World!!";
static U8 rem_IP[4] = {192,168,1,20};
extern LOCALM localm[];                       /* Local Machine Settings      */
#define MY_IP localm[NETIF_ETH].IpAdr
#define DHCP_TOUT   50                        /* DHCP timeout 5 seconds      */
#define msgLength 5
extern uint16_t ASCII_Table[];

static void init_io (void);
void init_display (void);
void send_data (U8 *data_buf, U8 data_length); 
U16 tcp_callback (U8 soc, U8 event, U8 *ptr, U16 par);
/*--------------------------- init ------------------------------------------*/

static void init () {
  /* Add System initialisation code here */ 

  init_io ();
  init_display ();
  init_TcpNet ();
	USART_Config();
  /* Setup and enable the SysTick timer for 100ms. */
  SysTick->LOAD = (25000000 / 10) - 1;
  SysTick->CTRL = 0x05;
}



/*--------------------------- timer_poll ------------------------------------*/

static void timer_poll () {
  /* System tick timer running in poll mode */

  if (SysTick->CTRL & 0x10000) {
    /* Timer tick every 100 ms */
    timer_tick ();
    tick = __TRUE;
  }
}

void delay (unsigned int cnt) 
{

  unsigned int i,j;  

  for (i=1;i<=cnt; i++)
  	for (j=1;j<10000;j++);
}
/*--------------------------- init_io ---------------------------------------*/

static void init_io () {

  /* Set the clocks. */
  SystemInit();
  RCC->APB2ENR |= 0x00000279;

  /* Configure the GPIO for Push Buttons */
  GPIOB->CRH &= 0xFFFFFF0F;
  GPIOB->CRH |= 0x00000040;
  GPIOC->CRH &= 0xFFF0FFFF;
  GPIOC->CRH |= 0x00040000;

  /* Configure the GPIO for LEDs. */
  GPIOD->CRL &= 0xFFF00FFF;
  GPIOD->CRL |= 0x00033000;
  GPIOD->CRH &= 0xFF0FFFFF;
  GPIOD->CRH |= 0x00300000;
  GPIOE->CRH &= 0xF0FFFFFF;
  GPIOE->CRH |= 0x03000000;

 
}


/*--------------------------- fputc -----------------------------------------*/

int fputc (int ch, FILE *f)  {
  /* Debug output to serial port. */

  if (ch == '\n')  {
    while (!(USART2->SR & 0x0080));
    USART2->DR = 0x0D;
  }
  while (!(USART2->SR & 0x0080));
  USART2->DR = (ch & 0xFF);
  return (ch);
}



/*--------------------------- get_button ------------------------------------*/

U8 get_button (void) 
{
  /* Read ARM Digital Input */
  U32 val = 0;

  if ((GPIOB->IDR & (1 << 9)) == 0) {
    /* Key button */
    //val |= 0x01;
		val =1;
		
  }
  if ((GPIOC->IDR & (1 << 13)) == 0) {
    /* Wakeup button */
    //val |= 0x02;
		val =2; 
  }
  return (val);
}


/*--------------------------- blink_led -------------------------------------*/

static void blink_led () 
{
  /* Blink the LEDs on an eval board */
  const U8 led_val[8] = { 0x01,0x03,0x07,0x0F,0x0E,0x0C,0x08,0x00 };
  static U32 cnt;

  if (tick == __TRUE) {
    /* Every 100 ms */
    tick = __FALSE;
    if (LEDrun == __TRUE) {
      LED_out (led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0;
      }
    }
    if (LCDupdate == __TRUE) {
      //upd_display ();
    }
  }
}

/*---------------------------------------------------------------------------*/

int main (void) 
{
  /* Main Thread of the TcpNet */
	int i=1;
	U32 buttonget;
  init ();
	
 // printf ("Program started\n");
  //LEDrun = __TRUE;
  ///dhcp_tout = DHCP_TOUT;

  tcp_soc = tcp_get_socket (TCP_TYPE_CLIENT, 0, 120, tcp_callback);
  soc_state = 0;
	USART1_Puts("This msg from USART1\n\r");
	//USART2_Puts("This msg from USART2\n\r");
	//tcp_connect (tcp_soc, rem_IP, 2020, 0);
	//send_datalog ();
	//send_data ();
	while (1) 
		{
			timer_poll ();
			main_TcpNet ();
			buttonget = get_button();
			tcp_connect (tcp_soc, rem_IP, 2013, 0);
								
#if 1
						
		if ( buttonget == 2)
			{
				
				//tcp_connect (tcp_soc, rem_IP, 2020, 0);
			  send_data ("SANG",4);
				
			}
			
		//USART2_Puts("*STS#");
		//delay(200);
		//GLCD_displayStringLn(Line7, "Sending: *STS#");
			GLCD_displayStringLn(Line7, "Starting...");
		if (SmartCard_DataCompare((uint8_t *)"*CP#", 4))
		{
			USART2_Puts("*R0802#");
			CARD_INSERT = YES;
			GLCD_clearLn(Line8);
			GLCD_displayStringLn(Line8, "CARD INSERTED");
			
			//GLCD_displayStringLn(Line8, "Sending: *R0802#");
			delay(200);
			
			if (SmartCard_DataCompare((uint8_t *)"*RD08024344#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "RD08024344");
					//tcp_connect (tcp_soc, rem_IP, 2020, 0);
					send_data ("RD08024344",10);
					delay(200);
					
					}
					
					//break;
				
			
			if (SmartCard_DataCompare((uint8_t *)"*RD08024142#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "RD08024142");
					//tcp_connect (tcp_soc, rem_IP, 2020, 0);
					send_data ("RD08024142",10);
					delay(200);
					//while (SmartCard_DataCompare((uint8_t *)"*CR#", 4) == 0); //waiting until card is removed
					//break;
				}
			
			if (SmartCard_DataCompare((uint8_t *)"*RD08024143#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 3");
					//tcp_connect (tcp_soc, rem_IP, 2020, 0);
					send_data ("RD08024143",10);
					delay(200);
					//while (SmartCard_DataCompare((uint8_t *)"*CR#", 4) == 0); //waiting until card is removed
					//break;
				}
			
					
			}
			
#endif
			
				if (RFID_DataCompare((uint8_t *)"4C00A1F41F", 10))
				{
				GLCD_clearLn(Line9);
				GLCD_displayStringLn(Line9, "4C00A1F41F");
				//tcp_connect (tcp_soc, rem_IP, 2020, 0);
				send_data ("4C00A1F41F",10);
				delay(200);
				}
				if (RFID_DataCompare((uint8_t *)"4C00A1F42A", 10))
				{
				GLCD_clearLn(Line9);
				GLCD_displayStringLn(Line9, "4C00A1F42A");
				//tcp_connect (tcp_soc, rem_IP, 2020, 0);
				send_data ("4C00A1F42A",10);
				delay(200);
				}
				if (RFID_DataCompare((uint8_t *)"4C00A1F429", 10))
				{
				GLCD_clearLn(Line9);
				GLCD_displayStringLn(Line9, "4C00A1F429");
				//tcp_connect (tcp_soc, rem_IP, 2020, 0);
				send_data ("4C00A1F429",10);
				delay(200);
				}
			
	  }
}

void send_data (U8 *data_buf, U8 data_length) 
{
  
  static int bcount;
	//int i;
	U32 max;
  U8 *sendbuf;
	U8 Blank[10] ="          ";
	

  switch (soc_state) {
    case 0:
      //tcp_connect (tcp_soc, rem_IP, 2020, 0);
      bcount    = 0;
      wait_ack  = __FALSE;
      soc_state = 1;
			DATA_SENT = NOT_YET;
			//connection_Flag = DISCONNECTED;
			//GLCD_clearLn (Line8);
			//GLCD_displayStringLn(Line8, "Connecting...");
      return;
		case 2:
      
			if (wait_ack == __TRUE) 
				{
					return;
				}
			
			if (tcp_check_send (tcp_soc))
				{
      
					sendbuf = tcp_get_buf (data_length);
      
					//memcpy (sendbuf, Blank, 10); //clear 10 character
					
					memcpy (sendbuf, data_buf, data_length);
					tcp_send (tcp_soc, sendbuf, data_length);
					DATA_SENT = FINISHED;
					//GLCD_clearLn (Line8);
					//GLCD_displayStringLn(Line8, "Message Sent");
					//connection_Flag = CONNECTED;
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
void init_display (void) 
{
  /* LCD Module init */

  GLCD_init();

  GLCD_clear(Navy);
  GLCD_setBackColor(Navy);
  GLCD_setTextColor(White);
    
  GLCD_displayStringLn(Line0, "       VBEB Co.,Ltd");
	GLCD_displayStringLn(Line1, "           -=*=-");
  //GLCD_displayStringLn(Line3, "Libarary Management");
	//GLCD_displayStringLn(Line4, "      Center");
	GLCD_displayStringLn(Line6, "    Version 1.0");

  GLCD_bitmap (5, 10, 95, 35, VBEBLogo); 

//  upd_display ();

}			

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

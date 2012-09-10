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


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define RFID_Debug 1;
/* Private variables ---------------------------------------------------------*/
uint8_t SmartCardDataBuffer[12];
/* Private function prototypes -----------------------------------------------*/
void init_display (void);

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
	
	
	while(1)
	{
#if 0	
		
		ReData = USART2_GetChar();
		//USART2_Puts((unsigned char*)ReData);
		USART_SendData(USART2, ReData);
		
#endif
		
#if 1
		
		
		USART2_Puts("*STS#");
		
		GLCD_displayStringLn(Line7, "Sending: *STS#");
		USART2_SmartCardGet(4); //updating data
		if (USART2_BufferCompare((uint8_t *)"*CP#", 4))
		{
			USART2_Puts("*R0802#");
			
			GLCD_displayStringLn(Line8, "Sending: *R0802#");
			USART2_SmartCardGet(12); //updating data
			if (USART2_BufferCompare((uint8_t *)"*RD08024344#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 1");
					//break;
				}
			
			if (USART2_BufferCompare((uint8_t *)"*RD08024142#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 2");
					//break;
				}
			
			if (USART2_BufferCompare((uint8_t *)"*RD08024143#", 12))
				{
					GLCD_clearLn(Line9);
					GLCD_displayStringLn(Line9, "Person 3");
					//break;
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
  GLCD_displayStringLn(Line3, "Libarary Management");
	GLCD_displayStringLn(Line4, "      Center");
	GLCD_displayStringLn(Line6, "    Version 1.0");

  GLCD_bitmap (5, 10, 95, 35, VBEBLogo); 

//  upd_display ();

}

/*----------------------------------------------------
*-------------------End of Code-----------------------
*----------------------------------------------------*/

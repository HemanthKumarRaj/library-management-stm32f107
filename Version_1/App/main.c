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


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

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
	SystemInit();
	USART_Config();
	init_display ();

	USART1_Puts("This msg from USART1\n\r");
	USART2_Puts("This msg from USART2\n\r");
	
	while(1)
	{
		
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

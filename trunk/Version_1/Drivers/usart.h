/**********************************************************************
* $Id$		usart.h					2012-07-02
*//**
* @file		usart.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void USART_Config(void);
void USART1_Puts(unsigned char *data);
void USART2_Puts(unsigned char *data);

#endif
/*----------------------------------------------------
*-------------------End of File-----------------------
*----------------------------------------------------*/


/**********************************************************************
* $Id$		usart_int.h					
*//**
* @file		usart_int.h
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
#ifndef _USART_INT_H_
#define _USART_INT_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
uint16_t USART2_BufferCompare(uint8_t *data, uint8_t length);
uint16_t USART1_GetChar(void);

#endif
/*----------------------------------------------------
*-------------------End of Code-----------------------
*----------------------------------------------------*/

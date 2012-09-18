/**********************************************************************
* $Id$		usart.c					2012-07-02
*//**
* @file		usart.c
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

#include "usart.h"
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USART1_BaudRate 9600;
#define USART2_BaudRate 9600;
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


void USART_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	
	
	/* enable peripheral clock for USART1 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  /* GPIOA,GPIOD clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	
	
	//RCC_PCLK2Config(RCC_HCLK_Div16);
	
	
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  /* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	/* GPIOA Configuration:  USART1  */
 
	/* Configure PA10 for USART1 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure PA9 for USART1 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	/* GPIOD Configuration:  USART2  */
	
	/* Configure PD6 for USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* Configure PD5 for USART2 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	
		
	/* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - Two Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = USART1_BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);
	
	
	/* USART2 configuration ------------------------------------------------------*/
  /* USART2 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - Two Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = USART2_BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART2, &USART_InitStructure);
	

  /* Enable the USART1 Receive interrupt: this interrupt is generated when the 
     USART1 receive data register is not empty */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* Enable the USART1 Receive interrupt: this interrupt is generated when the 
     USART2 receive data register is not empty */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	/* Enable the USART1 Transmit interrupt: this interrupt is generated when the 
     USART1 transmit data register is empty */  
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);
	/* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);
	
	/*Clear USART1 interrupt flag*/
	USART_ClearFlag(USART1, USART_FLAG_TC);
	/*Clear USART2 interrupt flag*/
	USART_ClearFlag(USART2, USART_FLAG_TC);
}

void USART1_Puts(unsigned char *data)
{
	int i=0;
	for (i = 0; data[i] != '\0'; i++)
	{
		  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
			USART_SendData( USART1, data[i]);
	}
}

void USART2_Puts(unsigned char *data)
{
	int i=0;
	for (i = 0; data[i] != '\0'; i++)
	{
		  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
			USART_SendData( USART2, data[i]);
	}
}
/*----------------------------------------------------
*-------------------End of Code-----------------------
*----------------------------------------------------*/


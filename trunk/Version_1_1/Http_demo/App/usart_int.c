/**********************************************************************
* $Id$		usart_int.c					
*//**
* @file		usart_int.c
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
#include "usart_int.h"
#include "stm32f10x_conf.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define TxBufferSize   (countof(TxBuffer) - 1)
#define RxBufferSize1   0x20
#define RxBufferSize2   0x20
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define rxBufferSize1 8
#define rxBufferSize2 8
/* Private variables ---------------------------------------------------------*/

uint8_t RxBuffer1[RxBufferSize1];
uint8_t RxBuffer2[RxBufferSize2];
uint8_t NbrOfDataToRead1 = RxBufferSize1;
uint16_t RxCounter1 = 0; 
uint8_t NbrOfDataToRead2 = RxBufferSize2;
uint16_t RxCounter2 = 0;
uint8_t rxBufferOverflow1;
uint16_t rxBuffer1[rxBufferSize1];
uint16_t rxWriteIndex1, rxReadIndex1, rxCounter1;
uint8_t rxBufferOverflow2;
uint16_t rxBuffer2[rxBufferSize2];
uint16_t rxWriteIndex2, rxReadIndex2, rxCounter2;

uint8_t ReceiveData1,ReceiveData2,rxIndex ;

uint8_t Buffer_Data[12];
extern uint8_t SmartCardDataBuffer[12];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            STM32F107 Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */

void USART1_IRQHandler(void) //USART1_IRQHandler
{

  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Wait for Char
  {
    ReceiveData1 = (USART_ReceiveData(USART1)  & 0x7F ); // Collect Char
    rxBuffer1[rxWriteIndex1] = ReceiveData1;
    if (++rxWriteIndex1 == rxBufferSize1) rxWriteIndex1 = 0;
   if (++rxCounter1 == rxBufferSize1)
      {
      rxCounter1 = 0;
      rxBufferOverflow1 = 1;
			
      }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  }
    
     
}
/**
  * @brief   
  * @param  None
  * @retval None
  */
uint16_t USART1_GetChar(void)
{
  uint16_t data;
  while (rxCounter1==0);
  data = rxBuffer1[rxReadIndex1];
  if (++rxReadIndex1 == rxBufferSize1) rxReadIndex1=0;
  --rxCounter1;
  return data;
}

uint16_t USART2_GetChar(void)
{
  uint16_t data;
  while (rxCounter2 == 0);
  data = rxBuffer2[rxReadIndex2];
  if (++rxReadIndex2 == rxBufferSize2) rxReadIndex2=0;
  --rxCounter2;
  return data;
}

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */

void USART2_IRQHandler(void) //USART1_IRQHandler
{

  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // Wait for Char
  {
    ReceiveData2 = (USART_ReceiveData(USART2)  & 0x7F ); // Collect Char
    //rxBuffer2[rxWriteIndex2] = ReceiveData2;
		Buffer_Data[rxIndex] = ReceiveData2;
		//USART_SendData( USART1,Buffer_Data[rxIndex]);
		rxIndex++;
		if (Buffer_Data[rxIndex-1] == '#')
		{
			rxIndex = 0;
		}
		
    //if (++rxWriteIndex2 == rxBufferSize2) rxWriteIndex2 = 0;
    if (++rxCounter2 == rxBufferSize2)
      {
      rxCounter2 = 0;
      rxBufferOverflow2 = 1;
			
      }
			
    USART_ClearITPendingBit(USART2,USART_IT_RXNE);
  }
    
     
}
/**
  * @brief   
  * @param  None
  * @retval None
  */

uint16_t USART2_BufferCompare(uint8_t *data, uint8_t length)
{
  uint8_t i=0;
	
	//rxReadIndex2 = 0;
  while (length > 0 )
	{
		
			//Buffer_Data[i] = USART2_GetChar();
				
			if(*data != Buffer_Data[i]) 
        return 0;
			//USART_SendData( USART1,Buffer_Data[i]);
			--length;
			data++;
			i++;
	}

	if(length ==0 )
      return 1; 
    else
      return 0;	
		
		
	}
/**
  * @brief   
  * @param  None
  * @retval None
  */
void USART2_SmartCardGet(uint8_t length)
{
  uint8_t i=0;
	
	//rxReadIndex2 = 0;
	while (length > 0)
	{
		Buffer_Data[i] = USART2_GetChar();
		//USART_SendData( USART1, Buffer_Data[i]);
		--length;
		i++;
	}		
		
	}
/*----------------------------------------------------
*-------------------End of Code-----------------------
*----------------------------------------------------*/

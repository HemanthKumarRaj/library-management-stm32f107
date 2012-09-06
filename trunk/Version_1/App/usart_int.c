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

uint16_t Data;
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
    Data = (USART_ReceiveData(USART1)  & 0x7F ); // Collect Char
    rxBuffer1[rxWriteIndex1] = Data;
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

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */

void USART2_IRQHandler(void) //USART1_IRQHandler
{

  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // Wait for Char
  {
    Data = (USART_ReceiveData(USART2)  & 0x7F ); // Collect Char
    rxBuffer2[rxWriteIndex2] = Data;
    if (++rxWriteIndex2 == rxBufferSize2) rxWriteIndex2 = 0;
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
uint16_t USART2_GetChar(void)
{
  uint16_t data;
  while (rxCounter2==0);
  data = rxBuffer2[rxReadIndex2];
  if (++rxReadIndex2 == rxBufferSize2) rxReadIndex2=0;
  --rxCounter2;
  return data;
}

/*----------------------------------------------------
*-------------------End of Code-----------------------
*----------------------------------------------------*/


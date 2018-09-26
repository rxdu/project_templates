#ifndef  MODULES_DEBUG_USART_H_
#define  MODULES_DEBUG_USART_H_
//----------------------------------------------
#include "stm32f10x_usart.h"

//----------------------------------------------
#define USART_DEBUG                                 USART1
#define USART_DEBUG_GPIO                        GPIOA
#define USART_DEBUG_CLK                         RCC_APB2Periph_USART1
#define USART_DEBUG_GPIO_CLK                RCC_APB2Periph_GPIOA
#define USART_DEBUG_RxPin                       GPIO_Pin_10
#define USART_DEBUG_TxPin                       GPIO_Pin_9
#define USART_DEBUG_IRQn                       USART1_IRQn
#define USART_DEBUG_Tx_DMA_Channel     DMA1_Channel4
#define USART_DEBUG_Tx_DMA_FLAG         DMA1_FLAG_TC4
#define USART_DEBUG_DR_Base                 0x40013804
//-----------------------------------------------
void DEBUG_UsartInit(void);

#endif /* MODULES_DEBUG_USART_H__ */

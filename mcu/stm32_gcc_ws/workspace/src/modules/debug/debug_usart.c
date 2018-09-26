


#include "debug_usart.h"


//-----------------------------------------------------
USART_InitTypeDef USART_InitStructure;

/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
uint8_t TxBuffer1[] = "USART DMA Interrupt: USARTy -> USARTz using DMA Tx and Rx Flag";
uint8_t TxBuffer2[] = "USART DMA Interrupt: USARTz -> USARTy using DMA Tx and Rx Interrupt";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint8_t NbrOfDataToRead = TxBufferSize1;
uint32_t index = 0;
//-------------------------------------------------------
void USARTInit(void)
{
/* USART_DEBUG and USARTz configuration -------------------------------------------*/
  /* USART_DEBUG and USARTz configured as follow:
        - BaudRate = 230400 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART_DEBUG */
  USART_Init(USART_DEBUG, &USART_InitStructure);

  /* Enable USART_DEBUG DMA TX request */
  //USART_DMACmd(USART_DEBUG, USART_DMAReq_Tx, ENABLE);

  /* Enable USART_DEBUG */
  USART_Cmd(USART_DEBUG, ENABLE);


  /* Enable USART_DEBUG DMA TX Channel */
  //DMA_Cmd(USART_DEBUG_Tx_DMA_Channel, ENABLE);

}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* DMA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USART_DEBUG_GPIO_CLK  | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USART_DEBUG Clock */
  RCC_APB2PeriphClockCmd(USART_DEBUG_CLK, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure USART_DEBUG Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USART_DEBUG_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USART_DEBUG_GPIO, &GPIO_InitStructure);

  /* Configure USART_DEBUG Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART_DEBUG_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USART_DEBUG_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
   NVIC_InitTypeDef NVIC_InitStructure;

  //Enable the USARTz Interrupt
  NVIC_InitStructure.NVIC_IRQChannel = USART_DEBUG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures the DMA.
  * @param  None
  * @retval None
  */
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  /* USART_DEBUG_Tx_DMA_Channel (triggered by USART_DEBUG Tx event) Config */
  DMA_DeInit(USART_DEBUG_Tx_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DEBUG_DR_Base;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(USART_DEBUG_Tx_DMA_Channel, &DMA_InitStructure);

}

void DEBUG_UsartInit(void)
{

  /* System Clocks Configuration */
  RCC_Configuration();

  /* NVIC configuration */
  NVIC_Configuration();

  /* Configure the GPIO ports */
  GPIO_Configuration();

  /* Configure the DMA */
  //DMA_Configuration();

  USARTInit();
  //USART_ITConfig(USART_DEBUG, USART_IT_TXE, ENABLE);
}

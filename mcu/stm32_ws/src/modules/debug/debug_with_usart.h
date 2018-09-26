/*
*********************************************************************************************************
*                                      wysdhl2005/ModeBus Communication
*
*                           (c) Copyright 2011; wysdhl2005, NCEPU.; BaoDing , hebei
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*
*                                      wysdhl2005/ModeBus
*
*                                      Communication: RS-232
*                                      Port for the ST STM32
*
* Filename      : Debug_With_Usart.h
* Version       : V1.0
* Programmer(s) : wysdhl2005 ����������ѧ ��������ϵ ����ʤ
*********************************************************************************************************
*/

#ifndef  MODULES_DEBUG_DEBUG_WITH_USART_H_
#define  MODULES_DEBUG_DEBUG_WITH_USART_H_

#include "xprintf.h"
#include "stm32f10x.h"
#include "debug_usart.h"
//typedef unsigned long     uint32_t;

#define xDEBUG

#ifdef  xDEBUG
#define DEBUG_READ     0x00000001
#define DEBUG_ERROR    0x00000002
#define DEBUG_PROGRAM  0x00000004
#define DEBUG_ERASE    0x00000008
#define DEBUG_ID       0x00000010
#define DEBUG_MAP      0x00000020
#define DEBUG_ECC      0x00000040
#define DEBUG_ADDR     0x00000080
#define DEBUG_BLKCHK   0x00000100
#define DEBUG_INFOR    0x00000200
#define DEBUG_WAIT     0x00000400
#define DEBUG_TEST     0x00000800
#define DEBUG_ALWAYS   0xffffffff


#define debug          (DEBUG_ERROR | DEBUG_INFOR | DEBUG_TEST)

#define DEBUG_PRINT(mask, string) \
        if ((debug & mask) || (mask == DEBUG_ALWAYS)) \
                xprintf  string

#else
    #define DEBUG_PRINT(mask, string)

#endif

typedef enum
{
  NotNull = 0,
  Null = !NotNull,
}DebugBufferStatus;

/*--------debug------*/
#define UsartTxIRQEnable        USART_ITConfig(USART_DEBUG, USART_IT_TXE, ENABLE)
#define UsartTxIRQDisable           USART_ITConfig(USART_DEBUG, USART_IT_TXE, DISABLE)
#define UsartRxIRQEnable        USART_ITConfig(USART_DEBUG, USART_IT_RXNE, ENABLE)
#define UsartRxIRQDisable           USART_ITConfig(USART_DEBUG, USART_IT_RXNE, DISABLE)

#define IsUsartRxIRQFlag            (USART_GetITStatus(USART_DEBUG, USART_IT_RXNE) != RESET)
#define IsUsartTxIRQFlag            (USART_GetITStatus(USART_DEBUG, USART_IT_TXE) != RESET)
#define ClearUsartRxIRQFlag     USART_ClearITPendingBit(USART_DEBUG, USART_IT_RXNE)                     /* Clear the USART1 Receive interrupt*/
#define ClearUsartTxIRQFlag     USART_ClearITPendingBit(USART_DEBUG, USART_IT_TXE)                       /* Clear the USART1 transmit interrupt                      */

#define Func_UsartIRQ                   USART1_IRQHandler
#define UsartReceiveByte(data)        data = USART_ReceiveData(USART_DEBUG)
#define UsartSendByte(data)     USART_SendData(USART_DEBUG,data)

void DebugUsartInit(void);
DebugBufferStatus CheckDebugBufferIsNull(void);  /* ����DBUG�������Ƿ�Ϊ�� */
/*---------------------*/
extern void (*USART_SendByte)(unsigned char);
void USART_SendString(unsigned char *str);
void USART_SendHex(unsigned char bSentData);
void PrintBuffer(unsigned char *bpPrintBuffer, unsigned char bLength);
void USART_Send32Dec(long  lLong);
/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif /* MODULES_DEBUG_DEBUG_WITH_USART_H_ */

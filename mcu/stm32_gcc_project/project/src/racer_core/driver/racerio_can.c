/* 
 * racerio_can.c
 * 
 * Created on: Feb 18, 2018 00:49
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "racerio_can.h"

#include <string.h>

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_can.h"

#include "racerio.h"

#define CANx CAN2
#define CAN_CLK (RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2)
#define CAN_RX_IT_FMP CAN_IT_FMP0
#define CAN_RX_FIFO CAN_FIFO0
#define CAN_RX_IRQN CAN2_RX0_IRQn

#define CAN_GPIO_PORT GPIOB
#define CAN_GPIO_CLK RCC_AHB1Periph_GPIOB
#define CAN_AF_PORT GPIO_AF_CAN2
#define CAN_RX_PIN GPIO_Pin_12
#define CAN_TX_PIN GPIO_Pin_13
#define CAN_RX_SOURCE GPIO_PinSource12
#define CAN_TX_SOURCE GPIO_PinSource13

static void RACERIO_InitCANGPIO(void);
static void RACERIO_InitCANNVIC(void);

void CAN2_RX0_IRQHandler();

// PB12 - CAN2_RX, PB13 - CAN2_TX
void RACERIO_InitCAN()
{
    RACERIO_InitCANGPIO();

    /* CAN configuration ********************************************************/
    /* Enable CAN clock */
    RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

    /* CAN register init */
    CAN_DeInit(CANx);

    CAN_InitTypeDef CAN_InitStructure;

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;

    /* CAN Baudrate = 1 MBps (APB1 at 42HHz, CAN clocked at 14 MHz) */
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //CAN_Mode_LoopBack or CAN_Mode_Normal
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
    CAN_InitStructure.CAN_Prescaler = 3;
    CAN_Init(CANx, &CAN_InitStructure);

    /* CAN filter init */
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    CAN_FilterInitStructure.CAN_FilterNumber = 14;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    /* NVIC */
    RACERIO_InitCANNVIC();

    /* Enable FIFO 0 message pending Interrupt */
    CAN_ITConfig(CANx, CAN_RX_IT_FMP, ENABLE);
}

void RACERIO_InitCANGPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* CAN GPIOs configuration **************************************************/

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK, ENABLE);

    /* Connect CAN pins to AF9 */
    GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
    GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_TX_SOURCE, CAN_AF_PORT);

    /* Configure CAN RX and TX pins */
    GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN | CAN_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);
}

void RACERIO_InitCANNVIC(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = RACERIO_IRQ_PRIO_HIGHEST;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * RACERIO_CAN_TxCANFrame transmits a data message with a specified ID
 * @param[in] id the CAN device ID
 * @param[in] msg_id The message ID (std ID < 0x7FF)
 * @param[in] data Pointer to data message
 * @returns number of bytes sent if successful, -1 if not
 */
int32_t RACERIO_CAN_TxCANFrame(uint32_t id, bool is_id_ext, const uint8_t *data, uint8_t data_len)
{
    // Format and send the message
    CanTxMsg msg;

    if (is_id_ext)
    {
        msg.StdId = 0;
        msg.ExtId = id;
        msg.IDE = CAN_ID_EXT;
    }
    else
    {
        msg.StdId = id & 0x7FF;
        msg.ExtId = 0;
        msg.IDE = CAN_ID_STD;
    }
    msg.RTR = CAN_RTR_DATA;
    msg.DLC = (data_len > 8) ? 8 : data_len;
    memcpy(msg.Data, data, msg.DLC);
    CAN_Transmit(CANx, &msg);

    return msg.DLC;
}

void CAN2_RX0_IRQHandler()
{
    CanRxMsg RxMessage;
    CAN_Receive(CANx, CAN_RX_FIFO, &RxMessage);

    uint32_t uavcan_id = 0;
    if (RxMessage.IDE == CAN_Id_Standard)
        uavcan_id = RxMessage.StdId;
    else
        uavcan_id = RxMessage.ExtId;
    (void)uavcan_id;

    JLinkRTTPrintf(0, "CAN msg received id: %d, data: %d, %d, %d\n", uavcan_id, RxMessage.Data[0], RxMessage.Data[1], RxMessage.Data[2]);

    // portEND_SWITCHING_ISR(pdTRUE);
}
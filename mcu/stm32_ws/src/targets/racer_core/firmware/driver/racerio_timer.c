/* 
 * racerio_timer.c
 * 
 * Created on: Feb 17, 2018 23:45
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "racerio_timer.h"

#include "stm32f4xx_tim.h"
#include "misc.h"

#include "racerio.h"
#include "racerio_driver.h"

static void RACERIO_InitTimerGPIO();
static void RACERIO_InitTimerClock();

// Interrupt handler
void TIM5_IRQHandler(void);

void RACERIO_InitTimerGPIO()
{
    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* Configure timer GPIOs */
    GPIO_InitTypeDef encoder_gpio;
    encoder_gpio.GPIO_Pin = GPIO_Pin_0;
    encoder_gpio.GPIO_Speed = GPIO_Speed_2MHz;
    encoder_gpio.GPIO_Mode = GPIO_Mode_AF;
    encoder_gpio.GPIO_OType = GPIO_OType_PP;
    encoder_gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &encoder_gpio);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);

    encoder_gpio.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &encoder_gpio);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

    encoder_gpio.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &encoder_gpio);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
}

void RACERIO_InitTimerClock()
{
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    /* Configure the dividers for this timer */
    TIM_TimeBaseInitTypeDef encoder_timer_base;
    encoder_timer_base.TIM_Prescaler = (uint16_t)((SystemCoreClock / 2) / 1000000) - 1;
    encoder_timer_base.TIM_CounterMode = TIM_CounterMode_Up;
    encoder_timer_base.TIM_Period = 0xFFFF;
    encoder_timer_base.TIM_ClockDivision = TIM_CKD_DIV1;
    encoder_timer_base.TIM_RepetitionCounter = 0x0000;
    TIM_TimeBaseInit(TIM5, &encoder_timer_base);

    /* Configure internal timer clocks */
    TIM_InternalClockConfig(TIM5);

    /* Enable timers */
    // TIM_Cmd(TIM5, ENABLE);

    /* Enable Interrupts */
    NVIC_InitTypeDef encoder_nvic;
    encoder_nvic.NVIC_IRQChannel = TIM5_IRQn;
    encoder_nvic.NVIC_IRQChannelPreemptionPriority = RACERIO_IRQ_PRIO_MID;
    encoder_nvic.NVIC_IRQChannelSubPriority = 0;
    encoder_nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&encoder_nvic);
}

void RACERIO_InitHallSensorInterface()
{
    /* Disable timer for more configurations */
    TIM_Cmd(TIM5, DISABLE);

    /* Configure GPIO and Timer clock */
    RACERIO_InitTimerGPIO();
    RACERIO_InitTimerClock();

    /* Enable hall sensor interface */
    TIM_SelectHallSensor(TIM5, ENABLE);

    /* Select slave input trigger */
    TIM_SelectInputTrigger(TIM5, TIM_TS_TI1F_ED);
    TIM_SelectSlaveMode(TIM5, TIM_SlaveMode_Reset);

    /* Config input capture channel */
    TIM_ICInitTypeDef encoder_ic;
    encoder_ic.TIM_ICPolarity = TIM_ICPolarity_BothEdge,
    encoder_ic.TIM_ICSelection = TIM_ICSelection_TRC,
    encoder_ic.TIM_ICPrescaler = TIM_ICPSC_DIV1,
    encoder_ic.TIM_ICFilter = 0x0,
    encoder_ic.TIM_Channel = TIM_Channel_1,
    TIM_ICInit(TIM5, &encoder_ic);

    /* Enable the Capture Compare Interrupt Request */
    TIM_ITConfig(TIM5, TIM_IT_Trigger, ENABLE);
    // TIM_ITConfig(TIM5, TIM_IT_Trigger | TIM_IT_Update, ENABLE);
    // TIM_ITConfig(TIM5, TIM_IT_CC1 | TIM_IT_Trigger | TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM5, ENABLE);
}

void TIM5_IRQHandler(void)
{
    // Encoder
    if (TIM_GetITStatus(TIM5, TIM_IT_Trigger) == SET)
    {
        /* Read the current counter */
        TIM_ClearITPendingBit(TIM5, TIM_IT_Trigger);
        // AutoCarUpdateHallsensorData(TIM_GetCapture1(timer));
        JLinkRTTPrintf(0, "Capture: %d\n", TIM_GetCapture1(TIM5));
    }

    // JLinkRTTPrintf(0, "TIM5 IT: %d\n", 0);
}
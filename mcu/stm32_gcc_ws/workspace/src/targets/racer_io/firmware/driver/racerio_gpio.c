/* 
 * racerio_gpio.c
 * 
 * Created on: Feb 18, 2018 12:35
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "racerio_gpio.h"
#include "stm32f4xx_gpio.h"

#define LED_RED_PORT GPIOB
#define LED_RED_PIN GPIO_Pin_4 

#define LED_BLUE_PORT GPIOB
#define LED_BLUE_PIN GPIO_Pin_5

void RACERIO_InitLED()
{
    // PB4, PB5
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOG Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    /* Configure PB4 and PB5 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = LED_RED_PIN | LED_BLUE_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_RED_PORT, &GPIO_InitStructure);

    GPIO_SetBits(LED_RED_PORT, LED_RED_PIN);
    GPIO_SetBits(LED_BLUE_PORT, LED_BLUE_PIN);
}

void RACERIO_TurnOnLED(LED_ID led)
{
    switch (led)
    {
    case RED:
        GPIO_SetBits(LED_RED_PORT, LED_RED_PIN);
        break;
    case BLUE:
        GPIO_SetBits(LED_BLUE_PORT, LED_BLUE_PIN);
        break;
    default:
        break;
    }
}

void RACERIO_TurOffLED(LED_ID led)
{
    switch (led)
    {
    case RED:
        GPIO_ResetBits(LED_RED_PORT, LED_RED_PIN);
        break;
    case BLUE:
        GPIO_ResetBits(LED_BLUE_PORT, LED_BLUE_PIN);
        break;
    default:
        break;
    }
}

void RACERIO_ToggleLED(LED_ID led)
{
    switch (led)
    {
    case RED:
        GPIO_ToggleBits(LED_RED_PORT, LED_RED_PIN);
        break;
    case BLUE:
        GPIO_ToggleBits(LED_BLUE_PORT, LED_BLUE_PIN);
        break;
    default:
        break;
    }
}
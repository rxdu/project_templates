/* 
 * racerio_gpio.h
 * 
 * Created on: Feb 18, 2018 12:33
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef RACERIO_GPIO_H
#define RACERIO_GPIO_H

typedef enum led_id {
    RED,
    BLUE
} LED_ID;

void RACERIO_InitLED();

void RACERIO_TurnOnLED(LED_ID led);
void RACERIO_TurOffLED(LED_ID led);
void RACERIO_ToggleLED(LED_ID led);

#endif /* RACERIO_GPIO_H */

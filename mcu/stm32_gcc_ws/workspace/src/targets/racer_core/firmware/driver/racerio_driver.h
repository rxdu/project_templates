/* 
 * racerio_driver.h
 * 
 * Created on: Feb 17, 2018 23:41
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */ 

#ifndef RACERIO_DRIVER_H
#define RACERIO_DRIVER_H

#include "racerio_gpio.h"
#include "racerio_timer.h"
#include "racerio_can.h"

//-------------------------
// Interrupt Priorities
//-------------------------
#define RACERIO_IRQ_PRIO_LOW				12              // lower than RTOS
#define RACERIO_IRQ_PRIO_MID				8               // higher than RTOS
#define RACERIO_IRQ_PRIO_HIGH				5               // for SPI, ADC, I2C etc...
#define RACERIO_IRQ_PRIO_HIGHEST			4               // for USART etc...

void RACERIO_SetupDriver();

#endif /* RACERIO_DRIVER_H */

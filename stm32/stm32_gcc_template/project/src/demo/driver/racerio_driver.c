/* 
 * racerio_driver.c
 * 
 * Created on: Feb 18, 2018 13:27
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "racerio_driver.h"

#include "misc.h"

void RACERIO_SetupDriver()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    RACERIO_InitLED();
    RACERIO_InitCAN();

    RACERIO_InitHallSensorInterface();
}
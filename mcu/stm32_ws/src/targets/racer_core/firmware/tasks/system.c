/* 
 * system.c
 * 
 * Created on: Feb 18, 2018 14:42
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "system.h"
#include "racerio.h"

static void vTaskSystem(void *p);

void SetupSystemTask()
{
    xTaskCreate(vTaskSystem, (const char *)"System", 128, NULL, TASK_PRIORITY_MID, NULL);
}

void vTaskSystem(void *p)
{
    uint8_t data[8];
    data[0] = 'a';
    data[1] = 'b';
    data[2] = 'c';
    for (;;)
    {
        RACERIO_ToggleLED(BLUE);

        RACERIO_CAN_TxCANFrame(0x11, true, data, 3);
        // JLinkRTTPrintf(0, "CAN msg sent\n", 0);

        // JLinkWriteString(0, "sytem running\n");
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

#include <stdint.h>

#include "racerio.h"
#include "system.h"

// #include "rtt_debug.h"

// void Delay(volatile uint32_t nCount)
// {
//   for (; nCount != 0; nCount--)
//     ;
// }

uint16_t loop_count;

int main(void)
{
  //    LED_Init();
  //  Motor_Init();
  //  Encoder_Init();
  //  Display_Init();
  // Platform_Init();
  RACERIO_SetupDriver();
  //loop_count = 0;

  // Setup tasks
  SetupSystemTask();

  JLinkRTTPrintf(0, "RacerIO running\n", 0);

  // Start RTOS scheduler
  vTaskStartScheduler();

  return 0;
}

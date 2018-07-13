#include <stdint.h>

#include "racerio.h"
#include "system.h"

uint16_t loop_count;

int main(void)
{
  RACERIO_SetupDriver();

  // Setup tasks
  SetupSystemTask();

  JLinkRTTPrintf(0, "RacerIO running\n", 0);

  // Start RTOS scheduler
  vTaskStartScheduler();

  return 0;
}

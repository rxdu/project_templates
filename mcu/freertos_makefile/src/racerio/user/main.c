/* Scheduler includes. */
// #include "FreeRTOS.h"
// #include "queue.h"
// #include "task.h"

#include <stdint.h>
// #include "rtt_debug.h"

// void Delay(volatile uint32_t nCount)
// {
//   for (; nCount != 0; nCount--)
//     ;
// }

// void vTaskLed(void *p);

uint16_t loop_count;

int main(void)
{
  //    LED_Init();
  //  Motor_Init();
  //  Encoder_Init();
  //  Display_Init();
  // Platform_Init();

  //loop_count = 0;

  // Create LED blink task
  // xTaskCreate(vTaskLed, (const char *)"LED Blink", 128, NULL, 1, NULL);

  // Start RTOS scheduler
  // vTaskStartScheduler();

  // None-OS version test code
  //     while (1) {
  //      loop_count++;
  //
  //      Motor_SetVelocity(left_pwm, right_pwm);
  //
  //#ifdef ENABLE_OLED
  //      Display_ShowString(0,20,"loop count");
  //      Display_ShowNumber(70,20,(uint16_t)loop_count,5,12);
  //      Display_RefreshGRam();
  //#endif
  //
  //      LED_Toggle(LED0);
  //      Delay(0xfffff);
  //      Delay(0xfffff);
  //     }

  return 0;
}

// void vTaskLed(void *p)
// {
//   for (;;)
//   {
//     // LED_Toggle(LED0);
//     // DEBUG_PRINT(DEBUG_TEST, ("Task led flash is running!\r\n"));

//     //SEGGER_RTT_WriteString(0, "Test msg from RTT!\r\n");
//     //RTT_printf(0, "Test msg, counter: %d\r\n", loop_count++);

//     vTaskDelay(500 / portTICK_RATE_MS);
//   }
// }

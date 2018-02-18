/*
 * =====================================================================================
 *
 *       Filename:  platform.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/27/2016 09:23:42 PM
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Ruixiang Du (rdu), ruixiang.du@gmail.com
 *   Organization:  Worcester Polytechnic Institute
 *
 * =====================================================================================
 */

#include "platform.h"

#include "display.h"
#include "encoder.h"
#include "led.h"
#include "motor.h"
#include "imu.h"
#include "nvic.h"

void Platform_Init(void) {
	// core components
	Nvic_Init();
    LED_Init();
    Motor_Init();
    Encoder_Init();
    IMU_Init();

    // optional components
#ifdef ENABLE_OLED
    Display_Init();
#endif
}

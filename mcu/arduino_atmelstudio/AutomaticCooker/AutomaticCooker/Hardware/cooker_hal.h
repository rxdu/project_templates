/*
 * cooker_hal.h
 *
 * Created: 7/25/2014 4:54:25 PM
 *  Author: rdu
 */ 


#ifndef COOKER_HAL_H_
#define COOKER_HAL_H_

//------------------- Function Prototypes --------------------//
void startMotor();
void stopMotor();
void startHeater();
void stopHeater();
void startBuzzer();
void stopBuzzer();
void stopActuators();

void blinkLED(byte count);
void startBuzzerForSec(byte seconds);

#endif /* COOKER_HAL_H_ */
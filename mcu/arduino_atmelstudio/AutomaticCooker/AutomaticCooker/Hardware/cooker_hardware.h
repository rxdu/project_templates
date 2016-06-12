/*
 * cooker_hardware.h
 *
 * Created: 7/25/2014 4:45:26 PM
 *  Author: rdu
 */ 


#ifndef COOKER_HARDWARE_H_
#define COOKER_HARDWARE_H_

//--------------------- Pin Definitions -----------------------//
#define CC3000_INT      2    // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7    // Can be any digital pin
#define CC3000_CS       10   // Preferred is pin 10 on Uno

#define RELAY_HEATER    6    // Output pin used to control the relay for heater
#define RELAY_MOTOR     3    // Output pin used to control the relay for motor
#define BUZZER          9    // Output pin used to control buzzer
#define LED             13   // Output pin used to control LED

//------------------- Function Prototypes --------------------//
void initGPIO();
void initSerial();
void initTimer();
void initWifi();

byte getGPIOState(byte pin);
void setGPIOState(byte pin, byte state);

#endif /* COOKER_HARDWARE_H_ */
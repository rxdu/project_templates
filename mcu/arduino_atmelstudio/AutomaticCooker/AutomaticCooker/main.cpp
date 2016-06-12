/*
 * AutomaticCooker.cpp
 *
 * Created: 7/25/2014 3:31:44 PM
 *  Author: rdu
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "Arduino.h"
#include "cooker_common.h"
#include "./Hardware/cooker_hardware.h"


int main(void)
{
	initGPIO();
	initTimer();
	
	//digitalWrite(LED, HIGH);
	
    while(1)
    {
        //TODO:: Please write your application code 
		//blinkLED(1);
    }
}

//------------------ ISR Definitions  --------------------//
ISR(TIMER1_COMPA_vect)
{
	digitalWrite(LED, !digitalRead(LED));
	//sys_tick++;
	//cmd_update_count++;
	//actuator_update_count++;
	//
	//if(cmd_update_count == CMD_UPDATE_PERIOD){
		//cmd_update_count = 0;
		//cmd_updated = false;
	//}
	//
	//if(actuator_update_count == ACTUATOR_UPDATE_PERIOD){
		//actuator_update_count = 0;
		//actuator_updated = false;
	//}
	
	// TODO
	// Write something to prevent horrible things happen when sys_tick overflows
}
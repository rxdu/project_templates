/*
 * cooker_hal.cpp
 *
 * Created: 7/25/2014 4:54:13 PM
 *  Author: rdu
 */ 


void blinkLED(byte count){
	byte i = 0;
	
	for( i=0; i<count; i++){
		digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(500L);               // wait for a second
		digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
		delay(500L);                // wait for a second
	}
}
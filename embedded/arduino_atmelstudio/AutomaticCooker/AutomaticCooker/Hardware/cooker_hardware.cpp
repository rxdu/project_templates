/*
 * cooker_hardware.cpp
 *
 * Created: 7/25/2014 4:46:02 PM
 *  Author: rdu
 */ 

#include "Arduino.h"
#include "cooker_hardware.h"

void initGPIO()
{
	pinMode(LED, OUTPUT);
}

void initSerial()
{
	Serial.begin(115200);
	Serial.println();
}

void initTimer()
{
	// Disable global interrupts
	cli();
	
	// Initialize Timer1
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	
	// Set compare match register to desired timer count:
	OCR1A = 15624;
	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);
	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	// Enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);
	
	// Enable global interrupts:
	sei();
}
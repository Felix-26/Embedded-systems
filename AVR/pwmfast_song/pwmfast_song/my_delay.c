/*
 * my_delay.c
 *
 * Created: 10/3/2025 12:16:15 PM
 *  Author: Felix Thomas
 */ 

#include "my_delay.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint16_t count;
volatile uint16_t delay_done = 0;

ISR(TIMER2_COMPA_vect) {
	count--;
	if (count==0) {
		delay_done = 1;
		TIMSK2 &= ~(1<<OCIE2A);
		TCCR2B &= ~((1<<CS22)|(1<<CS01)|(1<<CS00));
	}
}

void delay_init(void) {
	TCCR2A |= (1<<WGM21);
	TCCR2B |= (1<<CS22);
	OCR2A = 249;
	TIMSK2 |= (1<<OCIE2A);
	sei();
}

void delay(uint16_t ms) {
	count = ms;
	delay_done = 0;
	
	TCCR2B |= (1<<CS22);
	TIMSK2 |= (1<<OCIE2A);
	
	while(!delay_done);
	
}
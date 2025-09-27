/*
 * my_delay.c
 *
 * Created: 9/27/2025 2:37:57 PM
 *  Author: felix
 */ 

#include <avr/io.h>

void timer0_init() {
	TCCR0A |= (1<<WGM01);
	TCNT0 = 0;
	OCR0A = 249;
	TCCR0B |= (1<<CS00);
	TCCR0B |= (1<<CS01);
	TIFR0 |= (1<<OCF0A);
}

void delay(uint16_t ms) {
	while(ms--) {
		while(!(TIFR0 & (1<<OCF0A)));
		TIFR0 |= (1<<OCF0A);
	}
}
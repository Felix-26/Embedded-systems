/*
 * my_delay.c
 *
 * Created: 9/26/2025 8:32:52 PM
 *  Author: Felix Thomas
 */ 
#include <avr/io.h>
void timer0_init(void) {
	// to select CTC mode
	TCCR0A |= (1<<WGM01);
	// count value
	OCR0A = 249;
	// making counter 0
	TCNT0 = 0;
	// pre-scalar 64
	TCCR0B |= ( 1<<CS00 | 1<<CS01 );
	// setting flag bit 0
	TIFR0 |= (1<<OCF0A);
}

void delay(uint16_t ms){
	// count for ms times
	while(ms--) {
		// checking if OCF0A flag is set or not
		while(!(TIFR0 & (1<<OCF0A)));
		TIFR0 |= (1<<OCF0A);
		
	}
}
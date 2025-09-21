/*
 * Timer0_ctm.c
 *
 * Created: 9/19/2025 8:37:22 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRB |= (1<<DDB5);
	TCCR0A |= (1<<WGM01);			// to set timer0 to ctc mode set WGM01 bit of TCCR0A to 1
	OCR0A = 200;					// counter will count till OCR0A
	TCNT0 = 0;						// set counter to 0
	TCCR0B |= (1<<CS00);				// to give a clock with no 1024 set only CS00 to 1
	TCCR0B |= (1<<CS02);				// CS02 to 1 
	TIFR0 |= (1<<OCF0A);
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		for(int i=0;i<156;i++) {
			while (!(TIFR0&(1<<OCF0A)));
			TIFR0 |= (1<<OCF0A);
		}
    }
}


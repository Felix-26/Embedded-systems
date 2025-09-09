/*
 * Blink1.c
 *
 * Created: 9/8/2025 10:31:22 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//setting B5 as an output.
	DDRB = (1<<5);
	
    while (1) 
    {
		//setting B5 to high
		PORTB |= (1<<5);
		_delay_ms(500);
		//setting B5 to low
		PORTB &= ~(1<<5);
		_delay_ms(500);
    }
}


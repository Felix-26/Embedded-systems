/*
 * Switch(Active_Low).c
 *
 * Created: 9/9/2025 1:38:41 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// set PD3 as OUTPUT
	DDRD = (1<<3);
	// set PC0 as INPUT
	DDRC = ~(1);
	// enabling internal Pull-up resistor
	PORTC |= (1<<0);
	while (1)
	{
		// if PC0 receive LOW signal
		if (!(PINC & (1<<0)))
		{
			//then set PD3 OUTPUT to LOW without affecting others
			// LED on 
			PORTD |= (1<<3);
		}
		// if PC0 receive HIGH signal
		else
		{
			// Led off
			// then set PD3 OUTPUT to HIGH without affecting others
			PORTD &= ~(1<<3);
		}
	}
}




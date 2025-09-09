/*
 * Switch(pull_up).c
 *
 * Created: 9/9/2025 12:20:37 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
	
	// setting only PD3 as an INPUT pin others OUTPUT.
	DDRD = ~(1<<3);
	// setting PB1 as OUTPUT pin
	DDRB = (1<<1);
    while (1) 
    {
		// checking if PD3 is receiving any HIGH signal.
		if(PIND & (1<<3))
		{
			// then clear PB1
			PORTB &= ~(1<<1); 
		}
		// checking if PD3 is receiving any LOW signal.
		else
		{
			// then set PB1
			PORTB |= (1<<1);
		}
    }
}


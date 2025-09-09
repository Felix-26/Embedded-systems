/*
 * Switch(pull_down).c
 *
 * Created: 9/9/2025 11:54:29 AM
 * Author : Felix Thomas
 */ 

#define F_CPU 1600000000UL
#include <avr/io.h>

int main(void)
{
	// PD3 is set as INPUT pin.
	DDRD = ~(1<<3);
	// PB1 is set as OUTPUT pin.
	DDRB = (1<<1);
	
    while (1) 
    {
		// checking if INPUT of PD3 is receiving any high signal.
		if(PIND & (1<<3)) 
		{
			// then set OUPUT of PB1
			PORTB |= (1<<1);
		}
		// checking if INPUT of PD3 is receiving any low signal.
		else
		{
			// then clear OUTPUT of PB1
			PORTB &= ~(1<<1);
		}
    }
}


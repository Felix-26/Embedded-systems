/*
 * Switch(Active_High).c
 *
 * Created: 9/9/2025 1:15:34 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
	// set PD3 as OUTPUT
    DDRD = (1<<3);
	// set PC0 as INPUT 
	DDRC = 0;
	while (1) 
    {
		// if PC0 receive HIGH signal
		if (PINC & (1<<0))
		{
			// then set PD3 OUTPUT to HIGH without affecting others
			PORTD |= (1<<3);
		}
		// if PC0 receive LOW signal
		else
		{
			//then clear PD3 OUTPUT to LOW without affecting others
			PORTD &= ~(1<<3);
		}
    }
}


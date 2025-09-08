/*
 * input.c
 *
 * Created: 9/8/2025 8:21:46 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00100000;
	DDRD = 0b00000000;
	PORTD = 0b00000001;
    /* Replace with your application code */
    while (1) 
    {
		if(!(PIND&1)) 
		{
			PORTB |= (1<<5);
		}
		else
		{
			PORTB = 0;
		}
    }
}


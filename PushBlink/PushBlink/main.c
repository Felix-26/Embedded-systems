/*
 * PushBlink.c
 *
 * Created: 9/6/2025 9:54:09 AM
 * Author : felix
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = ~(1);
	DDRC = (1<<2);
    /* Replace with your application code */
    while (1) 
    {
		if(PINB&(1)) {
			PORTC = 1<<2;
		} else {
			PORTC = 0;
		}
    }
}


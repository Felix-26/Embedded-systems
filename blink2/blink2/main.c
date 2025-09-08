/*
 * blink2.c
 *
 * Created: 9/3/2025 5:54:50 PM
 * Author : felix
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = 0b00001000;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0b00001000;
    }
}


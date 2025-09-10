/*
 * Blink_bitwise.c
 *
 * Created: 9/10/2025 8:20:36 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<DDB5);
    while (1) 
    {
		PORTB |= (1<<PORTB5);
		_delay_ms(500);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(500);
    }
}


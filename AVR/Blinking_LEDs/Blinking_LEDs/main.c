/*
 * Blinking_LEDs.c
 *
 * Created: 9/9/2025 9:59:31 PM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0xFF;
	DDRC = 0xFF;
    while (1) 
    {
		PORTB = 0x55;
		PORTC = 0x55;
		_delay_ms(500);
		PORTB = ~(PORTB);
		PORTC = ~(PORTC);
		_delay_ms(500);
    }
}


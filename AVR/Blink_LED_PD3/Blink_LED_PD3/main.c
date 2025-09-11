/*
 * Blink_LED_PD3.c
 *
 * Created: 9/9/2025 12:40:12 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// set PD3 as OUTPUT.
    DDRD = (1<<DDB3);
    while (1) 
    {
		// set PD3 HIGH
		PORTD |= (1<<PORTD3);
		_delay_ms(500);
		// set PD3 LOW
		PORTD &= ~(1<<PORTD3);
		_delay_ms(500); 
    }
}


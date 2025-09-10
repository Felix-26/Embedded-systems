/*
 * DC_motor1.c
 *
 * Created: 9/10/2025 9:08:08 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB4);
    while (1) 
    {
		PORTB &= ~(1<<PORTB5);
		PORTB &= ~(1<<PORTB4);
		_delay_ms(1000);
		PORTB &= ~(1<<PORTB5);
		PORTB |= (1<<PORTB4);
		_delay_ms(2500);
		PORTB &= ~(1<<PORTB5);
		PORTB &= ~(1<<PORTB4);
		_delay_ms(1000);
		PORTB &= ~(1<<PORTB4);
		PORTB |= (1<<PORTB5);
		_delay_ms(2500);
    }
}


/*
 * input_motor.c
 *
 * Created: 9/15/2025 8:57:56 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB5);
	DDRD &= ~(1<<DDD2);
    while (1) 
    {
		if((PIND & (1<<PIND2))) {
			PORTB |= (1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
			_delay_ms(1000);
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
			_delay_ms(3000);
			PORTB &= ~(1<<PORTB5);
			PORTB |= (1<<PORTB4);
			_delay_ms(1000);
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
			_delay_ms(3000);
		} else {
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
		}
    }
}


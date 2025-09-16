/*
 * Input_motor2.c
 *
 * Created: 9/16/2025 11:48:09 AM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB4);
	DDRD &= ~(1<<DDD2);
	PORTD |= (1<<PORTD2);
	
    while (1) 
    {
		if(!(PIND & (1<<PIND2))) {
			PORTB |= (1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
			_delay_ms(1000);
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
			_delay_ms(2000);
			PORTB &= ~(1<<PORTB5);
			PORTB |= (1<<PORTB4);
			_delay_ms(1000);
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
			_delay_ms(2000);
		}
		else {
			PORTB &= ~(1<<PORTB5);
			PORTB &= ~(1<<PORTB4);
		}
    }
}


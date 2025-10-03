/*
 * external_interrupt.c
 *
 * Created: 10/3/2025 8:35:57 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

ISR(INT0_vect) {
	PORTB ^= (1<<PORTB5);
	_delay_ms(10000);
}

void toggleb4() {
	PORTB ^= (1<<PORTB4);
	_delay_ms(2000);
}


int main(void)
{
	DDRD&=~(1<<DDD2);
    DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB4);
	PORTD |= (1<<PORTD2);
	
	EIMSK |= (1<<INT0);
	EICRA |= (1<<ISC01);
	sei();
    while (1) 
    {
		toggleb4();
    }
}


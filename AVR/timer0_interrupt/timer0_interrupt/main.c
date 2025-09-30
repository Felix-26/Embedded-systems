/*
 * timer0_interrupt.c
 *
 * Created: 9/29/2025 8:47:07 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
volatile uint16_t count = 0;

ISR(TIMER0_OVF_vect) 
{
	if(count>=977) {
		PORTB ^= (1<<PORTB5);
		count = 0;
	}
	count++;
}

int main(void)
{
    DDRB |= (1<<DDB5);
	// donot want to set tcnt0 to 0
	// set normal mode
	TCCR0A = 0;
	// prescalar 64
	TCCR0B |= (1<<CS00 | 1<<CS01);
	// setting overflow interrupt flag
	TIMSK0 |= (1<<TOIE0);
	// setting global interrupt flag
	sei();
	while(1) {
		
	}
}


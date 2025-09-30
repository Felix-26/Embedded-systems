/*
 * Timer0_ctc_interrupt.c
 *
 * Created: 9/30/2025 11:45:01 AM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t count = 0;

ISR(TIMER0_COMPA_vect)
{
	if(count>=125) {
		PORTB ^= (1<<PORTB5);
		count = 0;
	}
	else {
		count++;
	}
}

int main(void)
{
	DDRB |= (1<<DDB5);
	// Timer0 in CTC mode
    TCCR0A |= (1<<WGM01);
	// pre-scalar 1024
	TCCR0B = ( 1<<CS02 | 1<<CS00 );
	// max value till timer0 should count
	OCR0A = 125;
	// setting CTC overflow interrupt flag 
	TIMSK0 |= (1<<OCIE0A);
	// setting global interrupt
	sei();
	
    while (1) 
    {
    }
}


/*
 * timer.c
 *
 * Created: 11/24/2025 11:36:53 AM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t millis = 0;

ISR(TIMER0_COMPA_vect)
{
	if (millis>0)
	{
		millis--;
	}
}

void timer_init(void)
{
	// CTC mode
	TCCR0A |= (1<<WGM01);
	// PRE-SCALAR = CLK/64
	TCCR0B |= (1<<CS00 | 1<<CS01);
	// Timer0 COMPARE OUTPUT MATCH interrupt enable
	TIMSK0 |= (1<<OCIE0A);
	OCR0A = 249;
}

void timer_delay(uint16_t ms)
{
	millis = ms;
	while(millis);
}
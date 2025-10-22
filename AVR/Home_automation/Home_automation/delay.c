/*
 * delay.c
 *
 * Created: 10/21/2025 7:26:07 PM
 *  Author: felix
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>

uint32_t ms = 0;

void delay_init(void)
{
	// CTC Mode
	TCCR0A = 0;
	// PRE-SCALAR 64
	TCCR0B |= (1<<CS01 | 1<<CS00);
	TCNT0 = 0;
	OCR0A = 249;
	TIMSK0 |=(1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	ms++;
}

void delay_ms(int t)
{
	
	while(t-ms);
	ms=0;
}
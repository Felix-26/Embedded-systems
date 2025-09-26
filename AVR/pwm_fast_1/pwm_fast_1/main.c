/*
 * pwm_fast_1.c
 *
 * Created: 9/24/2025 8:55:23 PM
 * Author : Felix THomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRD |= (1<<DDD6);
	DDRB |= (1<<DDB5);
    while (1) 
    {
		PORTB |= (1<<PORTB5);
		TCCR0A |= (1<<WGM01);
		TCCR0A |= (1<<WGM00);
		TCCR0A |= (1<<COM0A1);
		TCCR0B |= (1<<CS00);
		TCCR0B |= (1<<CS01);
		
		OCR0A = 128;
    }
}


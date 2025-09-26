/*
 * pwm_motor1.c
 *
 * Created: 9/26/2025 2:13:41 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD |= (1<<DDD6);
	DDRB &= ~( (1<<DDB1) | (1<<DDB2) | (1<<DDB3)  | (1<<DDB4) );
	// enabling pull up registers to avoid floating values in input
	PORTB |= ((1<<PORTB1) | (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4));			
	
	// for fast PWM mode set bits WGM00 and WGM01 of TCCR0A register.
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	// set COM0A1 bit of TCCR0B register for non-inverting PWM signal
	TCCR0A |= (1<<COM0A1);
	TCCR0B |= (1<<CS00);		// CLKpwm = (CLK)/(n X 256) ; n = prescalar
	TCCR0B |= (1<<CS01);		// here n = 64
	while(1) {
		if(!(PINB & (1<<PINB1))) {
			OCR0A = 64;	
		} else if (!(PINB & (1<<PINB2)))
		{
			OCR0A = 128;
		} else if (!(PINB & (1<<PINB3)))
		{
			OCR0A = 192;
		} else if (!(PINB & (1<<PINB4)))
		{
			OCR0A = 255;
		}
	}
}


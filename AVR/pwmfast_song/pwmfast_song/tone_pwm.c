/*
 * tone_pwm.c
 *
 * Created: 10/3/2025 2:41:21 PM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "tone_pwm.h"
#include "notes.h"

void tone(uint16_t freq,uint8_t duty) {
	DDRB |= (1<<DDB1);
	TCCR1A |= (1<<COM1A1);
	TCCR1B |= (1<<CS11);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13 | 1<<WGM12);
	
	ICR1 = (F_CPU/(freq*8UL))-1;
	OCR1A = (ICR1*duty)/100;
}

void no_tone() {
	TCCR1A = 0;
	TCCR1B = 0;
	PORTB &= ~(1<<PORTB1);
}
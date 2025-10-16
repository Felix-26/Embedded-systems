/*
 * adc.c
 *
 * Created: 10/13/2025 8:47:45 PM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void adc_init(void) {
	ADMUX = ( 1<<REFS0);
	ADCSRA = (1<<ADEN);
	ADCSRA |= (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0); // PRESCALAR 128
}

uint16_t adc_read(uint16_t channel) {
	channel &= 0x07;
	ADCSRA |= 1<<ADSC;
	ADMUX = (ADMUX & 0XF8) | channel;
	while (ADCSRA & (1<<ADSC));
	return (ADCL | (ADCH << 8));
}
/*
 * temperature.c
 *
 * Created: 10/21/2025 1:32:06 PM
 *  Author: felix
 */ 

#include <avr/io.h>

void thermo_init(void)
{
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADPS1 | 1<<ADPS2 | 1<<ADPS0);
}

float thermo(uint8_t channel)
{
	uint16_t value;
	channel &= 0x07;
	ADCSRA |= (1<<ADSC);
	ADMUX = (ADMUX & 0xF8) | channel;
	while(ADCSRA & (1<<ADSC));
	value = ADCL | (ADCH<<8);
	return value*0.488;
}
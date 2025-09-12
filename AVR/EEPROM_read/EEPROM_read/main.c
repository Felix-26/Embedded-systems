/*
 * EEPROM_read.c
 *
 * Created: 9/11/2025 7:19:08 PM
 * Author : felix
 */ 

#include <avr/io.h>
#define F_CPU 16000000;

int main(void)
{
	DDRD |= 0xFF;
    while(EECR & (1<<EEPE));
	EEAR = 0x5F;
	EECR |= (1<<EERE);
	PORTD = EEDR;
	return 0;
}


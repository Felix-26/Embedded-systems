/*
 * EEPROM_write.c
 *
 * Created: 9/11/2025 7:03:49 PM
 * Author : felix
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#define ADDRESS 0x5F

int main(void)
{
	while(EECR & (1<<EEPE));
    EEAR = ADDRESS;
	EEDR = 'F';
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}


/*
 * Modular_delay.c
 *
 * Created: 9/26/2025 8:19:58 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "my_delay.h"
#include <stdint.h>

int main(void)
{
    DDRB |= (1<<DDB5);
	timer0_init();
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		delay(5000);
    }
}


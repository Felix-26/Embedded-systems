/*
 * light.c
 *
 * Created: 10/18/2025 11:22:50 AM
 *  Author: Felix Thomas
 */ 

#include "light.h"

void light_init(void)
{
	DDRB |= (1<<DDB5);
}

void light_control()
{
	PORTB ^= (1<<PORTB5);
}
/*
 * my_gpio.c
 *
 * Created: 9/27/2025 2:59:22 PM
 *  Author: felix
 */ 

#include <avr/io.h>

void gpio_init(void) {
	DDRB |= ( 1<<DDB1 | 1<<DDB2 | 1<<DDB3 | 1<<DDB4 | 1<<DDB5 );
}

void toggle_gpio() {
	PORTB ^= ( 1<<PORTB1 | 1<<PORTB2 | 1<<PORTB3 | 1<<PORTB4 | 1<<PORTB5 );
}
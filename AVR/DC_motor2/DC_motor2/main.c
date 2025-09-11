/*
 * DC_motor2.c
 *
 * Created: 9/11/2025 11:35:36 AM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void motorCW() {
	PORTC |= (1<<PORTC4);
	PORTC &= ~(1<<PORTC5);
}

void motorSTP() {
	PORTC &= ~(1<<PORTC4);
	PORTC &= ~(1<<PORTC5);
}

void motorCCW() {
	PORTC &= ~(1<<PORTC4);
	PORTC |= (1<<PORTC5);
}

int main(void)
{
    DDRC |= (1<<DDC5);
	DDRC |= (1<<DDC4);
    while (1) 
    {
		motorCW();
		_delay_ms(2500);
		motorSTP();
		_delay_ms(2500);
		motorCCW();
		_delay_ms(2500);
		motorSTP();
		_delay_ms(2500);
    }
}


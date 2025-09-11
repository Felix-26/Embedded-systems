/*
 * DC_motor3.c
 *
 * Created: 9/11/2025 12:44:02 PM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#define DELAY 2500
#include <avr/io.h>
#include <util/delay.h>

void motorCW(int delayT) {
	PORTC |= (1<<PORTC4);
	PORTC &= ~(1<<PORTC5);
	while(delayT){
		// _delay_ms func receives only integer const
		_delay_ms(1);
		delayT--;
	}
}

void motorCCW(int delayT) {
	PORTC |= (1<<PORTC5);
	PORTC &= ~(1<<PORTC4);
	while(delayT){
		// _delay_ms func receives only integer const
		_delay_ms(1);
		delayT--;	
	}
}

void motorSTP(int delayT) {
	PORTC &= ~(1<<PORTC4);
	PORTC &= ~(1<<PORTC5);
	while(delayT) {
		_delay_ms(1);
		delayT--;
	}
}

int main(void)
{
    DDRC |= (1<<DDC4);
	DDRC |= (1<<DDC5);
    while (1) 
    {
		motorCW(DELAY);
		motorSTP(DELAY);
		motorCCW(DELAY);
		motorSTP(DELAY);	
    }
}


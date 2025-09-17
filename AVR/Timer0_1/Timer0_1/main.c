/*
 * Timer0_1.c
 *
 * Created: 9/17/2025 8:46:33 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void);

int main(void)
{
    DDRB |= (1<<DDB5);
    while (1) 
    {	
		PORTB ^= (1<<PORTB5);
		delay_1s();
    }
}

void delay_1s(void) {
	unsigned int i;
	unsigned int count = 62500;
	for(i=1;i<=count;i++) {
		// assigning Timer count 0 register to 0
		TCNT0 = 0;
		// the mode select is in TCCR0A register WGM01,WGM00
		TCCR0A = 0;
		// clock selector is in  TCCROB register CS02,CS01,CS00
		// here we need normal mode for over need
		TCCR0B |= (1<<CS00);
		// overflow flag TOV0 is in TIFR0 register
		TIFR0 |= (1<<TOV0);
		// looping till TOV0 is 1
		while(!(TIFR0 & (1<<TOV0)));
	} 
}

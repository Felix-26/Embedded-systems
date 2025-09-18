/*
 * Timer0_2.c
 *
 * Created: 9/18/2025 10:53:15 AM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


void delay_1s(void) {
	// 16000000Hz/1024 = 15625Hz
	// Time period for 1 clock pulse after using prescalar= 1/15625Hz = .000064s
	// so to overflow 1 time time required = 256 x .000064s = .016384s
	// so to get a delay of nearly 1s number of iterations of a loop required = 1/.016384 = 61(approx)
	int count = 61;
	for(int i=0;i<count;i++) {
		// resetting counter to 0
		TCNT0 = 0;
		
		TCCR0A = 0;
		TCCR0B |= (1<<CS02);
		TCCR0B |= (1<<CS00);
		TIFR0 |= (1<<TOV0);
		while(!(TIFR0 & (1<<TOV0)));
	}
}

int main(void)
{
    DDRB |= (1<<DDB5);
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		delay_1s();
    }
}


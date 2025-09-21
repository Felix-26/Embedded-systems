/*
 * Timer0_ctc_delay5s.c
 *
 * Created: 9/21/2025 6:25:12 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void Delay_5s(void);

int main(void)
{
	DDRB |= (1<<DDB5);
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		Delay_5s();
    }
}

void Delay_5s(void) {
	TCCR0A |= (1<<WGM01);			// to set timer0 to CTC mode WGM00,WGM01 need to be 0,1 respectively
	TCCR0B |= (1<<CS00);			// setting a prescalar to reduce the clock speed for the timer (clk/64)
	TCCR0B |= (1<<CS01);			// so for the timer0 clock speed it gets will be in this case 16MHz/64 = 250,000Hz.
	TCNT0 = 1;						// setting initial value from where counting to start to 0.
	OCR0A = 200;					// maximum value till the counter should go, in every count the OCR0A register is checked if it is 200 OCF0A is set to 1.
	TIFR0 |= (1<<OCF0A);			// clear OCF0A bit of TIFR0 register. 
	int count = 6250;				// no of iterations the counter should count
	for (int i=0;i<count;i++)
	{
		while(!(TIFR0 & (1<<OCF0A)));			// count till OCF0A register is not set.if set come out of loop
		TIFR0 |= (1<<OCF0A);					// clear the OCF0A bit of TIFR0 register.
	}
} 

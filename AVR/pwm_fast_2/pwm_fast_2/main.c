/*
 * pwm_fast_2.c
 *
 * Created: 9/24/2025 9:38:40 PM
 * Author : felix
 */ 

#define F_CPU 16000000Ul
#include <avr/io.h>
#include <util/delay.h>


void dim_to_bright() {
	int i;
	for(i=0;i<255;i++){
		OCR0A = i;
		_delay_ms(20);
	}
}

void bright_to_dim() {
	int i;
	for(i=255;i>=0;i--) {
		OCR0A = i;
		_delay_ms(20);
	}
}
int main(void)
{
	DDRD |= (1<<DDD6);
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5);

	while(1) {
		TCCR0A |= (1<<WGM01);
		TCCR0A |= (1<<WGM00);
		TCCR0A |= (1<<COM0A1);
		TCCR0B |= (1<<CS01);
		TCCR0B |= (1<<CS00);
		dim_to_bright();
		_delay_ms(500);
		bright_to_dim();
		_delay_ms(500);
		OCR0A=0;
	}
}



/*
 * USART.c
 *
 * Created: 10/17/2025 8:51:36 PM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void usart_TX(unsigned char data) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void usart_init() {
	UBRR0L = 103;
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<UCSZ01 | 1<<UCSZ00);
}

int main(void)
{
	char str[]	= "Hello ,this message is from ATmega328.\n";
	usart_init();
    while(1) {
		for (int i=0;i<strlen(str);i++)
		{
			usart_TX(str[i]);
		}
		_delay_ms(1000);
	}
}


/*
 * uart.c
 *
 * Created: 11/3/2025 10:48:00 PM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>

void uart_init(unsigned int BAUD)
{
	UBRR0L = 103;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void uart_tx(unsigned char c)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
}

void uart_send_string(char *str)
{
	while(*str)
	{
		uart_tx(*str++);
	}
}

void uart_send_hex(uint8_t hex)
{
	uart_tx('0');
	uart_tx('x');
	char buffer[10];
	itoa(hex,buffer,16);
	uart_send_string(buffer);
}

void uart_send_double(double t)
{
	char buffer[10];
	dtostrf(t,5,2,buffer);
	uart_send_string(buffer);
}

void uart_send_int(uint32_t x)
{
	char buffer[10];
	itoa(x,buffer,10);
	uart_send_string(buffer);
}
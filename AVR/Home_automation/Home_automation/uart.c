/*
 * uart.c
 *
 * Created: 10/21/2025 4:13:02 PM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t *tx_buffer;
volatile uint8_t tx_index = 0;
volatile uint8_t tx_length = 0;

ISR(USART_UDRE_vect)
{
	if (tx_index < tx_length)
	{
		UDR0 = tx_buffer[tx_index++];
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);
		tx_index = 0;
	}
}

void uart_TX_init(void)
{
	UBRR0L = 103;
	UCSR0B |= (1<<TXEN0);
	UCSR0C |= (1<<UCSZ01 | 1<<UCSZ00);
}

void uart_transfer(char *s)
{
	tx_buffer = (uint8_t *)s;
	while(s[tx_length] != '\0') tx_length++;
	
	tx_index = 0;
	UCSR0B |= (1<<UDRIE0);
}
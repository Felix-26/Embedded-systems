/*
 * lcd.c
 *
 * Created: 11/24/2025 12:28:37 PM
 *  Author: Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>

#include "names.h"

void enable_pulse(void)
{
	PORTC |= (1<<E);
	_delay_us(1);
	PORTC &= ~(1<<E);
	_delay_us(50);
}

void send_nibble(uint8_t nib)
{
	PORTD &= ~(0x0F << 4);
	
	if (nib & 0x08)
	{
		PORTD |= (1<<D7);
	}
	if (nib & 0x04)
	{
		PORTD |= (1<<D6);
	}
	if (nib & 0x02)
	{
		PORTD |= (1<<D5);
	}
	if (nib & 0x01)
	{
		PORTD |= (1<<D4);
	}
	enable_pulse();
}

void send_byte(uint8_t byte,uint8_t rs)
{
	if (rs==1) PORTC |= (1<<RS);
	else PORTC &= ~(1<<RS);
		
	send_nibble(byte>>4);
	send_nibble(byte&0x0F);
}

void send_cmd(uint8_t c)
{
	send_byte(c,0);
	_delay_us(40);
	
	if (c == 0x01 || c == 0x02)
	{
		_delay_ms(2);
	}
}

void send_data(uint8_t c)
{
	send_byte(c,1);
	_delay_us(40);
}

void display(const char *s)
{
	while(*s)
		send_data((uint8_t)*s++);
}

void send_int(int i)
{
	char buf[40];
	itoa(i,buf,10);
	display(buf);
} 

void send_hex(int i)
{
	char buf[40];
	itoa(i,buf,16);
	display(buf);
}

void send_double(double f)
{
	char buf[40];
	dtostrf(f,4,3,buf);
	display(buf);
}

void screen_clear(void)
{
	send_cmd(0x01);
}

void cursor_return(void)
{
	send_cmd(0x02);
}

void lcd_set_cursor(uint8_t row,uint8_t col)
{
	uint8_t addr = (row ? 0x40 : 0x00) + col;
	send_cmd(0x80|addr);
}

void lcd_init(void)
{
	CTRL |= (1<<RS|1<<E);
	DATA |= (1<<D7|1<<D6|1<<D5|1<<D4);
	_delay_ms(20);
	PORTC &= ~(1<<RS);
	PORTC &= ~(1<<E);
	send_nibble(0x03);
	_delay_ms(5);
	send_nibble(0x03);
	_delay_us(150);
	send_nibble(0x03);
	_delay_us(150);
	
	send_nibble(0x02);
	_delay_us(150);
	send_cmd(0x28);
	_delay_us(40);
	send_cmd(0x08);
	_delay_us(40);
	send_cmd(0x01);
	_delay_us(40);
	send_cmd(0x06);
	_delay_us(40);
	send_cmd(0x0C);
}
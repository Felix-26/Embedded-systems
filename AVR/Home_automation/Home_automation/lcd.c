/*
 * lcd.c
 *
 * Created: 10/18/2025 12:48:35 PM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <stdint.h>
#include "lcd.h"
#include <stdlib.h>

static void en_pulse(void) {
	en_PORT |= (1<<en_pin);
	_delay_us(1);
	en_PORT &= ~(1<<en_pin);
	_delay_us(50);
}

static void send_nibble(uint8_t x) {
	lcd_PORT &= ~((1<<lcd_d7) | (1<<lcd_d6) | (1<<lcd_d5) | (1<<lcd_d4) );
	
	if (x&0x8)
	{
		lcd_PORT |= (1<<lcd_d7);
	}
	if(x&0x4) {
		lcd_PORT |= (1<<lcd_d6);
	}
	if(x&0x2) {
		lcd_PORT |= (1<<lcd_d5);
	}
	if (x&0x1)
	{
		lcd_PORT |= (1<<lcd_d4);
	}
	en_pulse();
}

void send_byte(uint8_t value,uint8_t rs) {
	if(rs) 
	{
		rs_PORT |= (1<<rs_pin);
	} 
	else
	{
		rs_PORT &= ~(1<<rs_pin);
	}
	send_nibble(value >> 4);
	send_nibble(value&0x0F);
}

void send_cmd(uint8_t value) {
	send_byte(value,0);
	if (value == 0x01 || value == 0x02)
	_delay_ms(2);
}

void send_data(uint8_t d) {
	send_byte(d,1);
}

void set_cursor(uint8_t row,uint8_t col) {
	uint8_t addr = (row ? 0x40 : 0x00) + (col & 0x0F);
	send_cmd(0x80 | addr);
}

void lcd_clear(void) {
	send_cmd(0x01);
	_delay_ms(2);
}

void lcd_home(void) {
	send_cmd(0x02);
	_delay_ms(2);
}

void lcd_print(const char *s)
{
	while(*s)
	{
		send_data((uint8_t)*s++);
	}
}

void lcd_print_uint16(uint16_t v) {
	uint16_t div = 1;
	
	while((v/div) >= 10) {
		div *= 10;
	}
	
	while(div>0) {
		send_data('0'+v/div);
		v = v%div;
		div /= 10;
	}
}

/*void lcd_print_float(float v)
{
	if (v < 0)
	{
		send_data('-');
		v = -v;
	}

	uint16_t int_part = (uint16_t)v;
	uint16_t float_part = (uint16_t)(((v - int_part) * 1000)+0.5); // 2 decimal places

	lcd_print_uint16(int_part);
	send_data('.');

	if (float_part < 10)
	{
		send_data('0');
	}

	lcd_print_uint16(float_part);
}*/

void lcd_print_float(float v)
{
	char buffer[10];
	dtostrf(v,6,2,buffer);
	buffer[9] = '\0';
	lcd_print(buffer);
}

void lcd_init(void) {
	rs_DDR |= (1<<rs_pin);
	en_DDR |= (1<<en_pin);
	lcd_DDR |= ((1<<lcd_d7) | (1<<lcd_d6) | (1<<lcd_d5) | (1<<lcd_d4));
	// for giving command to the LCD set rs = 0
	_delay_ms(20);
	rs_PORT &= ~(1<<rs_pin); 
	en_PORT &= ~(1<<en_pin);
	
	send_nibble(0x03);
	_delay_ms(5);
	send_nibble(0x03);
	_delay_us(150);
	send_nibble(0x03);
	_delay_us(150);
	
	send_nibble(0x02);
	_delay_us(150);
	
	send_cmd(0x28);
	send_cmd(0x08);
	send_cmd(0x01);
	send_cmd(0x06);
	send_cmd(0x0C);
}
/*
 * lcd.h
 *
 * Created: 10/18/2025 12:48:15 PM
 *  Author: felix
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define en_DDR DDRB
#define en_PORT PORTB
#define en_pin PB3

#define rs_DDR DDRB
#define rs_PORT PORTB
#define rs_pin PB4

#define lcd_DDR DDRD
#define lcd_PORT PORTD
#define lcd_d4 PD5
#define lcd_d5 PD4
#define lcd_d6 PD3
#define lcd_d7 PD2

void lcd_print_uint16(uint16_t v);
void lcd_print_float(float v);
void lcd_print(const char *s);
void set_cursor(uint8_t row,uint8_t col);
void send_byte(uint8_t value,uint8_t rs);
void send_cmd(uint8_t value);
void send_data(uint8_t d);
void lcd_home(void);
void lcd_clear(void);
void lcd_init(void);

#endif /* LCD_H_ */
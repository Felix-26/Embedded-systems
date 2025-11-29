/*
 * lcd.h
 *
 * Created: 11/24/2025 12:28:17 PM
 *  Author: felix
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>   
#include <stddef.h>   
#include <stdio.h>


void lcd_init(void);
void lcd_set_cursor(uint8_t row,uint8_t col);
void cursor_return(void);
void screen_clear(void);
void display(const char *s);
void send_byte(uint8_t byte,uint8_t rs);
void send_data(uint8_t c);
void send_cmd(uint8_t c);
void send_int(int i);
void send_double(double f);
void send_hex(int i);

#endif /* LCD_H_ */
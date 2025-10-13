/*
 * 162_LCD.c
 *
 * Created: 10/8/2025 8:14:50 PM
 * Author : felix
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "Icd.h"

int main(void)
{
	lcd_init();
	lcd_set_cursor(0, 0);
	lcd_print("integer : ");
	lcd_print_uint16(173);

	lcd_set_cursor(1, 0);
	lcd_print("float : ");

	// small demo: print a number
	lcd_print_float(88.7);

	/*
	while (1)
	{
		lcd_print_uint16(1234);
		_delay_ms(1000);
		lcd_clear();
		_delay_ms(1000);

	}
	*/
}

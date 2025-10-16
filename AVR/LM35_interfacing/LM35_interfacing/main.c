/*
 * LM35.c
 *
 * Created: 10/13/2025 8:44:39 PM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "Icd.h"
#include "adc.h"

int main(void) {
    uint16_t adc_value;
	lcd_init();
	adc_init();
	while (1) 
    {
		float temp;
		lcd_clear();
		adc_value = adc_read(1);
		lcd_set_cursor(0,0);
		temp = adc_value*0.488;
		lcd_print("Temperature:");
		lcd_set_cursor(1,0);
		lcd_print_float(temp);
		lcd_data(0xDF);
		lcd_print("C");
		_delay_ms(500);
		
	}
}


/*
 * ADC.c
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
		lcd_clear();
		adc_value = adc_read(1);
		lcd_set_cursor(0,0);
		lcd_print("ADC value : ");
		lcd_print_uint16(adc_value);
		lcd_set_cursor(1,0);
		_delay_ms(1000);
		
	}
}


/*
 * Barometer-Thermometer.c
 *
 * Created: 11/24/2025 10:29:52 AM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "i2c.h"
#include "BMP280.h"

int main(void)
{
	lcd_init();
	i2c_init();
	temp_init();
	pres_init();
    while (1) 
    {
		display("T: ");
		send_double(get_temp());
		send_data(0b11011111);
		send_data('C');

		lcd_set_cursor(1,0);
		display("P: ");
		send_double(get_pres()/100.0);
		display("hPa");
		_delay_ms(1000);
		cursor_return();
    }
}


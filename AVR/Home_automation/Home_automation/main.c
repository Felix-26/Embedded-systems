/*
 * Home_automation.c
 *
 * Created: 10/18/2025 11:16:11 AM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "light.h"
#include "temperture.h"
#include "uart.h"
#include "delay.h"


int main(void)
{
	sei();
	delay_init();
	const char buffer[20];
	const char t[10];
	lcd_init();
	thermo_init();
	uart_TX_init();
	light_init();
	while(1) {
		set_cursor(0,0);
		lcd_print("temp");
		float temp = thermo(0);
		lcd_print_float(temp);
		send_data(0xDF);
		lcd_print("C");
		dtostrf(temp,6,2,t);
		sprintf(buffer,"temp : %s\n",t);
 		uart_transfer(buffer);
		light_control();
		delay_ms(1000);
	}
}


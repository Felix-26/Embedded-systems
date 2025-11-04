/*
 * BMP280.c
 *
 * Created: 11/3/2025 10:10:03 PM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "uart.h"
#include "temp.h"

int main(void)
{
	double temp;
	spi_init();
	bmp280_init();
	uart_init(9600);   
    while (1) 
    {
		write_data(0xF4,0x27);
		while (read_data(0xF3) & 0x08);
		_delay_ms(100);
		temp = get_temp();
		uart_send_string("Temperature = ");
		uart_send_double(temp);
		uart_tx(176);
		uart_tx('C');
		uart_tx('\n');
// 		write_data(0xF4, 0x27);           // Try writing normal mode
// 		_delay_ms(5);
// 		uint8_t val = read_data(0xF4);
// 		uart_send_string("F4 = ");
// 		uart_send_hex(val);
// 		uart_send_string("\r\n");

		_delay_ms(2000);
    }
}


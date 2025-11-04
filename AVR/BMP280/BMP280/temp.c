/*
 * temp.c
 *
 * Created: 11/4/2025 12:02:28 AM
 *  Author: felix
 */ 

#include <avr/io.h>
#include "spi.h"

static uint16_t dig_T1;
static int16_t dig_T2, dig_T3;

void bmp280_init(void)
{
	// Read calibration registers once
	dig_T1 = read_data(0x88) | (read_data(0x89) << 8);
	dig_T2 = read_data(0x8A) | (read_data(0x8B) << 8);
	dig_T3 = read_data(0x8C) | (read_data(0x8D) << 8);
}

double get_temp(void)
{
	uint8_t MSB,LSB,XSB;
	uint32_t adc_t;
	
	double var1,var2;
	
	write_data(0xF4,0x27);
	
	MSB = read_data(0xFA);
	LSB = read_data(0XFB);
	XSB = read_data(0XFC);
	
	adc_t = (uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XSB>>4;
	
	
	var1 = (((double)adc_t/16384.0)-((double)dig_T1/1024.0))*(double)dig_T2;
	var2 = var2 = ((((double)adc_t)/131072.0 - ((double)dig_T1)/8192.0) *
	(((double)adc_t)/131072.0 - ((double)dig_T1)/8192.0)) *
	((double)dig_T3);

	double T = (var1+var2)/5120.0;
	
	return T;
}
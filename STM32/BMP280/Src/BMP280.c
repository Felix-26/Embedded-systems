/*
 * BMP280.c
 *
 *  Created on: Dec 3, 2025
 *      Author: felix
 */


#include <stdint.h>
#include "i2c.h"

// data acquistion options of the device
static uint8_t ctrl_meas = ~(0xF);
// sets rate,filter and interface options of the device
static uint8_t config = ~(0xF);
// temperature calculating constants
static 	uint16_t dig_T1;
static  int16_t dig_T2;
static  int16_t dig_T3;
// pressure calculating constants
static uint16_t dig_P1;
static int16_t dig_P2;
static int16_t dig_P3;
static int16_t dig_P4;
static int16_t dig_P5;
static int16_t dig_P6;
static int16_t dig_P7;
static int16_t dig_P8;
static int16_t dig_P9;

static	uint32_t t_fine;

void temp_init(void)
{
	uint8_t bytes[2];
	uint8_t osrs_t = 0b101;
	uint8_t mode = 0b11;
	ctrl_meas |= ((osrs_t << 5)  | mode);

	uint8_t t_sb = 0b101;
	uint8_t filter = 0b100;
	config = ((t_sb << 5) | (filter<<2));

	i2c_WRITE(0x76,0xF4,ctrl_meas);
	i2c_WRITE(0x76,0xF5,config);

	i2c_READ(0x76,0x88,bytes,2);
	dig_T1 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x8A,bytes,2);
	dig_T2 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x8C,bytes,2);
	dig_T3 = (bytes[1]<<8|bytes[0]);
}

void pres_init(void)
{
	uint8_t bytes[2];
	uint8_t osrs_p = 0b101;
	uint8_t mode = 0b11;
	ctrl_meas |= ((osrs_p <<2)  | mode);

	uint8_t t_sb = 0b101;
	uint8_t filter = 0b100;
	config = ((t_sb << 5) | (filter<<2));

	i2c_WRITE(0x76,0xF4,ctrl_meas);
	i2c_WRITE(0x76,0xF5,config);

	i2c_READ(0x76,0x8E,bytes,2);
	dig_P1 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x90,bytes,2);
	dig_P2 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x92,bytes,2);
	dig_P3 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x94,bytes,2);
	dig_P4 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x96,bytes,2);
	dig_P5 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x98,bytes,2);
	dig_P6 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x9A,bytes,2);
	dig_P7 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x9C,bytes,2);
	dig_P8 = (bytes[1]<<8|bytes[0]);
	i2c_READ(0x76,0x9E,bytes,2);
	dig_P9 = (bytes[1]<<8|bytes[0]);
}

uint32_t get_adc_T(void)
{
	uint8_t bytes[3];

	i2c_READ(0X76,0XFA,bytes,3);
	return ((uint32_t)bytes[0]<<12 | (uint32_t)bytes[1]<<4 | (uint32_t)bytes[2]>>4);
}

uint32_t get_adc_P(void)
{
	uint8_t bytes[3];

	i2c_READ(0X76,0XF7,bytes,3);
	return ((uint32_t)bytes[0]<<12 | (uint32_t)bytes[1]<<4 | (uint32_t)bytes[2]>>4);
}

static void get_t_fine()
{
	uint32_t adc_T;
	double var1, var2;

	adc_T = get_adc_T();
	var1 = (((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) *
	(((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0)) *
	((double)dig_T3);

	t_fine = (int32_t)(var1 + var2);
}

double get_temp(void)
{
	get_t_fine();
	double T = t_fine / 5120.0;
	return T;
}

double get_pres(void)
{
	double var1, var2, P;
	uint32_t adc_P = get_adc_P();

	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);

	if (var1 == 0.0)
	return 0; // avoid divide by zero

	P = 1048576.0 - (double)adc_P;
	P = (P - (var2 / 4096.0)) * 6250.0 / var1;

	var1 = ((double)dig_P9) * P * P / 2147483648.0;
	var2 = P * ((double)dig_P8) / 32768.0;

	P = P + (var1 + var2 + ((double)dig_P7)) / 16.0;

	return P; // Pressure [Pa]
}

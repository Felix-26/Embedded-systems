/*
 * BMP280.c
 *
 * Created: 11/29/2025 12:15:25 AM
 *  Author: felix
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
	uint8_t osrs_t = 0b101;
	uint8_t mode = 0b11;
	ctrl_meas |= ((osrs_t << 5)  | mode);
	
	uint8_t t_sb = 0b101;
	uint8_t filter = 0b100;
	config = ((t_sb << 5) | (filter<<2));
	
	i2c_WRITE(0x76,0xF4,ctrl_meas);
	i2c_WRITE(0x76,0xF5,config);
	
	dig_T1 = i2c_READ16(0x76,0x88);
	dig_T2 = i2c_READ16(0x76,0x8A);
	dig_T3 = i2c_READ16(0x76,0x8C);
}

void pres_init(void)
{
	uint8_t osrs_p = 0b101;
	uint8_t mode = 0b11;
	ctrl_meas |= ((osrs_p <<2)  | mode);
	
	uint8_t t_sb = 0b101;
	uint8_t filter = 0b100;
	config = ((t_sb << 5) | (filter<<2));
	
	i2c_WRITE(0x76,0xF4,ctrl_meas);
	i2c_WRITE(0x76,0xF5,config);
	
	dig_P1 = i2c_READ16(0x76,0x8E);
	dig_P2 = i2c_READ16(0x76,0x90);
	dig_P3 = i2c_READ16(0x76,0x92);
	dig_P4 = i2c_READ16(0x76,0x94);
	dig_P5 = i2c_READ16(0x76,0x96);
	dig_P6 = i2c_READ16(0x76,0x98);
	dig_P7 = i2c_READ16(0x76,0x9A);
	dig_P8 = i2c_READ16(0x76,0x9C);
	dig_P9 = i2c_READ16(0x76,0x9E);
}

uint32_t get_adc_T(void)
{
	uint8_t MSB,LSB,XLSB;
	
	i2c_START();
	i2c_TRANSMIT(0X76<<1);
	i2c_TRANSMIT(0XFA);
	i2c_START();
	i2c_TRANSMIT((0X76<<1)|1);
	
	MSB = i2c_RECIEVE_with_ACK();
	LSB = i2c_RECIEVE_with_ACK();
	XLSB = i2c_RECIEVE_NACK();
	
	i2c_STOP();
	return ((uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XLSB>>4);
}

uint32_t get_adc_P(void)
{
	uint8_t MSB,LSB,XLSB;
	
	i2c_START();
	i2c_TRANSMIT(0X76<<1);
	i2c_TRANSMIT(0XF7);
	i2c_START();
	i2c_TRANSMIT((0X76<<1)|1);
	
	MSB = i2c_RECIEVE_with_ACK();
	LSB = i2c_RECIEVE_with_ACK();
	XLSB = i2c_RECIEVE_NACK();
	
	i2c_STOP();
	return ((uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XLSB>>4);
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
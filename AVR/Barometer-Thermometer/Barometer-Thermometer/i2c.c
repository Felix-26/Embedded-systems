/*
 * _12c.c
 *
 * Created: 11/24/2025 10:39:16 AM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void i2c_init(void)
{
	PRR &= (1<<PRTWI);
	TWBR = 72;
	TWCR |= (1<<TWEN);
	TWSR = 0X00;
}

void i2c_START(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void i2c_TRANSMIT(uint8_t DATA)
{
	TWDR = DATA;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

uint8_t i2c_RECIEVE_with_ACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t i2c_RECIEVE_NACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

void i2c_STOP(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
} 

uint8_t i2c_READ8(uint8_t SLA,uint8_t REG)
{
	i2c_START();
	i2c_TRANSMIT(SLA<<1);
	i2c_TRANSMIT(REG);
	
	i2c_START();
	i2c_TRANSMIT((SLA<<1)|1);
	uint8_t val = i2c_RECIEVE_NACK();
	i2c_STOP();
	
	return val;
}

uint32_t i2c_READ16(uint8_t SLA,uint8_t reg)
{
	uint8_t MSB,LSB;
	
	i2c_START();
	i2c_TRANSMIT(SLA<<1);
	i2c_TRANSMIT(reg);
	i2c_START();
	i2c_TRANSMIT((SLA<<1)|1);
	
	LSB = i2c_RECIEVE_with_ACK();
	MSB = i2c_RECIEVE_NACK();
	
	i2c_STOP();
	
	return (uint16_t)MSB<<8 | (uint16_t)LSB;
}

uint32_t i2c_READ32(uint8_t SLA,uint8_t reg)
{
	uint8_t MSB,LSB,XLSB;
	
	i2c_START();
	i2c_TRANSMIT(SLA<<1);
	i2c_TRANSMIT(reg);
	i2c_START();
	i2c_TRANSMIT((SLA<<1)|1);
	
	MSB = i2c_RECIEVE_with_ACK();
	LSB = i2c_RECIEVE_with_ACK();
	XLSB = i2c_RECIEVE_NACK();
	
	i2c_STOP();
	
	return ((uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XLSB>>4);
}

void i2c_WRITE(uint8_t SLA,uint8_t REG,uint8_t val)
{
	i2c_START();
	
	i2c_TRANSMIT(SLA<<1);
	i2c_TRANSMIT(REG);
	i2c_TRANSMIT(val);
	
	i2c_STOP();
		
}
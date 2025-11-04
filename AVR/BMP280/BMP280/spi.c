/*
 * spi.c
 *
 * Created: 11/3/2025 10:24:16 PM
 *  Author: felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void spi_init(void)
{
	DDRB |= (1<<PB3) | (1<<PB5) | (1<<PB2);
	DDRB &= ~(1<<PB4);
	
	PORTB |= (1<<PORTB2);
	
	SPCR = 0x00;
	SPSR = 0x00;
	
	SPCR |= (1<<SPE) |(1<<MSTR);
	SPCR |= (1<<SPR0); 
	SPCR &= ~(1<<CPOL | 1<<CPHA);
}

uint8_t spi_master_tx(uint8_t LOC)
{
	SPDR = LOC;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

uint8_t read_data(uint8_t LOC)
{
	uint8_t data,DUMMY;
	PORTB &= ~(1<<PORTB2);
	_delay_us(10);
	
	spi_master_tx(LOC|0x80);
	data = spi_master_tx(0xFF);
	
	_delay_us(10);
	PORTB |= (1<<PORTB2);
	
	return data;
}

void write_data(uint8_t LOC, uint8_t data)
{
	PORTB &= ~(1 << PORTB2);       // CS low

	spi_master_tx(LOC & 0x7F);     // MSB=0 for write
	spi_master_tx(data);
	
	PORTB |= (1 << PORTB2);        // CS high
}
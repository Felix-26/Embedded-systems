/*
 * spi.h
 *
 * Created: 11/3/2025 10:24:02 PM
 *  Author: felix
 */ 


#ifndef SPI_H_
#define SPI_H_


void spi_init(void);
uint8_t read_data(uint8_t LOC);
void write_data(uint8_t LOC,uint8_t data);


#endif /* SPI_H_ */
/*
 * i2c.c
 *
 *  Created on: Dec 3, 2025
 *      Author: felix
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "i2c.h"

void i2c_init(void)
{
	// enabling i2c1
	RCC->APB1ENR |= (1<<I2C1EN);
	// resetting i2c1 to a clean state
	RCC->APB1RSTR |= (1<<I2C1RST);
	// Release from reset state
	RCC->APB1RSTR &= ~(1 << I2C1RST);
	// enabling clock to the gpio where i2c1 is used
	GPIOB_CLK_EN();
	// setting PB8 and PB9 as alternate function mode
	GPIOB->MODER &= ~(0X3<<(PB8*2) | 0X3<<(PB9*2));
	GPIOB->MODER |= (0X2<<(PB8*2) | 0X2<<(PB9*2));
	// SDA and SCL to open-drain
	GPIOB->OTYPER |= (1<<PB8|1<<PB9);
	// output speed = high speed
	GPIOB->OSPEEDR |= (0X3<<(PB8*2)|0X3<<(PB9*2));
	// pull up resistor
	GPIOB->PUPDR &= ~(0X3<<(PB8*2) | 0X3<<(PB9*2));
	GPIOB->PUPDR |= (0X1<<(PB8*2) | 0X1<<(PB9*2));
	// selecting AF4(I2C alternate function number for gpio pin) for PB8 and PB9
	GPIOB->AFRH &= ~(0XF<<0|0XF<<4);
	GPIOB->AFRH |= (0X4<<0|0X4<<4);
	// PCLK1 frequency (42 MHz) in CR2 FREQ[5:0]
	I2C1->CR2 &= ~(0b111111);
	I2C1->CR2 |= 42;
	// SCL Clock Speed (100 kHz, Standard Mode) in CCR
	// CCR = 42,000,000 / (2 * 100,000) = 210
	I2C1->CCR = 0;
	I2C1->CCR |= 210;
	// Set Max Rise Time (43) in TRISE
    // TRISE = (1000ns / 23.8ns) + 1 = 43
	I2C1->TRISE = 0;
	I2C1->TRISE |= 43;
	// Enable Analog Filter (ANOFF = 0)
	I2C1->FLTR &= ~(1 << 4);

	// Enable Digital Filter (DNF = 1)
	I2C1->FLTR &= ~(0xF); // Clear DNF field
	I2C1->FLTR |= 1;       // Set DNF = 1
	I2C1->CR1 |= (1<<ACK);
	I2C1->CR1 |= (1<<PE);
}


void i2c_READ(uint8_t addr,uint8_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t dummy_read;

	I2C1->CR1 |= (1<<START);
	while(!(I2C1->SR1 & (1<<SB)));

	I2C1->DR = (addr<<1|0);
	while(!(I2C1->SR1 & (1<<ADDR)));
	dummy_read = I2C1->SR2;
	(void)dummy_read;

	I2C1->DR = reg;
	while(!(I2C1->SR1 & (1<<TxE)));

	I2C1->CR1 |= (1<<START);
	while(!(I2C1->SR1 & (1<<SB)));

	I2C1->DR = (addr<<1|1);
	while(!(I2C1->SR1 & (1<<ADDR)));

	if(len == 1)
	{
		I2C1->CR1 &= ~(1<<ACK);
		I2C1->CR1 |= (1<<STOP);
		dummy_read = I2C1->SR2;
		(void)dummy_read;

		while(!(I2C1->SR1 & (1<<RxNE)));

		buf[0] = I2C1->DR;
	}
	else
	{
		I2C1->CR1 |= (1<<ACK);
		dummy_read = I2C1->SR2;
		(void)dummy_read;

		for(uint8_t i=0;i<len-1;i++)
		{
			while(!(I2C1->SR1 & (1<<RxNE)));
			buf[i] = I2C1->DR;
		}

		while(!(I2C1->SR1 & (1<<RxNE)));
		I2C1->CR1 &= ~(1<<ACK);
		I2C1->CR1 |= (1<<STOP);

		buf[len-1] = I2C1->DR;
	}
}


void i2c_WRITE(uint8_t addr,uint8_t reg,uint8_t data)
{
	uint8_t dummy_read;

		I2C1->CR1 |= (1<<START);
		while(!(I2C1->SR1 & (1<<SB)));

		I2C1->DR = (addr<<1|0);
		while(!(I2C1->SR1 & (1<<ADDR)));
		dummy_read = I2C1->SR2;
		(void)dummy_read;

		I2C1->DR = reg;
		while(!(I2C1->SR1 & (1<<TxE)));

		I2C1->DR = data;
		while(!(I2C1->SR1 & (1<<TxE)));

		I2C1->CR1 |= (1<<STOP);
}

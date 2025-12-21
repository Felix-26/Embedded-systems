/*
 * USART.c
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */

#include "stm32f446xx.h"


void USART_init(void)
{
	// clk enable for usart peripheral
	USART2_PCLK_EN();

	// baud rate 115200 fCK / 8X(2-OVER8)XUSARTDIV
	USART2->BRR = 0x008B;
	// Transmitter enable
	USART2->CR1 |= (1<<3);
	// DMAT : DMA enable transmitter
	USART2->CR3 |= (1<<7);

}
void USART_start(void)
{
	// usart enable
	USART2->CR1 |= (1<<13);
}

/*
 * USART.c
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */

#include "stm32f446xx.h"


void USART_init(void)
{
	USART2_PCLK_EN();

	USART2->BRR = 0x008B;

	USART2->CR1 |= (1<<3);
	USART2->CR3 |= (1<<7);
	USART2->CR1 |= (1<<13);
}
void USART_start(void)
{

}

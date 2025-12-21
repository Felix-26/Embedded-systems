/*
 * TIM.h
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */


#include "TIM.h"

#include "stm32f446xx.h"

void TIM_init(void)
{
	TIM2_PCLK_EN();
	TIM2->PSC = 1599;
	TIM2->ARR = 99;
	TIM2->CR1 |= (1 << 4);

	TIM2->CR2 &= (0X7 << 4);
	TIM2->CR2 |= (0x2 << 4);
}

void TIM_start(void)
{
	TIM2->CR1 |= (1<<0);
}

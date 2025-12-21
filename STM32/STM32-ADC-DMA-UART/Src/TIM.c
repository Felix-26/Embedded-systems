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
	// CLK enable for TIM2
	TIM2_PCLK_EN();
	// clk = pclk/prescalar = 16000000/(1599+1) = 10000Hz
	TIM2->PSC = 1599;
	// clk = clk / 99+1 = 100Hz
	TIM2->ARR = 99;
	// up counter
	TIM2->CR1 |= (1 << 4);
	//  MMS[2:0]: Master mode selection
	TIM2->CR2 &= (0X7 << 4);
	// update trigger output
	TIM2->CR2 |= (0x2 << 4);
}

void TIM_start(void)
{
	// start timer counter
	TIM2->CR1 |= (1<<0);
}

/*
 * timer.c
 *
 *  Created on: Dec 4, 2025
 *      Author: felix
 */

#include "stm32f446xx.h"
#include "timer.h"

volatile uint8_t time = 0;

void TIM2_IRQHandler()
{
	if(TIM2->SR & (1<<UIF))
	{
		TIM2->SR = 0;
		time = 1;
	}
}


void timer2_init(void)
{
	RCC->APB1ENR |= (1<<TIM2EN);
	TIM2->PSC = 41;
	TIM2->ARR = 499999;
	TIM2->EGR |= (1<<UG);
	TIM2->CR1 |= (1<<ARPE | (1<<CEN));
	TIM2->DIER |= (1<<UIE);
	NVIC->ISER[0] |= (1<<28);
	NVIC->IPR[28] = (1<<4);
}

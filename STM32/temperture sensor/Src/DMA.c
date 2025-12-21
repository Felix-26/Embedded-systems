/*
 * DMA.c
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */


#include "stm32f446xx.h"

#define SAMPLES 100


void DMA2_init(uint16_t *adc_buffer)
{
	DMA2_PCLK_EN();


    DMA2->S[0].CR &= ~(1 << 0);


	DMA2->S[0].PAR = (uint32_t)&(ADC1->DR);
	DMA2->S[0].M0AR = (uint32_t)adc_buffer;
	DMA2->S[0].NDTR = SAMPLES;


	DMA2->S[0].CR = 0;

	DMA2->S[0].CR |= (0X1 <<13);
	DMA2->S[0].CR |= (0X1 << 11);
	DMA2->S[0].CR |= (1<<10);
	DMA2->S[0].CR |= (1<<8);
	DMA2->S[0].CR |=(1<<4);
	// Enable DMA2 Stream 0 interrupt in NVIC
	// 56 / 32 = 1 (ISER[1]), 56 % 32 = 24
	NVIC->ISER[1] |= (1 << 24);
	DMA2->S[0].CR |= (1<<0);
}

void DMA1_init(char* src)
{
	DMA1_PCLK_EN();

    DMA1->S[6].CR &= ~(1 << 0);

	DMA1->S[6].PAR = (uint32_t)&(USART2->DR);
	DMA1->S[6].M0AR = (uint32_t)src;
	DMA1->S[6].NDTR = SAMPLES;

    DMA1->S[6].CR = 0;

	DMA1->S[6].CR |= (0X4<<25);
	DMA2->S[0].CR |= (0X1 <<13);
	DMA2->S[0].CR |= (0X1 << 11);
	DMA1->S[6].CR |= (1<<10);
	DMA1->S[6].CR |= (0X1 << 6);
}

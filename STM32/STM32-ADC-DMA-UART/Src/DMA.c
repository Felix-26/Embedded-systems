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
	// enable clock for dma1
	DMA2_PCLK_EN();

	// disabling dma2
    DMA2->S[0].CR &= ~(1 << 0);
    while((DMA2->S[0].CR) & 1)
    {

    }

    // setting peripheral address as adc1->dr
	DMA2->S[0].PAR = (uint32_t)&(ADC1->DR);
	// 1st half of the buffer and second half of the buffer address too
	// M0AR and M1AR
	DMA2->S[0].M0AR = (uint32_t)adc_buffer;
	DMA2->S[0].M1AR = (uint32_t)(&adc_buffer[100]);
	// no of data transferred
	DMA2->S[0].NDTR = SAMPLES;

	// enbale DBM double buffer mode
	DMA2->S[0].CR = 0;
	// channel 0  selected [27:25]
	// DBM
	DMA2->S[0].CR |= (0X1 << 18);
	// MSIZE half word 16 bit
	DMA2->S[0].CR |= (0X1 <<13);
	// PSIZE half word 16 bit
	DMA2->S[0].CR |= (0X1 << 11);
	// memory increment
	DMA2->S[0].CR |= (1<<10);
	// circular mode
	DMA2->S[0].CR |= (1<<8);
	DMA2->S[0].CR &= ~(3 << 6); // DIR = 00 (Peripheral → Memory)
	// transfer complete interrupt enable
	DMA2->S[0].CR |= (1<<4);
	// data transfer peri to mem
	// Enable DMA2 Stream 0 interrupt in NVIC
	// 56 / 32 = 1 (ISER[1]), 56 % 32 = 24
	NVIC->ISER[1] |= (1 << 24);
	DMA2->S[0].CR |= (1<<0);
}

void DMA1_init()
{
	// enable clk
	DMA1_PCLK_EN();

	 DMA1->S[6].CR &= ~(1 << 0);
	while((DMA1->S[1].CR) & 1)
	{

	}
	// disable dma
    DMA1->S[6].CR &= ~(1 << 0);
    //while(DMA1->S[6].CR & (1 << 0));
    // peripheral addr usart data register
	DMA1->S[6].PAR = (uint32_t)&(USART2->DR);
	// 100 samples of data to transfer
	DMA1->S[6].NDTR = 20;

    DMA1->S[6].CR = 0;

    // channel 6
	DMA1->S[6].CR |= (0X4<<25);
	// msize 8 bit
	// psize 8 bit
	// mempry increment
	DMA1->S[6].CR |= (1<<10);
	// data transfer mem to peripheral
	DMA1->S[6].CR |= (0X1 << 6);
}

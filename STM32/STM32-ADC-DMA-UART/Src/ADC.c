/*
 * ADC.c
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */


#include "stm32f446xx.h"

void ADC_init(void)
{
	// clk enable macro for adc1
	ADC1_PCLK_EN();

	// ADCPRE: ADC prescaler pclk/2
	ADC_COMM->CCR |= (0x0 << 16);
	// conversion sequence
	// 0 in sq1 means 1 conversion
	ADC1->SQR3 = 0;
	// sequnce length = 1 L = 0000
	ADC1->SQR1 = 0;
	// sampling time for channel 0 set to 480 cycles (000)
	ADC1->SMPR1 = 0;
	ADC1->SMPR2 |= (0X7<<0);

	// reslution 12 bit
	ADC1->CR1 &= ~(0X3 << 24);
	// EXTEN: Trigger detection on the rising edge
	ADC1->CR2 &= ~(0x3<<28);
	ADC1->CR2 |= (0x1<<28);
	// EXTSEL[3:0]: 0110: Timer 2 TRGO event
	ADC1->CR2 &= ~(0xF<<24);
	ADC1->CR2 |= (0x6<<24);

	// ALIGN = 0 → right aligned
	ADC1->CR2 &= ~(1 << 11);
	// DMA: Direct memory access mode  | DDS DMA disable selection
	ADC1->CR2 |= (1 << 8) | (1<<9);
	// adc on
	ADC1->CR2 |= (1 << 0);
}
void ADC_Read(void)
{
	// start adc swstart
	ADC1->CR2 |= (1<<30);
}

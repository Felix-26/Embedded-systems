/*
 * ADC.c
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */


#include "stm32f446xx.h"

void ADC_init(void)
{
	ADC1_PCLK_EN();

	ADC_COMM->CCR |= (0x3 << 16);
	ADC1->SQR3 = 0;
	ADC1->SQR1 = 0;
	ADC1->SMPR1 = 0;
	ADC1->SMPR2 |= (0X7<<0);

	ADC1->CR2 |= (1 << 0);

	ADC1->CR2 &= ~(0x3<<28);
	ADC1->CR2 |= (0x1<<28);

	ADC1->CR2 &= ~(0xF<<24);
	ADC1->CR2 |= (0x6<<24);

	ADC1->CR2 |= (1 << 8) | (1<<9);

}
void ADC_Read(void)
{
	ADC1->CR2 |= (1<<30);
}

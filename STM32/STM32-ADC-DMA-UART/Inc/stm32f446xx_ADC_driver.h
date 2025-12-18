/*
 * stm32f446xx_ADC_driver.h
 *
 *  Created on: Dec 18, 2025
 *      Author: felix
 */

#ifndef STM32F446XX_ADC_DRIVER_H_
#define STM32F446XX_ADC_DRIVER_H_

#include "stm32f446xx.h"

typedef struct
{
	uint8_t				Seq_Len;		// 0 for 1 .... 15 for all
	uint32_t			Seq_Channel16_13;
	uint32_t 			Seq_Channel12_7;
	uint32_t			Seq_Channel6_1;
	uint32_t			smpr1;
	uint32_t			smpr2;
} ADC_Config_t;

typedef struct
{
	ADC_RegDef_t			*pADCx;
	ADC_Common_RegDef_t		*ADC_Com;
	ADC_Config_t			ADC_Config;
} ADC_Handle_t;


// ADC_CR2
#define ADON		0
#define CONT		1
#define DMA			8
#define DDS			9
#define SWSTART		30
#define CALIB		31
// ADC_SR
#define EOC			1
#define ADCPRE_POS	16 // Position of Prescaler bits (17:16)
#define ADCPRE_DIV8 (0x3U << ADCPRE_POS)
void ADC_PeriClockControl(ADC_RegDef_t *pADCx,uint8_t EnOrDi);


void ADC_Init(ADC_Handle_t *ADCHandle);
uint16_t ADC_Read(ADC_RegDef_t *pADCx);
void ADC_External_Trigger(ADC_RegDef_t *pADCx);

#endif /* STM32F446XX_ADC_DRIVER_H_ */

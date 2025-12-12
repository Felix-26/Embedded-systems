#include "stm32f446xx_adc_driver.h"


void ADC_PeriClockControl(ADC_RegDef_t  *pADCx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pADCx == ADC1)		ADC1_PCLK_EN();
		else if(pADCx == ADC2)	ADC2_PCLK_EN();
		else if(pADCx == ADC3)	ADC3_PCLK_EN();
	}
	else
	{
		if(pADCx == ADC1)		ADC1_PCLK_DI();
		else if(pADCx == ADC2)	ADC2_PCLK_DI();
		else if(pADCx == ADC3)	ADC3_PCLK_DI();
	}
}


void ADC_Init(ADC_Handle_t *ADCHandle)
{
	uint32_t tempreg = 0;
	ADC_PeriClockControl(ADCHandle->pADCx,ENABLE);
	uint8_t channels;

    ADCHandle->ADC_Com->CCR &= ~(0x3U << ADCPRE_POS); // Clear ADCPRE bits
    ADCHandle->ADC_Com->CCR |= ADCPRE_DIV8;

	tempreg |= ADCHandle->ADC_Config.Seq_Len << 20;
	ADCHandle->pADCx->SQR3 = tempreg;

	tempreg = 0;
	tempreg |= ADCHandle->ADC_Config.Seq_Channel16_13;
	ADCHandle->pADCx->SQR3 |= tempreg;

	tempreg = 0;
	tempreg |= ADCHandle->ADC_Config.Seq_Channel12_7;
	ADCHandle->pADCx->SQR2 |= tempreg;

	tempreg = 0;
	tempreg |= ADCHandle->ADC_Config.Seq_Channel6_1;
	ADCHandle->pADCx->SQR1 |= tempreg;

	tempreg = 0;
	tempreg |= ADCHandle->ADC_Config.smpr1;
	ADCHandle->pADCx->SMPR1 |= tempreg;

	tempreg = 0;
	tempreg |= ADCHandle->ADC_Config.smpr2;
	ADCHandle->pADCx->SMPR2 |= tempreg;

	ADCHandle->pADCx->CR2 |= (1<<ADON|1<<CONT);
	ADCHandle->pADCx->CR2 |= (1<<SWSTART);
}

uint16_t ADC_Read(ADC_RegDef_t *pADCx)
{
	// polling to check End of Conversion
	while(!(pADCx->SR & (1<<EOC)));
	// reading DR
	return pADCx->DR;
}

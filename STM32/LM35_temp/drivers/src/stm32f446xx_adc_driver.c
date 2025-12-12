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
    // 1. Clock Enable
	ADC_PeriClockControl(ADCHandle->pADCx, ENABLE);

    // ********** CRITICAL FIX 1: ADC Common Configuration (Prescaler) **********
    // The ADC clock must be configured. Setting to Div8 is safest (0b11 in ADCPRE[17:16])
    // NOTE: This assumes ADC_COMM and ADCPRE_DIV8 macros are defined in your header.
    ADC_COMM->CCR &= ~(0x3U << ADCPRE_POS); // Clear ADCPRE bits
    ADC_COMM->CCR |= ADCPRE_DIV8;           // Set prescaler to /8

    // ********** CRITICAL FIX 2: Correct Sequence Register Assignment **********
    // SQR1: Seq_Len (L, bits 23:20) and Ranks 13-16 (bits 19:0)
    ADCHandle->pADCx->SQR1 = (ADCHandle->ADC_Config.Seq_Len << 20) | ADCHandle->ADC_Config.Seq_Channel16_13;

    // SQR2: Ranks 7-12 (bits 29:0)
    ADCHandle->pADCx->SQR2 = ADCHandle->ADC_Config.Seq_Channel12_7;

    // SQR3: Ranks 1-6 (bits 29:0)
    ADCHandle->pADCx->SQR3 = ADCHandle->ADC_Config.Seq_Channel6_1;

    // 3. Sampling Time Configuration (Correct as before)
    ADCHandle->pADCx->SMPR1 = ADCHandle->ADC_Config.smpr1;
    ADCHandle->pADCx->SMPR2 = ADCHandle->ADC_Config.smpr2;

    // 4. Enable ADC (ADON)
    ADCHandle->pADCx->CR2 |= (1<<ADON);

    // ********** CRITICAL FIX 3: ADC Self-Calibration **********
    // Start calibration (CALIB = 1)
    // NOTE: This assumes CALIB macro is defined in your header.
    ADCHandle->pADCx->CR2 |= (1<<CALIB);
    // Wait for calibration to complete (CALIB bit is cleared by hardware)
    while (ADCHandle->pADCx->CR2 & (1<<CALIB));

    // 5. Start Continuous Conversion
    ADCHandle->pADCx->CR2 |= (1<<CONT) | (1<<SWSTART);
}

uint16_t ADC_Read(ADC_RegDef_t *pADCx)
{
	// polling to check End of Conversion
	while(!(pADCx->SR & (1<<EOC)));
	// reading DR
	return pADCx->DR;
}

//void ADC_Init(ADC_Handle_t *ADCHandle)
//{
//	uint32_t tempreg = 0;
//	ADC_PeriClockControl(ADCHandle->pADCx,ENABLE);
//	uint8_t channels;
//	tempreg |= ADCHandle->ADC_Config.SeqLen << 20;
//	ADCHandle->pADCx->SQR3 = tempreg;
//
//	tempreg = 0;
//	tempreg |= ADCHandle->ADC_Config.Seq_Channel16_13;
//	ADCHandle->pADCx->SQR3 |= tempreg;
//
//	tempreg = 0;
//	tempreg |= ADCHandle->ADC_Config.Seq_Channel12_7;
//	ADCHandle->pADCx->SQR2 |= tempreg;
//
//	tempreg = 0;
//	tempreg |= ADCHandle->ADC_Config.Seq_Channel6_1;
//	ADCHandle->pADCx->SQR3 |= tempreg;
//
//	tempreg = 0;
//	tempreg |= ADCHandle->ADC_Config.smpr1;
//	ADCHandle->pADCx->SMPR1 |= tempreg;
//
//	tempreg = 0;
//	tempreg |= ADCHandle->ADC_Config.smpr2;
//	ADCHandle->pADCx->SMPR2 |= tempreg;
//
//	ADCHandle->pADCx->CR2 |= (1<<ADON|1<<CONT);
//	ADCHandle->pADCx->CR2 |= 1<<SWSTART;
//}
//
//uint16_t ADC_Read(ADC_RegDef_t *pADCx)
//{
//	// polling to check End of Conversion
//	while(!(pADCx->SR & (1<<EOC)));
//	// reading DR
//	uint16_t dr = pADCx->DR;
//}

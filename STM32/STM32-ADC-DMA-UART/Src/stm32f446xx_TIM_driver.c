/*
 * stm32f446xx_TIM_driver.c
 *
 *  Created on: Dec 18, 2025
 *      Author: felix
 */


#include <stm32f446xx_TIM_driver.h>

void TIM_PeriClockControl(TIM_RegDef_t *pTIMx,uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pTIMx == TIM2)
			TIM2_PCLK_EN();
		else if(pTIMx == TIM3)
			TIM3_PCLK_EN();
		else if(pTIMx == TIM4)
			TIM4_PCLK_EN();
		else if(pTIMx == TIM5)
			TIM5_PCLK_EN();
	}
	else
	{
		if(pTIMx == TIM2)
			TIM2_PCLK_DI();
		else if(pTIMx == TIM3)
			TIM3_PCLK_DI();
		else if(pTIMx == TIM4)
			TIM4_PCLK_DI();
		else if(pTIMx == TIM5)
			TIM5_PCLK_DI();
	}
}


void TIM_Init(TIM_Handle_t *pTIMHandle)
{
	// enable clock for TIMx
	TIM_PeriClockControl(pTIMHandle->pTIMx,ENABLE);
	// configure the prescalar and auto reload value
	pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_Config.Prescalar;
	pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_Config.Period;
	// configure counter mode up/down first clear then copy from handle
	pTIMHandle->pTIMx->CR1 &= ~(1 << TIM_CR1_DIR_pos);
	pTIMHandle->pTIMx->CR1 |= pTIMHandle->TIM_Config.CounterMode;
}

void TIM_DeInit(TIM_RegDef_t *pTIMx)
{
	if(pTIMx == TIM2)
		TIM2_REG_RESET();
	else if(pTIMx == TIM3)
		TIM3_REG_RESET();
	else if(pTIMx == TIM4)
		TIM4_REG_RESET();
	else if(pTIMx == TIM5)
		TIM5_REG_RESET();
}

void TIM_Trigger_config(TIM_RegDef_t *pTIMx,uint8_t mms)
{
	pTIMx->CR2 &= ~(0X7<<TIM_CR2_MMS_pos);
	pTIMx->CR2 |= (mms);
}

void TIM_Counter_Start(TIM_RegDef_t *pTIMx)
{
	pTIMx->CR1 |= (1<<TIM_CR1_CEN_pos);
}


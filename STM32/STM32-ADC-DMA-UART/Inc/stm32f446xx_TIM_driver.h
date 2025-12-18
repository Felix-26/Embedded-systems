/*
 * stm32f44xx_TIM_driver.h
 *
 *  Created on: Dec 18, 2025
 *      Author: felix
 */

#ifndef STM32F446XX_TIM_DRIVER_H_
#define STM32F446XX_TIM_DRIVER_H_

#include "stm32f446xx.h"

typedef struct {
	uint32_t 	Prescalar;				// 0 to 65535
	uint32_t 	Period;					// value to be stored in ARR
	uint32_t 	CounterMode;			// up or down counter
} TIM_Config_t;

typedef struct {
	TIM_RegDef_t		*pTIMx;				// pointer to timer base address TIM2-TIM5
	TIM_Config_t 	TIM_Config;			// timer cofiguration settings
} TIM_Handle_t;

/*
 * Bit positions
 */

// CR1 register
#define TIM_CR1_DIR_pos		4
#define TIM_CR1_CEN_pos		0
// CR2 register
#define TIM_CR2_MMS_pos		4


/*
 * MMS selection info
 */

#define TIM_TRIGGER_ON_RESET				0<<TIM_CR2_MMS_pos
#define TIM_TRIGGER_ON_ENABLE				1<<TIM_CR2_MMS_pos
#define TIM_TRIGGER_ON_UPDATE				2<<TIM_CR2_MMS_pos

/*
 * APIs for Timer
 */

void TIM_Init(TIM_Handle_t *pTIMHandle);
void TIM_DeInit(TIM_RegDef_t *pTIMx);
void TIM_Trigger_config(TIM_RegDef_t *pTIMx,uint8_t mms);
void TIM_Counter_Start(TIM_RegDef_t *pTIMx);

#endif /* STM32F446XX_TIM_DRIVER_H_ */

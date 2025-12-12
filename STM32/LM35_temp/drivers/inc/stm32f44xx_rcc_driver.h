/*
 * stm32f44xx_rcc_driver.h
 *
 *  Created on: Dec 12, 2025
 *      Author: felix
 */

#ifndef STM32F44XX_RCC_DRIVER_H_
#define STM32F44XX_RCC_DRIVER_H_

#include "stm32f446xx.h"

/*
 * Returns the APB1 peripheral clock value
 */
uint32_t RCC_GetPCLK1Value(void);

/*
 * Returns the APB2 peripheral clock value
 */
uint32_t RCC_GetPCLK2Value(void);

/*
 * Returns the PLL output clock value
 */
uint32_t RCC_GetPLLOutputClock(void);

#endif /* STM32F44XX_RCC_DRIVER_H_ */

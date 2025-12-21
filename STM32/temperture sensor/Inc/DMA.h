/*
 * DMA.h
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>

void DMA2_init(uint16_t *adc_buffer);

void DMA1_init(char* src);

#endif /* DMA_H_ */

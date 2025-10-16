/*
 * adc.h
 *
 * Created: 10/13/2025 8:47:18 PM
 *  Author: felix
 */ 


#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000UL

void adc_init(void);
uint16_t adc_read(uint16_t channel);


#endif /* ADC_H_ */
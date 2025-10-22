/*
 * light.h
 *
 * Created: 10/18/2025 11:22:28 AM
 *  Author: Felix Thomas
 */ 


#ifndef LIGHT_H_
#define LIGHT_H_

#define F_CPU 16000000UL
#include <avr/io.h>

void light_init(void);
void light_control();

#endif /* LIGHT_H_ */
/*
 * Modular_delay_gpio.c
 *
 * Created: 9/27/2025 2:36:53 PM
 * Author : felix
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include "my_delay.h"
#include "my_gpio.h"

int main(void)
{
    gpio_init();
	timer0_init();
    while (1) 
    {
		toggle_gpio();
		delay(2000);
    }
}


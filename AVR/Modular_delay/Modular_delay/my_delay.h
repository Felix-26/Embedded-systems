/*
 * my_delay.h
 *
 * Created: 9/26/2025 8:35:25 PM
 *  Author: Felix Thomas
 */ 


#ifndef MY_DELAY_H_
#define MY_DELAY_H_

// delay function receives unsigned 16 bit integer
void delay(uint16_t);			
// function to initialize register values for timer0 to be used
void timer0_init(void);			

#endif /* MY_DELAY_H_ */
/*
 * pwmfast_song.c
 *
 * Created: 10/3/2025 11:57:23 AM
 * Author : Felix Thomas
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "my_delay.h"
#include "tone_pwm.h"
#include "music.h"

int main(void)
{
	delay_init();
    while (1) 
    {
		for (int i=0;i<sizeof(melody)/sizeof(melody[0]);i++)
		{
			int freq = melody[i];
			int duration = noteDuration[i];
			
			if(freq!=0) {
				tone(freq,50);
				delay(duration);
			} else {
				no_tone();
				delay(duration);
			}
		}
    }
}


/*
 * music.h
 *
 * Created: 10/3/2025 3:29:49 PM
 *  Author: Felix Thomas
 */ 


#ifndef MUSIC_H_
#define MUSIC_H_

#include "notes.h"

extern int melody[] = {
	// Intro
	NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0, 0, NOTE_G6, 0, 0, 0,
	// Main theme
	NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
	NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0, 0,
	// Repeat / bridge
	NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
	NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0, 0,
	// Ending snippet
	NOTE_G6, NOTE_C7, NOTE_E6, NOTE_A6, NOTE_B6, NOTE_AS6, NOTE_A6, NOTE_G6
};

extern int noteDuration[] = {
	// Intro
	150, 150, 150, 150, 150, 150, 150, 150, 300, 150, 150, 300, 300, 150, 150, 300,
	// Main theme
	150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
	150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
	// Repeat / bridge
	150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
	150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
	// Ending snippet
	150, 150, 150, 150, 150, 150, 150, 150
};


#endif /* MUSIC_H_ */
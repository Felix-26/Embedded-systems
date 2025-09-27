if (!(PINB & (1<<PINB1)))		// if PIND1 bit of PIND register is cleared go inside the loop
			OCR0A = 64;					// duty cycle = 25% 
		else if (!(PINB & (1<<PINB2)))
			OCR0A = 128;				// 50%
		else if (!(PINB & (1<<PINB3)))
			OCR0A = 192;				// 75%
		else if (!(PINB & (1<<PINB4)))
			OCR0A = 255;				// 100%



// for fast PWM mode set bits WGM00 and WGM01 of TCCR0A register.
		TCCR0A |= (1<<WGM00);		
		TCCR0A |= (1<<WGM01);
		// set COM0A1 bit of TCCR0B register for non-inverting PWM signal
		TCCR0B |= (1<<COM0A1);		
		TCCR0B |= (1<<CS00);		// CLKpwm = (CLK)/(n X 256) ; n = prescalar
		//TCCR0B |= (1<<CS02);		// here n = 1024
		
		OCR0A = 128;
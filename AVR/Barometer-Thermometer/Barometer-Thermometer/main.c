/*
 * Barometer-Thermometer.c
 *
 * Created: 11/24/2025 10:29:52 AM
 * Author : felix
 */ 

#define F_CPU 16000000UL // Define the CPU clock frequency (16 MHz) for delay functions
#include <avr/io.h>
#include <util/delay.h>   // For _delay_ms()
#include <avr/interrupt.h> // For enabling global interrupts (not explicitly used here, but good practice)

#include "lcd.h"       // LCD display driver functions
#include "i2c.h"       // I2C communication functions
#include "BMP280.h"    // BMP280 sensor driver functions (get_temp, get_pres, etc.)

/**
 * @brief The main entry point of the application.
 */
int main(void)
{
	// --- Initialization Sequence ---
	
	// Initialize the LCD in 4-bit mode
	lcd_init();
	
	// Initialize the AVR's TWI (I2C) hardware
	i2c_init();
	
	// Initialize the BMP280 for temperature measurements and read temp calibration data
	temp_init();
	
	// Initialize the BMP280 for pressure measurements and read pressure calibration data
	pres_init();
	
	// Note: Global interrupts should be enabled here if background tasks were needed (e.g., sei();)
	
    while (1) // Main loop for continuous operation
    {
		// --- Temperature Display (Row 0) ---
		
		// Display the label "T: "
		display("T: ");
		
		// Get the compensated temperature (°C) and display it as a double
		send_double(get_temp());
		
		// Display the degree symbol (ASCII code 0b11011111 = 0xDF, commonly the degree symbol on HD44780)
		send_data(0b11011111);
		
		// Display the unit 'C' for Celsius
		send_data('C');

		// --- Pressure Display (Row 1) ---
		
		// Move the cursor to the second row (row 1, column 0)
		lcd_set_cursor(1,0);
		
		// Display the label "P: "
		display("P: ");
		
		// Get the compensated pressure (in Pascals, Pa)
		// Divide by 100.0 to convert Pa to hectoPascals (hPa) or millibars (mbar)
		send_double(get_pres()/100.0);
		
		// Display the unit "hPa"
		display("hPa");
		
		// --- Timing and Refresh ---
		
		// Wait for 1 second before refreshing the display
		_delay_ms(1000);
		
		// Move the cursor back to the start of the first line (0,0) for the next refresh
		cursor_return();
    }
}
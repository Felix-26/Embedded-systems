/*
 * lcd.c
 *
 * Created: 11/24/2025 12:28:37 PM
 * Author: Felix Thomas
 */ 

#define F_CPU 16000000UL // Define the CPU clock frequency for delay functions
#include <avr/io.h>     // Header for AVR I/O registers (PORTC, PORTD, etc.)
#include <util/delay.h> // Header for delay functions (_delay_ms, _delay_us)
#include <stdlib.h>     // Header for general utilities (itoa, dtostrf)

#include "names.h"      // Custom header likely defining pin assignments (RS, E, D4-D7, CTRL, DATA)

// --- Helper Functions ---

/**
 * @brief Generates the Enable (E) pulse required by the LCD to latch the data/command on the data bus.
 */
void enable_pulse(void)
{
	// E high (start pulse)
	PORTC |= (1<<E);
	_delay_us(1); // Small delay to ensure minimum pulse width
	// E low (end pulse, data latched)
	PORTC &= ~(1<<E);
	_delay_us(50); // Delay for command execution time (general purpose)
}

/**
 * @brief Sends a 4-bit nibble of data to the LCD in 4-bit mode.
 * The nibble is sent on the data pins D4-D7.
 * @param nib The 4-bit nibble (only bits 0-3 are used).
 */
void send_nibble(uint8_t nib)
{
	// Clear the data pins D4-D7 (assuming they are bits 4-7 on PORTD)
	PORTD &= ~(0x0F << 4);
	
	// Check each bit of the nibble and set the corresponding data pin (D7-D4)
	if (nib & 0x08)
	{
		PORTD |= (1<<D7); // Set D7 if bit 3 of nib is set
	}
	if (nib & 0x04)
	{
		PORTD |= (1<<D6); // Set D6 if bit 2 of nib is set
	}
	if (nib & 0x02)
	{
		PORTD |= (1<<D5); // Set D5 if bit 1 of nib is set
	}
	if (nib & 0x01)
	{
		PORTD |= (1<<D4); // Set D4 if bit 0 of nib is set
	}
	
	enable_pulse(); // Trigger the Enable pulse to latch the nibble
}

/**
 * @brief Sends a full 8-bit byte to the LCD (command or data) by splitting it into two nibbles.
 * @param byte The 8-bit command or data to send.
 * @param rs The Register Select bit: 0 for command, 1 for data.
 */
void send_byte(uint8_t byte,uint8_t rs)
{
	// Set/Clear the RS pin based on the 'rs' parameter
	if (rs==1) PORTC |= (1<<RS);   // RS = 1 (Data Register)
	else PORTC &= ~(1<<RS);        // RS = 0 (Instruction Register/Command)
		
	send_nibble(byte>>4);  // Send the higher nibble (bits 7-4) first
	send_nibble(byte&0x0F); // Send the lower nibble (bits 3-0) second
}

// --- Command and Data Functions ---

/**
 * @brief Sends a command to the LCD.
 * @param c The 8-bit instruction code.
 */
void send_cmd(uint8_t c)
{
	send_byte(c,0); // Send the byte with RS=0 (command)
	_delay_us(40);  // Wait for the command to execute (typical execution time)
	
	// Commands that require longer execution time (Clear Display, Return Home)
	if (c == 0x01 || c == 0x02)
	{
		_delay_ms(2);
	}
}

/**
 * @brief Sends a data character to the LCD for display.
 * @param c The 8-bit ASCII character data.
 */
void send_data(uint8_t c)
{
	send_byte(c,1); // Send the byte with RS=1 (data)
	_delay_us(40);  // Wait for the data write to complete
}

/**
 * @brief Displays a null-terminated string on the LCD.
 * @param s A pointer to the constant string.
 */
void display(const char *s)
{
	while(*s)
		send_data((uint8_t)*s++); // Send each character until the null terminator ('\0') is reached
}

/**
 * @brief Displays an integer on the LCD.
 * @param i The integer value to display.
 */
void send_int(int i)
{
	char buf[40];
	// Convert integer to string (base 10)
	itoa(i,buf,10);
	display(buf);
} 

/**
 * @brief Displays an integer in hexadecimal format on the LCD.
 * @param i The integer value to display.
 */
void send_hex(int i)
{
	char buf[40];
	// Convert integer to string (base 16)
	itoa(i,buf,16);
	display(buf);
}

/**
 * @brief Displays a double-precision floating-point number on the LCD.
 * @param f The double value to display.
 */
void send_double(double f)
{
	char buf[40];
	// Convert float to string (with 4 digits width, 3 decimal places)
	dtostrf(f,4,3,buf); 
	display(buf);
}

/**
 * @brief Clears the entire LCD screen and sets the cursor to home (0,0).
 */
void screen_clear(void)
{
	send_cmd(0x01); // Clear Display command
}

/**
 * @brief Returns the cursor to the home position (0,0) without clearing the display.
 */
void cursor_return(void)
{
	send_cmd(0x02); // Return Home command
}

/**
 * @brief Sets the cursor to a specific row and column.
 * @param row The row (0 for first row, 1 for second row).
 * @param col The column (0-15 typically).
 */
void lcd_set_cursor(uint8_t row,uint8_t col)
{
	// Calculate the DDRAM address based on row and column:
	// Row 0 address starts at 0x00, Row 1 address starts at 0x40.
	uint8_t addr = (row ? 0x40 : 0x00) + col;
	// Set DDRAM Address command (0x80) ORed with the calculated address
	send_cmd(0x80|addr); 
}

/**
 * @brief Initializes the LCD into 4-bit mode.
 * This is a specific sequence of commands and timings required by the HD44780 controller.
 */
void lcd_init(void)
{
	// Set RS and E pins as outputs and set them high initially (assumes CTRL is the DDR register for PORTC)
	CTRL |= (1<<RS|1<<E); 
	// Set D4-D7 pins as outputs (assumes DATA is the DDR register for PORTD)
	DATA |= (1<<D7|1<<D6|1<<D5|1<<D4); 
	
	// Initial long delay required after power-on
	_delay_ms(20);
	
	// Start initialization sequence (always in 8-bit mode for the first steps)
	PORTC &= ~(1<<RS); // Set RS low (Command mode)
	PORTC &= ~(1<<E);  // Set E low
	
	// 1. Send 0x03 (8-bit command)
	send_nibble(0x03);
	_delay_ms(5);
	
	// 2. Send 0x03
	send_nibble(0x03);
	_delay_us(150);
	
	// 3. Send 0x03
	send_nibble(0x03);
	_delay_us(150);
	
	// 4. Set 4-bit mode: Send 0x02
	send_nibble(0x02);
	_delay_us(150);
	
	// --- Now in 4-bit mode, subsequent commands must be 8-bit (two nibbles) ---
	
	// Function Set: 0x28 (4-bit mode, 2 lines, 5x8 dots)
	send_cmd(0x28);
	_delay_us(40);
	
	// Display OFF/Control: 0x08 (Display off, Cursor off, Blink off)
	send_cmd(0x08);
	_delay_us(40);
	
	// Clear Display: 0x01
	send_cmd(0x01);
	_delay_us(40);
	
	// Entry Mode Set: 0x06 (Increment cursor, no shift)
	send_cmd(0x06);
	_delay_us(40);
	
	// Display ON/Control: 0x0C (Display ON, Cursor OFF, Blink OFF) - Ready for user output
	send_cmd(0x0C);
}
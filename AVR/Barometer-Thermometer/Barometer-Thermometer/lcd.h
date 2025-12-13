/*
 * lcd.h
 *
 * Created: 11/24/2025 12:28:17 PM
 * Author: felix
 */ 


#ifndef LCD_H_ // Start of include guard: prevents multiple inclusions of this header
#define LCD_H_

// Include standard headers for necessary types and functions
#include <stdint.h>   // For standard integer types like uint8_t
#include <stddef.h>   // For size_t and NULL
#include <stdio.h>    // For standard I/O (often included for string/math conversion functions like dtostrf)


// --- Function Prototypes for LCD Driver ---

/**
 * @brief Initializes the LCD into 4-bit mode and sets display parameters.
 */
void lcd_init(void);

/**
 * @brief Sets the cursor position on the LCD display.
 * @param row The row number (0 for top, 1 for bottom).
 * @param col The column number (0-15 typically).
 */
void lcd_set_cursor(uint8_t row,uint8_t col);

/**
 * @brief Moves the cursor back to the home position (0,0) and sets display memory address to 0.
 */
void cursor_return(void);

/**
 * @brief Clears the entire LCD display and sets the cursor to home (0,0).
 */
void screen_clear(void);

/**
 * @brief Displays a null-terminated string on the LCD.
 * @param s A pointer to the constant string.
 */
void display(const char *s);

/**
 * @brief Sends a full 8-bit byte to the LCD by splitting it into two 4-bit nibbles.
 * This function also handles setting the Register Select (RS) pin.
 * @param byte The 8-bit command or data to send.
 * @param rs Register Select bit: 0 for command, 1 for data.
 */
void send_byte(uint8_t byte,uint8_t rs);

/**
 * @brief Sends a single data character to the LCD (RS=1).
 * @param c The 8-bit ASCII character data.
 */
void send_data(uint8_t c);

/**
 * @brief Sends a command instruction to the LCD (RS=0).
 * @param c The 8-bit instruction code.
 */
void send_cmd(uint8_t c);

/**
 * @brief Converts an integer to a string and displays it on the LCD.
 * @param i The integer value.
 */
void send_int(int i);

/**
 * @brief Converts a double-precision float to a string and displays it on the LCD.
 * @param f The double value.
 */
void send_double(double f);

/**
 * @brief Converts an integer to a hexadecimal string and displays it on the LCD.
 * @param i The integer value.
 */
void send_hex(int i);

// --- End of Header Guard ---
#endif /* LCD_H_ */
/*
 * BMP280.c
 *
 * Created: 11/29/2025 12:15:25 AM
 * Author: felix
 */ 

#include <stdint.h>
#include "i2c.h" // Include I2C library for communication

// --- Configuration Registers and Variables ---

// data acquistion options of the device (0xF4 control register)
// Initialized to complement of 0xF to ensure bits 0-3 (mode/osrs_p) are set on first use
static uint8_t ctrl_meas = ~(0xF); 
// sets rate,filter and interface options of the device (0xF5 config register)
// Initialized to complement of 0xF to ensure bits 0-3 (spi3w_en/filter) are set on first use
static uint8_t config = ~(0xF); 

// --- Temperature Calculation Calibration Constants (Read from 0x88 to 0x8D) ---
// These are factory-programmed values for accurate temperature compensation.
static 	uint16_t dig_T1; // unsigned 16-bit
static  int16_t dig_T2;  // signed 16-bit
static  int16_t dig_T3;  // signed 16-bit

// --- Pressure Calculation Calibration Constants (Read from 0x8E to 0xA1) ---
// These are factory-programmed values for accurate pressure compensation.
static uint16_t dig_P1; // unsigned 16-bit
static int16_t dig_P2;  // signed 16-bit
static int16_t dig_P3;  // signed 16-bit
static int16_t dig_P4;  // signed 16-bit
static int16_t dig_P5;  // signed 16-bit
static int16_t dig_P6;  // signed 16-bit
static int16_t dig_P7;  // signed 16-bit
static int16_t dig_P8;  // signed 16-bit
static int16_t dig_P9;  // signed 16-bit

// Variable for fine temperature resolution compensation value, used by both temp and pressure calculations
static	uint32_t t_fine; 

// --- Initialization Functions ---

/**
 * @brief Initializes the BMP280 for temperature measurements.
 * Configures oversampling and device mode, and reads temperature calibration data.
 */
void temp_init(void)
{	
	// Set temperature oversampling rate (osrs_t bits 7:5 in ctrl_meas register 0xF4)
	// 0b101 corresponds to x16 oversampling (highest resolution)
	uint8_t osrs_t = 0b101; 
	// Set device mode (mode bits 1:0 in ctrl_meas register 0xF4)
	// 0b11 corresponds to Normal mode
	uint8_t mode = 0b11;
	// Combine osrs_t (shifted to bits 7:5) and mode (bits 1:0) into ctrl_meas
	ctrl_meas |= ((osrs_t << 5)  | mode);
	
	// Set standby time (t_sb bits 7:5 in config register 0xF5)
	// 0b101 corresponds to 1000ms standby time
	uint8_t t_sb = 0b101;
	// Set IIR filter coefficient (filter bits 4:2 in config register 0xF5)
	// 0b100 corresponds to coefficient 16
	uint8_t filter = 0b100;
	// Combine t_sb (shifted to bits 7:5) and filter (shifted to bits 4:2) into config
	config = ((t_sb << 5) | (filter<<2));
	
	// Write ctrl_meas to register 0xF4 (control/measurement)
	i2c_WRITE(0x76,0xF4,ctrl_meas);
	// Write config to register 0xF5 (config)
	i2c_WRITE(0x76,0xF5,config);
	
	// Read and store temperature calibration values (16-bit reads)
	dig_T1 = i2c_READ16(0x76,0x88);
	dig_T2 = i2c_READ16(0x76,0x8A);
	dig_T3 = i2c_READ16(0x76,0x8C);
}

/**
 * @brief Initializes the BMP280 for pressure measurements.
 * Configures oversampling and device mode, and reads pressure calibration data.
 */
void pres_init(void)
{
	// Set pressure oversampling rate (osrs_p bits 4:2 in ctrl_meas register 0xF4)
	// 0b101 corresponds to x16 oversampling (highest resolution)
	uint8_t osrs_p = 0b101;
	// Set device mode (mode bits 1:0 in ctrl_meas register 0xF4)
	// 0b11 corresponds to Normal mode
	uint8_t mode = 0b11;
	// Combine osrs_p (shifted to bits 4:2) and mode (bits 1:0) into ctrl_meas
	ctrl_meas |= ((osrs_p <<2)  | mode);
	
	// Set standby time (t_sb bits 7:5 in config register 0xF5)
	uint8_t t_sb = 0b101;
	// Set IIR filter coefficient (filter bits 4:2 in config register 0xF5)
	uint8_t filter = 0b100;
	// Combine t_sb and filter into config
	config = ((t_sb << 5) | (filter<<2));
	
	// Write ctrl_meas to register 0xF4
	i2c_WRITE(0x76,0xF4,ctrl_meas);
	// Write config to register 0xF5
	i2c_WRITE(0x76,0xF5,config);
	
	// Read and store pressure calibration values (16-bit reads)
	dig_P1 = i2c_READ16(0x76,0x8E);
	dig_P2 = i2c_READ16(0x76,0x90);
	dig_P3 = i2c_READ16(0x76,0x92);
	dig_P4 = i2c_READ16(0x76,0x94);
	dig_P5 = i2c_READ16(0x76,0x96);
	dig_P6 = i2c_READ16(0x76,0x98);
	dig_P7 = i2c_READ16(0x76,0x9A);
	dig_P8 = i2c_READ16(0x76,0x9C);
	dig_P9 = i2c_READ16(0x76,0x9E);
}

// --- Raw ADC Reading Functions ---

/**
 * @brief Reads the raw 20-bit temperature ADC value from the BMP280.
 * @return The uncompensated temperature value as a 32-bit integer.
 */
uint32_t get_adc_T(void)
{
	uint8_t MSB,LSB,XLSB;
	
	// Start I2C communication to read temperature registers (0xFA, 0xFB, 0xFC)
	i2c_START();
	i2c_TRANSMIT(0X76<<1);    // Send device address (0x76) + Write bit (0)
	i2c_TRANSMIT(0XFA);       // Send starting register address (temp MSB)
	i2c_START();              // Repeated START condition
	i2c_TRANSMIT((0X76<<1)|1); // Send device address (0x76) + Read bit (1)
	
	// Read 3 bytes: MSB, LSB, XLSB
	MSB = i2c_RECIEVE_with_ACK(); // Temp MSB (bits 19:12)
	LSB = i2c_RECIEVE_with_ACK(); // Temp LSB (bits 11:4)
	XLSB = i2c_RECIEVE_NACK();    // Temp XLSB (bits 3:0 in bits 7:4 of the byte)
	
	i2c_STOP();
	// Construct the 20-bit raw ADC value: (MSB << 12) | (LSB << 4) | (XLSB >> 4)
	return ((uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XLSB>>4);
}

/**
 * @brief Reads the raw 20-bit pressure ADC value from the BMP280.
 * @return The uncompensated pressure value as a 32-bit integer.
 */
uint32_t get_adc_P(void)
{
	uint8_t MSB,LSB,XLSB;
	
	// Start I2C communication to read pressure registers (0xF7, 0xF8, 0xF9)
	i2c_START();
	i2c_TRANSMIT(0X76<<1);    // Send device address (0x76) + Write bit (0)
	i2c_TRANSMIT(0XF7);       // Send starting register address (pressure MSB)
	i2c_START();              // Repeated START condition
	i2c_TRANSMIT((0X76<<1)|1); // Send device address (0x76) + Read bit (1)
	
	// Read 3 bytes: MSB, LSB, XLSB
	MSB = i2c_RECIEVE_with_ACK(); // Pressure MSB (bits 19:12)
	LSB = i2c_RECIEVE_with_ACK(); // Pressure LSB (bits 11:4)
	XLSB = i2c_RECIEVE_NACK();    // Pressure XLSB (bits 3:0 in bits 7:4 of the byte)
	
	i2c_STOP();
	// Construct the 20-bit raw ADC value: (MSB << 12) | (LSB << 4) | (XLSB >> 4)
	return ((uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XLSB>>4);
}

// --- Compensation and Calculation Functions ---

/**
 * @brief Calculates the fine resolution temperature compensation value (t_fine).
 * This value is required for both temperature and pressure compensation formulas.
 * It is stored in the global static variable t_fine.
 */
static void get_t_fine()
{
	uint32_t adc_T;
	double var1, var2;
	
	// Read raw temperature ADC value
	adc_T = get_adc_T();
	
	// The following calculations implement the formula from the BMP280 datasheet
	// to calculate the 32-bit t_fine value.
	var1 = (((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) *
	(((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0)) *
	((double)dig_T3);

	// t_fine is a signed 32-bit integer, but stored as uint32_t globally
	t_fine = (int32_t)(var1 + var2);
}

/**
 * @brief Calculates the compensated temperature in degrees Celsius (°C).
 * @return The temperature value as a double-precision floating point number.
 */
double get_temp(void)
{
	// Calculate the t_fine value first, as it's the intermediate temperature compensation value
	get_t_fine();
	// Convert t_fine into the final temperature value (T = t_fine / 5120.0)
	double T = t_fine / 5120.0;
	return T;
}

/**
 * @brief Calculates the compensated pressure in Pascals (Pa).
 * Note: get_t_fine() must be called before this function for accurate results.
 * @return The pressure value as a double-precision floating point number.
 */
double get_pres(void)
{
	double var1, var2, P;
	// Read raw pressure ADC value
	uint32_t adc_P = get_adc_P();
	
	// The following calculations implement the pressure compensation formula
	// from the BMP280 datasheet, using the stored t_fine value.
	
	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);

	if (var1 == 0.0)
	return 0; // avoid divide by zero if dig_P1 leads to zero var1

	P = 1048576.0 - (double)adc_P;
	// Calculate intermediate pressure value
	P = (P - (var2 / 4096.0)) * 6250.0 / var1;

	// Apply final compensation using dig_P7, dig_P8, and dig_P9
	var1 = ((double)dig_P9) * P * P / 2147483648.0;
	var2 = P * ((double)dig_P8) / 32768.0;

	P = P + (var1 + var2 + ((double)dig_P7)) / 16.0;

	return P; // Return Pressure in Pascals [Pa]
}
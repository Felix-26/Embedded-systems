/*
 * BMP280.h
 *
 * Created: 11/29/2025 12:15:05 AM
 * Author: felix
 */ 


#ifndef BMP280_H_
#define BMP280_H_

// --- Function Prototypes for BMP280 Driver ---

/**
 * @brief Initializes the BMP280 for temperature measurements and reads calibration data.
 */
void temp_init(void);

/**
 * @brief Initializes the BMP280 for pressure measurements and reads calibration data.
 */
void pres_init(void);

/**
 * @brief Reads the raw ADC temperature value, applies compensation, and returns temperature in °C.
 * @return The compensated temperature in degrees Celsius (°C).
 */
double get_temp(void);

/**
 * @brief Reads the raw ADC pressure value, applies compensation using t_fine, and returns pressure in Pa.
 * @return The compensated atmospheric pressure in Pascals (Pa).
 */
double get_pres(void);


// --- End of Header Guard ---
#endif /* BMP280_H_ */
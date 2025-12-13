/*
 * i2c.h
 *
 * Created: 11/24/2025 10:38:54 AM
 * Author: felix
 */ 


#ifndef I2C_H_ // Start of include guard
#define I2C_H_

// --- Function Prototypes for I2C Communication Driver ---

/**
 * @brief Initializes the TWI (I2C) hardware and sets the clock speed.
 */
void i2c_init(void);

/**
 * @brief Generates the I2C START or Repeated START condition.
 */
void i2c_START(void);

/**
 * @brief Transmits a single byte of data (address or register data).
 * @param DATA The 8-bit data to transmit.
 */
void i2c_TRANSMIT(uint8_t DATA);

/**
 * @brief Receives a single byte of data and sends an ACK (Acknowledge).
 * Used when the Master expects more bytes.
 * @return The received 8-bit data.
 */
uint8_t i2c_RECIEVE_with_ACK(void);

/**
 * @brief Receives a single byte of data and sends a NACK (Not Acknowledge).
 * Used when the Master expects this to be the last byte.
 * @return The received 8-bit data.
 */
uint8_t i2c_RECIEVE_NACK(void);

/**
 * @brief Performs a complete I2C register read sequence for an 8-bit value.
 * @param SLA The 7-bit slave address.
 * @param reg The register address to read from.
 * @return The 8-bit value read from the register.
 */
uint8_t i2c_READ8(uint8_t SLA,uint8_t reg);

/**
 * @brief Performs a complete I2C register read sequence for a 16-bit value (LSB then MSB).
 * @param SLA The 7-bit slave address.
 * @param reg The starting register address.
 * @return The 16-bit value.
 */
uint32_t i2c_READ16(uint8_t SLA,uint8_t reg);

/**
 * @brief Performs a complete I2C register read sequence for a multi-byte value (e.g., 20-bit BMP280 data).
 * @param SLA The 7-bit slave address.
 * @param reg The starting register address.
 * @return The constructed 32-bit value containing the read data.
 */
uint32_t i2c_READ32(uint8_t SLA,uint8_t reg);

/**
 * @brief Performs a complete I2C register write sequence (writes one byte to a register).
 * @param SLA The 7-bit slave address.
 * @param REG The register address to write to.
 * @param val The 8-bit value to write.
 */
void i2c_WRITE(uint8_t SLA,uint8_t REG,uint8_t val);

/**
 * @brief Generates the I2C STOP condition and releases the bus.
 */
void i2c_STOP(void);

// --- End of include guard ---
#endif /* I2C_H_ */
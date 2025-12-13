/*
 * _12c.c
 *
 * Created: 11/24/2025 10:39:16 AM
 * Author: felix
 */ 

// Define the CPU clock frequency (e.g., 16 MHz for common AVR boards)
#define F_CPU 16000000UL
#include <avr/io.h> // Header for AVR I/O registers

/**
 * @brief Initializes the TWI (Two-Wire Interface, AVR's I2C implementation) hardware.
 */
void i2c_init(void)
{
	// PRR (Power Reduction Register)
	// Clear PRTWI (Power Reduction TWI) bit to enable the TWI module (turn it on)
	PRR &= ~(1<<PRTWI);
	
	// TWBR (TWI Bit Rate Register)
	// Sets the SCL frequency. TWI Clock Frequency = F_CPU / (16 + 2 * TWBR * 4^TWPS)
	// With TWSR (prescaler) = 0 (4^0 = 1), TWBR = 72 results in:
	// 16,000,000 / (16 + 2 * 72 * 1) = 16,000,000 / 160 = 100,000 Hz (100 kHz standard)
	TWBR = 72;
	
	// TWCR (TWI Control Register)
	// Set TWEN (TWI Enable) bit to enable the TWI interface
	TWCR |= (1<<TWEN);
	
	// TWSR (TWI Status Register)
	// Set TWI Prescaler bits (TWPS1 and TWPS0) to 0, meaning a prescaler value of 1.
	TWSR = 0X00; 
}

/**
 * @brief Sends an I2C START condition.
 */
void i2c_START(void)
{
	// TWCR: Set TWINT (TWI Interrupt Flag), TWSTA (TWI START Condition), and TWEN (TWI Enable)
	// Setting TWINT initiates the operation (clears the previous interrupt).
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	// Wait until TWINT is set, indicating the START condition has been transmitted
	// and the operation is complete.
	while(!(TWCR & (1<<TWINT)));
}

/**
 * @brief Transmits a byte of data (e.g., Slave Address + R/W bit, or Data byte).
 * @param DATA The 8-bit data to transmit.
 */
void i2c_TRANSMIT(uint8_t DATA)
{
	// Load data into TWDR (TWI Data Register)
	TWDR = DATA;
	
	// TWCR: Set TWINT (clear previous interrupt) and TWEN (enable TWI) to start transmission
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	// Wait until TWINT is set, indicating data transmission is complete and ACK/NACK has been received.
	while(!(TWCR & (1<<TWINT)));
}

/**
 * @brief Receives a byte of data and sends an ACK (Acknowledge) back to the transmitter.
 * Used when more bytes are expected to follow.
 * @return The received 8-bit data.
 */
uint8_t i2c_RECIEVE_with_ACK(void)
{
	// TWCR: Set TWINT, TWEN, and TWEA (TWI Enable Acknowledge bit).
	// TWEA tells the TWI hardware to send an ACK after receiving data.
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	
	// Wait until TWINT is set, indicating the byte has been received.
	while(!(TWCR & (1<<TWINT)));
	
	// Return the received data from the TWI Data Register (TWDR)
	return TWDR;
}

/**
 * @brief Receives a byte of data and sends a NACK (Not Acknowledge) back to the transmitter.
 * Used for the last byte of data to signal the end of the read sequence.
 * @return The received 8-bit data.
 */
uint8_t i2c_RECIEVE_NACK(void)
{
	// TWCR: Set TWINT and TWEN. TWEA is NOT set, so a NACK will be sent after receiving data.
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	// Wait until TWINT is set, indicating the byte has been received.
	while(!(TWCR & (1<<TWINT)));
	
	// Return the received data from the TWI Data Register (TWDR)
	return TWDR;
}

/**
 * @brief Sends an I2C STOP condition.
 */
void i2c_STOP(void)
{
	// TWCR: Set TWINT, TWEN, and TWSTO (TWI STOP Condition bit).
	// This initiates the STOP condition and releases the bus.
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	// Note: We typically don't wait for TWINT after STOP as the master is done.
} 

// --- Combined I2C Read/Write Routines ---

/**
 * @brief Reads a single 8-bit register value from a slave device.
 * @param SLA The 7-bit slave address.
 * @param REG The register address to read from.
 * @return The 8-bit value read from the register.
 */
uint8_t i2c_READ8(uint8_t SLA,uint8_t REG)
{
	// 1. Send START condition
	i2c_START();
	
	// 2. Transmit Slave Address + Write bit (0)
	i2c_TRANSMIT(SLA<<1);
	
	// 3. Transmit Register Address (where to start reading)
	i2c_TRANSMIT(REG);
	
	// 4. Send Repeated START condition (required to change from Write to Read mode)
	i2c_START();
	
	// 5. Transmit Slave Address + Read bit (1)
	i2c_TRANSMIT((SLA<<1)|1);
	
	// 6. Receive data and send NACK (since this is the last byte we expect)
	uint8_t val = i2c_RECIEVE_NACK();
	
	// 7. Send STOP condition
	i2c_STOP();
	
	return val;
}

/**
 * @brief Reads a 16-bit value from two consecutive registers on a slave device.
 * Assumes Little-Endian (LSB first, then MSB).
 * @param SLA The 7-bit slave address.
 * @param reg The starting register address (for the LSB).
 * @return The 16-bit value.
 */
uint32_t i2c_READ16(uint8_t SLA,uint8_t reg)
{
	uint8_t MSB,LSB;
	
	// 1-3. Write sequence to set the register pointer (same as i2c_READ8)
	i2c_START();
	i2c_TRANSMIT(SLA<<1);
	i2c_TRANSMIT(reg);
	
	// 4-5. Repeated START and Slave Address + Read
	i2c_START();
	i2c_TRANSMIT((SLA<<1)|1);
	
	// 6. Receive LSB first and send ACK (expecting another byte)
	LSB = i2c_RECIEVE_with_ACK();
	
	// 7. Receive MSB last and send NACK (no more bytes expected)
	MSB = i2c_RECIEVE_NACK();
	
	i2c_STOP();
	
	// Combine the bytes: (MSB << 8) | LSB
	return (uint16_t)MSB<<8 | (uint16_t)LSB;
}

/**
 * @brief Reads a 20-bit or 24-bit value spread across three consecutive registers.
 * This specific implementation appears tailored for the BMP280, where a 20-bit value
 * is read (MSB, LSB, XLSB) and then the XLSB is right-shifted by 4 bits.
 * @param SLA The 7-bit slave address.
 * @param reg The starting register address (for the MSB).
 * @return The 32-bit (containing the constructed 20-bit/24-bit) value.
 */
uint32_t i2c_READ32(uint8_t SLA,uint8_t reg)
{
	uint8_t MSB,LSB,XLSB; // XLSB stands for eXtra Least Significant Byte
	
	// 1-3. Write sequence to set the register pointer (start reading from reg)
	i2c_START();
	i2c_TRANSMIT(SLA<<1);
	i2c_TRANSMIT(reg);
	
	// 4-5. Repeated START and Slave Address + Read
	i2c_START();
	i2c_TRANSMIT((SLA<<1)|1);
	
	// 6a. Receive MSB and send ACK
	MSB = i2c_RECIEVE_with_ACK();
	// 6b. Receive LSB and send ACK
	LSB = i2c_RECIEVE_with_ACK();
	// 7. Receive XLSB and send NACK
	XLSB = i2c_RECIEVE_NACK();
	
	i2c_STOP();
	
	// Combine the bytes into the final 20-bit value (common for Bosch sensors):
	// MSB (bits 19:12) << 12 | LSB (bits 11:4) << 4 | XLSB (bits 3:0) >> 4
	return ((uint32_t)MSB<<12 | (uint32_t)LSB<<4 | (uint32_t)XLSB>>4);
}

/**
 * @brief Writes a single 8-bit value to a specific register on a slave device.
 * @param SLA The 7-bit slave address.
 * @param REG The register address to write to.
 * @param val The 8-bit value to write into the register.
 */
void i2c_WRITE(uint8_t SLA,uint8_t REG,uint8_t val)
{
	// 1. Send START condition
	i2c_START();
	
	// 2. Transmit Slave Address + Write bit (0)
	i2c_TRANSMIT(SLA<<1);
	
	// 3. Transmit Register Address (where to write the data)
	i2c_TRANSMIT(REG);
	
	// 4. Transmit Data Value
	i2c_TRANSMIT(val);
	
	// 5. Send STOP condition
	i2c_STOP();
		
}
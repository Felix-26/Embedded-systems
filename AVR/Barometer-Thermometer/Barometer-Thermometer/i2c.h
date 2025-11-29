/*
 * i2c.h
 *
 * Created: 11/24/2025 10:38:54 AM
 *  Author: felix
 */ 


#ifndef I2C_H_
#define I2C_H_

void i2c_init(void);
void i2c_START(void);
void i2c_TRANSMIT(uint8_t DATA);
uint8_t i2c_RECIEVE_with_ACK(void);
uint8_t i2c_RECIEVE_NACK(void);
uint8_t i2c_READ8(uint8_t SLA,uint8_t reg);
uint32_t i2c_READ16(uint8_t SLA,uint8_t reg);
uint32_t i2c_READ32(uint8_t SLA,uint8_t reg);
void i2c_WRITE(uint8_t SLA,uint8_t REG,uint8_t val);
void i2c_STOP(void);

#endif /* I2C_H_ */
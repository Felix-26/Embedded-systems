/*
 * i2c.h
 *
 *  Created on: Dec 3, 2025
 *      Author: felix
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C1EN	21
#define I2C1RST 21
#define PB8		8
#define PB9		9
#define PE		0
#define START	8
#define STOP	9
#define SB		0
#define ADDR	1
#define TxE		7
#define RxNE	6
#define ACK		10

void i2c_init(void);
void i2c_READ(uint8_t addr,uint8_t reg,uint8_t *buf,uint8_t len);
void i2c_WRITE(uint8_t addr,uint8_t reg,uint8_t data);

#endif /* I2C_H_ */

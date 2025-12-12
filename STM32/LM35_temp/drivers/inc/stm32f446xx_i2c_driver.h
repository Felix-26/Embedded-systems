#ifndef STM32F446XX_I2C_DRIVER_H_
#define	STM32F446XX_I2C_DRIVER_H_

#include "stm32f446xx.h"

typedef struct
{
	uint32_t	I2C_SCLSpeed;
	uint8_t		I2C_DeviceAddress;
	uint8_t		I2C_AckControl;
	uint8_t		I2C_FMDutyCycle;
} I2C_Config_t;

typedef struct
{
	I2C_RegDef_t	*pI2Cx;
	I2C_Config_t	I2C_Config;
	uint8_t			*pTxBuffer;
	uint8_t			*pRxBuffer;
	uint32_t		TxLen;
	uint32_t		RxLen;
	uint8_t			TxRxState;
	uint8_t			DevAddr;
	uint32_t		RxSize;
	uint8_t			Sr;
} I2C_Handle_t;

// I2C_CR1

#define ACK			10

/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM 100000


void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi);
void I2C_Init(I2C_Handle_t *pI2CHandle);

#endif

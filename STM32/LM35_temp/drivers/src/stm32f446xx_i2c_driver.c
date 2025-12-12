
#include "stm32f446xx_i2c_driver.h"

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pI2Cx == I2C1)			I2C1_PCLK_EN();
		else if(pI2Cx == I2C2)		I2C2_PCLK_EN();
		else if(pI2Cx == I2C3)		I2C3_PCLK_EN();
	}
	else
	{
		if(pI2Cx == I2C1)			I2C1_PCLK_DI();
		else if(pI2Cx == I2C2)		I2C2_PCLK_DI();
		else if(pI2Cx == I2C3)		I2C3_PCLK_DI();
	}
}

//void I2C_RegReset(I2C_RegDef_t *pI2Cx)
//{
//	if(pI2Cx == I2C1) 	I2C1_REG_RESET();
//	else if(pI2Cx == I2C2) 	I2C2_REG_RESET();
//	else if(pI2Cx == I2C3) 	I2C3_REG_RESET();
//}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;
	// enable I2C clock
	I2C_PeriClockControl(pI2CHandle->pI2Cx,ENABLE);

	tempreg |= (pI2CHandle->I2C_Config.I2C_AckControl << ACK);
	pI2CHandle->pI2CX->CR1 = tempreg;
	// freq in cr2
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value()/1000000U;
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);
	// device own address
	tempreg = 0;
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1<<14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		ccr_value = (RCC_GetPCLK1Value()/(2 * PI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg |= (ccr_value & 0xFFF);
	}
	else
	{
		tempreg |= (1<<15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed ));
		}
		else
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed ));
		}
		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg;
	//TRISE Configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		//mode is standard mode

		tempreg = (RCC_GetPCLK1Value() /1000000U) + 1 ;

	}else
	{
		//mode is fast mode
		tempreg = ( (RCC_GetPCLK1Value() * 300) / 1000000000U ) + 1;

	}

	pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);
}

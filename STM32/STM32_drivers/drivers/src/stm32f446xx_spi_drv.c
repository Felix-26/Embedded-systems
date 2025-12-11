#include "stm32f446xx_spi_drv.h"


void SPI_PeriClockControl(SPI_RegDef *pSPIx,uint8_t EnorDi)
{
	if(EnorDi)
	{
		if		(pSPIx == SPI1)		SPI1_PCLK_EN();
		else if (pSPIx == SPI2)		SPI2_PCLK_EN();
		else if	(pSPIx == SPI3)		SPI3_PCLK_EN();
		else if (pSPIx == SPI4)		SPI4_PCLK_EN();
	}
	else
	{
		if		(pSPIx == SPI1)		SPI1_PCLK_DI();
		else if (pSPIx == SPI2)		SPI2_PCLK_DI();
		else if	(pSPIx == SPI3)		SPI3_PCLK_DI();
		else if (pSPIx == SPI4)		SPI4_PCLK_DI();
	}
}


void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// peripheral clock enable

	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);

	// configure SPI_CR1 register

	uint32_t temp = 0;
	// 1. configure device mode
	temp |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
	// 2. configure the bus
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		temp &= ~(1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		temp |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		temp &= ~(1 << SPI_CR1_BIDIMODE);
		temp |= (1 << SPI_CR1_RXONLY);
	}
	// 3.configure the spi serial clock speed
	temp |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
	// 4.configure the DFF
	temp |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;
	// configure CPOL
	temp |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
	// configure CPHA
	temp |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
	temp |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;
	pSPIHandle->pSPIx->CR1 = temp;
}



void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
		SPI_PeriClockControl(pSPIx,DISABLE);
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
		SPI_PeriClockControl(pSPIx,DISABLE);
	}
	else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
		SPI_PeriClockControl(pSPIx,DISABLE);
	}
	else if(pSPIx == SPI4)
	{
		SPI4_REG_RESET();
		SPI_PeriClockControl(pSPIx,DISABLE);
	}
}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


void SPI_SendData(SPI_RegDef *pSPIx,uint8_t *pTxBuffer,uint32_t Len)
{
	while(Len > 0)
	{
		//1. wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);

		//2. check the DFF bit in CR1
		if( (pPSIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			//16 bit DFF
			//1. load the data in to the DR
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			Len-=2;
			(uint16_t *)pTxBuffer++;
		}
		else
		{
			//8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}

void SPI_RecieveData(SPI_RegDef *pSPIx,uint8_t *pRxBuffer,uint32_t Len)
{
	while(Len > 0)
	{
		//1. wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == (uint8_t)FLAG_RESET);

		if( (pPSIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			//16 bit DFF
			//1. load the data from DR to Rxbuffer
			*((uint16_t *)pTxBuffer) = pSPIx->DR;
			Len-=2;
			(uint16_t *)pTxBuffer++;
		}
		else
		{
			//8 bit DFF
			*(pTxBuffer) = pSPIx->DR;
			Len--;
			pTxBuffer++;
		}
	}
}


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1<<SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
	}
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1<<SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);
	}
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR2 |= (1<<SPI_CR2_SSOE);
	}
	else
	{
		pSPIx->CR2 &= ~(1<<SPI_CR2_SSOE);
	}
}


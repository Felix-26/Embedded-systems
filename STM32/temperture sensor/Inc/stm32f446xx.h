/*
 * stm32f446xx.h
 *
 *  Created on: Dec 20, 2025
 *      Author: felix
 */

#ifndef STM32F446XX_H_
#define STM32F446XX_H_

#include <stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))

#define NVIC_BASEADDR          ( (__vo uint32_t*)0xE000E100 )

/*
 *  NVIC Register definition
 */

typedef struct {
    volatile uint32_t ISER[8];      /*!< Interrupt Set Enable Register           */
    uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];      /*!< Interrupt Clear Enable Register         */
    uint32_t RSERVED1[24];
    volatile uint32_t ISPR[8];      /*!< Interrupt Set Pending Register          */
    uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8];      /*!< Interrupt Clear Pending Register        */
    uint32_t RESERVED3[24];
    volatile uint32_t IABR[8];      /*!< Interrupt Active bit Register           */
    uint32_t RESERVED4[56];
    volatile uint8_t  IP[240];      /*!< Interrupt Priority Register (8Bit wide) */
    uint32_t RESERVED5[644];
    volatile uint32_t STIR;         /*!< Software Trigger Interrupt Register     */
} NVIC_RegDef_t;


/**********************************START: Bus Domain Base Addresses **********************************/
/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR                     0x40000000U
#define APB1PERIPH_BASEADDR                 PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR                 0x40010000U
#define AHB1PERIPH_BASEADDR                 0x40020000U
#define AHB2PERIPH_BASEADDR                 0x50000000U
#define AHB3PERIPH_BASEADDR                 0xA0000000U

/**********************************START: AHB1 Peripheral Base Addresses **********************************/
/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 * STM32F446xx has GPIO ports A to H (no GPIOI)
 */

#define GPIOA_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1C00)

#define RCC_BASEADDR                        (AHB1PERIPH_BASEADDR + 0x3800)
#define DMA1_BASEADDR                       (AHB1PERIPH_BASEADDR + 0x6000)
#define DMA2_BASEADDR                       (AHB1PERIPH_BASEADDR + 0x6400)

/**********************************START: APB1 Peripheral Base Addresses **********************************/
/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */

#define TIM2_BASEADDR                       (APB1PERIPH_BASEADDR + 0x0000)
#define TIM3_BASEADDR                       (APB1PERIPH_BASEADDR + 0x0400)
#define TIM4_BASEADDR                       (APB1PERIPH_BASEADDR + 0x0800)
#define TIM5_BASEADDR                       (APB1PERIPH_BASEADDR + 0x0C00)
#define TIM6_BASEADDR                       (APB1PERIPH_BASEADDR + 0x1000)
#define TIM7_BASEADDR                       (APB1PERIPH_BASEADDR + 0x1400)
#define TIM12_BASEADDR                      (APB1PERIPH_BASEADDR + 0x1800)
#define TIM13_BASEADDR                      (APB1PERIPH_BASEADDR + 0x1C00)
#define TIM14_BASEADDR                      (APB1PERIPH_BASEADDR + 0x2000)

#define USART2_BASEADDR                     (APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR                     (APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR                      (APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR                      (APB1PERIPH_BASEADDR + 0x5000)

/**********************************START: APB2 Peripheral Base Addresses **********************************/
/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */

#define TIM1_BASEADDR                       (APB2PERIPH_BASEADDR + 0x0000)
#define TIM8_BASEADDR                       (APB2PERIPH_BASEADDR + 0x0400)

#define USART1_BASEADDR                     (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR                     (APB2PERIPH_BASEADDR + 0x1400)

#define ADC1_BASEADDR                       (APB2PERIPH_BASEADDR + 0x2000)
#define ADC2_BASEADDR                       (APB2PERIPH_BASEADDR + 0x2100)
#define ADC3_BASEADDR                       (APB2PERIPH_BASEADDR + 0x2200)
#define ADC_COMMON_BASEADDR                 (APB2PERIPH_BASEADDR + 0x2300)

/**********************************peripheral register definition structures **********************************/

/*
 * Peripheral register definition structure for GPIO
 */
typedef struct
{
    __vo uint32_t MODER;                    /*!< GPIO port mode register,                       Address offset: 0x00 */
    __vo uint32_t OTYPER;                   /*!< GPIO port output type register,                Address offset: 0x04 */
    __vo uint32_t OSPEEDR;                  /*!< GPIO port output speed register,               Address offset: 0x08 */
    __vo uint32_t PUPDR;                    /*!< GPIO port pull-up/pull-down register,          Address offset: 0x0C */
    __vo uint32_t IDR;                      /*!< GPIO port input data register,                 Address offset: 0x10 */
    __vo uint32_t ODR;                      /*!< GPIO port output data register,                Address offset: 0x14 */
    __vo uint32_t BSRR;                     /*!< GPIO port bit set/reset register,              Address offset: 0x18 */
    __vo uint32_t LCKR;                     /*!< GPIO port configuration lock register,         Address offset: 0x1C */
    __vo uint32_t AFR[2];                   /*!< AFR[0]: GPIO alternate function low register,  Address offset: 0x20 */
                                            /*!< AFR[1]: GPIO alternate function high register, Address offset: 0x24 */
} GPIO_RegDef_t;


/*
 * Peripheral register definition structure for RCC
 */
typedef struct
{
    __vo uint32_t CR;                       /*!< RCC clock control register,                            Address offset: 0x00 */
    __vo uint32_t PLLCFGR;                  /*!< RCC PLL configuration register,                        Address offset: 0x04 */
    __vo uint32_t CFGR;                     /*!< RCC clock configuration register,                      Address offset: 0x08 */
    __vo uint32_t CIR;                      /*!< RCC clock interrupt register,                          Address offset: 0x0C */
    __vo uint32_t AHB1RSTR;                 /*!< RCC AHB1 peripheral reset register,                    Address offset: 0x10 */
    __vo uint32_t AHB2RSTR;                 /*!< RCC AHB2 peripheral reset register,                    Address offset: 0x14 */
    __vo uint32_t AHB3RSTR;                 /*!< RCC AHB3 peripheral reset register,                    Address offset: 0x18 */
    uint32_t      RESERVED0;                /*!< Reserved,                                              Address offset: 0x1C */
    __vo uint32_t APB1RSTR;                 /*!< RCC APB1 peripheral reset register,                    Address offset: 0x20 */
    __vo uint32_t APB2RSTR;                 /*!< RCC APB2 peripheral reset register,                    Address offset: 0x24 */
    uint32_t      RESERVED1[2];             /*!< Reserved,                                              Address offset: 0x28-0x2C */
    __vo uint32_t AHB1ENR;                  /*!< RCC AHB1 peripheral clock enable register,             Address offset: 0x30 */
    __vo uint32_t AHB2ENR;                  /*!< RCC AHB2 peripheral clock enable register,             Address offset: 0x34 */
    __vo uint32_t AHB3ENR;                  /*!< RCC AHB3 peripheral clock enable register,             Address offset: 0x38 */
    uint32_t      RESERVED2;                /*!< Reserved,                                              Address offset: 0x3C */
    __vo uint32_t APB1ENR;                  /*!< RCC APB1 peripheral clock enable register,             Address offset: 0x40 */
    __vo uint32_t APB2ENR;                  /*!< RCC APB2 peripheral clock enable register,             Address offset: 0x44 */
    uint32_t      RESERVED3[2];             /*!< Reserved,                                              Address offset: 0x48-0x4C */
    __vo uint32_t AHB1LPENR;                /*!< RCC AHB1 peripheral clock enable in low power mode,    Address offset: 0x50 */
    __vo uint32_t AHB2LPENR;                /*!< RCC AHB2 peripheral clock enable in low power mode,    Address offset: 0x54 */
    __vo uint32_t AHB3LPENR;                /*!< RCC AHB3 peripheral clock enable in low power mode,    Address offset: 0x58 */
    uint32_t      RESERVED4;                /*!< Reserved,                                              Address offset: 0x5C */
    __vo uint32_t APB1LPENR;                /*!< RCC APB1 peripheral clock enable in low power mode,    Address offset: 0x60 */
    __vo uint32_t APB2LPENR;                /*!< RCC APB2 peripheral clock enable in low power mode,    Address offset: 0x64 */
    uint32_t      RESERVED5[2];             /*!< Reserved,                                              Address offset: 0x68-0x6C */
    __vo uint32_t BDCR;                     /*!< RCC Backup domain control register,                    Address offset: 0x70 */
    __vo uint32_t CSR;                      /*!< RCC clock control & status register,                   Address offset: 0x74 */
    uint32_t      RESERVED6[2];             /*!< Reserved,                                              Address offset: 0x78-0x7C */
    __vo uint32_t SSCGR;                    /*!< RCC spread spectrum clock generation register,         Address offset: 0x80 */
    __vo uint32_t PLLI2SCFGR;               /*!< RCC PLLI2S configuration register,                     Address offset: 0x84 */
    __vo uint32_t PLLSAICFGR;               /*!< RCC PLLSAI configuration register,                     Address offset: 0x88 */
    __vo uint32_t DCKCFGR;                  /*!< RCC dedicated clocks configuration register,           Address offset: 0x8C */
    __vo uint32_t CKGATENR;                 /*!< RCC clocks gated enable register,                      Address offset: 0x90 */
    __vo uint32_t DCKCFGR2;                 /*!< RCC dedicated clocks configuration register 2,         Address offset: 0x94 */
} RCC_RegDef_t;

/*
 * TIMx (2-5) register definition .
 */

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SCMR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t RESERVED1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t RESERVED2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	// only for TIM2 AND TIM5
	volatile uint32_t OR;

} TIM_RegDef_t;

/*
 * Peripheral register definition structure for USART
 */
typedef struct
{
    __vo uint32_t SR;                       /*!< USART status register,                         Address offset: 0x00 */
    __vo uint32_t DR;                       /*!< USART data register,                           Address offset: 0x04 */
    __vo uint32_t BRR;                      /*!< USART baud rate register,                      Address offset: 0x08 */
    __vo uint32_t CR1;                      /*!< USART control register 1,                      Address offset: 0x0C */
    __vo uint32_t CR2;                      /*!< USART control register 2,                      Address offset: 0x10 */
    __vo uint32_t CR3;                      /*!< USART control register 3,                      Address offset: 0x14 */
    __vo uint32_t GTPR;                     /*!< USART guard time and prescaler register,       Address offset: 0x18 */
} USART_RegDef_t;

/*
 * Register definition for DMA
 */

typedef struct {
  volatile uint32_t CR;     /* Stream x configuration register      */
  volatile uint32_t NDTR;   /* Stream x number of data register     */
  volatile uint32_t PAR;    /* Stream x peripheral address register */
  volatile uint32_t M0AR;   /* Stream x memory 0 address register   */
  volatile uint32_t M1AR;   /* Stream x memory 1 address register   */
  volatile uint32_t FCR;    /* Stream x FIFO control register       */
} DMA_Stream_TypeDef;

typedef struct
{
	volatile uint32_t LISR;   /* DMA low interrupt status register    */
	volatile uint32_t HISR;   /* DMA high interrupt status register   */
	volatile uint32_t LIFCR;  /* DMA low interrupt flag clear register */
	volatile uint32_t HIFCR;  /* DMA high interrupt flag clear register*/
	DMA_Stream_TypeDef S[8];
} DMA_RegDef_t;


typedef struct
{										// offsetts			register info
	__vo uint32_t SR;						// 0X00
	__vo uint32_t CR1;						// 0X04
	__vo uint32_t CR2;						// 0X08
	__vo uint32_t SMPR1;					// 0X0C
	__vo uint32_t SMPR2;					// 0X10
	__vo uint32_t JOFR1;					// 0X14
	__vo uint32_t JOFR2;					// 0X18
	__vo uint32_t JOFR3;					// 0X1C
	__vo uint32_t JOFR4;					// 0X20
	__vo uint32_t HTR;						// 0X24
	__vo uint32_t LTR;						// 0X28
	__vo uint32_t SQR1;						// 0X2C
	__vo uint32_t SQR2;						// 0X30
	__vo uint32_t SQR3;						// 0X34
	__vo uint32_t JSQR;						// 0X38
	__vo uint32_t JDR1;						// 0X3C
	__vo uint32_t JDR2;						// 0X40
	__vo uint32_t JDR3;						// 0X44
	__vo uint32_t JDR4;						// 0X48
	__vo uint32_t DR;						// 0X4C
} ADC_RegDef_t;

typedef struct
{										// offsetts			register info
	uint32_t CSR;						// 0X00
	uint32_t CCR;						// 0X04
	uint32_t CDR;						// 0X08
} ADC_Common_RegDef_t;



/**********************************Peripheral Definitions **********************************/
/*
 * Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
 */

#define GPIOA                               ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                               ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                               ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                               ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                               ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                               ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                               ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH                               ((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC                                 ((RCC_RegDef_t*)RCC_BASEADDR)

#define USART1                              ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2                              ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3                              ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4                               ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5                               ((USART_RegDef_t*)UART5_BASEADDR)
#define USART6                              ((USART_RegDef_t*)USART6_BASEADDR)

#define TIM2								((TIM_RegDef_t *)TIM2_BASEADDR)
#define TIM3								((TIM_RegDef_t *)TIM3_BASEADDR)
#define TIM4								((TIM_RegDef_t *)TIM4_BASEADDR)
#define TIM5								((TIM_RegDef_t *)TIM5_BASEADDR)

#define ADC1								((ADC_RegDef_t *)(ADC1_BASEADDR))
#define ADC2								((ADC_RegDef_t *)(ADC2_BASEADDR))
#define ADC3								((ADC_RegDef_t *)(ADC3_BASEADDR))
#define ADC_COMM							((ADC_Common_RegDef_t *)(ADC_COMMON_BASEADDR))

#define DMA1								((DMA_RegDef_t *)DMA1_BASEADDR)
#define DMA2								((DMA_RegDef_t *)DMA2_BASEADDR)

#define NVIC               					((NVIC_RegDef_t *)NVIC_BASEADDR)

/**********************************Clock Enable Macros **********************************/

/*
 * Clock Enable Macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 7))

/*
 * Timer clock enable Macros
 */

#define TIM2_PCLK_EN()						(RCC->APB1ENR |= ( 1 << 0))
#define TIM3_PCLK_EN()						(RCC->APB1ENR |= ( 1 << 1))
#define TIM4_PCLK_EN()						(RCC->APB1ENR |= ( 1 << 2))
#define TIM5_PCLK_EN()						(RCC->APB1ENR |= ( 1 << 3))


/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN()                    (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()                    (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()                    (RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()                     (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()                     (RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()                    (RCC->APB2ENR |= (1 << 5))

/*
 * Clock Enable Macros for DMA peripherals
 */
#define DMA1_PCLK_EN()                      (RCC->AHB1ENR |= (1 << 21))
#define DMA2_PCLK_EN()                      (RCC->AHB1ENR |= (1 << 22))

/*
 *Clock Enable Macros for ADC peripherals
 */

#define ADC1_PCLK_EN()						(RCC->APB2ENR |= (1 << 8))
#define ADC2_PCLK_EN()						(RCC->APB2ENR |= (1 << 9))
#define ADC3_PCLK_EN()						(RCC->APB2ENR |= (1 << 10))



#endif /* STM32F446XX_H_ */

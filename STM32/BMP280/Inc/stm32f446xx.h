/*
 * stm32f446xx.h
 *
 *  Created on: Nov 20, 2025
 *      Author: felix
 */

#ifndef STM32F446XX_H_
#define STM32F446XX_H_

// GPIO base addresses AHB1 Bus

#define GPIOA_BASEADDR		0x40020000U
#define GPIOB_BASEADDR		0x40020400U
#define GPIOC_BASEADDR		0x40020800U
#define GPIOD_BASEADDR		0x40020C00U
#define GPIOE_BASEADDR		0x40021000U
#define GPIOF_BASEADDR		0x40021400U
#define GPIOG_BASEADDR		0x40021800U
#define GPIOH_BASEADDR		0x40021C00U

// GPIO REGISTER STRUCTURE

typedef struct {
	volatile uint32_t MODER;		// GPIO port mode register					(0x00)
	volatile uint32_t OTYPER;		// GPIO port output type register			(0x04)
	volatile uint32_t OSPEEDR;		// GPIO port output speed register			(0x08)
	volatile uint32_t PUPDR;		// GPIO port pull-up/pull-down register		(0x0C)
	volatile uint32_t IDR;			// GPIO port input data register			(0x10)
	volatile uint32_t ODR;			// GPIO port output data register			(0x14)
	volatile uint32_t BSRR;			// GPIO port bit set/reset register			(0x18)
	volatile uint32_t LCKR;			// GPIO port configuration lock register	(0x1C)
	volatile uint32_t AFRL;			// GPIO alternate function low register		(0x20)
	volatile uint32_t AFRH;			// GPIO alternate function high register	(0x24)
} GPIO_RegDef_t;


// GPIO pointers

#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t *)GPIOH_BASEADDR)

// RCC base address

#define RCC_BASEADDR	0x40023800U


// RCC register structure

typedef struct
{										// offsetts			register info

	volatile uint32_t CR;				// 0X00				RCC clock control register
	volatile uint32_t PLLCFGR;			// 0X04				PLL configuration register
	volatile uint32_t CFGR;				// 0X08				RCC clock configuration register
	volatile uint32_t CIR;				// 0X0C				RCC clock interrupt register
	volatile uint32_t AHB1RSTR;			// 0X10				RCC AHB1 peripheral reset register
	volatile uint32_t AHB2RSTR;			// 0X14				RCC AHB2 peripheral reset register
	volatile uint32_t AHB3RSTR;			// 0X18				RCC AHB3 peripheral reset register
	volatile uint32_t RESERVED1;		// 0X1C
	volatile uint32_t APB1RSTR;			// 0X20				RCC APB1 peripheral reset register
	volatile uint32_t APB2RSTR;			// 0X24				RCC APB2 peripheral reset register
	volatile uint32_t RESERVED2;		// 0X28
	volatile uint32_t RESERVED3;		// 0X2C
	volatile uint32_t AHB1ENR;			// 0X30				RCC AHB1 peripheral clock enable register
	volatile uint32_t AHB2ENR;			// 0X34				RCC AHB2 peripheral clock enable register
	volatile uint32_t AHB3ENR;			// 0X38				RCC AHB3 peripheral clock enable register
	volatile uint32_t RESERVED4;		// 0X3C
	volatile uint32_t APB1ENR;			// 0X40				RCC APB1 peripheral clock enable register
	volatile uint32_t APB2ENR;			// 0X44				RCC APB2 peripheral clock enable register
	volatile uint32_t RESERVED5;		// 0X48
	volatile uint32_t RESERVER6;		// 0X4C
	volatile uint32_t AHB1LPENR;		// 0X50				RCC AHB1 peripheral clock enable in low power mode register
	volatile uint32_t AHB2LPENR;		// 0X54				RCC AHB2 peripheral clock enable in low power mode register
	volatile uint32_t AHB3LPENR;		// 0X58				RCC AHB3 peripheral clock enable in low power mode register
	volatile uint32_t RESERVER7;		// 0X5C
	volatile uint32_t APB1LPENR;		// 0X60				RCC APB1 peripheral clock enable in low power mode register
	volatile uint32_t APB2LPENR;		// 0X64				RCC APB2 peripheral clock enabled in low power mode register
	volatile uint32_t RESERVED8;		// 0X68
	volatile uint32_t RESERVED9;		// 0X6C
	volatile uint32_t BDCR;				// 0X70				RCC Backup domain control register
	volatile uint32_t CSR;				// 0X74				RCC clock control and status register
	volatile uint32_t RESERVED10;		// 0X78
	volatile uint32_t RESERVED11;		// 0X7C
	volatile uint32_t SSCGR;			// 0X80				RCC spread spectrum clock generation register
	volatile uint32_t PLLI2SCFGR;		// 0X84				RCC PLLI2S configuration register
	volatile uint32_t PLLSAICFGR;		// 0X88				RCC PLL configuration register
	volatile uint32_t DCKCFGR;			// 0X8C				RCC dedicated clock configuration register
	volatile uint32_t CKGATENR;			// 0X90				RCC clocks gated enable register
	volatile uint32_t DCKCFGR2;			// 0X94				RCC dedicated clocks configuration register 2
} RCC_RegDef_t;


// RCC POINTER

#define RCC ((RCC_RegDef_t *)RCC_BASEADDR)

// CLOCK ENABLE MACROS(AHB1 BUS FOR GPIO)

#define GPIOA_CLK_EN()	(RCC->AHB1ENR |= (1<<0));
#define GPIOB_CLK_EN()	(RCC->AHB1ENR |= (1<<1));
#define GPIOC_CLK_EN()	(RCC->AHB1ENR |= (1<<2));
#define GPIOD_CLK_EN()	(RCC->AHB1ENR |= (1<<3));
#define GPIOE_CLK_EN()	(RCC->AHB1ENR |= (1<<4));
#define GPIOF_CLK_EN()	(RCC->AHB1ENR |= (1<<5));
#define GPIOG_CLK_EN()	(RCC->AHB1ENR |= (1<<6));
#define GPIOH_CLK_EN()	(RCC->AHB1ENR |= (1<<7));


// ADC base register for 1,2,3

#define ADC_BASEADDR 0x40012000U
#define ADC1_OFFSET 0X000
#define ADC2_OFFSET 0X100
#define ADC3_OFFSET 0X200

// ADC register structure

typedef struct
{										// offsetts			register info
	volatile uint32_t SR;						// 0X00
	volatile uint32_t CR1;						// 0X04
	volatile uint32_t CR2;						// 0X08
	volatile uint32_t SMPR1;					// 0X0C
	volatile uint32_t SMPR2;					// 0X10
	volatile uint32_t JOFR1;					// 0X14
	volatile uint32_t JOFR2;					// 0X18
	volatile uint32_t JOFR3;					// 0X1C
	volatile uint32_t JOFR4;					// 0X20
	volatile uint32_t HTR;						// 0X24
	volatile uint32_t LTR;						// 0X28
	volatile uint32_t SQR1;						// 0X2C
	volatile uint32_t SQR2;						// 0X30
	volatile uint32_t SQR3;						// 0X34
	volatile uint32_t JSQR;						// 0X38
	volatile uint32_t JDR1;						// 0X3C
	volatile uint32_t JDR2;						// 0X40
	volatile uint32_t JDR3;						// 0X44
	volatile uint32_t JDR4;						// 0X48
	volatile uint32_t DR;						// 0X4C
} ADC_RegDef_t;


// ADC1 pointer

#define ADC1	((ADC_RegDef_t *)(ADC_BASEADDR | ADC1_OFFSET))
#define ADC2	((ADC_RegDef_t *)(ADC_BASEADDR | ADC2_OFFSET))
#define ADC3	((ADC_RegDef_t *)(ADC_BASEADDR | ADC3_OFFSET))

// ADC common register base address
#define ADC_COMMON_BASEADDR 0x40012300U

typedef struct
{										// offsetts			register info
	volatile uint32_t CSR;						// 0X00
	volatile uint32_t CCR;						// 0X04
	volatile uint32_t CDR;						// 0X08
} ADC_Common_RegDef_t;


#define ADC_COMM	((ADC_Common_RegDef *)(ADC_COMMON_BASEADDR));

// System configuration controller (SYSCFG) Base Address

#define SYSCFG_BASE_ADDR	0x40013800U

// SYSCFG Register structure

typedef struct
{										// offsetts			register info
	volatile uint32_t MEMRMP;					// 0X00
	volatile uint32_t PMC;						// 0X04
	volatile uint32_t EXTICR[4];					// 0X08-0X14
	volatile uint32_t RESERVED1[2];				// 0x18=0x1C
	volatile uint32_t CMPCR;						// 0X20
	volatile uint32_t RESERVED2[2];				// 0X24-0X28
	volatile uint32_t CFGR;						// 0X2C
} SYSCFG_RegDef;

// SYSCFG Register pointer

#define SYSCFG		((SYSCFG_RegDef *)SYSCFG_BASE_ADDR)

// EXTI Register Base address

#define EXTI_BASE_ADDR		0x40013C00U

// EXTI Register Structure

typedef struct
{										// offsetts			register info
	volatile uint32_t IMR;					// 0X00
	volatile uint32_t EMR;						// 0X04
	volatile uint32_t RTSR;						// 0X08
	volatile uint32_t FTSR;						// 0X0C
	volatile uint32_t SWIER;						// 0X10
	volatile uint32_t PR;						// 0X14
} EXTI_RegDef;

// EXTI Register pointer

#define EXTI	((EXTI_RegDef *)EXTI_BASE_ADDR)




typedef struct
{
    volatile uint32_t ISER[8];      // 0x000 - 0x01C
    uint32_t RESERVED0[24];         // 0x020 - 0x07C

    volatile uint32_t ICER[8];      // 0x080 - 0x09C
    uint32_t RESERVED1[24];         // 0x0A0 - 0x0FC

    volatile uint32_t ISPR[8];      // 0x100 - 0x11C
    uint32_t RESERVED2[24];         // 0x120 - 0x17C

    volatile uint32_t ICPR[8];      // 0x180 - 0x19C
    uint32_t RESERVED3[24];         // 0x1A0 - 0x1FC

    volatile uint32_t IABR[8];      // 0x200 - 0x21C
    uint32_t RESERVED4[56];         // 0x220 - 0x2FC

    volatile uint8_t IPR[240];      // 0x300 - 0x3EF
    uint32_t RESERVED5[708];        // 0x3F0 - 0xEFC

    volatile uint32_t STIR;         // 0xF00
} NVIC_TypeDef;


#define NVIC_BASE      (0xE000E100UL)
#define NVIC           ((NVIC_TypeDef*) NVIC_BASE)


// TIMx

#define TIM2_BASEADDR		0x40000000U

typedef struct
{							// OFFSETS			DESCRIPTION
	volatile uint32_t CR1;			// 0X00
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

} TIMX_RegDef;


#define TIM2 ((TIMX_RegDef *) TIM2_BASEADDR)


// I2C register map


#define I2C1_BASEADDR	0x40005400U

typedef struct
{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t OAR1;
	uint32_t OAR2;
	uint32_t DR;
	uint32_t SR1;
	uint32_t SR2;
	uint32_t CCR;
	uint32_t TRISE;
	uint32_t FLTR;
} I2C_RegDef;

#define I2C1 ((I2C_RegDef *) I2C1_BASEADDR)











#endif /* STM32F446XX_H_ */


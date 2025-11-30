🧪 STM32F446RE Bare-Metal ADC on PA0

This project demonstrates how to read analog values from PA0 (ADC1_IN0) using bare-metal register programming on the STM32F446RE.
The measured ADC value is converted into a temperature-like output and printed using printf() via SWV/UART (depending on your setup).

📁 Project Structure
├── main.c             // Application code with ADC implementation
└── stm32f446xx.h      // Custom CMSIS-style register definitions

⚙️ Features

Direct register access (no HAL/LL drivers)

ADC1 continuous conversion mode

Uses channel 0 (PA0)

Sampling time set to 480 cycles (SMPR2 = 0x7)

Temperature calculation from ADC reading

Prints real-time data through printf()

🧩 How the ADC Works in This Project
1. Enable Clocks

Both GPIOA and ADC1 require separate clocks:

GPIOA clock → Needed to configure PA0 into analog mode

ADC1 clock → Powers the actual ADC hardware

GPIOA_CLK_EN();
RCC->APB2ENR |= (1 << ADC1EN);

2. Configure PA0 as Analog

Analog mode disconnects digital input/output buffers to reduce noise.

GPIOA->MODER |= (0x3 << (PA0 * 2));

3. Configure ADC1

One conversion in sequence

Channel 0

Longest sampling time (480 cycles) for stable readings

Continuous mode

Software trigger

ADC1->SQR3 = 0;       // Channel 0
ADC1->SQR1 = 0;       // 1 Conversion
ADC1->SMPR2 |= (0x7 << 0); // Sampling time
ADC1->CR2 |= (1 << ADON);
ADC1->CR2 |= (1 << CONT);
ADC1->CR2 |= (1 << SWSTART);

4. Reading ADC Data

Wait until EOC flag is set, then read DR.

while (!(ADC1->SR & (1 << EOC)));
uint16_t dr = ADC1->DR;

📡 Output Format

The calculation assumes:

3.3V ADC reference

12-bit ADC resolution

Sensor scaling = ×100 (example LM35-style conversion)

Output prints as:

T : 25.345°C

🖥️ Main Loop Summary

Wait for conversion to complete

Read ADC value

Convert to voltage

Convert to temperature

Print

Delay

From main.c 

main

:

while(1)
{
    while(!(ADC1->SR & (1<<EOC)));
    uint16_t dr = ADC1->DR;

    float temp = ((dr * 3.3) / 4095.0) * 100.0;
    printf("T : %.3f°C\n", temp);

    for (int i = 0; i < 1000000; i++);
}

🛠️ Requirements

STM32 Nucleo-F446RE

STM32CubeIDE or Makefile + arm-gcc

SWD debugging enabled (default)

Optional: Enable SWV ITM for printf debugging

📘 Custom Header (stm32f446xx.h)

Your custom header file implements register structs for:

GPIOA–GPIOH

RCC

ADC1/ADC2/ADC3

ADC common registers

This allows code like:

GPIOA->MODER |= ...
ADC1->CR2 |= ...


instead of using HAL.
Reference: stm32f446xx.h 

stm32f446xx

🚀 How to Use

Import project into STM32CubeIDE

Flash to the Nucleo board

Open SWV ITM console (if using printf via SWO)

Reset the board and observe output

🧯 Common Issues
1. Target Not Responding

Happens if you accidentally reconfigure SWD pins (PA13/PA14).
Fix:

Use Connect Under Reset in CubeProgrammer

Perform Full Chip Erase

2. Always Reads 0

GPIOA clock was not enabled

PA0 not set to analog mode

ADC clock disabled

No delay after enabling ADC

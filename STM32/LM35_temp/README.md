# ⚡ Bare-Metal ADC Driver for STM32F446xx

A lightweight, register-level driver for the Analog-to-Digital Converter (ADC) on the STM32F446 series microcontrollers. This project prioritizes low-level control and efficiency over high-level abstraction layers.

## ✨ Features

* **Zero-Overhead:** Implements functionality using direct register manipulation.
* **Continuous Mode:** Configured for seamless, non-stop ADC conversion cycles.
* **Blocking Read:** Simple polling mechanism to wait for the End-of-Conversion (EOC) flag.
* **Configurable:** Uses explicit configuration structs for initialization (prescaler, sequence, sampling time).

## 📌 Hardware & Setup

| Component | Detail |
| :--- | :--- |
| **Microcontroller** | STM32F446xx |
| **ADC Unit** | ADC1 |
| **Input Pin** | **PA0** (Analog Channel 0) |

The application configures **PA0** to Analog mode and performs a simple scaling on the 12-bit raw ADC value (0-4095).



## 📂 Project Structure

| File | Role |
| :--- | :--- |
| `stm32f446xx_adc_driver.c/h` | The core ADC driver logic, including initialization and data read functions. |
| `stm32f446xx.h` | Defines peripheral base addresses, register maps, and clock control macros. |
| `main.c` | The main application loop: GPIO setup, ADC initialization, and continuous data acquisition. |

## 🚀 Getting Started

1.  **Clone** this repository and integrate the source files into your bare-metal C project environment.
2.  **Build** the project using an ARM GCC toolchain, ensuring your linker script is correctly configured.
3.  **Flash** the executable to the STM32F446xx board.
4.  Monitor the output to see continuous, raw, or scaled ADC readings.

---
*Built for learning and maximizing peripheral control.*

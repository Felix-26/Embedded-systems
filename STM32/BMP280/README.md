# 🌡️ BMP280 Temperature & Pressure Sensor Driver (STM32F446RE Bare-Metal)

This project implements a **bare-metal (register-level)** driver for the **Bosch BMP280** sensor on the STM32F446RE microcontroller. It features complete control over the I²C bus and uses a timer interrupt for accurate periodic measurements.

---

## ⚙️ Core System Overview

### Microcontroller
* **MCU:** STM32F446RE

### Protocols & Peripherals
| Peripheral | Function | Configuration |
| :--- | :--- | :--- |
| **I²C1** | Sensor Communication | PB8 (SCL), PB9 (SDA). $100 \text{ kHz}$ Standard Mode. |
| **TIM2** | Time Base | Configured to generate an interrupt every $\approx 1 \text{ second}$. |
| **BMP280** | Sensor | Reads and applies compensation for temperature and pressure. |
| **SWV/SWD** | Debug Output | Uses semihosting (`syscalls.c`) for `printf` output. |

### Clock Assumption (PCLK1 = 42 MHz)
The timing values in the **I²C** (`i2c.c`) and **Timer** (`timer.c`) modules are based on the assumption that the **APB1 Peripheral Clock (PCLK1)** is running at **42 MHz**. This is critical for generating the correct $100 \text{ kHz}$ SCL signal and the 1-second delay.

---

## 🗂️ File Structure and Module Descriptions

| File | Module | Description |
| :--- | :--- | :--- |
| `stm32f446xx.h` | **Device Header** | Custom header defining the memory-mapped register structures and base addresses for all peripherals (GPIO, RCC, I2C, TIMx, NVIC). |
| `i2c.h`, `i2c.c` | **I²C Driver** | Implements low-level register configuration for I²C1. Includes bare-metal functions for single-byte write (`i2c_WRITE`) and multi-byte read (`i2c_READ`), correctly managing START/STOP conditions and ACK/NACK signaling. |
| **`timer.h`**, **`timer.c`** | **TIM2 Driver** | Initializes Timer 2 for interrupt-driven timing. The `TIM2_IRQHandler` sets the `time` flag, controlling the measurement frequency in `main.c`. |
| `BMP280.h`, `BMP280.c` | **BMP280 Driver** | Handles all sensor-specific logic: reading unique calibration constants (dig\_T, dig\_P), configuring oversampling/filter modes, reading raw ADC data, and applying the full floating-point Bosch compensation algorithms. |
| `main.c` | **Application** | Main entry point. Initializes all peripherals, calibrates the BMP280, and uses the `time` flag from the TIM2 interrupt to trigger periodic readings and output via `printf`. |
| `syscalls.c`, `sysmem.c` | **System Calls** | Standard Newlib stubs to enable C library functions like `printf` to output data over the debugger's SWV/ITM channel (Semihosting). |

---

## 🚀 Usage and Data Flow

The application flow is interrupt-driven for periodic data acquisition:

1.  `main()` calls `i2c_init()`, `temp_init()`, `pres_init()`, and `timer2_init()`.
2.  The program enters the infinite `for(;;)` loop.
3.  Every time **TIM2** overflows (approx. $1 \text{ second}$), the **`TIM2_IRQHandler`** executes, setting the `time` flag: `time = 1;`.
4.  The main loop detects `time == 1` and calls `get_temp()` and `get_pres()`.
5.  `get_temp()`/`get_pres()` initiate I²C transactions via `i2c_READ` to fetch raw sensor data.
6.  The compensated values are printed via `printf`.

### Timer Configuration Details (42 MHz PCLK1)

* **Target Delay:** $1 \text{ second}$
* **PCLK1:** $42,000,000 \text{ Hz}$
* **Prescaler Value (PSC):** 41 (Divides clock by $41+1 = 42$, resulting in $1 \text{ MHz}$ timer clock)
* **ARR Value (ARR):** 999,999 ($1,000,000$ counts for $1 \text{ second}$)

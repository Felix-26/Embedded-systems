# STM32F446xx Bare-Metal Peripheral Driver Library

## 🚀 Project Overview

This repository contains a **Bare-Metal Peripheral Driver Library** for the **STM32F446xx** microcontroller series. This project aims to provide a modular, register-level abstraction layer (similar to a HAL, but built from scratch) to simplify the configuration and use of various on-chip peripherals without relying on ST's official HAL or CubeMX generated code.

The driver is developed in C and directly manipulates the microcontroller's hardware registers, making it highly efficient and providing full control over the hardware.

## 🛠️ Status and Roadmap

| Peripheral | Status | Notes |
| :--- | :--- | :--- |
| **SPI** | **In Progress** | Basic initialization, send, receive (polling), and interrupt handling implemented. |
| **GPIO** | **Planned** | Header file initiated. Register structure and base addresses defined. |
| **I2C** | **Planned** | Register definitions available. Driver implementation pending. |
| **USART/UART** | **Planned** | Register definitions available. Driver implementation pending. |

### Immediate Goals (Next Steps)

* **Complete SPI Driver:** Thorough testing and implementation of all remaining APIs (e.g., error handling, CRC).
* **GPIO Driver:** Implement `GPIO_Init`, `GPIO_DeInit`, and data read/write APIs.
* **Interrupt Management:** Create unified APIs for NVIC configuration.

## 📁 Repository Structure

The core of the driver is organized by peripheral:

| File/Directory | Description |
| :--- | :--- |
| `inc/` | Contains all header files (`.h`). |
| `inc/stm32f446xx.h` | **The Core Header.** Contains all MCU-specific details: memory map, peripheral register definitions (`_RegDef_t`), base addresses, clock/reset macros, and interrupt numbers. |
| `inc/stm32f446xx_spi_drv.h` | SPI driver header. Defines configuration structures (`SPI_Config_t`, `SPI_Handle_t`), mode macros, and public API function prototypes. |
| `src/` | Contains all source files (`.c`). |
| `src/stm32f446xx_spi_drv.c` | **SPI Driver Implementation.** Contains the logic for SPI clock control, initialization, data transfer (polling and interrupt-based), and peripheral control. |
| `README.md` | This file. |

## ⚙️ Implemented SPI Driver Features

The current SPI driver supports the following configurations and operations:

### Configuration (`SPI_Config_t`)
* **Device Mode:** Master (`SPI_DEVICE_MODE_MASTER`) or Slave (`SPI_DEVICE_MODE_SLAVE`).
* **Bus Configuration:** Full-Duplex (FD), Half-Duplex (HD), or Simplex Receive-Only.
* **Clock Speed:** Configurable Baud Rate Prescaler (e.g., `SPI_SCLK_SPEED_DIV2` to `DIV256`).
* **Data Frame Format (DFF):** 8-bit or 16-bit.
* **Clock Polarity (CPOL) and Phase (CPHA):** Fully configurable for different SPI modes (Mode 0, 1, 2, 3).
* **Slave Select Management (SSM):** Software-managed or Hardware-managed.

### Key APIs
* **Initialization:** `SPI_Init()` and `SPI_DeInit()`.
* **Data Transfer (Polling):** `SPI_SendData()` and `SPI_ReceiveData()`.
* **Data Transfer (Interrupt-driven):** `SPI_SendDataIT()` and `SPI_ReceiveDataIT()`.
* **Control:** `SPI_PeriClockControl()`, `SPI_PeripheralControl()` (Enable/Disable).

## 💡 Register-Level Details

The core of this driver relies on the register definitions in `stm32f446xx.h`. Key register fields are abstracted using macros (e.g., `SPI_CR1_MSTR`, `SPI_CR1_DFF`).

The `SPI_Init()` function, for example, directly configures the SPI Control Register 1 (`CR1`) using the user-defined `SPI_Config_t` settings.

```c
// Inside SPI_Init(SPI_Handle_t *pSPIHandle)
uint32_t temp = 0;
// 1. configure device mode (MSTR bit)
temp |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
// ... other configurations ...
pSPIHandle->pSPIx->CR1 = temp;

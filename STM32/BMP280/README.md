# 🌡️ BMP280 Barometric Sensor Interface (STM32F446RE Bare-Metal)

This project implements a bare-metal driver for the **Bosch BMP280** temperature and pressure sensor using the **I²C protocol** on the **STM32F446RE** microcontroller.

The code is written at the register-level, bypassing standard HAL libraries, to provide a deep understanding of peripheral configuration.

---

## 🛠️ Hardware & Tools

* **Microcontroller:** STM32F446RE (Nucleo-F446RE or custom board)
* **Sensor:** BMP280 (I²C Mode)
* **Communication:** I²C1
    * **SCL:** PB8
    * **SDA:** PB9
* **External Components:** Required **pull-up resistors** (typically 4.7kΩ or 10kΩ) on the SDA and SCL lines.
* **IDE/Toolchain:** STM32CubeIDE or equivalent GCC/Make toolchain.

---

## ⚙️ Clock Configuration Assumption

This project assumes the following clock configuration for timing peripheral speeds:

| Peripheral | Clock | Frequency |
| :--- | :--- | :--- |
| **System Clock (f_HCLK)** | HSI/PLL | **42 MHz** (assumed, check `SystemInit()`) |
| **APB1 Clock (f_PCLK1)** | Used by I2C1, TIM2 | **42 MHz** |
| **I2C SCL Speed** | Standard Mode | **100 kHz** |

***Note:*** *The timing values in `i2c.c` (`I2C1->CR2 = 42; I2C1->CCR = 210;`) are based on an assumed 42 MHz APB1 clock. If your actual system clock configuration is different, these values must be adjusted.*

---

## 📂 Project Structure and Files

| File | Description | Key Functions |
| :--- | :--- | :--- |
| **`main.c`** | Initializes I²C and the BMP280. Enters an infinite loop to read and print temperature and pressure, controlled by a simple busy-wait delay. | `main()` |
| **`i2c.h`** | Defines all I²C register bit offsets (e.g., `SB`, `ADDR`, `TxE`, `ACK`) and function prototypes. | `i2c_init`, `i2c_READ`, `i2c_WRITE` |
| **`i2c.c`** | **Bare-metal I²C Driver.** Handles clock, GPIO, and register timing configuration. Implements the multi-byte read and single-byte write I²C protocol sequences. | `i2c_init`, `i2c_READ`, `i2c_WRITE` |
| **`BMP280.h`** | Prototypes for all BMP280 initialization and calibration functions. | `get_temp`, `get_pres`, `temp_init`, `pres_init` |
| **`BMP280.c`** | **BMP280 Application Driver.** Reads calibration data, sets sensor mode (`ctrl_meas`), retrieves raw ADC values, and performs the complex floating-point compensation algorithm. | `temp_init`, `pres_init`, `get_t_fine`, `get_temp`, `get_pres` |
| **`stm32f446xx.h`** | Custom header defining the memory-mapped register structures and base addresses for the MCU peripherals (GPIO, RCC, I2C, etc.). | `GPIO_RegDef_t`, `RCC_RegDef_t`, `I2C_RegDef` |

---

## 📋 BMP280 Initialization Sequence

The sensor is configured and calibrated in the following order:

1.  **`main.c`** calls `i2c_init()` to set up the I²C bus.
2.  **`main.c`** calls `temp_init()`:
    * Sets **Temperature Oversampling (`osrs_t`)** and **Normal Mode (`mode`)** in the `ctrl_meas` register (`0xF4`).
    * Sets **Standby Time (`t_sb`)** and **IIR Filter (`filter`)** in the `config` register (`0xF5`).
    * Reads the 3-word **Temperature Calibration** constants (`dig_T1` to `dig_T3`) from registers `0x88` to `0x8C`.
3.  **`main.c`** calls `pres_init()`:
    * Sets **Pressure Oversampling (`osrs_p`)** in the `ctrl_meas` register (`0xF4`).
    * Reads the 9-word **Pressure Calibration** constants (`dig_P1` to `dig_P9`) from registers `0x8E` to `0x9E`.

---

## 🔬 Calibration and Measurement Flow

The core data flow inside the infinite loop (`main.c`) is:

1.  **`get_temp()`** is called:
    * Calls `get_t_fine()`.
    * `get_t_fine()` calls `get_adc_T()` which reads **3 bytes** (uncompensated temperature) from register `0xFA` using `i2c_READ`.
    * It then calculates and stores the intermediate compensation value, `t_fine`.
    * Returns the compensated temperature $T$.
2.  **`get_pres()`** is called:
    * Calls `get_adc_P()` which reads **3 bytes** (uncompensated pressure) from register `0xF7` using `i2c_READ`.
    * Uses the previously calculated `t_fine` along with the pressure calibration constants to compute the fully compensated pressure $P$.
    * Returns the compensated pressure $P$ in Pascals ($\text{Pa}$).

---


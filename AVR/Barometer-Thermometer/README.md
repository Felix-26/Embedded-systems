
demo link - https://youtu.be/IpLHLLHpiFo

## 🌡️ Atmospheric Monitor (Barometer/Thermometer) 📈

This repository contains the firmware for an embedded system based on an AVR microcontroller (e.g., ATmega328P) that measures and displays atmospheric pressure and temperature using the **Bosch BMP280** sensor and an **HD44780-compatible LCD**.

### 🛠️ Hardware Requirements

* **Microcontroller:** AVR Microcontroller (e.g., ATmega328P, running at 16MHz)
* **Sensor:** BMP280 Digital Barometric Pressure and Temperature Sensor
* **Display:** 16x2 or 20x4 Character LCD (HD44780 compatible)
* **Interface:** Inter-Integrated Circuit (I2C/TWI) bus for the sensor, 4-bit parallel interface for the LCD.

### ⚙️ Project Structure

The project is organized into modular C and header files, each responsible for a specific subsystem:

| File(s) | Description |
| :--- | :--- |
| `main.c` | Main application logic; handles initialization and the primary sensing/display loop. |
| `i2c.c`/`i2c.h` | **I2C/TWI Driver.** Implements low-level functions for START, STOP, Transmit, and Read operations on the AVR's TWI module. |
| `lcd.c`/`lcd.h` | **HD44780 LCD Driver.** Implements functions for 4-bit initialization, commanding, data transmission, and display of text and numeric values. |
| `BMP280.c`/`BMP280.h` | **BMP280 Sensor Driver.** Handles sensor initialization, reading calibration data, reading raw ADC values, and applying compensation formulas to get final temperature (°C) and pressure (Pa/hPa). |
| `timer.c`/`timer.h` | **Timer Driver.** Implements a millisecond delay function (`timer_delay`) using Timer/Counter 0 in CTC (Clear Timer on Compare Match) mode. |
| `names.h` | **Hardware Abstraction Layer (HAL).** Defines the specific AVR I/O pins used for the LCD control (`RS`, `E`) and data lines (`D4` through `D7`). |

### 💻 Key Features and Implementation Details

#### 1. Sensor Reading and Compensation

The BMP280 driver handles the full compensation process as detailed in the sensor's datasheet:

* **Calibration Data:** Reads and stores nine pressure constants (`dig_P1` to `dig_P9`) and three temperature constants (`dig_T1` to `dig_T3`) from the device upon initialization.
* **Raw ADC Reading:** Uses the I2C driver's `i2c_READ32` function to fetch the 20-bit raw pressure (`UP`) and temperature (`UT`) values.
* **Compensation:** Calculates the intermediate value `t_fine` (required for both measurements) and then applies the floating-point compensation formulas to return temperature in **°C** and pressure in **Pa**.

#### 2. I2C/TWI Communication

The I2C driver is configured for standard mode (100 kHz) and provides low-level control of the TWI hardware:

* **Frequency:** Set to **100 kHz** based on a 16 MHz CPU clock and `TWBR = 72` (with a prescaler of 1).
* **Low-Level Functions:** Provides explicit functions for I2C bus state changes: `i2c_START()`, `i2c_TRANSMIT()`, `i2c_RECIEVE_with_ACK()`, `i2c_RECIEVE_NACK()`, and `i2c_STOP()`.
* **Read Macros:** Dedicated functions like `i2c_READ8`, `i2c_READ16`, and `i2c_READ32` simplify multi-byte register reading.

#### 3. LCD Display

The display uses the common 4-bit interface to save microcontroller pins:

* **Mode:** Initialized for **4-bit mode**, **2 lines**, and **5x8 dots** character display.
* **Data Presentation:** The `main.c` loop formats the data, displaying updates every 1000ms using `_delay_ms(1000)`:
    * Temperature: `T: XX.XX °C`
    * Pressure: `P: XXXX.XX hPa` (Pressure is converted from Pascals by dividing by 100.0)

### 🔗 Wiring/Connection Reference

The pin definitions are stored in `names.h` and assume the following connections for the LCD on a standard AVR board (using PORTC for control and PORTD for data):

| LCD Pin (HD44780) | `names.h` Macro | AVR Pin (Example: ATmega328P) | Purpose |
| :--- | :--- | :--- | :--- |
| **RS** (Register Select) | `RS` (PC0) | PORTC Pin 0 | Command/Data Selection |
| **E** (Enable) | `E` (PC1) | PORTC Pin 1 | Data Latching Pulse |
| **D4** (Data 4) | `D4` (PD4) | PORTD Pin 4 | 4-bit Data LSB |
| **D5** (Data 5) | `D5` (PD5) | PORTD Pin 5 | 4-bit Data |
| **D6** (Data 6) | `D6` (PD6) | PORTD Pin 6 | 4-bit Data |
| **D7** (Data 7) | `D7` (PD7) | PORTD Pin 7 | 4-bit Data MSB |

**I2C Connection:**

| BMP280 Pin | AVR Pin (Example: ATmega328P) |
| :--- | :--- |
| **SDA** (Data) | PC4 (or A4 on Arduino) |
| **SCL** (Clock) | PC5 (or A5 on Arduino) |



### ➡️ Getting Started

1.  **Toolchain:** Ensure you have the AVR-GCC toolchain installed (e.g., using Atmel Studio or VS Code with PlatformIO).
2.  **Compile:** Compile all `.c` files into a single project ELF/HEX file.
3.  **Flash:** Program the resulting HEX file onto your AVR microcontroller.
4.  **Run:** The system will initialize the peripherals and begin displaying real-time temperature and pressure updates every 1000 milliseconds (1 second).

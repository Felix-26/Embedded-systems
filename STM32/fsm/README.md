# STM32F446RE FSM: LED Blinking and Temperature Monitoring

## 📝 Overview

This project implements a simple **Finite State Machine (FSM)** on an STM32F446RE microcontroller (or similar STM32F4 series) to switch between two core functionalities:

1.  **LED Blinking:** Toggles the onboard LED (PA5) periodically.
2.  **Temperature Monitoring:** Reads the ambient temperature via an LM35 sensor connected to the ADC (PA0) and prints the result via a serial interface (assumed, via `printf`).

The transition between these two states is controlled by an **External Interrupt** triggered by a user button (PC13). The actions within each state are timed using a **Timer Interrupt (TIM2)**.

## ⚙️ Hardware & Peripherals

| Peripheral | Pin/Channel | Function |
| :--- | :--- | :--- |
| **GPIO Output** | PA5 | Onboard LED (Active High or Low depending on board wiring) |
| **GPIO Input** | PC13 | User Button (Configured for Falling Edge Interrupt) |
| **ADC Input** | PA0 (ADC1, Channel 0) | Analog input for the LM35 Temperature Sensor |
| **Timer** | TIM2 | Provides a periodic interrupt (e.g., 0.5s) to pace the FSM actions |
| **Interrupts** | TIM2 IRQ, EXTI15_10 IRQ | Drive the FSM logic |

## 💡 Finite State Machine (FSM)

The system operates in one of two states, determined by the `current_state` variable:

| State | Action on TIM2 Interrupt | Transition |
| :--- | :--- | :--- |
| **STATE\_BLINK** (Default) | Toggles the LED (PA5) status. | Triggered by a button press (PC13 interrupt). |
| **STATE\_TEMP** | Reads the ADC value from PA0, converts it to Celsius, and prints the result. | Triggered by a button press (PC13 interrupt). |



## 🛠️ Code Structure

The project is structured with functions dedicated to initialization, interrupt handling, and FSM logic.

### 1. Initialization (`main` calls)

* `led_en()`: Configures **PA5** as a push-pull output.
* `analog_LM35_init()`: Configures **PA0** as an analog input and initializes **ADC1** for continuous conversion on Channel 0.
* `set_input()`: Configures **PC13** as an external interrupt source (EXTI Line 13) on the falling edge.
* `timer2_init()`: Configures **TIM2** to generate a periodic interrupt (Update Event) and enables its NVIC line.

### 2. Interrupt Service Routines (ISRs)

* `TIM2_IRQHandler()`: Clears the timer flag and sets the global flag `blink_or_temp` to signal a time-based action.
* `EXTI15_10_IRQHandler()`: Clears the EXTI pending bit and **toggles the FSM state** (`current_state`).

### 3. Core Logic

* `fsm()`: The main switch-case structure that reads `current_state` and executes the corresponding action when the `blink_or_temp` flag is set by the timer.
* `temp_print()`: Performs a busy-wait (polling) for the ADC conversion to complete, reads the data register (DR), and calculates the temperature using the formula:
    $$T (°C) = \left( \frac{\text{ADC}_{\text{DR}} \times 3.3}{4095} \right) \times 100$$
    *Note: The code assumes a $3.3 \text{V}$ reference voltage and a 12-bit ADC resolution (4095).*

## 📌 Build and Run

### Prerequisites

* **Toolchain:** ARM GCC Compiler (e.g., GNU Tools for ARM Embedded Processors).
* **Debugger/Flasher:** ST-Link utility or OpenOCD.
* **IDE (Optional):** VS Code with extensions, STM32CubeIDE, or similar.
* **Header Files:** The project requires `stm32f446xx.h` and standard library headers (`stdint.h`, `stdio.h`).

### Steps

1.  **Compile:** Compile the C source file (`main.c`) along with any startup files and necessary library code.
2.  **Flash:** Flash the generated executable (`.elf` or `.hex`) onto the STM32F446RE board.
3.  **Monitor:** Use a serial terminal program (e.g., PuTTY, Tera Term) to monitor the UART output for `printf` messages (assuming UART initialization is done elsewhere or handled by the development environment).

### Usage

1.  **Initial State:** The LED will blink periodically.
2.  **Button Press (1st):** Press the user button (PC13) to transition to `STATE_TEMP`. The console will print temperature readings at the timer interval.
3.  **Button Press (2nd):** Press the user button again to transition back to `STATE_BLINK`. The console will print "STATE\_BLINK" and the LED will resume blinking.

---
**Disclaimer:** This code is written using direct register access and relies on specific definitions (`TIM2EN`, `PA5`, `ADC1EN`, etc.) matching the STM32F446xx reference manual and the included `stm32f446xx.h` header file.

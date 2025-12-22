# STM32F446 ADC Data Acquisition with DMA & USART

This project implements a high-performance data acquisition system on the **STM32F446RE** microcontroller. It uses **Timer 2** to trigger **ADC1** conversions at a fixed frequency, transfers the data into a double buffer using **DMA2**, and subsequently offloads that data to **USART2** via **DMA1**.

---

 ## Key Features

* **Hardware Triggering:** Timer 2 (TRGO) triggers ADC conversions at 100Hz, ensuring precise sampling intervals without CPU intervention.
* **Double Buffering:** DMA2 is configured in Double Buffer Mode (DBM) to switch between two memory locations (`M0AR` and `M1AR`), preventing data overwriting during processing.
* **DMA-to-USART:** Once a buffer is full, an interrupt triggers DMA1 to transmit the collected samples over USART2.
* **Bare-Metal Development:** Written using direct register access for performance and clarity of peripheral hardware logic.

---

 ## Project Structure

| File | Description |
| --- | --- |
| `main.c` | Application entry point, GPIO initialization, and DMA2 Interrupt Handler. |
| `ADC.c` | Configures ADC1 for external trigger (Timer 2) and DMA integration. |
| `TIM.c` | Sets up Timer 2 to generate a 100Hz trigger output (TRGO). |
| `DMA.c` | Configures DMA2 (ADC to Memory) and DMA1 (Memory to USART). |
| `USART.c` | Configures USART2 for 115200 baud with DMA transmitter support. |
| `stm32f446xx.h` | Custom peripheral register definitions and clock enable macros. |

---

 ## Peripheral Configuration

 ### ADC & Timer (Sampling)

* **Timer 2:** Prescaler (PSC) is set to 1599 and Auto-Reload Register (ARR) to 99. With a 16MHz clock, this results in a **100Hz** trigger frequency.
* **ADC1:** Configured for 12-bit resolution and set to be triggered by the **Timer 2 TRGO** event on the rising edge.

 ### DMA Settings

* **DMA2 (Stream 0, Channel 0):** * **Direction:** Peripheral-to-Memory (ADC1 Data Register  `adc_buffer`).
* **Mode:** Double Buffer Mode (DBM) with circular addressing.
* **Data Size:** 16-bit (Half-word) for both peripheral and memory.
* **Interrupt:** Transfer Complete (TC) enabled to facilitate buffer management in the ISR.


* **DMA1 (Stream 6, Channel 4):**
* **Direction:** Memory-to-Peripheral (`adc_buffer`  USART2 Data Register).
* **Mode:** Normal mode with memory increment enabled.



 ### USART

* **Baud Rate:** Set to 115200 (BRR = 0x008B).
* **Pinout:** PA2 (TX) is configured in Alternate Function Mode (AF7).

---

 ## How It Works

1. **Initialization:** The system initializes GPIOs, USART, DMA2 (ADC-side), DMA1 (USART-side), and the ADC.
2. **Sampling:** Timer 2 is started, sending a Master Mode trigger pulse to ADC1 every 10ms.
3. **Transfer:** ADC1 converts the analog signal on PA0, and DMA2 automatically moves the result into the currently active memory buffer (`M0` or `M1`).
4. **Interrupt:** When a buffer of 100 samples is full, the `DMA2_Stream0_IRQHandler` is triggered.
5. **Transmission:** The ISR identifies which buffer was just completed, updates the DMA1 memory source address accordingly, and restarts DMA1 to send that block of data via USART2.

---

 ## Hardware Requirements

* **Microcontroller:** STM32F446xx.
* **Input Pin:** Analog signal on **PA0**.
* **Output Pin:** Serial data transmission on **PA2** (USART2 TX).

Would you like me to provide a Python script to visualize this ADC data on your computer?

# LTC2959-library
A library for communicating with the LTC2959 Ultra-Low Power Battery Gas Gauge

Updated with code to tgake into account the dev board "MoJo" that has a sense resistor of 250 mOhm, instead of the 50 mOhm that is recomended in the datasheet of the LTC2959. 
Because of this we need to do some additional maths when reading the mAh counter. 

Rsense = 0.250 Ω:

Forked from Pius Onyema Ndukwu
https://github.com/Pius171/LTC2959-library

📧 Email: [onyemandukwu@gmail.com](mailto:onyemandukwu@gmail.com)


# LTC2959 Arduino Library

![Arduino](https://img.shields.io/badge/platform-arduino-blue.svg)
![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)

> A lightweight and user-friendly Arduino library for interfacing with the [LTC2959](https://www.analog.com/en/products/ltc2959.html), a versatile power monitor and Coulomb counter IC by Analog Devices.


## 🔍 Overview

The **LTC2959** library allows Arduino and compatible boards to communicate with the LTC2959 over I2C. It supports:

- Voltage monitoring (up to 62.6 V)
- Current monitoring (via sense resistor)
- Temperature monitoring (internal sensor)
- Charge accumulation (mAh)
- Min/Max tracking for voltage and current
- Coulomb counter enable/disable
- Manual charge counter reset

This library abstracts low-level register access and handles scaling, conversions, and two’s complement math for you.


## ✨ Features

- ✅ Read **voltage**, **current**, **temperature**, and **accumulated charge**
- ✅ Enable/disable Coulomb counter with optional deadband
- ✅ Reset charge counter manually
- ✅ Read max/min voltage and current
- ✅ Overwrite min current value (for testing)
- ⚙️ Easy to integrate into any project


##  Installation

### Option 1: Arduino IDE (manual)

1. Download or clone this repository.
2. Copy the folder to your Arduino libraries directory:
3. Restart the Arduino IDE.

### Option 2: Use the Library Manager
Search for the LTC2959 library in the Arduino Library Manager
###  API Reference

| Function                                   | Return Type | Description |
|--------------------------------------------|-------------|-------------|
| `begin()`                                  | `bool`      | Initializes I2C and checks if the LTC2959 is present. Returns `true` if successful. |
| `readVoltage()`                            | `float`     | Reads the supply/battery voltage (in volts). |
| `readCurrent()`                            | `float`     | Reads the instantaneous current (in amps). |
| `readTemperature()`                        | `float`     | Reads internal temperature of the chip (in °C). |
| `readCharge_mAh()`                         | `float`     | Reads accumulated charge since last reset (in mAh). |
| `enableCounter(Deadband deadband)`         | `bool`      | Enables the Coulomb counter with a chosen deadband setting. |
| `disableCounter()`                         | `bool`      | Disables the Coulomb counter. |
| `resetChargeCounter()`                     | `void`      | Resets the charge accumulator (ACR) to 0. |
| `readMaxVoltage()`                         | `float`     | Reads the highest recorded voltage since power-up. |
| `readMinVoltage()`                         | `float`     | Reads the lowest recorded voltage since power-up. |
| `readMaxCurrent()`                         | `float`     | Reads the highest recorded current since power-up. |
| `readMinCurrent()`                         | `float`     | Reads the lowest recorded current since power-up. |


###  Requirements

- Arduino-compatible board (e.g., Uno, Mega, ESP32, STM32)
- LTC2959 IC or breakout board
- I2C connection (usually `Wire.begin()` is sufficient)
- External RSENSE resistor (default assumed 0.250 Ω)
- Arduino IDE 1.8+ or Arduino CLI

###  Author

**Pius Onyema Ndukwu**  
Electrical & Electronics Engineer | Embedded Systems Developer  
📧 Email: [onyemandukwu@gmail.com](mailto:onyemandukwu@gmail.com)


### 🔗 Useful Links

- [ltc2959.pdf](https://github.com/user-attachments/files/21163301/ltc2959.pdf)


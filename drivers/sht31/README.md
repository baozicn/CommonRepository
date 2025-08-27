# SHT31 Driver for STM32 (HAL)

This directory contains a driver for the Sensirion SHT31 temperature and humidity sensor using the STM32Cube HAL I\u00b2C interface.

## Features

- Supports basic commands: initialization, soft reset, read temperature and humidity, heater enable/disable, status read/clear.
- Works with STM32F4xx HAL (can be adapted to other STM32 families).
- Non-blocking HAL calls (polling mode). You can modify to use DMA/interrupt as needed.

## Files

- `sht31.h` – header file defining the driver API and handle structure.
- `sht31.c` – implementation of the driver functions.
- `README.md` – this document.

## Usage

1. **Hardware connections**: connect SHT31's SDA and SCL pins to the MCU's I\u00b2C bus, provide VCC (3.3\u00a0V) and GND. Pull‑up resistors (~10\u00a0k\u03a9) on SDA/SCL may be required.

2. **I\u00b2C configuration**: use STM32CubeMX or manually configure the I\u00b2C peripheral (e.g., `I2C1`) with standard mode (100\u00a0kHz) or fast mode (400\u00a0kHz). Ensure the HAL handle (`I2C_HandleTypeDef`) is available.

3. **Include and initialize**:

   ```c
   #include "sht31.h"

   SHT31_HandleTypeDef sht31;
   I2C_HandleTypeDef hi2c1; // your I2C handle

   // Initialize I2C peripheral (MX_I2C1_Init) before this call
   SHT31_Init(&sht31, &hi2c1, 0x44); // 0x44 or 0x45 based on ADDR pin
   ```

4. **Read temperature and humidity**:

   ```c
   float temperature, humidity;
   if (SHT31_ReadTempHum(&sht31, &temperature, &humidity) == HAL_OK) {
       // use temperature (\u00b0C) and humidity (%RH)
   }
   ```

5. **Heater control**:

   ```c
   SHT31_SetHeater(&sht31, 1); // enable heater
   HAL_Delay(100);
   SHT31_SetHeater(&sht31, 0); // disable heater
   ```

Refer to `examples/sht31_demo` for a complete example using this driver.

## License

This driver is released under the MIT License (see repository `LICENSE` file).

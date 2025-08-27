# STM32 SHT31 Driver

This folder contains a lightweight driver for the Sensirion SHT31 temperature and humidity sensor using the STM32 HAL.

## Files

- `sht31.h` / `sht31.c` – sensor driver implementation using `HAL_I2C_*` functions.
- `main.c` – minimal example showing how to initialize the driver and read temperature/humidity in a loop.

## Requirements

- STM32F4 microcontroller (other STM32 families may work with minor adjustments).
- STM32 HAL drivers and STM32CubeMX generated initialization code.
- I2C peripheral configured (the example uses `I2C1` and default sensor address `0x44`).

## Usage

1. Add `sht31.c` and `sht31.h` to your project’s `Src`/`Inc` folders.
2. Ensure `stm32f4xx_hal.h` and your I2C handle are included.
3. Initialize the I2C peripheral with STM32CubeMX (for example, `MX_I2C1_Init()`).
4. Declare a `SHT31_HandleTypeDef` and call `SHT31_Init(&sensor, &hi2c1, 0x44)` to initialize the sensor.
5. Call `SHT31_ReadTempHum(&sensor, &temperature, &humidity)` to obtain sensor readings.
6. Optionally use `SHT31_SetHeater()`, `SHT31_ReadStatus()`, or `SHT31_ClearStatus()` as needed.

See `main.c` for a full example.

## Notes

The driver implements the CRC-8 algorithm recommended in the Sensirion datasheet to verify data integrity. It issues single-shot high-repeatability measurements (command `0x2400`). Modify `SHT31_CMD_MEAS_HIGHREP` in `sht31.c` to use different repeatability or clock-stretching options.

This code is provided as-is under the MIT license.

#ifndef __SHT31_H
#define __SHT31_H

#include "stm32f4xx_hal.h"

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
} SHT31_HandleTypeDef;

HAL_StatusTypeDef SHT31_Init(SHT31_HandleTypeDef *sensor, I2C_HandleTypeDef *hi2c, uint8_t address);
HAL_StatusTypeDef SHT31_ReadTempHum(SHT31_HandleTypeDef *sensor, float *temperature, float *humidity);
HAL_StatusTypeDef SHT31_SetHeater(SHT31_HandleTypeDef *sensor, uint8_t enable);
HAL_StatusTypeDef SHT31_ReadStatus(SHT31_HandleTypeDef *sensor, uint16_t *status);
HAL_StatusTypeDef SHT31_ClearStatus(SHT31_HandleTypeDef *sensor);
HAL_StatusTypeDef SHT31_SoftReset(SHT31_HandleTypeDef *sensor);

#endif /* __SHT31_H */

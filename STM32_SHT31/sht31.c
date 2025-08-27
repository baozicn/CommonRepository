#include "sht31.h"

#define SHT31_CMD_READSTATUS      0xF32D
#define SHT31_CMD_CLEARSTATUS     0x3041
#define SHT31_CMD_SOFTRESET       0x30A2
#define SHT31_CMD_HEATEREN        0x306D
#define SHT31_CMD_HEATERDIS       0x3066
#define SHT31_CMD_MEAS_HIGHREP    0x2400

static uint8_t calculate_crc(uint8_t *data, int len)
{
    uint8_t crc = 0xFF;
    for(int i = 0; i < len; i++){
        crc ^= data[i];
        for(int bit = 0; bit < 8; bit++){
            if(crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;
        }
    }
    return crc;
}

static HAL_StatusTypeDef send_command(SHT31_HandleTypeDef *sensor, uint16_t cmd)
{
    uint8_t buffer[2];
    buffer[0] = (uint8_t)(cmd >> 8);
    buffer[1] = (uint8_t)(cmd & 0xFF);
    return HAL_I2C_Master_Transmit(sensor->hi2c, sensor->address, buffer, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef SHT31_Init(SHT31_HandleTypeDef *sensor, I2C_HandleTypeDef *hi2c, uint8_t address)
{
    if(sensor == NULL || hi2c == NULL){
        return HAL_ERROR;
    }
    sensor->hi2c = hi2c;
    sensor->address = address << 1;
    return SHT31_SoftReset(sensor);
}

HAL_StatusTypeDef SHT31_SoftReset(SHT31_HandleTypeDef *sensor)
{
    return send_command(sensor, SHT31_CMD_SOFTRESET);
}

HAL_StatusTypeDef SHT31_ReadStatus(SHT31_HandleTypeDef *sensor, uint16_t *status)
{
    HAL_StatusTypeDef ret = send_command(sensor, SHT31_CMD_READSTATUS);
    if(ret != HAL_OK) return ret;
    HAL_Delay(10);
    uint8_t data[3];
    ret = HAL_I2C_Master_Receive(sensor->hi2c, sensor->address, data, 3, HAL_MAX_DELAY);
    if(ret != HAL_OK) return ret;
    if(calculate_crc(data, 2) != data[2]) return HAL_ERROR;
    *status = ((uint16_t)data[0] << 8) | data[1];
    return HAL_OK;
}

HAL_StatusTypeDef SHT31_ClearStatus(SHT31_HandleTypeDef *sensor)
{
    return send_command(sensor, SHT31_CMD_CLEARSTATUS);
}

HAL_StatusTypeDef SHT31_SetHeater(SHT31_HandleTypeDef *sensor, uint8_t enable)
{
    uint16_t cmd = enable ? SHT31_CMD_HEATEREN : SHT31_CMD_HEATERDIS;
    return send_command(sensor, cmd);
}

HAL_StatusTypeDef SHT31_ReadTempHum(SHT31_HandleTypeDef *sensor, float *temperature, float *humidity)
{
    HAL_StatusTypeDef ret = send_command(sensor, SHT31_CMD_MEAS_HIGHREP);
    if(ret != HAL_OK) return ret;
    HAL_Delay(20);
    uint8_t data[6];
    ret = HAL_I2C_Master_Receive(sensor->hi2c, sensor->address, data, 6, HAL_MAX_DELAY);
    if(ret != HAL_OK) return ret;
    if(calculate_crc(data, 2) != data[2]) return HAL_ERROR;
    if(calculate_crc(data + 3, 2) != data[5]) return HAL_ERROR;
    uint16_t rawT = ((uint16_t)data[0] << 8) | data[1];
    uint16_t rawH = ((uint16_t)data[3] << 8) | data[4];
    if(temperature){
        *temperature = -45.0f + (175.0f * (float)rawT) / 65535.0f;
    }
    if(humidity){
        *humidity = 100.0f * (float)rawH / 65535.0f;
    }
    return HAL_OK;
}

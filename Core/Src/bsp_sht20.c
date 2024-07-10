/**
  ******************************************************************************
  * @file   bsp_hdc1080.c
  * @brief  温湿度传感器HDC1080驱动
  *   
  ******************************************************************************
  */
#include "bsp_sht20.h"
#include "i2c.h"

volatile HDC1080_TemRH_Val gTemRH_Val;  // 存储温湿度值

/*
**********************************************************************
* @fun     :HDC1080_ReadRegister 
* @brief   :读取HDC1080寄存器的值
* @param   :reg - 要读取的寄存器地址
* @return  :寄存器值
**********************************************************************
*/
uint16_t HDC1080_ReadRegister(uint8_t reg)
{
    uint16_t reg_val = 0;
    uint8_t reg_buff[2] = {0x00, 0x00};

    // 发送控制指令，设置要读取的寄存器地址
    HAL_I2C_Master_Transmit(&hi2c1, HDC1080_ADDR << 1, &reg, 1, 100);
    // 适当增加延时，等待设置完成
    HAL_Delay(15);
    // 读取数据，两个字节
    HAL_I2C_Master_Receive(&hi2c1, HDC1080_ADDR << 1, reg_buff, 2, 100);

    reg_val = (reg_buff[0] << 8) | reg_buff[1];

    return reg_val;
}

/*
**********************************************************************
* @fun     :HDC1080_Init
* @brief   :初始化HDC1080传感器
* @param   :none
* @return  :none
**********************************************************************
*/
void HDC1080_Init(void)
{
    uint8_t config_reg = HDC1080_CONFIG_REG;
    uint16_t config_val = 0x1000; // 设置为同时测量温度和湿度，14位分辨率
    uint8_t config_data[3] = {config_reg, config_val >> 8, config_val & 0xFF};

    // 写入配置寄存器
    HAL_I2C_Master_Transmit(&hi2c1, HDC1080_ADDR << 1, config_data, 3, 100);
    HAL_Delay(15); // 等待配置完成
}

/*
**********************************************************************
* @fun     :HDC1080_GetData 
* @brief   :获取HDC1080的温湿度数据
* @param   :none
* @return  :none
**********************************************************************
*/
void HDC1080_GetData(void)
{
    uint16_t rawTemp = 0, rawHum = 0;
    // 读取温湿度数据
    rawTemp = HDC1080_ReadRegister(HDC1080_TEMP_REG);
    rawHum = HDC1080_ReadRegister(HDC1080_HUMIDITY_REG);
    // 数据转换
    gTemRH_Val.Temperature = -40.0f + 165.0f * ((float)rawTemp / 65536);
    gTemRH_Val.Humidity = 100.0f * ((float)rawHum / 65536);
}

/**
  ******************************************************************************
  * @file   bsp_ap3216c.c
  * @brief  光强度、接近、红外传感器LTR-553ALS-01驱动
  *   
  ******************************************************************************
  */
#include "bsp_ap3216c.h"
#include "i2c.h"

volatile StruLTR553_Val gLTR553_Val;	//LTR-553数据结构

/* 写寄存器的值 */
static void write_reg(uint8_t reg, uint8_t data)
{
    HAL_I2C_Mem_Write(&hi2c1, LTR553ALS_ADDR_WRITE, reg, 1, &data, 1, 10);
}

/* 读寄存器的值 */
static void read_regs(uint8_t reg, uint8_t len, uint8_t *buf)
{
    HAL_I2C_Mem_Read(&hi2c1, LTR553ALS_ADDR_READ, reg, 1, buf, len, 10);	
}

/* 软件复位传感器 */
static void reset_sensor(void)
{
    write_reg(LTR553ALS_ALS_CONTR_REG, 0x00); // reset
    write_reg(LTR553ALS_PS_CONTR_REG, 0x00); // reset
}

/**
 * This function is convenient to getting data except including high and low
 * data for this sensor. note:after reading lower register first,reading higher
 * add one.
 */
static uint32_t read_low_and_high(uint8_t reg)
{
    uint8_t  buf[2] = {0};
    read_regs(reg, 2, buf); // 读低字节和高字节
    return (buf[1] << 8) | buf[0]; // 合并数据
}

void ltr553_init(void)
{
    /* reset LTR-553 */
    reset_sensor();
    HAL_Delay(100);
    write_reg(LTR553ALS_ALS_CONTR_REG, 0x01); // 启动ALS
    write_reg(LTR553ALS_PS_CONTR_REG, 0x01); // 启动PS
    HAL_Delay(150); // delay at least 112.5ms
}

uint16_t ltr553_read_ambient_light(void)
{
    uint16_t ch0_data = read_low_and_high(LTR553ALS_ALS_DATA_CH0_0_REG);
    uint16_t ch1_data = read_low_and_high(LTR553ALS_ALS_DATA_CH1_0_REG);
    return (ch0_data + ch1_data) / 2; // 示例返回平均光照强度
}

uint16_t ltr553_read_ps_data(void)
{
    return read_low_and_high(LTR553ALS_PS_DATA_0_REG);
}

uint8_t ltr553_get_IntStatus(void)
{
    uint8_t IntStatus;
    read_regs(LTR553ALS_ALS_PS_STATUS_REG, 1, &IntStatus);
    return IntStatus;
}

/**
 * This function sets parameter of ltr553 sensor
 *
 * @param cmd the parameter cmd of device
 * @param value for setting value in cmd register
 */
void ltr553_set_param(ltr553_cmd_t cmd, uint8_t value)
{
    switch (cmd) {
        case LTR553_SYSTEM_MODE:
            write_reg(LTR553ALS_ALS_CONTR_REG, value);
            write_reg(LTR553ALS_PS_CONTR_REG, value);
            break;
        case LTR553_INT_PARAM:
            write_reg(LTR553ALS_INTERRUPT_REG, value);
            break;
        case LTR553_ALS_MEAS_RATE:
            write_reg(LTR553ALS_ALS_MEAS_RATE_REG, value);
            break;
        case LTR553_PS_MEAS_RATE:
            write_reg(LTR553ALS_PS_MEAS_RATE_REG, value);
            break;
        // 其他参数配置可根据需要添加
        default:
            break;
    }
}

/**
 * This function gets parameter of ltr553 sensor
 *
 * @param cmd the parameter cmd of device
 * @param value to get value in cmd register
 */
void ltr553_get_param(ltr553_cmd_t cmd, uint8_t *value)
{
    switch (cmd) {
        case LTR553_SYSTEM_MODE:
            read_regs(LTR553ALS_ALS_CONTR_REG, 1, value);
            break;
        case LTR553_INT_PARAM:
            read_regs(LTR553ALS_INTERRUPT_REG, 1, value);
            break;
        case LTR553_ALS_MEAS_RATE:
            read_regs(LTR553ALS_ALS_MEAS_RATE_REG, 1, value);
            break;
        case LTR553_PS_MEAS_RATE:
            read_regs(LTR553ALS_PS_MEAS_RATE_REG, 1, value);
            break;
        // 其他参数读取可根据需要添加
        default:
            break;
    }
}

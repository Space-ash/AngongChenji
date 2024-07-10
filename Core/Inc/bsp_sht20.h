/**
  ******************************************************************************
  * @file   bsp_hdc1080.h
  * @brief  温湿度传感器HDC1080驱动
  *          
  ******************************************************************************
  */
#ifndef __BSP_HDC1080_H__
#define __BSP_HDC1080_H__
//
#include "main.h"

#define HDC1080_ADDR 0x40

// HDC1080寄存器地址
#define HDC1080_TEMP_REG 0x00
#define HDC1080_HUMIDITY_REG 0x01
#define HDC1080_CONFIG_REG 0x02

//温湿度传感器数据结构
typedef struct
{
    float   Temperature;
    float   Humidity;
} HDC1080_TemRH_Val;

//
uint16_t HDC1080_ReadRegister(uint8_t reg);
void HDC1080_Init(void);
void HDC1080_GetData(void);

#endif /* __BSP_HDC1080_H__ */

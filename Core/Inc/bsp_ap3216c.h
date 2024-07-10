/**
  ******************************************************************************
  * @file   bsp_ap3216c.h
  * @brief  光强度、接近、红外传感器LTR-553ALS-01驱动
  *          
  ******************************************************************************
  */
#ifndef __BSP_LTR553_H__
#define __BSP_LTR553_H__

#include "main.h"

#define LTR553ALS_ADDR        0x23

#define LTR553ALS_ADDR_READ   0x47
#define LTR553ALS_ADDR_WRITE  0x46

// System Register
#define LTR553ALS_ALS_CONTR_REG          0x80
#define LTR553ALS_PS_CONTR_REG           0x81
#define LTR553ALS_PS_LED_REG             0x82
#define LTR553ALS_PS_N_PULSES_REG        0x83
#define LTR553ALS_PS_MEAS_RATE_REG       0x84
#define LTR553ALS_ALS_MEAS_RATE_REG      0x85
#define LTR553ALS_PART_ID_REG            0x86
#define LTR553ALS_MANUFAC_ID_REG         0x87
#define LTR553ALS_ALS_DATA_CH1_0_REG     0x88
#define LTR553ALS_ALS_DATA_CH1_1_REG     0x89
#define LTR553ALS_ALS_DATA_CH0_0_REG     0x8A
#define LTR553ALS_ALS_DATA_CH0_1_REG     0x8B
#define LTR553ALS_ALS_PS_STATUS_REG      0x8C
#define LTR553ALS_PS_DATA_0_REG          0x8D
#define LTR553ALS_PS_DATA_1_REG          0x8E
#define LTR553ALS_INTERRUPT_REG          0x8F
#define LTR553ALS_PS_THRES_UP_0_REG      0x90
#define LTR553ALS_PS_THRES_UP_1_REG      0x91
#define LTR553ALS_PS_THRES_LOW_0_REG     0x92
#define LTR553ALS_PS_THRES_LOW_1_REG     0x93
#define LTR553ALS_PS_OFFSET_1_REG        0x94
#define LTR553ALS_PS_OFFSET_0_REG        0x95
#define LTR553ALS_ALS_THRES_UP_0_REG     0x97
#define LTR553ALS_ALS_THRES_UP_1_REG     0x98
#define LTR553ALS_ALS_THRES_LOW_0_REG    0x99
#define LTR553ALS_ALS_THRES_LOW_1_REG    0x9A
#define LTR553ALS_INTERRUPT_PERSIST_REG  0x9E

enum ltr553_mode_value {
    LTR553_MODE_POWER_DOWN,
    LTR553_MODE_ALS,
    LTR553_MODE_PS,
    LTR553_MODE_ALS_AND_PS,
    LTR553_MODE_SW_RESET,
    LTR553_MODE_ALS_ONCE,
    LTR553_MODE_PS_ONCE,
    LTR553_MODE_ALS_AND_PS_ONCE,
};

enum ltr553_int_clear_manner {
    LTR553_INT_CLEAR_MANNER_BY_READING,
    LTR553_ALS_CLEAR_MANNER_BY_SOFTWARE,
};

enum als_meas_rate {
    LTR553_ALS_MEAS_RATE_50MS,
    LTR553_ALS_MEAS_RATE_100MS,
    LTR553_ALS_MEAS_RATE_200MS,
    LTR553_ALS_MEAS_RATE_500MS,
    LTR553_ALS_MEAS_RATE_1000MS,
    LTR553_ALS_MEAS_RATE_2000MS,
};
typedef enum als_meas_rate als_meas_rate_t;

enum ps_meas_rate {
    LTR553_PS_MEAS_RATE_10MS,
    LTR553_PS_MEAS_RATE_50MS,
    LTR553_PS_MEAS_RATE_100MS,
    LTR553_PS_MEAS_RATE_200MS,
    LTR553_PS_MEAS_RATE_500MS,
    LTR553_PS_MEAS_RATE_1000MS,
    LTR553_PS_MEAS_RATE_2000MS,
};
typedef enum ps_meas_rate ps_meas_rate_t;

enum ltr553_cmd {
    LTR553_SYSTEM_MODE,
    LTR553_INT_PARAM,
    LTR553_ALS_MEAS_RATE,
    LTR553_PS_MEAS_RATE,
    // 其他命令根据需要添加
};
typedef enum ltr553_cmd ltr553_cmd_t;

/* 中断参数 */
struct ltr553_threshold {
    uint16_t min; /* als 16 bits, ps 10 bits available */
    uint16_t max; /* als 16 bits, ps 10 bits available */
};
typedef struct ltr553_threshold ltr553_threshold_t;

uint8_t ltr553_get_IntStatus(void);

void ltr553_init(void);

uint16_t ltr553_read_ambient_light(void);

uint16_t ltr553_read_ps_data(void);

void ltr553_set_param(ltr553_cmd_t cmd, uint8_t value);

void ltr553_get_param(ltr553_cmd_t cmd, uint8_t *value);

typedef struct
{
    uint16_t ALS;
    uint16_t PS;
    uint16_t IR;
} StruLTR553_Val;

#endif /* __BSP_LTR553_H__ */

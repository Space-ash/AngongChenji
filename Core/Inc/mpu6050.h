#ifndef __MPU6050_H
#define __MPU6050_H
/* Includes ------------------------------------------------------------------*/
//****************************************
// MPU6050 IIC���Գ���
//****************************************

#include "stm32u5xx_hal.h"

//typedef unsigned char  uchar;
typedef unsigned short ushort;
//typedef unsigned int   uint;

//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			  0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ����������ֵ��0x00(��������)
#define	WHO_AM_I			0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
//#define	SlaveAddress		//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define SlaveAddress     (MPU6050_ADDRESS_AD0_HIGH<<1)

void InitMPU6050(void);	
void mpu6050_ACCEL    (int16_t *x, int16_t *y, int16_t *z);
void mpu6050_GYRO(int16_t *x, int16_t *y, int16_t *z)	;
void mpu6050_verify  (int16_t *x, int16_t *y, int16_t *z);
#endif 



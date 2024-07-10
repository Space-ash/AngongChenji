/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.21.3. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
}
extern "C"
{
	#include "bsp_ft6336.h"
}
extern "C" FT6336_TouchPointType tp;
extern volatile uint32_t ft6336_on_touch_count;
//
bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
		uint16_t xDiff = 0,yDiff = 0;	
		static uint16_t pI_Touch_X = 0, pI_Touch_Y = 0;
		//触摸中断产生
		if (ft6336_on_touch_count) // irq done
		{
			uint8_t id1 = FT6336_read_touch1_id(); // id1 = 0 or 1
			tp.tp[id1].status = (tp.tp[id1].status == release) ? touch : stream;
			tp.tp[id1].x = FT6336_read_touch1_x();
			tp.tp[id1].y = FT6336_read_touch1_y();
			tp.tp[~id1 & 0x01].status = release;
			//更新数据至TouchGFX
			if (tp.tp[0].status == 1)	//�?多支持两个触�?
			{ 
				xDiff = tp.tp[0].x > pI_Touch_X ? (tp.tp[0].x - pI_Touch_X): (pI_Touch_X - tp.tp[0].x);
				yDiff = tp.tp[0].y > pI_Touch_Y ? (tp.tp[0].y - pI_Touch_Y): (pI_Touch_Y - tp.tp[0].y);
				//判断阈�??
				if ((xDiff + yDiff) > 5)
				{
					pI_Touch_X = tp.tp[0].x;
					pI_Touch_Y = tp.tp[0].y;
				}
				//更新触摸,横屏触摸坐标变换
				x = pI_Touch_Y;
				y = 240 - pI_Touch_X;
			}
			
			ft6336_on_touch_count = 0;
			//
			return true;
		}
		//
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

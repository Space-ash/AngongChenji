/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : TouchGFXHAL.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.21.2. This file is only
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

#include <TouchGFXHAL.hpp>

/* USER CODE BEGIN TouchGFXHAL.cpp */
#include <touchgfx/hal/OSWrappers.hpp>
//用户外设驱动头文�?
#include "spi.h"
#include "stm32u5xx_hal.h"
//
extern "C" void ILI9341_SetArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);	//设置显示区域
extern "C"  void ILI9341_WriteRAM_Prepare(void);
//
extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef handle_GPDMA1_Channel0;
//
using namespace touchgfx;

void TouchGFXHAL::initialize()
{
    // Calling parent implementation of initialize().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::initialize() must be called to initialize the framework.

    TouchGFXGeneratedHAL::initialize();
}

/**
 * Gets the frame buffer address used by the TFT controller.
 *
 * @return The address of the frame buffer currently being displayed on the TFT.
 */
uint16_t* TouchGFXHAL::getTFTFrameBuffer() const
{
    // Calling parent implementation of getTFTFrameBuffer().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    return TouchGFXGeneratedHAL::getTFTFrameBuffer();
}

/**
 * Sets the frame buffer address used by the TFT controller.
 *
 * @param [in] address New frame buffer address.
 */
void TouchGFXHAL::setTFTFrameBuffer(uint16_t* address)
{
    // Calling parent implementation of setTFTFrameBuffer(uint16_t* address).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::setTFTFrameBuffer(address);
}
static void USER_SPI_Transmit_DMA(const uint16_t *pData, uint16_t pSize)
{
		//Set the transaction information
		hspi1.State       = HAL_SPI_STATE_READY;
		hspi1.ErrorCode   = HAL_SPI_ERROR_NONE;

		//Init field not used in handle to zero
		hspi1.RxISR       = NULL;
		hspi1.TxISR       = NULL;

		//Configure communication direction : 1Line
		SPI_2LINES_TX(&hspi1);

		// Packing mode management is enabled by the DMA settings
		IS_SPI_FULL_INSTANCE(hspi1.Instance);

		//Clear TXDMAEN bit
		CLEAR_BIT(hspi1.Instance->CFG1, SPI_CFG1_TXDMAEN);

		//Update the DMA channel state
		handle_GPDMA1_Channel0.State = HAL_DMA_STATE_BUSY;
		//Update the DMA channel error code
		handle_GPDMA1_Channel0.ErrorCode = HAL_DMA_ERROR_NONE;

		//Configure the source address, destination address, the data size and clear flags
		MODIFY_REG(handle_GPDMA1_Channel0.Instance->CBR1, DMA_CBR1_BNDT, ((pSize) & DMA_CBR1_BNDT));

		//Clear all interrupt flags
		__HAL_DMA_CLEAR_FLAG(&handle_GPDMA1_Channel0, DMA_FLAG_TC | DMA_FLAG_HT | DMA_FLAG_DTE | DMA_FLAG_ULE | DMA_FLAG_USE | DMA_FLAG_SUSP |
												 DMA_FLAG_TO);

		//Configure DMA channel source address
		handle_GPDMA1_Channel0.Instance->CSAR = (uint32_t)pData;

		//Configure DMA channel destination address
		handle_GPDMA1_Channel0.Instance->CDAR = (uint32_t)&hspi1.Instance->TXDR;

		//Enable common interrupts: Transfer Complete and Transfer Errors ITs
		__HAL_DMA_ENABLE_IT(&handle_GPDMA1_Channel0, (DMA_IT_TC | DMA_IT_DTE | DMA_IT_ULE | DMA_IT_USE | DMA_IT_TO));

		//If Half Transfer complete callback is set, enable the corresponding IT
		__HAL_DMA_ENABLE_IT(&handle_GPDMA1_Channel0, DMA_IT_HT);

		//Enable DMA channel
		__HAL_DMA_ENABLE(&handle_GPDMA1_Channel0);

		//Set the number of data at current transfer
		MODIFY_REG(hspi1.Instance->CR2, SPI_CR2_TSIZE, (pSize));

		//Enable Tx DMA Request
		SET_BIT(hspi1.Instance->CFG1, SPI_CFG1_TXDMAEN);

		//Enable the SPI Error Interrupt Bit
		__HAL_SPI_ENABLE_IT(&hspi1, (SPI_IT_UDR | SPI_IT_FRE | SPI_IT_MODF));

		//Enable SPI peripheral
		__HAL_SPI_ENABLE(&hspi1);
		//
		if (((hspi1.Instance->AUTOCR & SPI_AUTOCR_TRIGEN) == 0U) && (hspi1.Init.Mode == SPI_MODE_MASTER))
		{
			/* Master transfer start */
			SET_BIT(hspi1.Instance->CR1, SPI_CR1_CSTART);
		}	
}
/**
 * This function is called whenever the framework has performed a partial draw.
 *
 * @param rect The area of the screen that has been drawn, expressed in absolute coordinates.
 *
 * @see flushFrameBuffer().
 */
static uint16_t flushAreaBuf[31745];	//62KB区域性刷新缓冲区
void TouchGFXHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    // Calling parent implementation of flushFrameBuffer(const touchgfx::Rect& rect).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::flushFrameBuffer(const touchgfx::Rect& rect) must
    // be called to notify the touchgfx framework that flush has been performed.
    // To calculate he start adress of rect,
    // use advanceFrameBufferToRect(uint8_t* fbPtr, const touchgfx::Rect& rect)
    // defined in TouchGFXGeneratedHAL.cpp
		/*************************************屏幕刷新�?�?*************************************/
		__IO uint16_t *pixels;  //帧缓冲地�?
		__IO uint16_t pheight = 0,pWidth = 0,pBuffCnt = 0;
		//保存长度
		__IO uint32_t pTotalPixel = rect.width * rect.height * 2;
		__IO uint32_t pFull = pTotalPixel / 63488;	//62KB取整
		__IO uint32_t pRemain = pTotalPixel % 63488;	//62KB取余
		//设置显示区域
		ILI9341_SetArea(rect.x, rect.y,rect.x+rect.width-1, rect.y+rect.height-1);
		ILI9341_WriteRAM_Prepare();		//�?始写入GRAM	
	
		//设置SPI数据格式�?16位，缓冲区数据采用小端模式，ILI9341数据传输高字节在�?
		hspi1.Instance->CFG1 &= (~0x1F);
		hspi1.Instance->CFG1 |= SPI_DATASIZE_16BIT;		
		//
		if((rect.width == 320) && (rect.height ==240))  //采用横屏，整个屏幕刷�?
		{
			//获取像素点地�?
			pixels = getClientFrameBuffer() + rect.x + (rect.y) * HAL::DISPLAY_WIDTH;	
			//传输长度�?62KB的像素点
			for (pBuffCnt = 0; pBuffCnt < pFull; pBuffCnt++)
			{
				//启动DMA传输
				USER_SPI_Transmit_DMA((uint16_t *)pixels,63488);	//DMA单次传输�?�?0xFFFF
				//
				pixels = pixels + 31744;  //地址偏移
				//等待DMA传输完成
				while(HAL_DMA_GetState(&handle_GPDMA1_Channel0) != HAL_DMA_STATE_READY);	
				//适当延时
				HAL_Delay(0);
				//阻塞模式下，终止正在的传�?
				HAL_SPI_Abort(&hspi1);
			}
			//启动DMA传输
			USER_SPI_Transmit_DMA((uint16_t *)pixels,pRemain);	//剩余数据传输
			//等待DMA传输完成
			while(HAL_DMA_GetState(&handle_GPDMA1_Channel0) != HAL_DMA_STATE_READY);	
			//适当延时
			HAL_Delay(0);
			//阻塞模式下，终止正在的传�?
			HAL_SPI_Abort(&hspi1);
		}
		else	//屏幕区域刷新
		{
			for (pheight = 0; pheight < rect.height; pheight++)
			{
				//缓冲区数据采用小端模式，ILI9341数据传输高字节在�?
				pixels = getClientFrameBuffer() + rect.x + (pheight + rect.y) * HAL::DISPLAY_WIDTH;
				//读取限度点至缓冲�?
				for (pWidth = 0; pWidth < rect.width; pWidth++)
				{
					flushAreaBuf[pBuffCnt++] = *pixels;	//读取像素�?
					pixels++;	//调整偏移地址
					if(pBuffCnt >= 31744)	//缓冲区数据满，传输数据至屏幕
					{
						//启动DMA传输
						USER_SPI_Transmit_DMA((uint16_t *)flushAreaBuf,63488);
						//等待DMA传输完成
						while(HAL_DMA_GetState(&handle_GPDMA1_Channel0) != HAL_DMA_STATE_READY);	
						//适当延时
						HAL_Delay(0);
						//阻塞模式下，终止正在的传�?
						HAL_SPI_Abort(&hspi1);
						//复位计数�?
						pBuffCnt =0;
					}
				}
			}
			//启动DMA传输
			USER_SPI_Transmit_DMA((uint16_t *)flushAreaBuf,pBuffCnt * 2);
			//等待DMA传输完成
			while(HAL_DMA_GetState(&handle_GPDMA1_Channel0) != HAL_DMA_STATE_READY);	
			//适当延时
			HAL_Delay(0);
			//阻塞模式下，终止正在的传�?
			HAL_SPI_Abort(&hspi1);
		}
		//设置SPI数据格式�?8�?
		hspi1.Instance->CFG1 &= (~0x1F);
		hspi1.Instance->CFG1 |= SPI_DATASIZE_8BIT;	
		/*************************************屏幕刷新完成*************************************/
		//
    TouchGFXGeneratedHAL::flushFrameBuffer(rect);
}

bool TouchGFXHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
    return TouchGFXGeneratedHAL::blockCopy(dest, src, numBytes);
}

/**
 * Configures the interrupts relevant for TouchGFX. This primarily entails setting
 * the interrupt priorities for the DMA and LCD interrupts.
 */
void TouchGFXHAL::configureInterrupts()
{
    // Calling parent implementation of configureInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::configureInterrupts();
}

/**
 * Used for enabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::enableInterrupts()
{
    // Calling parent implementation of enableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableInterrupts();
}

/**
 * Used for disabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::disableInterrupts()
{
    // Calling parent implementation of disableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::disableInterrupts();
}

/**
 * Configure the LCD controller to fire interrupts at VSYNC. Called automatically
 * once TouchGFX initialization has completed.
 */
void TouchGFXHAL::enableLCDControllerInterrupt()
{
    // Calling parent implementation of enableLCDControllerInterrupt().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableLCDControllerInterrupt();
}

bool TouchGFXHAL::beginFrame()
{
    return TouchGFXGeneratedHAL::beginFrame();
}

void TouchGFXHAL::endFrame()
{
    TouchGFXGeneratedHAL::endFrame();
}

extern "C"
void touchgfx_signalVSynTimer(void)
{
    /* VSync has occurred, increment TouchGFX engine vsync counter */
    HAL::getInstance()->vSync();

    /* VSync has occurred, signal TouchGFX engine */
    OSWrappers::signalVSync();
}
/* USER CODE END TouchGFXHAL.cpp */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

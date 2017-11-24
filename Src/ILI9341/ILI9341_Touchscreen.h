//	MIT License
//
//	Copyright (c) 2017 Matej Artnak
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//
//
//-----------------------------------
//	ILI9341 Touchscreen library for STM32
//-----------------------------------
//
//	Very simple Touchscreen library for ILI9341.
//	Extremly basic reading of position. No runtime calibration, No prediction, basic noise removal. Simple but stupid.
//	Basic hardcoded calibration values saved in .h file
//
//	Library is written for STM32 HAL library and supports STM32CUBEMX. To use the library with Cube software
//	you need to tick the box that generates peripheral initialization code in their own respective .c and .h file
//
//
//-----------------------------------
//	How to use this library
//-----------------------------------
//
//	-If using MCUs other than STM32F7 you will have to change the #include "stm32f7xx_hal.h" in the ILI9341_Touchscreen.h to your respective .h file
//	-define GPIO inputs and outputs then map the Pins and Ports inside the ILI9341_Touchscreen.h
//	-Library does not require any initialization calls apart from GPIO initialization. Initialize GPIOs before calling library functions!
//
//		Touchpad GPIO defines
//			Outputs:
//				CLK
//				MOSI
//				CS
//
//			Inputs:
//				IRQ
//				MISO
//
//
//	-Touchpad library bitbangs SPI interface and only requires basic GPIOs.
//	-Setting GPIOs as FREQ_VERY_HIGH Recommended
//
//	-Warning! Library is written for "ILI9341_Set_Rotation(SCREEN_VERTICAL_1)"	(See ILI9341_STM32_Driver for information about function)
//	-If using different layout you will have to Re-Map X and Y coordinates of the Screen
//
//
//	-NO_OF_POSITION_SAMPLES makes location output less noisy but increases reading time. Increase and decrease to your liking
//
//----------EXAMPLE------------------
/*
if(TP_Touchpad_Pressed())
	{					
		uint16_t x_pos = 0;
		uint16_t y_pos = 0;
		
		uint16_t position_array[2];
		if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK)
		{
		x_pos = position_array[0];
		y_pos = position_array[1];
		}							
	}
*/
//-----------------------------------


#ifndef TOUCH_H
#define TOUCH_H

#include "stm32f7xx_hal.h"


#define TP_CLK_PORT								GPIOE
#define TP_CLK_PIN								T_CLK_Pin

#define TP_CS_PORT								GPIOE
#define TP_CS_PIN									T_CS_Pin

#define TP_MISO_PORT							GPIOE
#define TP_MISO_PIN								T_MISO_Pin

#define TP_MOSI_PORT							GPIOE
#define TP_MOSI_PIN								T_MOSI_Pin

#define TP_IRQ_PORT								GPIOE
#define TP_IRQ_PIN								T_IRQ_Pin

#define CMD_RDY             			0X90
#define CMD_RDX             			0XD0

//RETURN VALUES FOR TP_Touchpad_Pressed 
#define TOUCHPAD_NOT_PRESSED			0
#define TOUCHPAD_PRESSED					1

//RETURN VALUES FOR TP_Read_Coordinates
#define TOUCHPAD_DATA_OK					1
#define TOUCHPAD_DATA_NOISY				0

//HARDCODED CALIBRATION, CHANGE IF REQUIRED
#define X_OFFSET									13
#define Y_OFFSET									15
#define X_MAGNITUDE								1.16
#define Y_MAGNITUDE								1.16

//CONVERTING 16bit Value to Screen coordinates
// 65535/273 = 240!
// 65535/204 = 320!
#define X_TRANSLATION							273
#define Y_TRANSLATION							204

//In order to increase accuracy of location reads library samples
//NO_OF_POSITION_SAMPLES numbers of locations and averages them
//If library runs too slow decrease NO_OF_POSITION_SAMPLES, but
//expect inreasingly noisy or incorrect locations returned

#define NO_OF_POSITION_SAMPLES	 	1000

//Internal Touchpad command, do not call directly
uint16_t TP_Read(void);

//Internal Touchpad command, do not call directly
void TP_Write(uint8_t value);

//Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2]);

//Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void);

#endif

# STM32-ILI9341
Simple driver for ILI9341 320x240 TFT LCD with Touchscreen for STM32 microcontrollers

Requires no DMA or Interrupts while still maintaining very fast screen draws. See performance analysis below

The intent of this library is to provide a really simple way to get ILI9341 projects started without complex methods.
Basic SPI and GPIO inputs/Outputs are enough to use the library.

Contains:
  - main driver for initialization and basic functions "ILI9341_STM32_Driver"
  - GFX driver for advanced functionality (fonts, pictures)
  - Touchscreen driver
  - Example project with CubeMX built for STM32F746ZG Nucleo board
    - Example usage of functions

Downloading project and setting up example based on STM32F7:
  - Extract the project into a folder and run CubeMX project
  - Generate code using CubeMX
  - Add ILI9341 folder to flash->configure flash tools->C/C++ ->Include paths
  - Add files in ILI9341 folder to project (Add existing files to group...)
  
Alternatively download entire project in .rar file. Paths might be broken and might require re-linking.
 ¯\\_(ツ)_/¯

ILI9341 Driver library for STM32


While there are other libraries for ILI9341 they mostly require either interrupts, DMA or both for fast drawing
The intent of this library is to offer a simple yet still reasonably fast alternatives for those that
do not wish to use interrupts or DMA in their projects.

Library is written for STM32 HAL library and supports STM32CUBEMX. To use the library with Cube software
you need to tick the box that generates peripheral initialization code in their own respective .c and .h file


Performance

Settings:	
  - SPI @ 50MHz 
  - STM32F746ZG Nucleo board
  - Redraw entire screen

  Theoretical maximum FPS with 50Mhz SPI calculated to be 40.69 FPS
  
  320x240 = 76800 pixels, each pixel contains 16bit colour information (2x8)
  Theoretical Max FPS: 1/((320x240x16)/50000000)

With ART Accelerator, instruction prefetch, CPU ICACHE and CPU DCACHE enabled:

 - FPS:							39.62
 - SPI utilization:					97.37%
 - MB/Second:						6.09

With ART Accelerator, instruction prefetch, CPU ICACHE and CPU DCACHE disabled:

 - FPS:							35.45
 - SPI utilization:					87.12%
 - MB/Second:						5.44

ART Accelerator, instruction prefetch, CPU ICACHE and CPU DCACHE settings found in MXCUBE under "System-> CORTEX M7 button"


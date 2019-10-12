//
// Created by Ilia.Motornyi on 10/10/2019.
//

/**
 * INDIVIDUAL PIXEL EXAMPLE
 */
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include "snow_tiger.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

void demoPixels() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Random position and colour", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("500000 pixels", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);


    for (uint32_t i = 0; i < 500000; i++) {
        uint32_t random_num = 0;
        uint16_t xr = 0;
        uint16_t yr = 0;
        random_num = random();
        xr = random_num;
        random_num = random();
        yr = random_num;
        uint16_t color = random();

        xr &= 0x01FFu;
        yr &= 0x01FFu;
        ILI9341_Draw_Pixel(xr, yr, color);
    }
    HAL_Delay(2000);
}

/**
 * LINES EXAMPLE
 */
void demoLines() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("Horizontal and Vertical lines", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    for (uint32_t i = 0; i < 30000; i++) {
        uint32_t random_num = 0;
        uint16_t xr = 0;
        uint16_t yr = 0;
        uint16_t radiusr = 0;
        uint16_t colourr = 0;
        random_num = random();
        xr = random_num;
        random_num = random();
        yr = random_num;
        random_num = random();
        radiusr = random_num;
        random_num = random();
        colourr = random_num;

        xr &= 0x01FFu;
        yr &= 0x01FFu;
        radiusr &= 0x001Fu;
//ili9341_drawpixel(xr, yr, WHITE);
        ILI9341_Draw_Horizontal_Line(xr, yr, radiusr, colourr);
        ILI9341_Draw_Vertical_Line(xr, yr, radiusr, colourr);
    }

    HAL_Delay(1000);
}

static char Temp_Buffer_text[40];

/**
 * COUNTING MULTIPLE SEGMENTS
 */
void demoMultipleSegments() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Counting multiple segments at once", 10, 10, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);


    for (uint16_t i = 0; i <= 10; i++) {
        sprintf(Temp_Buffer_text, "Counting: %d", i);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 10, BLACK, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 30, BLUE, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 50, RED, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 70, GREEN, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 90, BLACK, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 110, BLUE, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 130, RED, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 150, GREEN, 2, WHITE);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 170, WHITE, 2, BLACK);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 190, BLUE, 2, BLACK);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 210, RED, 2, BLACK);
    }

    HAL_Delay(1000);
}

/**
 * PERFORMANCE TEST
 */

void perfTest() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("FPS TEST, 30 loop 2 screens", 3, 2, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    uint32_t Timer_Counter = HAL_GetTick();
    for (uint32_t j = 0; j < 2; j++) {
        for (uint16_t i = 0; i < 30; i++) {
            ILI9341_Fill_Screen(WHITE);
            ILI9341_Fill_Screen(BLACK);
        }

    }
    Timer_Counter = HAL_GetTick() - Timer_Counter;

    char counter_buff[30];
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    sprintf(counter_buff, "Timer counter value: %ld", Timer_Counter);
    ILI9341_Draw_Text(counter_buff, 10, 10, BLACK, 1, WHITE);

    double seconds_passed = (Timer_Counter / 1000.0);
    sprintf(counter_buff, "Time: %.3f Sec", seconds_passed);
    ILI9341_Draw_Text(counter_buff, 10, 30, BLACK, 2, WHITE);

    double timer_float = 60 / seconds_passed;    //Frames per sec

    sprintf(counter_buff, "FPS:  %.2f", timer_float);
    ILI9341_Draw_Text(counter_buff, 10, 50, BLACK, 2, WHITE);
    double MB_PS = timer_float * 240.0 * 320 * 2 / 1000000.0;
    sprintf(counter_buff, "MB/S: %.2f", MB_PS);
    ILI9341_Draw_Text(counter_buff, 10, 70, BLACK, 2, WHITE);
    double SPI_utilized_percentage = (MB_PS / (5.0)) * 100;        //40mbps / 8 bits
    sprintf(counter_buff, "SPI Utilized: %.2f", SPI_utilized_percentage);
    ILI9341_Draw_Text(counter_buff, 10, 90, BLACK, 2, WHITE);
    HAL_Delay(10000);

}

/**
 * IMAGE EXAMPLE, Snow Tiger
 */
void demoImage() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("RGB Picture", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("TIGER", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    uint32_t t = HAL_GetTick();
    for(int i = 0;i <10;i++) {
        ILI9341_Draw_Image((const char *) snow_tiger, SCREEN_VERTICAL_2);
    }
    char buf[100];
    snprintf(buf, 99, "FPS: %.2f", 10.0 / ((HAL_GetTick() - t) / 1000.0));
    ILI9341_Draw_Text(buf, 2, 2, YELLOW, 3, DARKCYAN);
    HAL_Delay(10000);
}

/**
 * INDIVIDUAL PIXEL EXAMPLE
 */
void demoIndividualPixel() {

    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Slow draw by selecting", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("and adressing pixels", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);


    int x = 0;
    int y = 0;
    while (y < 240) {
        while ((x < 320) && (y < 240)) {

            if (x % 2) {
                ILI9341_Draw_Pixel(x, y, BLACK);
            }

            x++;
        }

        y++;
        x = 0;
    }

    x = 0;
    y = 0;


    while (y < 240) {
        while ((x < 320) && (y < 240)) {

            if (y % 2) {
                ILI9341_Draw_Pixel(x, y, BLACK);
            }

            x++;
        }

        y++;
        x = 0;
    }
    HAL_Delay(2000);
}

/**
 * 565 COLOUR EXAMPLE, Grayscale
 */
void demoGrayscale() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Colour gradient", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("Grayscale", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);


    for (uint16_t i = 0; i <= (320); i++) {
        uint16_t Red = 0;
        uint16_t Green = 0;
        uint16_t Blue = 0;

        Red = i / (10);
        Red <<= 11u;
        Green = i / (5);
        Green <<= 5u;
        Blue = i / (10);


        uint16_t RGB_color = Red + Green + Blue;
        ILI9341_Draw_Rectangle(i, 0, 1, 240, RGB_color);

    }
    HAL_Delay(2000);
}

/**
 * ALIGNMENT TEST
 */
void demoAlignment() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Rectangle alignment check", 10, 10, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    ILI9341_Draw_Hollow_Rectangle_Coord(50, 50, 100, 100, BLACK);
    ILI9341_Draw_Filled_Rectangle_Coord(20, 20, 50, 50, BLACK);
    ILI9341_Draw_Hollow_Rectangle_Coord(10, 10, 19, 19, BLACK);
    HAL_Delay(1000);
}

/**
 * COUNTING SINGLE SEGMENT
 */
void demoSingleSegment() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Counting single segment", 10, 10, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    for (uint16_t i = 0; i <= 100; i++) {
        sprintf(Temp_Buffer_text, "Counting: %d", i);
        ILI9341_Draw_Text(Temp_Buffer_text, 10, 10, BLACK, 3, WHITE);
    }

    HAL_Delay(1000);
}

/**
 * FILLED CIRCLES EXAMPLE
 */
void demoFilledCircles() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("Filled Circles", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    for (uint32_t i = 0; i < 1000; i++) {
        uint32_t random_num = 0;
        uint16_t xr = 0;
        uint16_t yr = 0;
        uint16_t radiusr = 0;
        uint16_t colourr = 0;
        random_num = random();
        xr = random_num;
        random_num = random();
        yr = random_num;
        random_num = random();
        radiusr = random_num;
        random_num = random();
        colourr = random_num;

        xr &= 0x01FFu;
        yr &= 0x01FFu;
        radiusr &= 0x001Fu;
        //ili9341_drawpixel(xr, yr, WHITE);
        ILI9341_Draw_Filled_Circle(xr, yr, radiusr / 2, colourr);
    }
    HAL_Delay(1000);
}

/**
 * FILLED RECTANGLES EXAMPLE
 */
void demoFilledRectangles() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("Filled Rectangles", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    for (uint32_t i = 0; i < 20000; i++) {
        uint32_t random_num = 0;
        uint16_t xr = 0;
        uint16_t yr = 0;
        uint16_t radiusr = 0;
        uint16_t colourr = 0;
        random_num = random();
        xr = random_num;
        random_num = random();
        yr = random_num;
        random_num = random();
        radiusr = random_num;
        random_num = random();
        colourr = random_num;

        xr &= 0x01FFu;
        yr &= 0x01FFu;
        radiusr &= 0x001Fu;
        //ili9341_drawpixel(xr, yr, WHITE);
        ILI9341_Draw_Rectangle(xr, yr, radiusr, radiusr, colourr);
    }
    HAL_Delay(1000);
}

/**
 * HOLLOW RECTANGLES EXAMPLE
 */
void demoHollowRectangles() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("Rectangles", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);

    for (uint32_t i = 0; i < 20000; i++) {
        uint32_t random_num = 0;
        uint16_t xr = 0;
        uint16_t yr = 0;
        uint16_t radiusr = 0;
        uint16_t colourr = 0;
        random_num = random();
        xr = random_num;
        random_num = random();
        yr = random_num;
        random_num = random();
        radiusr = random_num;
        random_num = random();
        colourr = random_num;

        xr &= 0x01FFu;
        yr &= 0x01FFu;
        radiusr &= 0x001Fu;
        //ili9341_drawpixel(xr, yr, WHITE);
        ILI9341_Draw_Hollow_Rectangle_Coord(xr, yr, xr + radiusr, yr + radiusr, colourr);
    }
    HAL_Delay(1000);
}

/**
 * HOLLOW CIRCLES EXAMPLE
 */
void demoHollowCircles() {
    ILI9341_Fill_Screen(WHITE);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
    ILI9341_Draw_Text("Randomly placed and sized", 10, 10, BLACK, 1, WHITE);
    ILI9341_Draw_Text("Circles", 10, 20, BLACK, 1, WHITE);
    HAL_Delay(2000);
    ILI9341_Fill_Screen(WHITE);


    for (uint32_t i = 0; i < 3000; i++) {
        uint32_t random_num = 0;
        uint16_t xr = 0;
        uint16_t yr = 0;
        uint16_t radiusr = 0;
        uint16_t colourr = 0;
        random_num = random();
        xr = random_num;
        random_num = random();
        yr = random_num;
        random_num = random();
        radiusr = random_num;
        random_num = random();
        colourr = random_num;

        xr &= 0x01FFu;
        yr &= 0x01FFu;
        radiusr &= 0x001Fu;
        //ili9341_drawpixel(xr, yr, WHITE);
        ILI9341_Draw_Hollow_Circle(xr, yr, radiusr * 2, colourr);
    }
    HAL_Delay(1000);
}


void demoAll() {
    perfTest();
    demoMultipleSegments();
    demoSingleSegment();
    demoAlignment();
    demoLines();
    demoHollowCircles();
    demoFilledCircles();
    demoHollowRectangles();
    demoFilledRectangles();
    demoIndividualPixel();
    demoPixels();
    demoGrayscale();
    demoImage();
}


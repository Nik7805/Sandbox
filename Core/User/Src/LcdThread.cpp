#include "LcdThread.hpp"

extern "C"{
#include "FreeRTOS.h"
#include "task.h"
#include "lcd.h"
}
#include "/home/nik/Hobby/STM32H7/Sandbox/lvgl/lvgl.h"

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGH 80

#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /* will be 2 for RGB565 */
#define BUFF_SIZE (DISPLAY_WIDTH * 10 * BYTES_PER_PIXEL)
static uint8_t buf_1[BUFF_SIZE];
static uint8_t buf_2[BUFF_SIZE];

void LcdThread(void *params)
{
    lv_init();
    lv_display_t *display = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGH); /* Create the display */
    while(1)
    {

    }
    // char text[20];
    // LCD_Test();
    // while(1)
    // {
    //     TickType_t ticks = xTaskGetTickCount();
    //     sprintf(text, "Time:%04d", ticks / 1000);
	//     LCD_ShowString(4, 58, ST7735Ctx.Width, 16, 16, (uint8_t*)text);
    //     vTaskDelay(1000);
    // }

    vTaskDelete(NULL);
}
#include "LcdThread.hpp"

extern "C"{
#include "FreeRTOS.h"
#include "task.h"
#include "lcd.h"
}

void LcdThread(void *params)
{
    char text[20];
    LCD_Test();
    while(1)
    {
        TickType_t ticks = xTaskGetTickCount();
        sprintf(text, "Time:%04d", ticks / 1000);
	    LCD_ShowString(4, 58, ST7735Ctx.Width, 16, 16, (uint8_t*)text);
        vTaskDelay(1000);
    }

    vTaskDelete(NULL);
}
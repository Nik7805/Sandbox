#include "InitTasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Blink.hpp"
#include "LcdThread.hpp"


TaskHandle_t blink_handle;
TaskHandle_t lcd_handle;

void InitTasks()
{
    xTaskCreate(Blink, "BlinkTsk", 4096, NULL, 1, &blink_handle);
    xTaskCreate(LcdThread, "Lcd", 512, NULL, 1, &lcd_handle);
}
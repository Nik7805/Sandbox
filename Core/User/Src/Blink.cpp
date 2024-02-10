#include "Blink.hpp"

extern "C" {
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32h7xx_hal_gpio.h"
}

void Blink(void *params)
{
    while(1)
    {
        HAL_GPIO_WritePin(E3_GPIO_Port, E3_Pin, GPIO_PIN_SET);
        vTaskDelay(50);

        HAL_GPIO_WritePin(E3_GPIO_Port, E3_Pin, GPIO_PIN_RESET);
        vTaskDelay(950);
    }
}
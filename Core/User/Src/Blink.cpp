#include "Blink.hpp"

extern "C" {
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32h7xx_hal_gpio.h"
#include "w25qxx_qspi.h"
#include "string.h"
}

void Blink(void *params)
{
    w25qxx_Init();
    uint8_t buffer[30];
    const char* msg = "This is tread write process!";
    W25qxx_EraseSector(0);
    W25qxx_Write_RTOS((uint8_t*)msg, 0, strlen(msg));
    W25qxx_Read_RTOS(buffer, 0, 30);

    while(1)
    {
        HAL_GPIO_WritePin(E3_GPIO_Port, E3_Pin, GPIO_PIN_SET);
        vTaskDelay(50);

        HAL_GPIO_WritePin(E3_GPIO_Port, E3_Pin, GPIO_PIN_RESET);
        vTaskDelay(950);
    }
}
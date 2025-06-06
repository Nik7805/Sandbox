#include "Blink.hpp"

extern "C" {
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32h7xx_hal_gpio.h"
#include "w25qxx_qspi.h"
#include "string.h"
}
#include "fatfs.h"

#define WORK_BUF_SIZE 4096
static uint8_t work_buffer[WORK_BUF_SIZE];

void Blink(void *params)
{

    MX_FATFS_Init();
    FATFS fs;
    volatile FRESULT res;
    res = f_mount(&fs, "0:/", 1);
    if(res != FR_OK)
    {
        res = f_mkfs("0:/", FM_FAT, 0, work_buffer, WORK_BUF_SIZE);
        if(res != FR_OK)
        {
            __NOP();
        }

        res = f_mount(&fs, "0:/", 1);
        if(res != FR_OK)
        {
            __NOP();
        }
    }


    uint32_t freeClust;
    FATFS* fs_ptr = &fs;
    // Warning! This fills fs.n_fatent and fs.csize!
    res = f_getfree("0:/", &freeClust, &fs_ptr);
    if(res != FR_OK) 
    {
        __NOP();
    }

    uint32_t totalBlocks = (fs.n_fatent - 2) * fs.csize;
    uint32_t freeBlocks = freeClust * fs.csize;

    __NOP();

    // DIR dir;
    // res = f_opendir(&dir, "0:/");
    // if(res != FR_OK) 
    // {
    //     __NOP();
    // }

    FIL logFile;
    int i = 5;
    UINT writen = 0;
    res = f_open(&logFile, "cfg.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
    if(res != FR_OK) {
        __NOP();
        f_open(&logFile, "cfg.txt", FA_CREATE_NEW | FA_WRITE);
    }
    else
    {
        f_read(&logFile, &i, sizeof(i), &writen);
    }
    ++i;
    res = f_lseek(&logFile, 0);
    res = f_write(&logFile, &i, sizeof(i), &writen);
    res = f_close(&logFile);

    res = f_mount(NULL, "", 0);

    while(1)
    {
        HAL_GPIO_WritePin(E3_GPIO_Port, E3_Pin, GPIO_PIN_SET);
        vTaskDelay(50);

        HAL_GPIO_WritePin(E3_GPIO_Port, E3_Pin, GPIO_PIN_RESET);
        vTaskDelay(950);
    }
}
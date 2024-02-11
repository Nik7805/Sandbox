cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(TOOLCHAIN_PATH /usr/bin)
set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_AR ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}ar)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}objdump)
set(SIZE ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
 
# Add you project name
project(Sandbox C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
 
# Add carnel name
set(MCPU cortex-m7)
 
# Uncomment for hardware floating point
# add_compile_definitions(ARM_MATH_CM7;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv5-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv5-d16)
 
# Uncomment for software floating point
# add_compile_options(-mfloat-abi=soft)
 
add_compile_options(-mcpu=${MCPU} -mthumb)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
 
# Uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
 
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()
 
# Add Include directories
include_directories(
        ${CMAKE_SOURCE_DIR}/Core/Inc 
        ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc 
        ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy 
        ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include 
        ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 
        ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F 
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include 
        ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
        ${CMAKE_SOURCE_DIR}/Core/User/Inc
        ${CMAKE_SOURCE_DIR}/Drivers/BSP/ST7735
        ${CMAKE_SOURCE_DIR}/STM32-W25Q-QSPI/Library
        ${CMAKE_SOURCE_DIR}/Drivers/BSP/W25QXX
        )
 
# Add C defines
add_definitions(-DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96)
 
# Add you source file
set(SOURCES
#Drivers and RTOS
Core/Src/main.c 
Core/Src/gpio.c 
Core/Src/freertos.c 
Core/Src/quadspi.c 
Core/Src/rtc.c 
Core/Src/spi.c 
Core/Src/tim.c 
Core/Src/stm32h7xx_it.c 
Core/Src/stm32h7xx_hal_msp.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c 
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c 
Core/Src/system_stm32h7xx.c 
Middlewares/Third_Party/FreeRTOS/Source/croutine.c 
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c 
Middlewares/Third_Party/FreeRTOS/Source/list.c 
Middlewares/Third_Party/FreeRTOS/Source/queue.c 
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c 
Middlewares/Third_Party/FreeRTOS/Source/tasks.c 
Middlewares/Third_Party/FreeRTOS/Source/timers.c 
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c 
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c  
startup_stm32h743xx.s
#BSP
Drivers/BSP/ST7735/lcd.c
Drivers/BSP/ST7735/logo_128_160.c
Drivers/BSP/ST7735/logo_160_80.c
Drivers/BSP/ST7735/st7735_reg.c
Drivers/BSP/ST7735/st7735.c
Drivers/BSP/W25QXX/w25qxx_qspi.c
Drivers/BSP/W25QXX/w25qxx.c
#Libs
STM32-W25Q-QSPI/Library/w25q_mem.c
#User sources
Core/User/Src/InitTasks.cpp
Core/User/Src/Blink.cpp
Core/User/Src/LcdThread.cpp
)
 
# Add lincer file
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32H743VITx_FLASH.ld)
 
# this options for C++
add_link_options(-specs=nosys.specs -lstdc++)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=${MCPU} -mthumb)
add_link_options(-T ${LINKER_SCRIPT})
 
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
 
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
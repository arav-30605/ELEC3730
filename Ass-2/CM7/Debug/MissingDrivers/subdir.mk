################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MissingDrivers/stm32h7xx_hal_dma2d.c \
../MissingDrivers/stm32h7xx_hal_dsi.c \
../MissingDrivers/stm32h7xx_hal_ltdc.c \
../MissingDrivers/stm32h7xx_hal_ltdc_ex.c \
../MissingDrivers/stm32h7xx_hal_sdram.c \
../MissingDrivers/stm32h7xx_hal_uart.c \
../MissingDrivers/stm32h7xx_hal_uart_ex.c \
../MissingDrivers/stm32h7xx_ll_fmc.c 

OBJS += \
./MissingDrivers/stm32h7xx_hal_dma2d.o \
./MissingDrivers/stm32h7xx_hal_dsi.o \
./MissingDrivers/stm32h7xx_hal_ltdc.o \
./MissingDrivers/stm32h7xx_hal_ltdc_ex.o \
./MissingDrivers/stm32h7xx_hal_sdram.o \
./MissingDrivers/stm32h7xx_hal_uart.o \
./MissingDrivers/stm32h7xx_hal_uart_ex.o \
./MissingDrivers/stm32h7xx_ll_fmc.o 

C_DEPS += \
./MissingDrivers/stm32h7xx_hal_dma2d.d \
./MissingDrivers/stm32h7xx_hal_dsi.d \
./MissingDrivers/stm32h7xx_hal_ltdc.d \
./MissingDrivers/stm32h7xx_hal_ltdc_ex.d \
./MissingDrivers/stm32h7xx_hal_sdram.d \
./MissingDrivers/stm32h7xx_hal_uart.d \
./MissingDrivers/stm32h7xx_hal_uart_ex.d \
./MissingDrivers/stm32h7xx_ll_fmc.d 


# Each subdirectory must supply rules for building sources it contributes
MissingDrivers/%.o MissingDrivers/%.su MissingDrivers/%.cyclo: ../MissingDrivers/%.c MissingDrivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"../../CM7/MissingDrivers" -I"../../CM7/MissingDrivers/lcd" -I"../../CM7/MissingDrivers/BSP/Components/Common" -I../../CM7/MissingDrivers/BSP/STM32H747I-DISCO -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MissingDrivers

clean-MissingDrivers:
	-$(RM) ./MissingDrivers/stm32h7xx_hal_dma2d.cyclo ./MissingDrivers/stm32h7xx_hal_dma2d.d ./MissingDrivers/stm32h7xx_hal_dma2d.o ./MissingDrivers/stm32h7xx_hal_dma2d.su ./MissingDrivers/stm32h7xx_hal_dsi.cyclo ./MissingDrivers/stm32h7xx_hal_dsi.d ./MissingDrivers/stm32h7xx_hal_dsi.o ./MissingDrivers/stm32h7xx_hal_dsi.su ./MissingDrivers/stm32h7xx_hal_ltdc.cyclo ./MissingDrivers/stm32h7xx_hal_ltdc.d ./MissingDrivers/stm32h7xx_hal_ltdc.o ./MissingDrivers/stm32h7xx_hal_ltdc.su ./MissingDrivers/stm32h7xx_hal_ltdc_ex.cyclo ./MissingDrivers/stm32h7xx_hal_ltdc_ex.d ./MissingDrivers/stm32h7xx_hal_ltdc_ex.o ./MissingDrivers/stm32h7xx_hal_ltdc_ex.su ./MissingDrivers/stm32h7xx_hal_sdram.cyclo ./MissingDrivers/stm32h7xx_hal_sdram.d ./MissingDrivers/stm32h7xx_hal_sdram.o ./MissingDrivers/stm32h7xx_hal_sdram.su ./MissingDrivers/stm32h7xx_hal_uart.cyclo ./MissingDrivers/stm32h7xx_hal_uart.d ./MissingDrivers/stm32h7xx_hal_uart.o ./MissingDrivers/stm32h7xx_hal_uart.su ./MissingDrivers/stm32h7xx_hal_uart_ex.cyclo ./MissingDrivers/stm32h7xx_hal_uart_ex.d ./MissingDrivers/stm32h7xx_hal_uart_ex.o ./MissingDrivers/stm32h7xx_hal_uart_ex.su ./MissingDrivers/stm32h7xx_ll_fmc.cyclo ./MissingDrivers/stm32h7xx_ll_fmc.d ./MissingDrivers/stm32h7xx_ll_fmc.o ./MissingDrivers/stm32h7xx_ll_fmc.su

.PHONY: clean-MissingDrivers


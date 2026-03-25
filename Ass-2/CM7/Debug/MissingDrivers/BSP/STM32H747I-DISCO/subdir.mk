################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.c \
../MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.c \
../MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.c \
../MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.c \
../MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.c 

OBJS += \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.o \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.o \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.o \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.o \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.o 

C_DEPS += \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.d \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.d \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.d \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.d \
./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
MissingDrivers/BSP/STM32H747I-DISCO/%.o MissingDrivers/BSP/STM32H747I-DISCO/%.su MissingDrivers/BSP/STM32H747I-DISCO/%.cyclo: ../MissingDrivers/BSP/STM32H747I-DISCO/%.c MissingDrivers/BSP/STM32H747I-DISCO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"../../CM7/MissingDrivers" -I"../../CM7/MissingDrivers/lcd" -I"../../CM7/MissingDrivers/BSP/Components/Common" -I../../CM7/MissingDrivers/BSP/STM32H747I-DISCO -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MissingDrivers-2f-BSP-2f-STM32H747I-2d-DISCO

clean-MissingDrivers-2f-BSP-2f-STM32H747I-2d-DISCO:
	-$(RM) ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.cyclo ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.d ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.o ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.su ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.cyclo ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.d ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.o ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.su ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.cyclo ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.d ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.o ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.su ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.cyclo ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.d ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.o ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.su ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.cyclo ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.d ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.o ./MissingDrivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.su

.PHONY: clean-MissingDrivers-2f-BSP-2f-STM32H747I-2d-DISCO


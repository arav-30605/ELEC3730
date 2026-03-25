################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MissingDrivers/Fonts/font12.c \
../MissingDrivers/Fonts/font16.c \
../MissingDrivers/Fonts/font20.c \
../MissingDrivers/Fonts/font24.c \
../MissingDrivers/Fonts/font8.c 

OBJS += \
./MissingDrivers/Fonts/font12.o \
./MissingDrivers/Fonts/font16.o \
./MissingDrivers/Fonts/font20.o \
./MissingDrivers/Fonts/font24.o \
./MissingDrivers/Fonts/font8.o 

C_DEPS += \
./MissingDrivers/Fonts/font12.d \
./MissingDrivers/Fonts/font16.d \
./MissingDrivers/Fonts/font20.d \
./MissingDrivers/Fonts/font24.d \
./MissingDrivers/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
MissingDrivers/Fonts/%.o MissingDrivers/Fonts/%.su MissingDrivers/Fonts/%.cyclo: ../MissingDrivers/Fonts/%.c MissingDrivers/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"../../CM7/MissingDrivers" -I"../../CM7/MissingDrivers/lcd" -I"../../CM7/MissingDrivers/BSP/Components/Common" -I../../CM7/MissingDrivers/BSP/STM32H747I-DISCO -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MissingDrivers-2f-Fonts

clean-MissingDrivers-2f-Fonts:
	-$(RM) ./MissingDrivers/Fonts/font12.cyclo ./MissingDrivers/Fonts/font12.d ./MissingDrivers/Fonts/font12.o ./MissingDrivers/Fonts/font12.su ./MissingDrivers/Fonts/font16.cyclo ./MissingDrivers/Fonts/font16.d ./MissingDrivers/Fonts/font16.o ./MissingDrivers/Fonts/font16.su ./MissingDrivers/Fonts/font20.cyclo ./MissingDrivers/Fonts/font20.d ./MissingDrivers/Fonts/font20.o ./MissingDrivers/Fonts/font20.su ./MissingDrivers/Fonts/font24.cyclo ./MissingDrivers/Fonts/font24.d ./MissingDrivers/Fonts/font24.o ./MissingDrivers/Fonts/font24.su ./MissingDrivers/Fonts/font8.cyclo ./MissingDrivers/Fonts/font8.d ./MissingDrivers/Fonts/font8.o ./MissingDrivers/Fonts/font8.su

.PHONY: clean-MissingDrivers-2f-Fonts


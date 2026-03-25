################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MissingDrivers/BSP/Components/ft6x06/ft6x06.c \
../MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.c 

OBJS += \
./MissingDrivers/BSP/Components/ft6x06/ft6x06.o \
./MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.o 

C_DEPS += \
./MissingDrivers/BSP/Components/ft6x06/ft6x06.d \
./MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.d 


# Each subdirectory must supply rules for building sources it contributes
MissingDrivers/BSP/Components/ft6x06/%.o MissingDrivers/BSP/Components/ft6x06/%.su MissingDrivers/BSP/Components/ft6x06/%.cyclo: ../MissingDrivers/BSP/Components/ft6x06/%.c MissingDrivers/BSP/Components/ft6x06/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"../../CM7/MissingDrivers" -I"../../CM7/MissingDrivers/lcd" -I"../../CM7/MissingDrivers/BSP/Components/Common" -I../../CM7/MissingDrivers/BSP/STM32H747I-DISCO -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MissingDrivers-2f-BSP-2f-Components-2f-ft6x06

clean-MissingDrivers-2f-BSP-2f-Components-2f-ft6x06:
	-$(RM) ./MissingDrivers/BSP/Components/ft6x06/ft6x06.cyclo ./MissingDrivers/BSP/Components/ft6x06/ft6x06.d ./MissingDrivers/BSP/Components/ft6x06/ft6x06.o ./MissingDrivers/BSP/Components/ft6x06/ft6x06.su ./MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.cyclo ./MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.d ./MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.o ./MissingDrivers/BSP/Components/ft6x06/ft6x06_reg.su

.PHONY: clean-MissingDrivers-2f-BSP-2f-Components-2f-ft6x06


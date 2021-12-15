################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L1X/platform/src/vl53l1_platform.c \
../Drivers/VL53L1X/platform/src/vl53l1_platform_log.c 

OBJS += \
./Drivers/VL53L1X/platform/src/vl53l1_platform.o \
./Drivers/VL53L1X/platform/src/vl53l1_platform_log.o 

C_DEPS += \
./Drivers/VL53L1X/platform/src/vl53l1_platform.d \
./Drivers/VL53L1X/platform/src/vl53l1_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L1X/platform/src/%.o: ../Drivers/VL53L1X/platform/src/%.c Drivers/VL53L1X/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


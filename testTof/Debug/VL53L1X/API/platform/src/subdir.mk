################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VL53L1X/API/platform/src/vl53l1_platform.c \
../VL53L1X/API/platform/src/vl53l1_platform_log.c 

OBJS += \
./VL53L1X/API/platform/src/vl53l1_platform.o \
./VL53L1X/API/platform/src/vl53l1_platform_log.o 

C_DEPS += \
./VL53L1X/API/platform/src/vl53l1_platform.d \
./VL53L1X/API/platform/src/vl53l1_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
VL53L1X/API/platform/src/%.o: ../VL53L1X/API/platform/src/%.c VL53L1X/API/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/STM32CubeIDE/workspace_1.5.1/testTof/VL53L1X/API/platform/inc" -I"C:/Users/user/STM32CubeIDE/workspace_1.5.1/testTof/VL53L1X/API/platform/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


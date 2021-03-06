################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L1X/core/src/vl53l1_api.c \
../Drivers/VL53L1X/core/src/vl53l1_api_calibration.c \
../Drivers/VL53L1X/core/src/vl53l1_api_core.c \
../Drivers/VL53L1X/core/src/vl53l1_api_debug.c \
../Drivers/VL53L1X/core/src/vl53l1_api_preset_modes.c \
../Drivers/VL53L1X/core/src/vl53l1_api_strings.c \
../Drivers/VL53L1X/core/src/vl53l1_core.c \
../Drivers/VL53L1X/core/src/vl53l1_core_support.c \
../Drivers/VL53L1X/core/src/vl53l1_error_strings.c \
../Drivers/VL53L1X/core/src/vl53l1_register_funcs.c \
../Drivers/VL53L1X/core/src/vl53l1_silicon_core.c \
../Drivers/VL53L1X/core/src/vl53l1_wait.c 

OBJS += \
./Drivers/VL53L1X/core/src/vl53l1_api.o \
./Drivers/VL53L1X/core/src/vl53l1_api_calibration.o \
./Drivers/VL53L1X/core/src/vl53l1_api_core.o \
./Drivers/VL53L1X/core/src/vl53l1_api_debug.o \
./Drivers/VL53L1X/core/src/vl53l1_api_preset_modes.o \
./Drivers/VL53L1X/core/src/vl53l1_api_strings.o \
./Drivers/VL53L1X/core/src/vl53l1_core.o \
./Drivers/VL53L1X/core/src/vl53l1_core_support.o \
./Drivers/VL53L1X/core/src/vl53l1_error_strings.o \
./Drivers/VL53L1X/core/src/vl53l1_register_funcs.o \
./Drivers/VL53L1X/core/src/vl53l1_silicon_core.o \
./Drivers/VL53L1X/core/src/vl53l1_wait.o 

C_DEPS += \
./Drivers/VL53L1X/core/src/vl53l1_api.d \
./Drivers/VL53L1X/core/src/vl53l1_api_calibration.d \
./Drivers/VL53L1X/core/src/vl53l1_api_core.d \
./Drivers/VL53L1X/core/src/vl53l1_api_debug.d \
./Drivers/VL53L1X/core/src/vl53l1_api_preset_modes.d \
./Drivers/VL53L1X/core/src/vl53l1_api_strings.d \
./Drivers/VL53L1X/core/src/vl53l1_core.d \
./Drivers/VL53L1X/core/src/vl53l1_core_support.d \
./Drivers/VL53L1X/core/src/vl53l1_error_strings.d \
./Drivers/VL53L1X/core/src/vl53l1_register_funcs.d \
./Drivers/VL53L1X/core/src/vl53l1_silicon_core.d \
./Drivers/VL53L1X/core/src/vl53l1_wait.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L1X/core/src/%.o: ../Drivers/VL53L1X/core/src/%.c Drivers/VL53L1X/core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


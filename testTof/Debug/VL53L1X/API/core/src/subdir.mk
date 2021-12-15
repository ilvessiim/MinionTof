################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../VL53L1X/API/core/src/vl53l1_api.c \
../VL53L1X/API/core/src/vl53l1_api_calibration.c \
../VL53L1X/API/core/src/vl53l1_api_core.c \
../VL53L1X/API/core/src/vl53l1_api_debug.c \
../VL53L1X/API/core/src/vl53l1_api_preset_modes.c \
../VL53L1X/API/core/src/vl53l1_api_strings.c \
../VL53L1X/API/core/src/vl53l1_core.c \
../VL53L1X/API/core/src/vl53l1_core_support.c \
../VL53L1X/API/core/src/vl53l1_error_strings.c \
../VL53L1X/API/core/src/vl53l1_register_funcs.c \
../VL53L1X/API/core/src/vl53l1_silicon_core.c \
../VL53L1X/API/core/src/vl53l1_wait.c 

OBJS += \
./VL53L1X/API/core/src/vl53l1_api.o \
./VL53L1X/API/core/src/vl53l1_api_calibration.o \
./VL53L1X/API/core/src/vl53l1_api_core.o \
./VL53L1X/API/core/src/vl53l1_api_debug.o \
./VL53L1X/API/core/src/vl53l1_api_preset_modes.o \
./VL53L1X/API/core/src/vl53l1_api_strings.o \
./VL53L1X/API/core/src/vl53l1_core.o \
./VL53L1X/API/core/src/vl53l1_core_support.o \
./VL53L1X/API/core/src/vl53l1_error_strings.o \
./VL53L1X/API/core/src/vl53l1_register_funcs.o \
./VL53L1X/API/core/src/vl53l1_silicon_core.o \
./VL53L1X/API/core/src/vl53l1_wait.o 

C_DEPS += \
./VL53L1X/API/core/src/vl53l1_api.d \
./VL53L1X/API/core/src/vl53l1_api_calibration.d \
./VL53L1X/API/core/src/vl53l1_api_core.d \
./VL53L1X/API/core/src/vl53l1_api_debug.d \
./VL53L1X/API/core/src/vl53l1_api_preset_modes.d \
./VL53L1X/API/core/src/vl53l1_api_strings.d \
./VL53L1X/API/core/src/vl53l1_core.d \
./VL53L1X/API/core/src/vl53l1_core_support.d \
./VL53L1X/API/core/src/vl53l1_error_strings.d \
./VL53L1X/API/core/src/vl53l1_register_funcs.d \
./VL53L1X/API/core/src/vl53l1_silicon_core.d \
./VL53L1X/API/core/src/vl53l1_wait.d 


# Each subdirectory must supply rules for building sources it contributes
VL53L1X/API/core/src/%.o: ../VL53L1X/API/core/src/%.c VL53L1X/API/core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/STM32CubeIDE/workspace_1.5.1/testTof/VL53L1X/API/platform/inc" -I"C:/Users/user/STM32CubeIDE/workspace_1.5.1/testTof/VL53L1X/API/platform/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


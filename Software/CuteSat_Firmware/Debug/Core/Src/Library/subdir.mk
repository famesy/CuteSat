################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Library/AS5047U.c \
../Core/Src/Library/DRV10975.c \
../Core/Src/Library/EDAC.c \
../Core/Src/Library/FRAM.c \
../Core/Src/Library/INA238.c \
../Core/Src/Library/KalmanFilter.c \
../Core/Src/Library/Logging.c \
../Core/Src/Library/Neopixel.c \
../Core/Src/Library/TMP75.c \
../Core/Src/Library/Utils.c 

OBJS += \
./Core/Src/Library/AS5047U.o \
./Core/Src/Library/DRV10975.o \
./Core/Src/Library/EDAC.o \
./Core/Src/Library/FRAM.o \
./Core/Src/Library/INA238.o \
./Core/Src/Library/KalmanFilter.o \
./Core/Src/Library/Logging.o \
./Core/Src/Library/Neopixel.o \
./Core/Src/Library/TMP75.o \
./Core/Src/Library/Utils.o 

C_DEPS += \
./Core/Src/Library/AS5047U.d \
./Core/Src/Library/DRV10975.d \
./Core/Src/Library/EDAC.d \
./Core/Src/Library/FRAM.d \
./Core/Src/Library/INA238.d \
./Core/Src/Library/KalmanFilter.d \
./Core/Src/Library/Logging.d \
./Core/Src/Library/Neopixel.d \
./Core/Src/Library/TMP75.d \
./Core/Src/Library/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Library/%.o Core/Src/Library/%.su: ../Core/Src/Library/%.c Core/Src/Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Library

clean-Core-2f-Src-2f-Library:
	-$(RM) ./Core/Src/Library/AS5047U.d ./Core/Src/Library/AS5047U.o ./Core/Src/Library/AS5047U.su ./Core/Src/Library/DRV10975.d ./Core/Src/Library/DRV10975.o ./Core/Src/Library/DRV10975.su ./Core/Src/Library/EDAC.d ./Core/Src/Library/EDAC.o ./Core/Src/Library/EDAC.su ./Core/Src/Library/FRAM.d ./Core/Src/Library/FRAM.o ./Core/Src/Library/FRAM.su ./Core/Src/Library/INA238.d ./Core/Src/Library/INA238.o ./Core/Src/Library/INA238.su ./Core/Src/Library/KalmanFilter.d ./Core/Src/Library/KalmanFilter.o ./Core/Src/Library/KalmanFilter.su ./Core/Src/Library/Logging.d ./Core/Src/Library/Logging.o ./Core/Src/Library/Logging.su ./Core/Src/Library/Neopixel.d ./Core/Src/Library/Neopixel.o ./Core/Src/Library/Neopixel.su ./Core/Src/Library/TMP75.d ./Core/Src/Library/TMP75.o ./Core/Src/Library/TMP75.su ./Core/Src/Library/Utils.d ./Core/Src/Library/Utils.o ./Core/Src/Library/Utils.su

.PHONY: clean-Core-2f-Src-2f-Library


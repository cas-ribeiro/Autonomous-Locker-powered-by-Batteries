################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ProjectDrivers/Src/led.c \
../ProjectDrivers/Src/lock.c \
../ProjectDrivers/Src/scanner.c \
../ProjectDrivers/Src/security.c \
../ProjectDrivers/Src/utils.c 

OBJS += \
./ProjectDrivers/Src/led.o \
./ProjectDrivers/Src/lock.o \
./ProjectDrivers/Src/scanner.o \
./ProjectDrivers/Src/security.o \
./ProjectDrivers/Src/utils.o 

C_DEPS += \
./ProjectDrivers/Src/led.d \
./ProjectDrivers/Src/lock.d \
./ProjectDrivers/Src/scanner.d \
./ProjectDrivers/Src/security.d \
./ProjectDrivers/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
ProjectDrivers/Src/%.o ProjectDrivers/Src/%.su ProjectDrivers/Src/%.cyclo: ../ProjectDrivers/Src/%.c ProjectDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../ProjectDrivers/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ProjectDrivers-2f-Src

clean-ProjectDrivers-2f-Src:
	-$(RM) ./ProjectDrivers/Src/led.cyclo ./ProjectDrivers/Src/led.d ./ProjectDrivers/Src/led.o ./ProjectDrivers/Src/led.su ./ProjectDrivers/Src/lock.cyclo ./ProjectDrivers/Src/lock.d ./ProjectDrivers/Src/lock.o ./ProjectDrivers/Src/lock.su ./ProjectDrivers/Src/scanner.cyclo ./ProjectDrivers/Src/scanner.d ./ProjectDrivers/Src/scanner.o ./ProjectDrivers/Src/scanner.su ./ProjectDrivers/Src/security.cyclo ./ProjectDrivers/Src/security.d ./ProjectDrivers/Src/security.o ./ProjectDrivers/Src/security.su ./ProjectDrivers/Src/utils.cyclo ./ProjectDrivers/Src/utils.d ./ProjectDrivers/Src/utils.o ./ProjectDrivers/Src/utils.su

.PHONY: clean-ProjectDrivers-2f-Src


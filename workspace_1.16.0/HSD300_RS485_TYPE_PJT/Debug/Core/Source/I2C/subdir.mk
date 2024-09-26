################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/I2C/I2C.c 

OBJS += \
./Core/Source/I2C/I2C.o 

C_DEPS += \
./Core/Source/I2C/I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/I2C/%.o Core/Source/I2C/%.su Core/Source/I2C/%.cyclo: ../Core/Source/I2C/%.c Core/Source/I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32Workspace_1.14.0/HSD300_RS485_TYPE_TEST/HSD300_RS485_TYPE_PJT/Core/Source/I2C/VL53L3CX/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-I2C

clean-Core-2f-Source-2f-I2C:
	-$(RM) ./Core/Source/I2C/I2C.cyclo ./Core/Source/I2C/I2C.d ./Core/Source/I2C/I2C.o ./Core/Source/I2C/I2C.su

.PHONY: clean-Core-2f-Source-2f-I2C


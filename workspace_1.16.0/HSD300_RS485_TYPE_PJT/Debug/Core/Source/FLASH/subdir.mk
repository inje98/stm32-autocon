################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/FLASH/FLASH.c 

OBJS += \
./Core/Source/FLASH/FLASH.o 

C_DEPS += \
./Core/Source/FLASH/FLASH.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/FLASH/%.o Core/Source/FLASH/%.su Core/Source/FLASH/%.cyclo: ../Core/Source/FLASH/%.c Core/Source/FLASH/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32Workspace_1.14.0/HSD300_RS485_TYPE_TEST/HSD300_RS485_TYPE_PJT/Core/Source/I2C/VL53L3CX/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-FLASH

clean-Core-2f-Source-2f-FLASH:
	-$(RM) ./Core/Source/FLASH/FLASH.cyclo ./Core/Source/FLASH/FLASH.d ./Core/Source/FLASH/FLASH.o ./Core/Source/FLASH/FLASH.su

.PHONY: clean-Core-2f-Source-2f-FLASH


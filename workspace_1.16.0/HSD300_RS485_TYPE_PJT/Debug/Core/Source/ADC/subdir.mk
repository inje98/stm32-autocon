################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/ADC/ADC.c 

OBJS += \
./Core/Source/ADC/ADC.o 

C_DEPS += \
./Core/Source/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/ADC/%.o Core/Source/ADC/%.su Core/Source/ADC/%.cyclo: ../Core/Source/ADC/%.c Core/Source/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/autocon/STM32CubeIDE/Autocon_Code/HSD300_RS485_TYPE_PJT/Core/Source/I2C/VL53L3CX/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-ADC

clean-Core-2f-Source-2f-ADC:
	-$(RM) ./Core/Source/ADC/ADC.cyclo ./Core/Source/ADC/ADC.d ./Core/Source/ADC/ADC.o ./Core/Source/ADC/ADC.su

.PHONY: clean-Core-2f-Source-2f-ADC


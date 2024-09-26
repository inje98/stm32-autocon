################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/SMOKE_SENSOR/Smoke_Sensor.c 

OBJS += \
./Core/Source/SMOKE_SENSOR/Smoke_Sensor.o 

C_DEPS += \
./Core/Source/SMOKE_SENSOR/Smoke_Sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/SMOKE_SENSOR/%.o Core/Source/SMOKE_SENSOR/%.su Core/Source/SMOKE_SENSOR/%.cyclo: ../Core/Source/SMOKE_SENSOR/%.c Core/Source/SMOKE_SENSOR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32Workspace_1.14.0/HSD300_RS485_TYPE_TEST/HSD300_RS485_TYPE_PJT/Core/Source/I2C/VL53L3CX/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-SMOKE_SENSOR

clean-Core-2f-Source-2f-SMOKE_SENSOR:
	-$(RM) ./Core/Source/SMOKE_SENSOR/Smoke_Sensor.cyclo ./Core/Source/SMOKE_SENSOR/Smoke_Sensor.d ./Core/Source/SMOKE_SENSOR/Smoke_Sensor.o ./Core/Source/SMOKE_SENSOR/Smoke_Sensor.su

.PHONY: clean-Core-2f-Source-2f-SMOKE_SENSOR


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/TIME_TASK/TIME_TASK.c 

OBJS += \
./Core/Source/TIME_TASK/TIME_TASK.o 

C_DEPS += \
./Core/Source/TIME_TASK/TIME_TASK.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/TIME_TASK/%.o Core/Source/TIME_TASK/%.su Core/Source/TIME_TASK/%.cyclo: ../Core/Source/TIME_TASK/%.c Core/Source/TIME_TASK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/autocon/STM32CubeIDE/Autocon_Code/HSD300_RS485_TYPE_PJT/Core/Source/I2C/VL53L3CX/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-TIME_TASK

clean-Core-2f-Source-2f-TIME_TASK:
	-$(RM) ./Core/Source/TIME_TASK/TIME_TASK.cyclo ./Core/Source/TIME_TASK/TIME_TASK.d ./Core/Source/TIME_TASK/TIME_TASK.o ./Core/Source/TIME_TASK/TIME_TASK.su

.PHONY: clean-Core-2f-Source-2f-TIME_TASK


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TOF/Target/custom.c \
../TOF/Target/custom_ranging_sensor.c 

OBJS += \
./TOF/Target/custom.o \
./TOF/Target/custom_ranging_sensor.o 

C_DEPS += \
./TOF/Target/custom.d \
./TOF/Target/custom_ranging_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
TOF/Target/%.o TOF/Target/%.su TOF/Target/%.cyclo: ../TOF/Target/%.c TOF/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32Workspace_1.14.0/HSD300_RS485_TYPE_TEST/HSD300_RS485_TYPE_PJT/TOF/App" -I../TOF/App -I../TOF/Target -I../Drivers/BSP/Components/vl53l3cx/modules -I../Drivers/BSP/Components/vl53l3cx/porting -I../Drivers/BSP/Components/vl53l3cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TOF-2f-Target

clean-TOF-2f-Target:
	-$(RM) ./TOF/Target/custom.cyclo ./TOF/Target/custom.d ./TOF/Target/custom.o ./TOF/Target/custom.su ./TOF/Target/custom_ranging_sensor.cyclo ./TOF/Target/custom_ranging_sensor.d ./TOF/Target/custom_ranging_sensor.o ./TOF/Target/custom_ranging_sensor.su

.PHONY: clean-TOF-2f-Target


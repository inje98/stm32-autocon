################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/vl53l3cx/vl53l3cx.c 

OBJS += \
./Drivers/BSP/Components/vl53l3cx/vl53l3cx.o 

C_DEPS += \
./Drivers/BSP/Components/vl53l3cx/vl53l3cx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/vl53l3cx/%.o Drivers/BSP/Components/vl53l3cx/%.su Drivers/BSP/Components/vl53l3cx/%.cyclo: ../Drivers/BSP/Components/vl53l3cx/%.c Drivers/BSP/Components/vl53l3cx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32Workspace_1.14.0/HSD300_RS485_TYPE_TEST/HSD300_RS485_TYPE_PJT/TOF/App" -I../TOF/App -I../TOF/Target -I../Drivers/BSP/Components/vl53l3cx/modules -I../Drivers/BSP/Components/vl53l3cx/porting -I../Drivers/BSP/Components/vl53l3cx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx

clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx:
	-$(RM) ./Drivers/BSP/Components/vl53l3cx/vl53l3cx.cyclo ./Drivers/BSP/Components/vl53l3cx/vl53l3cx.d ./Drivers/BSP/Components/vl53l3cx/vl53l3cx.o ./Drivers/BSP/Components/vl53l3cx/vl53l3cx.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-vl53l3cx


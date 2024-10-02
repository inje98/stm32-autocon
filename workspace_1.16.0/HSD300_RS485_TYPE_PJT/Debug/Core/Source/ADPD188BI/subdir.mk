################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/ADPD188BI/ADPD188BI.c 

OBJS += \
./Core/Source/ADPD188BI/ADPD188BI.o 

C_DEPS += \
./Core/Source/ADPD188BI/ADPD188BI.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/ADPD188BI/%.o Core/Source/ADPD188BI/%.su Core/Source/ADPD188BI/%.cyclo: ../Core/Source/ADPD188BI/%.c Core/Source/ADPD188BI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/autocon/STM32CubeIDE/Autocon_Code/HSD300_RS485_TYPE_PJT/Core/Source/I2C/VL53L3CX/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-ADPD188BI

clean-Core-2f-Source-2f-ADPD188BI:
	-$(RM) ./Core/Source/ADPD188BI/ADPD188BI.cyclo ./Core/Source/ADPD188BI/ADPD188BI.d ./Core/Source/ADPD188BI/ADPD188BI.o ./Core/Source/ADPD188BI/ADPD188BI.su

.PHONY: clean-Core-2f-Source-2f-ADPD188BI


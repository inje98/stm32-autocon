################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.c 

OBJS += \
./Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.o 

C_DEPS += \
./Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/NUCLEOVB/hdc1080/%.o Drivers/BSP/NUCLEOVB/hdc1080/%.su Drivers/BSP/NUCLEOVB/hdc1080/%.cyclo: ../Drivers/BSP/NUCLEOVB/hdc1080/%.c Drivers/BSP/NUCLEOVB/hdc1080/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"C:/Users/autocon/STM32CubeIDE/workspace_1.16.0/18_HDC1080/Drivers/BSP/NUCLEOVB" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-NUCLEOVB-2f-hdc1080

clean-Drivers-2f-BSP-2f-NUCLEOVB-2f-hdc1080:
	-$(RM) ./Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.cyclo ./Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.d ./Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.o ./Drivers/BSP/NUCLEOVB/hdc1080/hdc1080.su

.PHONY: clean-Drivers-2f-BSP-2f-NUCLEOVB-2f-hdc1080


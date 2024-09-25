################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/DAC/DAC.c \
../Core/Source/DAC/LTC2666.c \
../Core/Source/DAC/LTC2668.c 

OBJS += \
./Core/Source/DAC/DAC.o \
./Core/Source/DAC/LTC2666.o \
./Core/Source/DAC/LTC2668.o 

C_DEPS += \
./Core/Source/DAC/DAC.d \
./Core/Source/DAC/LTC2666.d \
./Core/Source/DAC/LTC2668.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/DAC/%.o Core/Source/DAC/%.su Core/Source/DAC/%.cyclo: ../Core/Source/DAC/%.c Core/Source/DAC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-DAC

clean-Core-2f-Source-2f-DAC:
	-$(RM) ./Core/Source/DAC/DAC.cyclo ./Core/Source/DAC/DAC.d ./Core/Source/DAC/DAC.o ./Core/Source/DAC/DAC.su ./Core/Source/DAC/LTC2666.cyclo ./Core/Source/DAC/LTC2666.d ./Core/Source/DAC/LTC2666.o ./Core/Source/DAC/LTC2666.su ./Core/Source/DAC/LTC2668.cyclo ./Core/Source/DAC/LTC2668.d ./Core/Source/DAC/LTC2668.o ./Core/Source/DAC/LTC2668.su

.PHONY: clean-Core-2f-Source-2f-DAC


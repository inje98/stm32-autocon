################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/RTC/RTC.c 

OBJS += \
./Core/Source/RTC/RTC.o 

C_DEPS += \
./Core/Source/RTC/RTC.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/RTC/%.o Core/Source/RTC/%.su Core/Source/RTC/%.cyclo: ../Core/Source/RTC/%.c Core/Source/RTC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/BSP/Components/dp83848 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"D:/OneDrive/2.Workspace/STM32_IDE_1.14.0/LEPTON_STM32F746_PJT_V3_5/Core/Source/LEPTON_LIBRARY" -I"D:/OneDrive/2.Workspace/STM32_IDE_1.14.0/LEPTON_STM32F746_PJT_V3_5/Core/Source/LEPTON_LIBRARY/Src" -I"D:/OneDrive/2.Workspace/STM32_IDE_1.14.0/LEPTON_STM32F746_PJT_V3_5/Core/Source/LEPTON_LIBRARY/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-RTC

clean-Core-2f-Source-2f-RTC:
	-$(RM) ./Core/Source/RTC/RTC.cyclo ./Core/Source/RTC/RTC.d ./Core/Source/RTC/RTC.o ./Core/Source/RTC/RTC.su

.PHONY: clean-Core-2f-Source-2f-RTC


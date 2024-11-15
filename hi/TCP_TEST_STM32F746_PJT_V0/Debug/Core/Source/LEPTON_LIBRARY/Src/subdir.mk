################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.c \
../Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.c \
../Core/Source/LEPTON_LIBRARY/Src/crc16fast.c \
../Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.c 

OBJS += \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.o \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.o \
./Core/Source/LEPTON_LIBRARY/Src/crc16fast.o \
./Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.o 

C_DEPS += \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.d \
./Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.d \
./Core/Source/LEPTON_LIBRARY/Src/crc16fast.d \
./Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/LEPTON_LIBRARY/Src/%.o Core/Source/LEPTON_LIBRARY/Src/%.su Core/Source/LEPTON_LIBRARY/Src/%.cyclo: ../Core/Source/LEPTON_LIBRARY/Src/%.c Core/Source/LEPTON_LIBRARY/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/BSP/Components/dp83848 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"D:/OneDrive/2.Workspace/STM32_IDE_1.14.0/LEPTON_STM32F746_PJT_V3_5/Core/Source/LEPTON_LIBRARY" -I"D:/OneDrive/2.Workspace/STM32_IDE_1.14.0/LEPTON_STM32F746_PJT_V3_5/Core/Source/LEPTON_LIBRARY/Src" -I"D:/OneDrive/2.Workspace/STM32_IDE_1.14.0/LEPTON_STM32F746_PJT_V3_5/Core/Source/LEPTON_LIBRARY/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-LEPTON_LIBRARY-2f-Src

clean-Core-2f-Source-2f-LEPTON_LIBRARY-2f-Src:
	-$(RM) ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_AGC.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Protocol.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_I2C_Service.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_OEM.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_RAD.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SDK.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_SYS.su ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.cyclo ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.d ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.o ./Core/Source/LEPTON_LIBRARY/Src/LEPTON_VID.su ./Core/Source/LEPTON_LIBRARY/Src/crc16fast.cyclo ./Core/Source/LEPTON_LIBRARY/Src/crc16fast.d ./Core/Source/LEPTON_LIBRARY/Src/crc16fast.o ./Core/Source/LEPTON_LIBRARY/Src/crc16fast.su ./Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.cyclo ./Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.d ./Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.o ./Core/Source/LEPTON_LIBRARY/Src/stm32_i2c.su

.PHONY: clean-Core-2f-Source-2f-LEPTON_LIBRARY-2f-Src


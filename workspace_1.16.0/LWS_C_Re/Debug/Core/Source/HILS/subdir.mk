################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Source/HILS/HILS.c \
../Core/Source/HILS/Hils_Ctrl_Block.c \
../Core/Source/HILS/Hils_SequenceCtrl.c \
../Core/Source/HILS/Input_Processor.c \
../Core/Source/HILS/Lws_HilsCtrl.c \
../Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.c \
../Core/Source/HILS/Output_Processor.c 

OBJS += \
./Core/Source/HILS/HILS.o \
./Core/Source/HILS/Hils_Ctrl_Block.o \
./Core/Source/HILS/Hils_SequenceCtrl.o \
./Core/Source/HILS/Input_Processor.o \
./Core/Source/HILS/Lws_HilsCtrl.o \
./Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.o \
./Core/Source/HILS/Output_Processor.o 

C_DEPS += \
./Core/Source/HILS/HILS.d \
./Core/Source/HILS/Hils_Ctrl_Block.d \
./Core/Source/HILS/Hils_SequenceCtrl.d \
./Core/Source/HILS/Input_Processor.d \
./Core/Source/HILS/Lws_HilsCtrl.d \
./Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.d \
./Core/Source/HILS/Output_Processor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Source/HILS/%.o Core/Source/HILS/%.su Core/Source/HILS/%.cyclo: ../Core/Source/HILS/%.c Core/Source/HILS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Source-2f-HILS

clean-Core-2f-Source-2f-HILS:
	-$(RM) ./Core/Source/HILS/HILS.cyclo ./Core/Source/HILS/HILS.d ./Core/Source/HILS/HILS.o ./Core/Source/HILS/HILS.su ./Core/Source/HILS/Hils_Ctrl_Block.cyclo ./Core/Source/HILS/Hils_Ctrl_Block.d ./Core/Source/HILS/Hils_Ctrl_Block.o ./Core/Source/HILS/Hils_Ctrl_Block.su ./Core/Source/HILS/Hils_SequenceCtrl.cyclo ./Core/Source/HILS/Hils_SequenceCtrl.d ./Core/Source/HILS/Hils_SequenceCtrl.o ./Core/Source/HILS/Hils_SequenceCtrl.su ./Core/Source/HILS/Input_Processor.cyclo ./Core/Source/HILS/Input_Processor.d ./Core/Source/HILS/Input_Processor.o ./Core/Source/HILS/Input_Processor.su ./Core/Source/HILS/Lws_HilsCtrl.cyclo ./Core/Source/HILS/Lws_HilsCtrl.d ./Core/Source/HILS/Lws_HilsCtrl.o ./Core/Source/HILS/Lws_HilsCtrl.su ./Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.cyclo ./Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.d ./Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.o ./Core/Source/HILS/Lws_HilsCtrl_240218_v_1_0.su ./Core/Source/HILS/Output_Processor.cyclo ./Core/Source/HILS/Output_Processor.d ./Core/Source/HILS/Output_Processor.o ./Core/Source/HILS/Output_Processor.su

.PHONY: clean-Core-2f-Source-2f-HILS


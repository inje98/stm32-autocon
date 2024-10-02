################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Source/TIME_TASK/subdir.mk
-include Core/Source/SMOKE_SENSOR/subdir.mk
-include Core/Source/RS485/subdir.mk
-include Core/Source/Modbus/subdir.mk
-include Core/Source/I2C/VL53L3CX/Library/subdir.mk
-include Core/Source/I2C/subdir.mk
-include Core/Source/FLASH/subdir.mk
-include Core/Source/EEPROM/subdir.mk
-include Core/Source/DIO/subdir.mk
-include Core/Source/Bootloader/subdir.mk
-include Core/Source/ADPD188BI/subdir.mk
-include Core/Source/ADC/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := HSD300_RS485_TYPE_PJT
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
HSD300_RS485_TYPE_PJT.elf \

MAP_FILES += \
HSD300_RS485_TYPE_PJT.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
HSD300_RS485_TYPE_PJT.list \

OBJCOPY_HEX += \
HSD300_RS485_TYPE_PJT.hex \


# All Target
all: main-build

# Main-build Target
main-build: HSD300_RS485_TYPE_PJT.elf secondary-outputs

# Tool invocations
HSD300_RS485_TYPE_PJT.elf HSD300_RS485_TYPE_PJT.map: $(OBJS) $(USER_OBJS) C:\Users\autocon\STM32CubeIDE\Autocon_Code\HSD300_RS485_TYPE_PJT\STM32G491RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "HSD300_RS485_TYPE_PJT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\autocon\STM32CubeIDE\Autocon_Code\HSD300_RS485_TYPE_PJT\STM32G491RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="HSD300_RS485_TYPE_PJT.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

HSD300_RS485_TYPE_PJT.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "HSD300_RS485_TYPE_PJT.list"
	@echo 'Finished building: $@'
	@echo ' '

HSD300_RS485_TYPE_PJT.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "HSD300_RS485_TYPE_PJT.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) HSD300_RS485_TYPE_PJT.elf HSD300_RS485_TYPE_PJT.hex HSD300_RS485_TYPE_PJT.list HSD300_RS485_TYPE_PJT.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

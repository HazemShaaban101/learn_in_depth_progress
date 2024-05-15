################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Blinking_led_macro_approach.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Blinking_led_macro_approach.list \

OBJCOPY_HEX += \
Blinking_led_macro_approach.hex \

OBJCOPY_BIN += \
Blinking_led_macro_approach.bin \


# All Target
all: Blinking_led_macro_approach.elf secondary-outputs

# Tool invocations
Blinking_led_macro_approach.elf: $(OBJS) $(USER_OBJS) C:\Users\Hazem\Desktop\learn_in_depth\learn_in_depth_progress\Embedded_C\homework1\Blinking_led_macro_approach\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Blinking_led_macro_approach.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Hazem\Desktop\learn_in_depth\learn_in_depth_progress\Embedded_C\homework1\Blinking_led_macro_approach\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Blinking_led_macro_approach.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Blinking_led_macro_approach.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Blinking_led_macro_approach.list"
	@echo 'Finished building: $@'
	@echo ' '

Blinking_led_macro_approach.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Blinking_led_macro_approach.hex"
	@echo 'Finished building: $@'
	@echo ' '

Blinking_led_macro_approach.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Blinking_led_macro_approach.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

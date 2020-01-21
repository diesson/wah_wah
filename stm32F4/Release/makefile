################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/src/stm32f4_discovery/subdir.mk
-include system/src/stm32f4-hal/subdir.mk
-include system/src/newlib/subdir.mk
-include system/src/diag/subdir.mk
-include system/src/cortexm/subdir.mk
-include system/src/cmsis/DSP_Lib/TransformFunctions/subdir.mk
-include system/src/cmsis/DSP_Lib/FilteringFunctions/subdir.mk
-include system/src/cmsis/DSP_Lib/FastMathFunctions/subdir.mk
-include system/src/cmsis/DSP_Lib/ComplexMathFunctions/subdir.mk
-include system/src/cmsis/DSP_Lib/CommonTables/subdir.mk
-include system/src/cmsis/DSP_Lib/BasicMathFunctions/subdir.mk
-include system/src/cmsis/subdir.mk
-include system/src/Components/wm5102/subdir.mk
-include system/src/Components/lis3dsh/subdir.mk
-include system/src/Components/lis302dl/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
projeto_wah_wah2.hex \

SECONDARY_SIZE += \
projeto_wah_wah2.siz \


# All Target
all: projeto_wah_wah2.elf secondary-outputs

# Tool invocations
projeto_wah_wah2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"projeto_wah_wah2.map" --specs=nano.specs -u _printf_float -u _scanf_float -o "projeto_wah_wah2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

projeto_wah_wah2.hex: projeto_wah_wah2.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "projeto_wah_wah2.elf"  "projeto_wah_wah2.hex"
	@echo 'Finished building: $@'
	@echo ' '

projeto_wah_wah2.siz: projeto_wah_wah2.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "projeto_wah_wah2.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) projeto_wah_wah2.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets

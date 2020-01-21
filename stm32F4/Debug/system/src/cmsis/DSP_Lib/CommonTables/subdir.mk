################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/DSP_Lib/CommonTables/arm_common_tables.c 

OBJS += \
./system/src/cmsis/DSP_Lib/CommonTables/arm_common_tables.o 

C_DEPS += \
./system/src/cmsis/DSP_Lib/CommonTables/arm_common_tables.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/DSP_Lib/CommonTables/%.o: ../system/src/cmsis/DSP_Lib/CommonTables/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -D__FPU_PRESENT -DARM_MATH_CM4 -DDEBUG -DOS_USE_SEMIHOSTING -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"../system/src/stm32f4_discovery" -I"../system/src/Components" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



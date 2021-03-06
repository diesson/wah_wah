################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f4_discovery/stm32f4_discovery.c \
../system/src/stm32f4_discovery/stm32f4_discovery_accelerometer.c 

OBJS += \
./system/src/stm32f4_discovery/stm32f4_discovery.o \
./system/src/stm32f4_discovery/stm32f4_discovery_accelerometer.o 

C_DEPS += \
./system/src/stm32f4_discovery/stm32f4_discovery.d \
./system/src/stm32f4_discovery/stm32f4_discovery_accelerometer.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f4_discovery/%.o: ../system/src/stm32f4_discovery/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -D__FPU_PRESENT -DARM_MATH_CM4 -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"../system/src/stm32f4_discovery" -I"../system/src/Components" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



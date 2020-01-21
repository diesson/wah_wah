################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_f32.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_q15.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_q31.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_f32.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_q15.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_q31.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sqrt_q15.c \
../system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_f32.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_q15.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_q31.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_f32.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_q15.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_q31.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sqrt_q15.o \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_f32.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_q15.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_cos_q31.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_f32.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_q15.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sin_q31.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sqrt_q15.d \
./system/src/cmsis/DSP_Lib/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/DSP_Lib/FastMathFunctions/%.o: ../system/src/cmsis/DSP_Lib/FastMathFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -D__FPU_PRESENT -DARM_MATH_CM4 -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"../system/src/stm32f4_discovery" -I"../system/src/Components" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



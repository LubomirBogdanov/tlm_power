################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc8xx.c \
../src/crp.c \
../src/mtb.c \
../src/multi_proc_system.c 

OBJS += \
./src/cr_startup_lpc8xx.o \
./src/crp.o \
./src/mtb.o \
./src/multi_proc_system.o 

C_DEPS += \
./src/cr_startup_lpc8xx.d \
./src/crp.d \
./src/mtb.d \
./src/multi_proc_system.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=256 -D__LPC8XX__ -D__REDLIB__ -I"/home/lbogdanov/git_projects/tlm_power/lpc_chip_8xx/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



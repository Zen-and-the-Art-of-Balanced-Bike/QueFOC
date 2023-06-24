################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Startup/startup_ch32v30x_D8.S 

OBJS += \
./Startup/startup_ch32v30x_D8.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v30x_D8.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32v30x_D8.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Startup/startup_ch32v30x_D8.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


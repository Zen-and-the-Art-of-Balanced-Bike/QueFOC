################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/core_riscv.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../3rdparty/oled.c 

OBJS += \
./3rdparty/oled.o 

C_DEPS += \
./3rdparty/oled.d 


# Each subdirectory must supply rules for building sources it contributes
3rdparty/%.o: ../3rdparty/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


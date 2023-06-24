################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/adc_sensor.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/comm.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/encoder.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/fast_math.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/filter.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/foc.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/motor.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/pid.c \
S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/pwm.c 

OBJS += \
./QueFOC_dev/adc_sensor.o \
./QueFOC_dev/comm.o \
./QueFOC_dev/encoder.o \
./QueFOC_dev/fast_math.o \
./QueFOC_dev/filter.o \
./QueFOC_dev/foc.o \
./QueFOC_dev/motor.o \
./QueFOC_dev/pid.o \
./QueFOC_dev/pwm.o 

C_DEPS += \
./QueFOC_dev/adc_sensor.d \
./QueFOC_dev/comm.d \
./QueFOC_dev/encoder.d \
./QueFOC_dev/fast_math.d \
./QueFOC_dev/filter.d \
./QueFOC_dev/foc.d \
./QueFOC_dev/motor.d \
./QueFOC_dev/pid.d \
./QueFOC_dev/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
QueFOC_dev/adc_sensor.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/adc_sensor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/comm.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/comm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/encoder.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/fast_math.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/fast_math.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/filter.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/filter.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/foc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/foc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/motor.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/motor.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/pid.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/pid.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
QueFOC_dev/pwm.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_dev/pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/adc.c \
../Hardware/delay.c \
../Hardware/dma.c \
../Hardware/gpio.c \
../Hardware/it.c \
../Hardware/nvic.c \
../Hardware/spi.c \
../Hardware/timer.c \
../Hardware/usart.c \
../Hardware/usb.c 

OBJS += \
./Hardware/adc.o \
./Hardware/delay.o \
./Hardware/dma.o \
./Hardware/gpio.o \
./Hardware/it.o \
./Hardware/nvic.o \
./Hardware/spi.o \
./Hardware/timer.o \
./Hardware/usart.o \
./Hardware/usb.o 

C_DEPS += \
./Hardware/adc.d \
./Hardware/delay.d \
./Hardware/dma.d \
./Hardware/gpio.d \
./Hardware/it.d \
./Hardware/nvic.d \
./Hardware/spi.d \
./Hardware/timer.d \
./Hardware/usart.d \
./Hardware/usb.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


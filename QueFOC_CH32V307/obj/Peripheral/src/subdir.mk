################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32v30x_adc.c \
../Peripheral/src/ch32v30x_bkp.c \
../Peripheral/src/ch32v30x_can.c \
../Peripheral/src/ch32v30x_crc.c \
../Peripheral/src/ch32v30x_dac.c \
../Peripheral/src/ch32v30x_dbgmcu.c \
../Peripheral/src/ch32v30x_dma.c \
../Peripheral/src/ch32v30x_dvp.c \
../Peripheral/src/ch32v30x_eth.c \
../Peripheral/src/ch32v30x_exti.c \
../Peripheral/src/ch32v30x_flash.c \
../Peripheral/src/ch32v30x_fsmc.c \
../Peripheral/src/ch32v30x_gpio.c \
../Peripheral/src/ch32v30x_i2c.c \
../Peripheral/src/ch32v30x_iwdg.c \
../Peripheral/src/ch32v30x_misc.c \
../Peripheral/src/ch32v30x_opa.c \
../Peripheral/src/ch32v30x_pwr.c \
../Peripheral/src/ch32v30x_rcc.c \
../Peripheral/src/ch32v30x_rng.c \
../Peripheral/src/ch32v30x_rtc.c \
../Peripheral/src/ch32v30x_sdio.c \
../Peripheral/src/ch32v30x_spi.c \
../Peripheral/src/ch32v30x_tim.c \
../Peripheral/src/ch32v30x_usart.c \
../Peripheral/src/ch32v30x_usbotg_device.c \
../Peripheral/src/ch32v30x_wwdg.c 

OBJS += \
./Peripheral/src/ch32v30x_adc.o \
./Peripheral/src/ch32v30x_bkp.o \
./Peripheral/src/ch32v30x_can.o \
./Peripheral/src/ch32v30x_crc.o \
./Peripheral/src/ch32v30x_dac.o \
./Peripheral/src/ch32v30x_dbgmcu.o \
./Peripheral/src/ch32v30x_dma.o \
./Peripheral/src/ch32v30x_dvp.o \
./Peripheral/src/ch32v30x_eth.o \
./Peripheral/src/ch32v30x_exti.o \
./Peripheral/src/ch32v30x_flash.o \
./Peripheral/src/ch32v30x_fsmc.o \
./Peripheral/src/ch32v30x_gpio.o \
./Peripheral/src/ch32v30x_i2c.o \
./Peripheral/src/ch32v30x_iwdg.o \
./Peripheral/src/ch32v30x_misc.o \
./Peripheral/src/ch32v30x_opa.o \
./Peripheral/src/ch32v30x_pwr.o \
./Peripheral/src/ch32v30x_rcc.o \
./Peripheral/src/ch32v30x_rng.o \
./Peripheral/src/ch32v30x_rtc.o \
./Peripheral/src/ch32v30x_sdio.o \
./Peripheral/src/ch32v30x_spi.o \
./Peripheral/src/ch32v30x_tim.o \
./Peripheral/src/ch32v30x_usart.o \
./Peripheral/src/ch32v30x_usbotg_device.o \
./Peripheral/src/ch32v30x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32v30x_adc.d \
./Peripheral/src/ch32v30x_bkp.d \
./Peripheral/src/ch32v30x_can.d \
./Peripheral/src/ch32v30x_crc.d \
./Peripheral/src/ch32v30x_dac.d \
./Peripheral/src/ch32v30x_dbgmcu.d \
./Peripheral/src/ch32v30x_dma.d \
./Peripheral/src/ch32v30x_dvp.d \
./Peripheral/src/ch32v30x_eth.d \
./Peripheral/src/ch32v30x_exti.d \
./Peripheral/src/ch32v30x_flash.d \
./Peripheral/src/ch32v30x_fsmc.d \
./Peripheral/src/ch32v30x_gpio.d \
./Peripheral/src/ch32v30x_i2c.d \
./Peripheral/src/ch32v30x_iwdg.d \
./Peripheral/src/ch32v30x_misc.d \
./Peripheral/src/ch32v30x_opa.d \
./Peripheral/src/ch32v30x_pwr.d \
./Peripheral/src/ch32v30x_rcc.d \
./Peripheral/src/ch32v30x_rng.d \
./Peripheral/src/ch32v30x_rtc.d \
./Peripheral/src/ch32v30x_sdio.d \
./Peripheral/src/ch32v30x_spi.d \
./Peripheral/src/ch32v30x_tim.d \
./Peripheral/src/ch32v30x_usart.d \
./Peripheral/src/ch32v30x_usbotg_device.d \
./Peripheral/src/ch32v30x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32v30x_adc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_bkp.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_bkp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_can.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_can.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_crc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_crc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_dac.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_dac.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_dbgmcu.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_dbgmcu.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_dma.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_dma.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_dvp.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_eth.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_eth.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_exti.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_flash.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_fsmc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_fsmc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_gpio.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_i2c.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_i2c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_iwdg.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_iwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_misc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_misc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_opa.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_opa.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_pwr.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_pwr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_rcc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_rcc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_rng.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_rng.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_rtc.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_rtc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_sdio.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_sdio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_spi.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_tim.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_tim.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_usart.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_usart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_usbotg_device.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_usbotg_device.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Peripheral/src/ch32v30x_wwdg.o: S:/EE/SmartCar/BLDC/code/QueFOC/QueFOC_CH32V307/Peripheral/src/ch32v30x_wwdg.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\3rdparty" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\User" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_dev" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Core" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Hardware" -I"S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


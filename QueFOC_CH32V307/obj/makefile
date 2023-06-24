################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include QueFOC_dev/subdir.mk
-include Peripheral/src/subdir.mk
-include Hardware/subdir.mk
-include Core/subdir.mk
-include 3rdparty/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
QueFOC.hex \

SECONDARY_LIST += \
QueFOC.lst \

SECONDARY_SIZE += \
QueFOC.siz \


# All Target
all: QueFOC.elf secondary-outputs

# Tool invocations
QueFOC.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -T "S:\EE\SmartCar\BLDC\code\QueFOC\QueFOC_CH32V307\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"QueFOC.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "QueFOC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
QueFOC.hex: QueFOC.elf
	@	riscv-none-embed-objcopy -O ihex "QueFOC.elf"  "QueFOC.hex"
	@	@
QueFOC.lst: QueFOC.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble "QueFOC.elf" > "QueFOC.lst"
	@	@
QueFOC.siz: QueFOC.elf
	@	riscv-none-embed-size --format=berkeley "QueFOC.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) QueFOC.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets

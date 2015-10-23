################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/avr-libc/subdir.mk
-include arduino/core/subdir.mk
-include Libraries/TimerOne/subdir.mk
-include Libraries/FlexiTimer2/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
D:/workspace/base/Release/arduino.ar \

ELF += \
base.elf \

EEP += \
base.eep \

FLASH_IMAGE += \
base.hex \


# All Target
all: base

# Tool invocations
base: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-size" -A "D:/workspace/base/Release/base.elf"
	@echo 'Finished building target: $@'
	@echo ' '

D:/workspace/base/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-ar" rcs "D:/workspace/base/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

base.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega2560 -o "D:/workspace/base/Release/base.elf"   $(LINK_OBJ) $(AR)  "D:/workspace/base/Release/arduino.ar" "-LD:/workspace/base/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

base.eep: $(ELF)
	@echo 'Create eeprom image'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "D:/workspace/base/Release/base.elf" "D:/workspace/base/Release/base.eep"
	@echo 'Finished building: $@'
	@echo ' '

base.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom "D:/workspace/base/Release/base.elf" "D:/workspace/base/Release/base.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) base
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

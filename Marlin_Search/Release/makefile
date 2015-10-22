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
-include Marlin/subdir.mk
-include LiquidCrystal/subdir.mk
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
D:/workspace/Marlin_Search/Release/arduino.ar \

ELF += \
Marlin_Search.elf \

EEP += \
Marlin_Search.eep \

FLASH_IMAGE += \
Marlin_Search.hex \


# All Target
all: Marlin_Search

# Tool invocations
Marlin_Search: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-size" -A "D:/workspace/Marlin_Search/Release/Marlin_Search.elf"
	@echo 'Finished building target: $@'
	@echo ' '

D:/workspace/Marlin_Search/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-ar" rcs "D:/workspace/Marlin_Search/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Marlin_Search.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega2560 -o "D:/workspace/Marlin_Search/Release/Marlin_Search.elf"   $(LINK_OBJ) $(AR)  "D:/workspace/Marlin_Search/Release/arduino.ar" "-LD:/workspace/Marlin_Search/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Marlin_Search.eep: $(ELF)
	@echo 'Create eeprom image'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "D:/workspace/Marlin_Search/Release/Marlin_Search.elf" "D:/workspace/Marlin_Search/Release/Marlin_Search.eep"
	@echo 'Finished building: $@'
	@echo ' '

Marlin_Search.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom "D:/workspace/Marlin_Search/Release/Marlin_Search.elf" "D:/workspace/Marlin_Search/Release/Marlin_Search.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) Marlin_Search
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

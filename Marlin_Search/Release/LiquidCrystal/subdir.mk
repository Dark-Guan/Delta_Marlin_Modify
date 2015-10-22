################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LiquidCrystal/LiquidCrystal.cpp 

CPP_DEPS += \
./LiquidCrystal/LiquidCrystal.cpp.d 

LINK_OBJ += \
./LiquidCrystal/LiquidCrystal.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
LiquidCrystal/LiquidCrystal.cpp.o: D:/workspace/Marlin_Search/LiquidCrystal/LiquidCrystal.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '



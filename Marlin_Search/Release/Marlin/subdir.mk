################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Marlin/BlinkM.cpp \
../Marlin/ConfigurationStore.cpp \
../Marlin/LiquidCrystalRus.cpp \
../Marlin/MarlinSerial.cpp \
../Marlin/Sd2Card.cpp \
../Marlin/SdBaseFile.cpp \
../Marlin/SdFatUtil.cpp \
../Marlin/SdFile.cpp \
../Marlin/SdVolume.cpp \
../Marlin/Servo.cpp \
../Marlin/cardreader.cpp \
../Marlin/digipot_mcp4451.cpp \
../Marlin/motion_control.cpp \
../Marlin/planner.cpp \
../Marlin/qr_solve.cpp \
../Marlin/stepper.cpp \
../Marlin/temperature.cpp \
../Marlin/ultralcd.cpp \
../Marlin/vector_3.cpp \
../Marlin/watchdog.cpp 

CPP_DEPS += \
./Marlin/BlinkM.cpp.d \
./Marlin/ConfigurationStore.cpp.d \
./Marlin/LiquidCrystalRus.cpp.d \
./Marlin/MarlinSerial.cpp.d \
./Marlin/Sd2Card.cpp.d \
./Marlin/SdBaseFile.cpp.d \
./Marlin/SdFatUtil.cpp.d \
./Marlin/SdFile.cpp.d \
./Marlin/SdVolume.cpp.d \
./Marlin/Servo.cpp.d \
./Marlin/cardreader.cpp.d \
./Marlin/digipot_mcp4451.cpp.d \
./Marlin/motion_control.cpp.d \
./Marlin/planner.cpp.d \
./Marlin/qr_solve.cpp.d \
./Marlin/stepper.cpp.d \
./Marlin/temperature.cpp.d \
./Marlin/ultralcd.cpp.d \
./Marlin/vector_3.cpp.d \
./Marlin/watchdog.cpp.d 

LINK_OBJ += \
./Marlin/BlinkM.cpp.o \
./Marlin/ConfigurationStore.cpp.o \
./Marlin/LiquidCrystalRus.cpp.o \
./Marlin/MarlinSerial.cpp.o \
./Marlin/Sd2Card.cpp.o \
./Marlin/SdBaseFile.cpp.o \
./Marlin/SdFatUtil.cpp.o \
./Marlin/SdFile.cpp.o \
./Marlin/SdVolume.cpp.o \
./Marlin/Servo.cpp.o \
./Marlin/cardreader.cpp.o \
./Marlin/digipot_mcp4451.cpp.o \
./Marlin/motion_control.cpp.o \
./Marlin/planner.cpp.o \
./Marlin/qr_solve.cpp.o \
./Marlin/stepper.cpp.o \
./Marlin/temperature.cpp.o \
./Marlin/ultralcd.cpp.o \
./Marlin/vector_3.cpp.o \
./Marlin/watchdog.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Marlin/BlinkM.cpp.o: D:/workspace/Marlin_Search/Marlin/BlinkM.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/ConfigurationStore.cpp.o: D:/workspace/Marlin_Search/Marlin/ConfigurationStore.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/LiquidCrystalRus.cpp.o: D:/workspace/Marlin_Search/Marlin/LiquidCrystalRus.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/MarlinSerial.cpp.o: D:/workspace/Marlin_Search/Marlin/MarlinSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/Sd2Card.cpp.o: D:/workspace/Marlin_Search/Marlin/Sd2Card.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/SdBaseFile.cpp.o: D:/workspace/Marlin_Search/Marlin/SdBaseFile.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/SdFatUtil.cpp.o: D:/workspace/Marlin_Search/Marlin/SdFatUtil.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/SdFile.cpp.o: D:/workspace/Marlin_Search/Marlin/SdFile.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/SdVolume.cpp.o: D:/workspace/Marlin_Search/Marlin/SdVolume.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/Servo.cpp.o: D:/workspace/Marlin_Search/Marlin/Servo.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/cardreader.cpp.o: D:/workspace/Marlin_Search/Marlin/cardreader.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/digipot_mcp4451.cpp.o: D:/workspace/Marlin_Search/Marlin/digipot_mcp4451.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/motion_control.cpp.o: D:/workspace/Marlin_Search/Marlin/motion_control.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/planner.cpp.o: D:/workspace/Marlin_Search/Marlin/planner.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/qr_solve.cpp.o: D:/workspace/Marlin_Search/Marlin/qr_solve.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/stepper.cpp.o: D:/workspace/Marlin_Search/Marlin/stepper.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/temperature.cpp.o: D:/workspace/Marlin_Search/Marlin/temperature.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/ultralcd.cpp.o: D:/workspace/Marlin_Search/Marlin/ultralcd.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/vector_3.cpp.o: D:/workspace/Marlin_Search/Marlin/vector_3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

Marlin/watchdog.cpp.o: D:/workspace/Marlin_Search/Marlin/watchdog.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '



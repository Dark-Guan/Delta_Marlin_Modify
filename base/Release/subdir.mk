################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConfigurationStore.cpp \
../base.cpp \
../planner.cpp \
../stepper.cpp \
../watchdog.cpp 

CPP_DEPS += \
./ConfigurationStore.cpp.d \
./base.cpp.d \
./planner.cpp.d \
./stepper.cpp.d \
./watchdog.cpp.d 

LINK_OBJ += \
./ConfigurationStore.cpp.o \
./base.cpp.o \
./planner.cpp.o \
./stepper.cpp.o \
./watchdog.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
ConfigurationStore.cpp.o: ../ConfigurationStore.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"E:\Arduino\arduino-1.5.6-r2\libraries\FlexiTimer2" -I"E:\Arduino\arduino-1.5.6-r2\libraries\TimerOne" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

base.cpp.o: ../base.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"E:\Arduino\arduino-1.5.6-r2\libraries\FlexiTimer2" -I"E:\Arduino\arduino-1.5.6-r2\libraries\TimerOne" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

planner.cpp.o: ../planner.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"E:\Arduino\arduino-1.5.6-r2\libraries\FlexiTimer2" -I"E:\Arduino\arduino-1.5.6-r2\libraries\TimerOne" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

stepper.cpp.o: ../stepper.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"E:\Arduino\arduino-1.5.6-r2\libraries\FlexiTimer2" -I"E:\Arduino\arduino-1.5.6-r2\libraries\TimerOne" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

watchdog.cpp.o: ../watchdog.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"E:\Arduino\arduino-1.5.6-r2\libraries\FlexiTimer2" -I"E:\Arduino\arduino-1.5.6-r2\libraries\TimerOne" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '



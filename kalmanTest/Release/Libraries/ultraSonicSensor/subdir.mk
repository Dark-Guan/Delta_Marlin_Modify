################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
E:/Arduino/arduino-1.5.6-r2/libraries/ultraSonicSensor/ultraSonicSensor.cpp 

CPP_DEPS += \
./Libraries/ultraSonicSensor/ultraSonicSensor.cpp.d 

LINK_OBJ += \
./Libraries/ultraSonicSensor/ultraSonicSensor.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/ultraSonicSensor/ultraSonicSensor.cpp.o: E:/Arduino/arduino-1.5.6-r2/libraries/ultraSonicSensor/ultraSonicSensor.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\standard" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\libraries\Wire" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\libraries\Wire\utility" -I"E:\Arduino\arduino-1.5.6-r2\libraries\ultraSonicSensor" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Arduino/arduino-1.5.6-r2/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c \
E:/Arduino/arduino-1.5.6-r2/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c 

C_DEPS += \
./arduino/malloc.c.d \
./arduino/realloc.c.d 

AR_OBJ += \
./arduino/malloc.c.o \
./arduino/realloc.c.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/malloc.c.o: E:/Arduino/arduino-1.5.6-r2/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-gcc" -c -g -Os -w -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

arduino/realloc.c.o: E:/Arduino/arduino-1.5.6-r2/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"E:/Arduino/arduino-1.5.6-r2/hardware/tools/avr/bin/avr-gcc" -c -g -Os -w -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\arduino-1.5.6-r2\hardware\arduino\avr\variants\mega" -I"D:\workspace\Marlin_Search\Marlin" -I"D:\workspace\Marlin_Search\LiquidCrystal" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '



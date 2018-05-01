################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/circbuf.c \
../Sources/conversion.c \
../Sources/dma.c \
../Sources/logger.c \
../Sources/logger_queue.c \
../Sources/main.c \
../Sources/memory.c \
../Sources/nordic.c \
../Sources/port.c \
../Sources/profile.c \
../Sources/project1.c \
../Sources/project2.c \
../Sources/project3.c \
../Sources/project4.c \
../Sources/rtc.c \
../Sources/spi.c \
../Sources/uart.c 

OBJS += \
./Sources/circbuf.o \
./Sources/conversion.o \
./Sources/dma.o \
./Sources/logger.o \
./Sources/logger_queue.o \
./Sources/main.o \
./Sources/memory.o \
./Sources/nordic.o \
./Sources/port.o \
./Sources/profile.o \
./Sources/project1.o \
./Sources/project2.o \
./Sources/project3.o \
./Sources/project4.o \
./Sources/rtc.o \
./Sources/spi.o \
./Sources/uart.o 

C_DEPS += \
./Sources/circbuf.d \
./Sources/conversion.d \
./Sources/dma.d \
./Sources/logger.d \
./Sources/logger_queue.d \
./Sources/main.d \
./Sources/memory.d \
./Sources/nordic.d \
./Sources/port.d \
./Sources/profile.d \
./Sources/project1.d \
./Sources/project2.d \
./Sources/project3.d \
./Sources/project4.d \
./Sources/rtc.d \
./Sources/spi.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DPROJECT4 -DDEBUG -DKL25Z -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/circbuf.c \
../Sources/conversion.c \
../Sources/data.c \
../Sources/main.c \
../Sources/memory.c \
../Sources/port.c \
../Sources/project1.c \
../Sources/project2.c \
../Sources/uart.c 

OBJS += \
./Sources/circbuf.o \
./Sources/conversion.o \
./Sources/data.o \
./Sources/main.o \
./Sources/memory.o \
./Sources/port.o \
./Sources/project1.o \
./Sources/project2.o \
./Sources/uart.o 

C_DEPS += \
./Sources/circbuf.d \
./Sources/conversion.d \
./Sources/data.d \
./Sources/main.d \
./Sources/memory.d \
./Sources/port.d \
./Sources/project1.d \
./Sources/project2.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DPROJECT2 -DENTER -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



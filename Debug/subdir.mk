################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../command_parser.c \
../commands.c \
../constants.c \
../environment.c \
../file_processing.c \
../main.c \
../variables.c 

O_SRCS += \
../command_parser.o \
../commands.o \
../constants.o \
../environment.o \
../file_processing.o \
../main.o \
../variables.o 

OBJS += \
./command_parser.o \
./commands.o \
./constants.o \
./environment.o \
./file_processing.o \
./main.o \
./variables.o 

C_DEPS += \
./command_parser.d \
./commands.d \
./constants.d \
./environment.d \
./file_processing.d \
./main.d \
./variables.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



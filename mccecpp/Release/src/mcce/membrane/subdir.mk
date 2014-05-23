################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/membrane/add_membrane.cpp \
../src/mcce/membrane/mem_position.cpp \
../src/mcce/membrane/probe.cpp 

OBJS += \
./src/mcce/membrane/add_membrane.o \
./src/mcce/membrane/mem_position.o \
./src/mcce/membrane/probe.o 

CPP_DEPS += \
./src/mcce/membrane/add_membrane.d \
./src/mcce/membrane/mem_position.d \
./src/mcce/membrane/probe.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/membrane/%.o: ../src/mcce/membrane/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



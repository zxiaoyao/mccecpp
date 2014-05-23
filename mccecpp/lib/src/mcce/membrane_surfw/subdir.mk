################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/membrane_surfw/add_membrane.cpp \
../src/mcce/membrane_surfw/mem_position.cpp \
../src/mcce/membrane_surfw/probe.cpp \
../src/mcce/membrane_surfw/surfw.cpp 

OBJS += \
./src/mcce/membrane_surfw/add_membrane.o \
./src/mcce/membrane_surfw/mem_position.o \
./src/mcce/membrane_surfw/probe.o \
./src/mcce/membrane_surfw/surfw.o 

CPP_DEPS += \
./src/mcce/membrane_surfw/add_membrane.d \
./src/mcce/membrane_surfw/mem_position.d \
./src/mcce/membrane_surfw/probe.d \
./src/mcce/membrane_surfw/surfw.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/membrane_surfw/%.o: ../src/mcce/membrane_surfw/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



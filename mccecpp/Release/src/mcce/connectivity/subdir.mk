################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/connectivity/collect_connect.cpp \
../src/mcce/connectivity/get_connect12.cpp 

OBJS += \
./src/mcce/connectivity/collect_connect.o \
./src/mcce/connectivity/get_connect12.o 

CPP_DEPS += \
./src/mcce/connectivity/collect_connect.d \
./src/mcce/connectivity/get_connect12.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/connectivity/%.o: ../src/mcce/connectivity/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



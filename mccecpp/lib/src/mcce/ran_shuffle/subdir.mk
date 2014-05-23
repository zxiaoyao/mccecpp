################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/ran_shuffle/ran2.cpp \
../src/mcce/ran_shuffle/shuffle_n.cpp 

OBJS += \
./src/mcce/ran_shuffle/ran2.o \
./src/mcce/ran_shuffle/shuffle_n.o 

CPP_DEPS += \
./src/mcce/ran_shuffle/ran2.d \
./src/mcce/ran_shuffle/shuffle_n.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/ran_shuffle/%.o: ../src/mcce/ran_shuffle/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



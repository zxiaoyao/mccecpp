################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/acrp/protein.cpp \
../src/mcce/acrp/residue.cpp 

OBJS += \
./src/mcce/acrp/protein.o \
./src/mcce/acrp/residue.o 

CPP_DEPS += \
./src/mcce/acrp/protein.d \
./src/mcce/acrp/residue.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/acrp/%.o: ../src/mcce/acrp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/relax/relax_h.cpp \
../src/mcce/relax/relax_water.cpp \
../src/mcce/relax/relaxation.cpp 

OBJS += \
./src/mcce/relax/relax_h.o \
./src/mcce/relax/relax_water.o \
./src/mcce/relax/relaxation.o 

CPP_DEPS += \
./src/mcce/relax/relax_h.d \
./src/mcce/relax/relax_water.d \
./src/mcce/relax/relaxation.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/relax/%.o: ../src/mcce/relax/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



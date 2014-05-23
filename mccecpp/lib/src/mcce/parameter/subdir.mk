################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/parameter/assign_rad.cpp \
../src/mcce/parameter/db_param.cpp 

OBJS += \
./src/mcce/parameter/assign_rad.o \
./src/mcce/parameter/db_param.o 

CPP_DEPS += \
./src/mcce/parameter/assign_rad.d \
./src/mcce/parameter/db_param.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/parameter/%.o: ../src/mcce/parameter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



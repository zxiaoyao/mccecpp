################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/construct_insert_sort_clean_struct.cpp \
../src/mcce/geometry_arithmetic.cpp \
../src/mcce/init.cpp \
../src/mcce/torsion.cpp 

OBJS += \
./src/mcce/construct_insert_sort_clean_struct.o \
./src/mcce/geometry_arithmetic.o \
./src/mcce/init.o \
./src/mcce/torsion.o 

CPP_DEPS += \
./src/mcce/construct_insert_sort_clean_struct.d \
./src/mcce/geometry_arithmetic.d \
./src/mcce/init.d \
./src/mcce/torsion.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/%.o: ../src/mcce/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



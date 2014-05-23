################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/utility/construct_insert_sort_clean_struct.cpp \
../src/mcce/utility/geometry_arithmetic.cpp \
../src/mcce/utility/get_files.cpp \
../src/mcce/utility/init.cpp \
../src/mcce/utility/premcce_rename.cpp \
../src/mcce/utility/strip.cpp \
../src/mcce/utility/torsion.cpp 

OBJS += \
./src/mcce/utility/construct_insert_sort_clean_struct.o \
./src/mcce/utility/geometry_arithmetic.o \
./src/mcce/utility/get_files.o \
./src/mcce/utility/init.o \
./src/mcce/utility/premcce_rename.o \
./src/mcce/utility/strip.o \
./src/mcce/utility/torsion.o 

CPP_DEPS += \
./src/mcce/utility/construct_insert_sort_clean_struct.d \
./src/mcce/utility/geometry_arithmetic.d \
./src/mcce/utility/get_files.d \
./src/mcce/utility/init.d \
./src/mcce/utility/premcce_rename.d \
./src/mcce/utility/strip.d \
./src/mcce/utility/torsion.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/utility/%.o: ../src/mcce/utility/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



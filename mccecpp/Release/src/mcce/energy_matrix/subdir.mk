################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/energy_matrix/make_matrices.cpp \
../src/mcce/energy_matrix/zip.cpp 

OBJS += \
./src/mcce/energy_matrix/make_matrices.o \
./src/mcce/energy_matrix/zip.o 

CPP_DEPS += \
./src/mcce/energy_matrix/make_matrices.d \
./src/mcce/energy_matrix/zip.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/energy_matrix/%.o: ../src/mcce/energy_matrix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



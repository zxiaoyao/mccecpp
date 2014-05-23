################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/main/energies.cpp \
../src/mcce/main/mcce.cpp \
../src/mcce/main/monte.cpp \
../src/mcce/main/monte2.cpp \
../src/mcce/main/premcce.cpp \
../src/mcce/main/rotamers.cpp 

OBJS += \
./src/mcce/main/energies.o \
./src/mcce/main/mcce.o \
./src/mcce/main/monte.o \
./src/mcce/main/monte2.o \
./src/mcce/main/premcce.o \
./src/mcce/main/rotamers.o 

CPP_DEPS += \
./src/mcce/main/energies.d \
./src/mcce/main/mcce.d \
./src/mcce/main/monte.d \
./src/mcce/main/monte2.d \
./src/mcce/main/premcce.d \
./src/mcce/main/rotamers.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/main/%.o: ../src/mcce/main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



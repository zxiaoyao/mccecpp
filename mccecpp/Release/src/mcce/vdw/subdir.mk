################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/vdw/assign_crg.cpp \
../src/mcce/vdw/get_vdw0.cpp \
../src/mcce/vdw/get_vdw1.cpp \
../src/mcce/vdw/vdw.cpp \
../src/mcce/vdw/vdw_conf.cpp \
../src/mcce/vdw/vdw_fast.cpp 

OBJS += \
./src/mcce/vdw/assign_crg.o \
./src/mcce/vdw/get_vdw0.o \
./src/mcce/vdw/get_vdw1.o \
./src/mcce/vdw/vdw.o \
./src/mcce/vdw/vdw_conf.o \
./src/mcce/vdw/vdw_fast.o 

CPP_DEPS += \
./src/mcce/vdw/assign_crg.d \
./src/mcce/vdw/get_vdw0.d \
./src/mcce/vdw/get_vdw1.d \
./src/mcce/vdw/vdw.d \
./src/mcce/vdw/vdw_conf.d \
./src/mcce/vdw/vdw_fast.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/vdw/%.o: ../src/mcce/vdw/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mcce/pdb/load_pdb.cpp \
../src/mcce/pdb/pdbline2atom.cpp \
../src/mcce/pdb/write_pdb.cpp 

OBJS += \
./src/mcce/pdb/load_pdb.o \
./src/mcce/pdb/pdbline2atom.o \
./src/mcce/pdb/write_pdb.o 

CPP_DEPS += \
./src/mcce/pdb/load_pdb.d \
./src/mcce/pdb/pdbline2atom.d \
./src/mcce/pdb/write_pdb.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcce/pdb/%.o: ../src/mcce/pdb/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/xzhu/git/mccecpp/mccecpp/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



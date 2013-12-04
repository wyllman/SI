################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/source/model/abstracts/Model.cpp 

OBJS += \
./src/source/model/abstracts/Model.o 

CPP_DEPS += \
./src/source/model/abstracts/Model.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/model/abstracts/%.o: ../src/source/model/abstracts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/abstracts/Model.cpp 

OBJS += \
./src/model/abstracts/Model.o 

CPP_DEPS += \
./src/model/abstracts/Model.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/abstracts/%.o: ../src/model/abstracts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/maikel/workspace/SI/include" -I/usr/include/SDL2 -I"/home/maikel/workspace/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



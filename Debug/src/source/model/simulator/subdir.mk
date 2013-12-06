################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/source/model/simulator/Simulator.cpp 

OBJS += \
./src/source/model/simulator/Simulator.o 

CPP_DEPS += \
./src/source/model/simulator/Simulator.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/model/simulator/%.o: ../src/source/model/simulator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Library/Frameworks/SDL2.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



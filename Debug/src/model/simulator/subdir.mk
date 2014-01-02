################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/simulator/Simulator.cpp 

OBJS += \
./src/model/simulator/Simulator.o 

CPP_DEPS += \
./src/model/simulator/Simulator.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/simulator/%.o: ../src/model/simulator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -I/Library/Frameworks/SDL2.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I"/Users/tenerent/Downloads/temporal/SI/include" -I"/Users/tenerent/Downloads/temporal/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/agents/Agent.cpp \
../src/model/agents/BuildAgent.cpp \
../src/model/agents/GatherAgent.cpp \
../src/model/agents/MainAgent.cpp \
../src/model/agents/SearchAgent.cpp \
../src/model/agents/WorkingAgent.cpp 

OBJS += \
./src/model/agents/Agent.o \
./src/model/agents/BuildAgent.o \
./src/model/agents/GatherAgent.o \
./src/model/agents/MainAgent.o \
./src/model/agents/SearchAgent.o \
./src/model/agents/WorkingAgent.o 

CPP_DEPS += \
./src/model/agents/Agent.d \
./src/model/agents/BuildAgent.d \
./src/model/agents/GatherAgent.d \
./src/model/agents/MainAgent.d \
./src/model/agents/SearchAgent.d \
./src/model/agents/WorkingAgent.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/agents/%.o: ../src/model/agents/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -I/Library/Frameworks/SDL2.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I"/Users/tenerent/Downloads/temporal/SI/include" -I"/Users/tenerent/Downloads/temporal/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Agent.cpp \
../src/Belief.cpp \
../src/BeliefSet.cpp \
../src/BuildAgent.cpp \
../src/Desire.cpp \
../src/GatherAgent.cpp \
../src/Goals.cpp \
../src/Intentions.cpp \
../src/MainAgent.cpp \
../src/Map.cpp \
../src/MapBuilder.cpp \
../src/Plan.cpp \
../src/SDL2App.cpp \
../src/SearchAgent.cpp \
../src/WorkingAgent.cpp \
../src/main.cpp 

OBJS += \
./src/Agent.o \
./src/Belief.o \
./src/BeliefSet.o \
./src/BuildAgent.o \
./src/Desire.o \
./src/GatherAgent.o \
./src/Goals.o \
./src/Intentions.o \
./src/MainAgent.o \
./src/Map.o \
./src/MapBuilder.o \
./src/Plan.o \
./src/SDL2App.o \
./src/SearchAgent.o \
./src/WorkingAgent.o \
./src/main.o 

CPP_DEPS += \
./src/Agent.d \
./src/Belief.d \
./src/BeliefSet.d \
./src/BuildAgent.d \
./src/Desire.d \
./src/GatherAgent.d \
./src/Goals.d \
./src/Intentions.d \
./src/MainAgent.d \
./src/Map.d \
./src/MapBuilder.d \
./src/Plan.d \
./src/SDL2App.d \
./src/SearchAgent.d \
./src/WorkingAgent.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -D_GLIBCXX_PROFILE -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



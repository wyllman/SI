################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/bdi/Belief.cpp \
../src/model/bdi/BeliefSet.cpp \
../src/model/bdi/Desire.cpp \
../src/model/bdi/Goals.cpp \
../src/model/bdi/Intentions.cpp \
../src/model/bdi/Plan.cpp 

OBJS += \
./src/model/bdi/Belief.o \
./src/model/bdi/BeliefSet.o \
./src/model/bdi/Desire.o \
./src/model/bdi/Goals.o \
./src/model/bdi/Intentions.o \
./src/model/bdi/Plan.o 

CPP_DEPS += \
./src/model/bdi/Belief.d \
./src/model/bdi/BeliefSet.d \
./src/model/bdi/Desire.d \
./src/model/bdi/Goals.d \
./src/model/bdi/Intentions.d \
./src/model/bdi/Plan.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/bdi/%.o: ../src/model/bdi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -I/Library/Frameworks/SDL2.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I"/Users/tenerent/Downloads/temporal/SI/include" -I"/Users/tenerent/Downloads/temporal/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



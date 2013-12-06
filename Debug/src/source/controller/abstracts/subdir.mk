################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/source/controller/abstracts/Action.cpp \
../src/source/controller/abstracts/Controller.cpp \
../src/source/controller/abstracts/Event.cpp \
../src/source/controller/abstracts/Loop.cpp 

OBJS += \
./src/source/controller/abstracts/Action.o \
./src/source/controller/abstracts/Controller.o \
./src/source/controller/abstracts/Event.o \
./src/source/controller/abstracts/Loop.o 

CPP_DEPS += \
./src/source/controller/abstracts/Action.d \
./src/source/controller/abstracts/Controller.d \
./src/source/controller/abstracts/Event.d \
./src/source/controller/abstracts/Loop.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/controller/abstracts/%.o: ../src/source/controller/abstracts/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Library/Frameworks/SDL2.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



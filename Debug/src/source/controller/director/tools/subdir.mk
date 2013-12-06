################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/source/controller/director/tools/ActionsList.cpp \
../src/source/controller/director/tools/EventsList.cpp \
../src/source/controller/director/tools/FileLog.cpp \
../src/source/controller/director/tools/MainLoop.cpp 

OBJS += \
./src/source/controller/director/tools/ActionsList.o \
./src/source/controller/director/tools/EventsList.o \
./src/source/controller/director/tools/FileLog.o \
./src/source/controller/director/tools/MainLoop.o 

CPP_DEPS += \
./src/source/controller/director/tools/ActionsList.d \
./src/source/controller/director/tools/EventsList.d \
./src/source/controller/director/tools/FileLog.d \
./src/source/controller/director/tools/MainLoop.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/controller/director/tools/%.o: ../src/source/controller/director/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Library/Frameworks/SDL2.framework/Versions/A/Headers -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



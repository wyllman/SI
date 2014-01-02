################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/controller/director/tools/FileLog.cpp \
../src/controller/director/tools/MainLoop.cpp 

OBJS += \
./src/controller/director/tools/FileLog.o \
./src/controller/director/tools/MainLoop.o 

CPP_DEPS += \
./src/controller/director/tools/FileLog.d \
./src/controller/director/tools/MainLoop.d 


# Each subdirectory must supply rules for building sources it contributes
src/controller/director/tools/%.o: ../src/controller/director/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/maikel/workspace/SI/include" -I/usr/include/SDL2 -I"/home/maikel/workspace/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



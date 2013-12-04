################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/source/view/interface/tools/Context.cpp \
../src/source/view/interface/tools/Scene.cpp \
../src/source/view/interface/tools/Window.cpp 

OBJS += \
./src/source/view/interface/tools/Context.o \
./src/source/view/interface/tools/Scene.o \
./src/source/view/interface/tools/Window.o 

CPP_DEPS += \
./src/source/view/interface/tools/Context.d \
./src/source/view/interface/tools/Scene.d \
./src/source/view/interface/tools/Window.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/view/interface/tools/%.o: ../src/source/view/interface/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



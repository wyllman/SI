################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/view/interface/tools/Context.cpp \
../src/view/interface/tools/Scene.cpp \
../src/view/interface/tools/Window.cpp 

OBJS += \
./src/view/interface/tools/Context.o \
./src/view/interface/tools/Scene.o \
./src/view/interface/tools/Window.o 

CPP_DEPS += \
./src/view/interface/tools/Context.d \
./src/view/interface/tools/Scene.d \
./src/view/interface/tools/Window.d 


# Each subdirectory must supply rules for building sources it contributes
src/view/interface/tools/%.o: ../src/view/interface/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/maikel/workspace/SI/include" -I/usr/include/SDL2 -I"/home/maikel/workspace/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



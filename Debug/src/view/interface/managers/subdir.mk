################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/view/interface/managers/Bureaucrat.cpp \
../src/view/interface/managers/Scenographer.cpp 

OBJS += \
./src/view/interface/managers/Bureaucrat.o \
./src/view/interface/managers/Scenographer.o 

CPP_DEPS += \
./src/view/interface/managers/Bureaucrat.d \
./src/view/interface/managers/Scenographer.d 


# Each subdirectory must supply rules for building sources it contributes
src/view/interface/managers/%.o: ../src/view/interface/managers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/maikel/workspace/SI/include" -I/usr/include/SDL2 -I"/home/maikel/workspace/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



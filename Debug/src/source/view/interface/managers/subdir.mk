################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/source/view/interface/managers/Bureaucrat.cpp \
../src/source/view/interface/managers/Scenographer.cpp 

OBJS += \
./src/source/view/interface/managers/Bureaucrat.o \
./src/source/view/interface/managers/Scenographer.o 

CPP_DEPS += \
./src/source/view/interface/managers/Bureaucrat.d \
./src/source/view/interface/managers/Scenographer.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/view/interface/managers/%.o: ../src/source/view/interface/managers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



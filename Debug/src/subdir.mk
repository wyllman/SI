################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map.cpp \
../src/MapBuilder.cpp \
../src/SDL2App.cpp \
../src/main.cpp 

OBJS += \
./src/Map.o \
./src/MapBuilder.o \
./src/SDL2App.o \
./src/main.o 

CPP_DEPS += \
./src/Map.d \
./src/MapBuilder.d \
./src/SDL2App.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/map/Map.cpp \
../src/model/map/MapBuilder.cpp \
../src/model/map/MapConsoleInterface.cpp 

OBJS += \
./src/model/map/Map.o \
./src/model/map/MapBuilder.o \
./src/model/map/MapConsoleInterface.o 

CPP_DEPS += \
./src/model/map/Map.d \
./src/model/map/MapBuilder.d \
./src/model/map/MapConsoleInterface.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/map/%.o: ../src/model/map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/maikel/workspace/SI/include" -I/usr/include/SDL2 -I"/home/maikel/workspace/SI/assets" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


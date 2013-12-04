################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
<<<<<<< HEAD
../src/Map.cpp \
../src/MapBuilder.cpp \
../src/MapConsoleInterface.cpp \
../src/main.cpp 

OBJS += \
./src/Map.o \
./src/MapBuilder.o \
./src/MapConsoleInterface.o \
./src/main.o 

CPP_DEPS += \
./src/Map.d \
./src/MapBuilder.d \
./src/MapConsoleInterface.d \
./src/main.d 
=======
../src/PreColonia.cpp 

OBJS += \
./src/PreColonia.o 

CPP_DEPS += \
./src/PreColonia.d 
>>>>>>> 7a993e9867b4edf5fb874c2bba44827b6c9dc4d0


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
<<<<<<< HEAD
	g++ -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -Wno-trigraphs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
=======
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
>>>>>>> 7a993e9867b4edf5fb874c2bba44827b6c9dc4d0
	@echo 'Finished building: $<'
	@echo ' '



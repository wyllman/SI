################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
<<<<<<< HEAD
-include src/include/subdir.mk
-include src/bdi/subdir.mk
-include src/agents/subdir.mk
-include src/subdir.mk
-include assets/subdir.mk
=======
-include src/source/view/interface/tools/subdir.mk
-include src/source/view/interface/managers/subdir.mk
-include src/source/view/interface/subdir.mk
-include src/source/view/abstracts/subdir.mk
-include src/source/controller/director/tools/subdir.mk
-include src/source/controller/director/subdir.mk
-include src/source/controller/abstracts/subdir.mk
-include src/subdir.mk
>>>>>>> 7a993e9867b4edf5fb874c2bba44827b6c9dc4d0
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
<<<<<<< HEAD
all: SI

# Tool invocations
SI: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "SI" $(OBJS) $(USER_OBJS) $(LIBS)
=======
all: PreColonia

# Tool invocations
PreColonia: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	g++  -o "PreColonia" $(OBJS) $(USER_OBJS) $(LIBS)
>>>>>>> 7a993e9867b4edf5fb874c2bba44827b6c9dc4d0
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
<<<<<<< HEAD
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) SI
=======
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) PreColonia
>>>>>>> 7a993e9867b4edf5fb874c2bba44827b6c9dc4d0
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

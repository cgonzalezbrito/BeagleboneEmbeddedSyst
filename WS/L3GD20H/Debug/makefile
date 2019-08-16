################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include scr/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: L3GD20H

# Tool invocations
L3GD20H: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	arm-buildroot-linux-uclibcgnueabihf-gcc -L/home/cgonzalezbrito/BeagleBone/buildroot-2016.05/output/host/usr/lib -L/home/cgonzalezbrito/BeagleBone/buildroot-2016.05/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/lib -o "L3GD20H" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) L3GD20H
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

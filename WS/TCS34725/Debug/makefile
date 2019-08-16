################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: TCS34725

# Tool invocations
TCS34725: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	arm-buildroot-linux-uclibcgnueabihf-gcc -L/home/cgonzalezbrito/BeagleBone/buildroot-2016.05/output/host/usr/lib -L/home/cgonzalezbrito/BeagleBone/buildroot-2016.05/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/lib -o "TCS34725" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TCS34725
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

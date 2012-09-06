################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PhysicsTools/Force.cpp 

OBJS += \
./PhysicsTools/Force.o 

CPP_DEPS += \
./PhysicsTools/Force.d 


# Each subdirectory must supply rules for building sources it contributes
PhysicsTools/%.o: ../PhysicsTools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



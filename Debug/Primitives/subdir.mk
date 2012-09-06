################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Primitives/Object.cpp \
../Primitives/Plane.cpp \
../Primitives/Sphere.cpp 

OBJS += \
./Primitives/Object.o \
./Primitives/Plane.o \
./Primitives/Sphere.o 

CPP_DEPS += \
./Primitives/Object.d \
./Primitives/Plane.d \
./Primitives/Sphere.d 


# Each subdirectory must supply rules for building sources it contributes
Primitives/%.o: ../Primitives/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



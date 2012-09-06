################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../OgreRendering/OgreObjects/OgreObject.cpp \
../OgreRendering/OgreObjects/OgrePlane.cpp \
../OgreRendering/OgreObjects/OgreSphere.cpp 

OBJS += \
./OgreRendering/OgreObjects/OgreObject.o \
./OgreRendering/OgreObjects/OgrePlane.o \
./OgreRendering/OgreObjects/OgreSphere.o 

CPP_DEPS += \
./OgreRendering/OgreObjects/OgreObject.d \
./OgreRendering/OgreObjects/OgrePlane.d \
./OgreRendering/OgreObjects/OgreSphere.d 


# Each subdirectory must supply rules for building sources it contributes
OgreRendering/OgreObjects/%.o: ../OgreRendering/OgreObjects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



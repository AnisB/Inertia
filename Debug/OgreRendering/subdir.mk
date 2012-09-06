################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../OgreRendering/CameraMan.cpp \
../OgreRendering/InputListener.cpp \
../OgreRendering/Renderer.cpp 

OBJS += \
./OgreRendering/CameraMan.o \
./OgreRendering/InputListener.o \
./OgreRendering/Renderer.o 

CPP_DEPS += \
./OgreRendering/CameraMan.d \
./OgreRendering/InputListener.d \
./OgreRendering/Renderer.d 


# Each subdirectory must supply rules for building sources it contributes
OgreRendering/%.o: ../OgreRendering/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



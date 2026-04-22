################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/ZBook\ Fury/Desktop/note/Faraz_Workstation/Projects/Git_Repo/Faraz_PRJ_AntennaTracker_MCU_Firmware/Libraries/TimerControl_STM32/TimerControl.cpp 

OBJS += \
./Libraries/TimerControl_STM32/TimerControl.o 

CPP_DEPS += \
./Libraries/TimerControl_STM32/TimerControl.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/TimerControl_STM32/TimerControl.o: C:/Users/ZBook\ Fury/Desktop/note/Faraz_Workstation/Projects/Git_Repo/Faraz_PRJ_AntennaTracker_MCU_Firmware/Libraries/TimerControl_STM32/TimerControl.cpp Libraries/TimerControl_STM32/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../../../../../TimerControl_STM32" -I"C:/Users/ZBook Fury/Desktop/note/Faraz_Workstation/Projects/Git_Repo/Faraz_PRJ_AntennaTracker_MCU_Firmware/Libraries/TimerControl_STM32" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Libraries/TimerControl_STM32/TimerControl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-TimerControl_STM32

clean-Libraries-2f-TimerControl_STM32:
	-$(RM) ./Libraries/TimerControl_STM32/TimerControl.cyclo ./Libraries/TimerControl_STM32/TimerControl.d ./Libraries/TimerControl_STM32/TimerControl.o ./Libraries/TimerControl_STM32/TimerControl.su

.PHONY: clean-Libraries-2f-TimerControl_STM32


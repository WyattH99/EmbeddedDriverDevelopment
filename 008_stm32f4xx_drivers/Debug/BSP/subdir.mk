################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/ds1307.c 

OBJS += \
./BSP/ds1307.o 

C_DEPS += \
./BSP/ds1307.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o BSP/%.su BSP/%.cyclo: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"/home/wyatt/Desktop/EmbeddedDriverDevelopment/008_stm32f4xx_drivers/Drivers/Inc" -I"/home/wyatt/Desktop/EmbeddedDriverDevelopment/008_stm32f4xx_drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP

clean-BSP:
	-$(RM) ./BSP/ds1307.cyclo ./BSP/ds1307.d ./BSP/ds1307.o ./BSP/ds1307.su

.PHONY: clean-BSP


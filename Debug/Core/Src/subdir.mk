################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EXTI_lib.c \
../Core/Src/GPIO_Lib.c \
../Core/Src/I2c_lib.c \
../Core/Src/NVIC_lib.c \
../Core/Src/RTC.c \
../Core/Src/UART_lib.c \
../Core/Src/clocks_lib.c \
../Core/Src/delay_timer_lib.c \
../Core/Src/dht22.c \
../Core/Src/interrupts.c \
../Core/Src/lcd.c \
../Core/Src/main.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/systick_IR_\ timer_lib.c 

OBJS += \
./Core/Src/EXTI_lib.o \
./Core/Src/GPIO_Lib.o \
./Core/Src/I2c_lib.o \
./Core/Src/NVIC_lib.o \
./Core/Src/RTC.o \
./Core/Src/UART_lib.o \
./Core/Src/clocks_lib.o \
./Core/Src/delay_timer_lib.o \
./Core/Src/dht22.o \
./Core/Src/interrupts.o \
./Core/Src/lcd.o \
./Core/Src/main.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/systick_IR_\ timer_lib.o 

C_DEPS += \
./Core/Src/EXTI_lib.d \
./Core/Src/GPIO_Lib.d \
./Core/Src/I2c_lib.d \
./Core/Src/NVIC_lib.d \
./Core/Src/RTC.d \
./Core/Src/UART_lib.d \
./Core/Src/clocks_lib.d \
./Core/Src/delay_timer_lib.d \
./Core/Src/dht22.d \
./Core/Src/interrupts.d \
./Core/Src/lcd.d \
./Core/Src/main.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/systick_IR_\ timer_lib.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/systick_IR_\ timer_lib.o: ../Core/Src/systick_IR_\ timer_lib.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/systick_IR_ timer_lib.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/EXTI_lib.d ./Core/Src/EXTI_lib.o ./Core/Src/GPIO_Lib.d ./Core/Src/GPIO_Lib.o ./Core/Src/I2c_lib.d ./Core/Src/I2c_lib.o ./Core/Src/NVIC_lib.d ./Core/Src/NVIC_lib.o ./Core/Src/RTC.d ./Core/Src/RTC.o ./Core/Src/UART_lib.d ./Core/Src/UART_lib.o ./Core/Src/clocks_lib.d ./Core/Src/clocks_lib.o ./Core/Src/delay_timer_lib.d ./Core/Src/delay_timer_lib.o ./Core/Src/dht22.d ./Core/Src/dht22.o ./Core/Src/interrupts.d ./Core/Src/interrupts.o ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/systick_IR_\ timer_lib.d ./Core/Src/systick_IR_\ timer_lib.o

.PHONY: clean-Core-2f-Src


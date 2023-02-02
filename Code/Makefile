microcontrollerName = atmega32
clockFrequency = 8000000UL
sourceFiles = main.c APP/app.c MCAL/DIO_program.c MCAL/TIMER0_program.c HAL/LCD_program.c HAL/KPD_program.c
compilerName = avr-gcc
target = main

all: $(sourceFiles)
	@$(compilerName) -mmcu=$(microcontrollerName) -DF_CPU=$(clockFrequency) $^ -o $(target).o
	@avr-objcopy -j .text -j .data -O ihex $(target).o $(target).hex
	@avr-size --format=berkeley $(target).hex
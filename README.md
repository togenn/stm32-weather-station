# stm32-weather-station
This project displays time, date, temperature and humidity on a LCD screen. 
STM32F401RE microcontroller is used to read data from dht22 sensor an display it on a LCD screen which is controlled by an I2C
serial adapter. Internal RTC module of the microcontroller is used to get time and date. The software is made almost entirely from scratch. Only the startup file and STM32F4xx header files are not made by me.
They include code for initializing memory of the microcontroller and definitions of register structures.

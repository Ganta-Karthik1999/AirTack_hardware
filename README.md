# TM7711 ADC for pressure sensors

Simple platformIO example to use the TM7711 ADC converter used in cheap pressure sensors.


----
# Hardware : 

## Module : 
- Bridge : MPS20N0040D-S
- ADC : TM7711 www.titanmec.com/search?keywords=TM7711

<img width="68" alt="20241229-657" src="https://github.com/user-attachments/assets/b27f690a-46c0-49fc-b39d-d9b24d7aa3f7" />


## Board:
- ESP32-C3 Mini
  
  <img width="94" alt="20241229-658" src="https://github.com/user-attachments/assets/6a0c611b-20b3-44dc-9831-595d15361f7e" />

## Connections : 
- module GND - GND
- module VCC - 3v3
- module SCK - GPIO5 (esp32c3 pin 5)
- module OUT - GPIO4 (esp32c3 pin 4)

# Getting started : 
Download the folder, and open it in VSCode/PlatformIO

# Calibration : 
Please adapt the mapping from RAW values in TM7711.cpp
Note that the pressure sensor can output negative values if pressure is negative.

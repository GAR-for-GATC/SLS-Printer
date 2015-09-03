# SLS-Printer

This project aims to create a 600$ SLS printer.  The printer will use a TM4C123GH6PM ARM
microcontroller to drive several TB6560AHQ Stepper Controllers, a TTL Laser driver, a
small NHD-C12832A1Z-FSW-FBW-3V3 LCD module (parsed by an ATMega328) and several temperature
sensors, fans and a hot air/inert-gas heating system.  The laser used will probably be a 
2W or 5W CO2 Diode laser due to safety and size constraints and will utilize a scanning mirror 
system to distribute puled light to the powder bed to increase the resolution and the speed
at which the print is created.  The code will be written in C using the Keil uvision IDE.
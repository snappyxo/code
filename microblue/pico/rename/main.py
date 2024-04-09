'''
 ******************************************************************
 * Mechanismic Inc.
 *
 * Created 2024
 * Created by Amanjeet Bagga
 * Last Modified 29/03/2024
 * Version 2.0
 *
 *
 * Rename HM10 with Pico
 * 
 * Rename the HM10 BLE Module using AT commands and serial
 * communication on the Raspberry Pi Pico.
 *
 * https://snappyxo.io/
 *
 ******************************************************************
 '''


# import modules
from machine import UART

# enable UART communication
uart = UART(0,9600)

# start an infinite loop
while True:
    # Rename device to xxxxxx (The maximum length for a name is 12 characters)
    uart.write("AT+NAMEXXXX")
    

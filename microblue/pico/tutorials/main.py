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
 * Pico Tutorials
 * 
 * Learn how to use each command element on MicroBlue using the
 * Raspberry Pi Pico connected to a HM10 BLE Module.
 *
 * https://snappyxo.io/
 *
 ******************************************************************
 '''


# import modules
from machine import UART

# import other .py files
import led	# Example 1: Control onboard LED
import rgb	# Example 2: Toggle RGB LED on/off
                # Example 3: Control RGB LED brightness
import drive	# Example 4: Control 2 Motors with Joystick

# enable UART communication
uart = UART(0,9600)

# initialize variables
id = ''
value = ''
data = ''
counter = 0

# function to decode data from app to the id and value of the message
def decode_data(command):
    global data, counter, id, value
    # check for header characters and replace them
    if command in [b'\x01', b'\x02', b'\x03']:
        counter += 1
        data += '_'
    else:
        data += str(command, 'ASCII')
    
    # check for entire message being decoded
    if counter == 3:
        # mutate data to get separate id and value strings
        data = data[1:len(data)-1].split('_')
        id = data[0]
        value = data[1]
        
        # check for joystick or d-pad command
        if value.find(',') != -1:
            value = value.split(',')
            print(f"ID: {id} | Values: {value[0], value[1]}")
            value = [int(value[0]), int(value[1])]
        # check for text command
        elif value.isdigit() == 0:  
            print(f"ID: {id} | Value: {value}")
        # confirmed button, switch, or slider command
        else:
            print(f"ID: {id} | Value: {value}")
            value = int(value)
        
        # put loop logic here
        if id == 't0':
            value = str(value).lower().replace(' ','')
            print(value)
            if value == 'onboard':
                example = 1
            elif value == 'rgbtoggle':            
                example = 2
            elif value == 'rgbpwm':
                example = 3
            elif value == 'drive':
                example = 4
    
        if example == 1 and id != 't0':
            led.toggle(id, value)
        elif example == 2 and id != 't0':
            rgb.toggle(id, value)
        elif example == 3 and id != 't0':
            rgb.pwm(id, value)
        elif example == 4 and id != 't0':
            drive.joystick(id, value)
        
        # reset variables for next message
        counter = 0
        data = ''

# start an infinite loop
while True:
    # check for uart communication
    while uart.any():
        command = uart.readline() # read data from communication by character
        decode_data(command) # decode data
        

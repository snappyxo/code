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
 * Pico W Tutorials
 * 
 * Learn how to use each command element on MicroBlue using the
 * Raspberry Pi Pico W.
 *
 * https://snappyxo.io/
 *
 ******************************************************************
 '''


# Import modules
import bluetooth

# Import other .py files
from ble_simple_peripheral import BLESimplePeripheral

import led	# Example 1: Control onboard LED
import rgb	# Example 2: Toggle RGB LED on/off
                # Example 3: Control RGB LED brightness
import drive	# Example 4: Control 2 Motors with Joystick

# Create a Bluetooth Low Energy (BLE) object
ble = bluetooth.BLE()

# Create an instance of the BLESimplePeripheral class with the BLE object
sp = BLESimplePeripheral(ble)

# Variables to store id and value of data sent over
id = ''
value = ''
example = 0;

# Decode data sent from MicroBlue
def decode_data(data):
    global id, value, example
    ''' The received data is mutated by:
            1) Converting from bytestring coded in ASCII to regular string
            2) Replacing the middle header with a space
            3) Slicing to get rid of the first and last headers
            4) Splitting the string across the space for the id and value
    '''
    data = str(data, 'ASCII').replace(' ','_')[1:len(data)-1].split('_')
    
    id = data[0]
    value = data[1].lower().replace(' ','')
    
    # Check if the data was sent from the D-Pad or the Joystick
    if value.find(',') != -1:
        value = value.split(',')  # Separate string into the two values sent
        print("id:", id, "values:", value[0], value[1])
        value = [int(value[0]), int(value[1])]
        
    # Check if the data was sent from the Text command element
    elif value.isdigit() == 0:
        print("id:", id, "value:", value)  # Print value as string
        
    # Confirmed that command element was button, slider, or switch
    else:
        print("id:", id, "value:", value)
        value = int(value)
    
    # Put loop logic here
    if id == 't0':
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

# Start an infinite loop
while True:
    if sp.is_connected():  # Check if a BLE connection is established
        sp.on_write(decode_data)  # Set the callback function for data reception

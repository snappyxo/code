
# Import modules
from machine import Pin, PWM
from time import sleep

# Map function to convert from one value range to the other
def map(var, in_start, in_end, out_start, out_end):
    output = 0
    in_range, out_range = in_end - in_start, out_end - out_start
    output = out_range * var / in_range
    return int(output)

# Use bluetooth data to toggle RGB LED on/off
def toggle(id, value):
    led1 = Pin(22, Pin.OUT)
    led2 = Pin(21, Pin.OUT)
    led3 = Pin(19, Pin.OUT)
    if id == 'sw0':
        if value == 1:
            led1.value(1)
        elif value == 0:
            led1.value(0)
    elif id == 'sw1':
        if value == 1:
            led2.value(1)
        elif value == 0:
            led2.value(0)
    elif id == 'sw2':
        if value == 1:
            led3.value(1)
        elif value == 0:
            led3.value(0)

# Use bluetooth data to control RGB LED brightness
def pwm(id, value):
    led1 = PWM(Pin(22))
    led2 = PWM(Pin(21))
    led3 = PWM(Pin(19))
    led1.freq(1000)
    led2.freq(1000)
    led3.freq(1000)
    
    # Map slider value to analog output range for Pico
    bright = map(value, 0, 100, 0, 65025)
    print(bright)
    
    if id == 'sl0':
        led1.duty_u16(bright)
        sleep(0.001)
    elif id == 'sl1':
        led2.duty_u16(bright)
        sleep(0.001)
    elif id == 'sl2':
        led3.duty_u16(bright)
        sleep(0.001)
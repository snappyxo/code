
# Import modules
from machine import Pin

# Use bluetooth data to control onboard LED
def toggle(id, value):
    led = Pin("LED", Pin.OUT)
    
    if id == 'b0':
        if value == 1:
            led.on()
        if value == 0:
            led.off()
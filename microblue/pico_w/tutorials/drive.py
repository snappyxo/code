
# Import other files
import rgb as analog

# Motor Parameters
# Minimum PWM duty cycle value
MINIMUM_MOTOR_SPEED = 65025 * 40 / 255

# Set pins for motor control
def setPins():
    IN1 = Pin(18, Pin.OUT)
    IN2 = Pin(19, Pin.OUT)
    ENA = PWM(Pin(20))
    ENA.freq(60)
    
    IN3 = Pin(12, Pin.OUT)
    IN4 = Pin(13, Pin.OUT)
    ENB = PWM(Pin(11))
    ENB.freq(60)

# Stop the motors
def motorBrake():
    IN1.value(0)
    IN2.value(0)
    IN3.value(0)
    IN4.value(0)
    ENA.duty_u16(65025)
    ENB.duty_u16(65025)

# Move forward
def motorSetForward():
    IN1.value(0)
    IN2.value(1)
    IN3.value(0)
    IN4.value(1)
    
# Move backward
def motorSetBackward():
    IN1.value(1)
    IN2.value(0)
    IN3.value(1)
    IN4.value(0)

# Use joystick values to set motor speeds and direction
def drive(throttle, steering):
    # Print Debug Info
    print(f"throttle: {throttle}	steering: {steering}")
    
    if throttle == 0:
        # If throttle is zero, don't move
        motorBrake()
        return
    elif throttle > 0:
        motorSetForward()
    else:
        motorSetBackward()
    
    # Map throttle & steering to PWM range
    mappedSpeed = analog.map(abs(throttle), 0, 512, MINIMUM_MOTOR_SPEED, 65025)
    reducedSpeed = analog.map(abs(steering), 0, 512, mappedSpeed, MINIMUM_MOTOR_SPEED)
    
    int leftMotorSpeed, rightMotorSpeed
    if steering > 0:
        # Turn Left
        leftMotorSpeed = mappedSpeed
        rightMotorSpeed = reducedSpeed
    else:
        # Turn Right
        leftMotorSpeed = reducedSpeed
        rightMotorSpeed = mappedSpeed
    
    # Set motor speeds
    ENA.duty_u16(leftMotorSpeed)
    ENB.duty_u16(rightMotorSpeed)
    
    # Print Debug Info
    print(f"mappedSpeed: {mapped Speed}		reducedSpeed: {reducedSpeed}")
    print(f"leftMotorSpeed: {leftMotorSpeed}	rightMotorSpeed: {rightMotorSpeed}")
    
# Use joystick data to get throttle & steering values
def joystick(id, value):
    setPins()
    
    # Check for joystick
    if id == 'd1':
        throttle = value[1] - 512
        steering = value[0] - 512
        drive(throttle, steering)
        

/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Renix Calle
 * Last Modified 07/25/2023
 * Version 2.0
 *
 *
 * This project aims to educate the user on how to control a 2WD car 
 * using bluetooth as well as an excavator mechanism using finite servos.
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */






#include <SoftwareSerial.h> // SoftwareSerial for serial communication with HM10 bluetooth module.
#include <ArduinoBlue.h> // ArduinoBlue bluetooth library
#include <Servo.h> // Servo Library


//Declares Servos
Servo arm;
Servo sweeper;


// MOTOR LEFT PINS
const int ENA = 6;
const int IN1 = 4;
const int IN2 = 5;

// MOTOR RIGHT PINS
const int ENB = 11;
const int IN3 = 12;
const int IN4 = 13;


// MOTOR PARAMETERS
// Minimum PWM value of analogWrite to spin motor when robot is on the ground.
const int MINIMUM_MOTOR_SPEED = 40;
int armpos = 0;
int angle;


// HM10 BLUETOOTH MODULE PINS
// NOTE: Not all pins on your Arduino may support SoftwareSerial.
// Please check: https://www.arduino.cc/en/Reference/softwareSerial
const int BLUETOOTH_TX = 7;
const int BLUETOOTH_RX = 8;

SoftwareSerial softSerial(BLUETOOTH_TX, BLUETOOTH_RX); // Object for serial communication to HM 10 bluetooth module using ditigal pins.
ArduinoBlue phone(softSerial); // Object for smartphone robot control.
int button;
// Configures the motor controller to stop the motors.
void motorBrake() {
	digitalWrite(ENA, LOW);
	digitalWrite(ENB, LOW);
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
	digitalWrite(ENA, HIGH);
	digitalWrite(ENB, HIGH);
	// Do not write the motor speeds on this function. It simply configures the motor controller.
}

// Configures the motor controller to have the robot move forward.
void motorSetForward() {
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);
	// Do not write the motor speeds on this function. It simply configures the motor controller.
}

// Configures the motor controller to have the robot move backwards.
void motorSetBackward() {
	digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);
	// Do not write the motor speeds on this function. It simply configures the motor controller.
}

void setPins() {
	// Set pins as input or output
	pinMode(ENA, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(ENB, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
}


void driveControl() {
	// THROTTLE AND STEERING CONTROL
	// throttle values after subtracting 49:
	//     50 = max forward throttle
	//     0 = no throttole
	//     -49 = max reverse throttle
	// steering values after subtracting 49:
	//     50 = max right
	//     0 = straight
	//     -49 = max left
	int throttle = phone.getThrottle() - 49;
	int steering = phone.getSteering() - 49;

	if (throttle == 0) {
		// If throttle is zero, don't move.
		motorBrake();
		return;
	}

	// Determine forwards or backwards.
	if (throttle > 0) {
		// Forward
		motorSetForward();
	}
	else {
		// Backward
		motorSetBackward();
	}

	// Map throttle to PWM range.
	int mappedSpeed = map(abs(throttle), 0, 50, MINIMUM_MOTOR_SPEED, 255);
	// Map steering to PWM range.
	int reducedSpeed = map(abs(steering), 0, 50, mappedSpeed, MINIMUM_MOTOR_SPEED);

	int leftMotorSpeed, rightMotorSpeed;
	if (steering > 0) {
		// Turn Right: reduce right motor speed
		leftMotorSpeed = mappedSpeed;
		rightMotorSpeed = reducedSpeed;
	}
	else {
		// Turn Left: reduce left motor speed
		leftMotorSpeed = reducedSpeed;
		rightMotorSpeed = mappedSpeed;
	}

	// Set motor speeds
	analogWrite(ENA, leftMotorSpeed);
	analogWrite(ENB, rightMotorSpeed);
}



void setup() {
  // Delay to allow time for communication with bluetooth.
	delay(500);

	// Start communication with HM10 bluetooth module.
	softSerial.begin(9600);

	// Begin serial communication with computer.
	Serial.begin(9600);

	// Set pin modes
	setPins();

  arm.attach(9);
  sweeper.attach(A0);
	Serial.println("SETUP COMPLETE");
}

void loop() {
	// Refer to comment on top for step by step instructions.
//	doTesting(); // Comment this after testing.

	 driveControl(); // Uncomment this after testing.
   button = phone.getButton();
   int sliderId = phone.getSliderId();
   int sliderVal = phone.getSliderVal();
   delay(10);
   Serial.println(button);

 if (sliderId == 0) {
    arm.write (sliderVal);
    Serial.println(angle);
   }   // This will put the arm in a position where it is waiting to grab


   if (sliderId == 1) {
  
    sweeper.write (sliderVal);
    Serial.println(angle);
  }   // This will put the arm in a position where it is waiting to grab
 }
 




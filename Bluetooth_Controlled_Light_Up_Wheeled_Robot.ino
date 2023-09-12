#include <SoftwareSerial.h> // SoftwareSerial for serial communication with HM10 bluetooth module.
#include <ArduinoBlue.h> // ArduinoBlue bluetooth library

//LED pins
int LED_GREEN = 9;
int LED_RED = 2;
int LED_BLUE = 3;

// MOTOR LEFT PINS
const int ENA = 6;
const int IN1 = 4;
const int IN2 = 5;

// MOTOR RIGHT PINS
const int ENB = 11;
const int IN3 = 13;
const int IN4 = 12;


// MOTOR PARAMETERS
// Minimum PWM value of analogWrite to spin motor when robot is on the ground.
const int MINIMUM_MOTOR_SPEED = 40;


// HM10 BLUETOOTH MODULE PINS
// NOTE: Not all pins on your Arduino may support SoftwareSerial.
// Please check: https://www.arduino.cc/en/Reference/softwareSerial
const int BLUETOOTH_TX = 7;
const int BLUETOOTH_RX = 8;

SoftwareSerial softSerial(BLUETOOTH_TX, BLUETOOTH_RX); // Object for serial communication to HM 10 bluetooth module using ditigal pins.
ArduinoBlue phone(softSerial); // Object for smartphone robot control.

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
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
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
    red();
    return;
  }

  // Determine forwards or backwards.
  if (throttle > 0) {
    // Forward
    motorSetForward();
    green();
  }
  else {
    // Backward
    motorSetBackward();\
    blue();
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

  // Print Debug Info
  Serial.print("throttle: "); Serial.print(throttle);
  Serial.print("\tsteering: "); Serial.print(steering);
  Serial.print("\tmappedSpeed: "); Serial.print(mappedSpeed);
  Serial.print("\treducedSpeed: "); Serial.print(reducedSpeed);
  Serial.print("\tleftMotorSpeed: "); Serial.print(leftMotorSpeed);
  Serial.print("\trightMotorSpeed: "); Serial.println(rightMotorSpeed);
}

void doTesting() {
  // Uncomment to test.
  // motorSetForward();
  // motorSetBackward();
  // motorBrake();

  // Set motor speeds to max
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void setup() {
  delay(500);

  // Start communication with HM10 bluetooth module.
  softSerial.begin(9600);

  // Begin serial communication with computer.
  Serial.begin(9600);

  // Set pin modes
  setPins();

  Serial.println("SETUP COMPLETE");
}

void loop() {
  // Refer to comment on top for step by step instructions.

  driveControl(); // Uncomment this after testing.
}

void red(){
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void blue(){
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, LOW);
}

void green(){
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, HIGH);
}


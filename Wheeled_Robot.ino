/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Digvijay Patil
 * Last Modified 07/25/2023
 * Version 2.0
 *
 *
 * This project aims to educate the user on how to connect 
 * the motors of a 2WD car and program it through Arduino.
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */
 
//Pin Declarations
const int motorLeft_InputTwo = 4;
const int motorLeft_InputOne = 5;
const int motorLeft_Enable = 6;
const int motorRight_Enable = 11;
const int motorRight_InputOne = 12;
const int motorRight_InputTwo = 13;

//This setup section will be executed once
void setup() {
  //This initializes the serial monitors
  Serial.begin(9600);

  //This sets all pins as output pins
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // Sets the enable pins to HIGH, turning on the motors
  digitalWrite(motorLeft_Enable, HIGH);
  digitalWrite(motorRight_Enable, HIGH);
}

// This is the main loop the code will follow
void loop() {
  forward();
  delay(1000);
  turnright();
  delay(1000);
  turnleft();
  delay(1000);
  reverse();
  delay(1000);
}

//Defines functions that will cause the robot to drive in different directions
void forward() {
  Serial.println("Forward.");
  digitalWrite(motorLeft_InputOne, LOW);
  digitalWrite(motorLeft_InputTwo, HIGH);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, HIGH);
}

void reverse() {
  Serial.println("Reverse");
  digitalWrite(motorLeft_InputOne, HIGH);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, HIGH);
  digitalWrite(motorRight_InputTwo, LOW);
}

void turnright() {
  Serial.println("Turn Right");
  digitalWrite(motorLeft_InputOne, LOW);
  digitalWrite(motorLeft_InputTwo, HIGH);
  digitalWrite(motorRight_InputOne, HIGH);
  digitalWrite(motorRight_InputTwo, LOW);
}

void turnleft() {
  Serial.println("Turn Left");
  digitalWrite(motorLeft_InputOne, HIGH);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, HIGH);
}

void pause() {
  Serial.println("PAUSE");
  digitalWrite(motorLeft_InputOne, LOW);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, LOW);
}

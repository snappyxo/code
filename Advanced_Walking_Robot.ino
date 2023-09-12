/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Digvijay Patel
 * Last Modified 09/12/2023
 * By Josh Prentice
 * Version 2.0
 *
 *
 * This project aims to educate the user on how two motors can generate
 * the motion needed to create a walking robot
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */


// MOTOR LEFT PINS
const int ENA = 6;
const int IN1 = 4;
const int IN2 = 5;

// MOTOR RIGHT PINS
const int ENB = 11;
const int IN3 = 12;
const int IN4 = 13;



void setPins() {
  // Set pins as input or output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

//This setup section will be executed once
void setup() {
  //This initializes the serial monitors
 Serial.begin(9600);
 setPins();
 
}

// This is the main loop the code will follow
void loop() {

  forward();

}

//Defines forward functions that will cause the robot to walk forward
void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

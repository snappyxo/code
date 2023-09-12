/*
 ************************************************************************************
 * Mechanismic License
 *
 * Copyright (c) 2023 (Insert Coder's Name(s))
 *
 * Version 1.0
 *
 * This project aims to educate the user on how linkage mechanisms 
 * may be used in combination with motors to produce forward motion.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this code and associated documentation files (the "code"), to deal
 * in the code without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the code, and to permit persons to whom the code is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the code.
 *
 *
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


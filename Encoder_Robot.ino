/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Kamil Gozalov
 * Last Modified 07/24/2023
 * Version 2.0
 *
 *
 * This project aims to educate the user on how to use an encoder wheel and 
 * speed sensor to control a 2WD car by counting the number of wheel revolutions.
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */

//encoder pins
int leftEncoderPin = 2;
int rightEncoderPin = 3;

//const unsigned long MIN_PULSE_INTERVAL = 175; // Minimum number of time between pulses in microseconds 
//float pulsesPerRotation = 136;
float leftPulsesPerRotation = 278;
float rightPulsesPerRotation = 291;
int rspeed;

unsigned volatile long leftPulses = 0; // Variable to store number of pulses by speed sensor 
unsigned long leftTimedPulses = 0;
unsigned volatile long rightPulses = 0; 
unsigned long rightTimedPulses = 0;

const int MIN_PULSE_INTERVAL = 150;
unsigned long leftPrevTime; // Variable to store previous pulse time in microseconds 
unsigned long rightPrevTime; 
unsigned long previous;// previous time in milliseconds to calculate revolutions per second
unsigned long elapsed = 0;// time that has passed by in milliseconds to calculate revolutions per second
float leftRPS;// store revolutions per second
float rightRPS;

//motor pins
const int motorOne_InputOne = 4;
const int motorOne_InputTwo = 5;
const int motorOne_Enable = 6;
const int motorTwo_InputOne = 12;
const int motorTwo_InputTwo = 13;
const int motorTwo_Enable = 11;

int outputPins[] = {4,5,6,11,12,13};


void setup()
{
Serial.begin(9600);
  
  	for(int i = 0; i < 6; i++) //Assigns pinModes to the above pins
	{
	pinMode(outputPins[i], OUTPUT);
	}
  pinMode(leftEncoderPin, INPUT);
  pinMode(rightEncoderPin, INPUT);
  
//attach interrupt to encoderPin to execute the pulse function when the digital signal from the sensor changes  
attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftPulse, RISING);
attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightPulse, RISING);

digitalWrite(motorOne_Enable, HIGH);//Set enable pins to HIGH so that the motors would turn on
digitalWrite(motorTwo_Enable, HIGH);

leftPulses = 0; //initializes pulses to 0
rightPulses = 0;
}


void leftPulse() { // function for counting sensor pulses
  // increment pulses by 1 if sensor outputs a HIGH signal and more than 150 microseconds have passed
  if (micros() - leftPrevTime > MIN_PULSE_INTERVAL)
  {
    leftPulses++;
    leftTimedPulses++;
    leftPrevTime = micros();
  } 
} 

void rightPulse() {
  if (micros() - rightPrevTime > MIN_PULSE_INTERVAL)
  {
    rightPulses++;
    rightTimedPulses++;
    rightPrevTime = micros();
  } 
}

void loop() {
  Forward(10.0,200);
  delay(250);
  turnRight(245);
  delay(250);
  Forward(1.0,200);
  delay(250);
  turnLeft(245);
  delay(250);
  turnLeft(245);
  delay(250);
  turnLeft(245);
  delay(250);
}


void stop() {
  digitalWrite(motorOne_Enable, HIGH);
  digitalWrite(motorTwo_Enable, HIGH);
  digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, LOW);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, LOW);
}

void data() {
  unsigned long current = millis();// record current time in milliseconds
    if (elapsed >= 125) { // if the amount of time elapsed is 1 second
      previous = current; //set the previous time to current time
      leftRPS = 8*(leftTimedPulses / leftPulsesPerRotation); //then calculate the rotational speed
      rightRPS =  8*(rightTimedPulses / rightPulsesPerRotation);
      Serial.print("Left RPS: ");
      Serial.println(leftRPS);
      Serial.print("Right RPS: ");
      Serial.println(rightRPS);
      Serial.print("Left Pulses: ");
      Serial.println(leftPulses);
      Serial.print("Right Pulses: ");
      Serial.println(rightPulses);

     rightTimedPulses = 0;// reset pulses
     leftTimedPulses = 0; 
    }
    elapsed = current - previous;// update elapsed time
}

void Forward(float revs, int Speed) {
  digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, HIGH);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, HIGH);
    Go(revs, Speed);
}

void Reverse(float revs, int Speed) {
  digitalWrite(motorOne_InputOne, HIGH);
  digitalWrite(motorOne_InputTwo, LOW);
  digitalWrite(motorTwo_InputOne, HIGH);
  digitalWrite(motorTwo_InputTwo, LOW);
    Go(revs, Speed);
}

void Go(float revs, int Speed) {
  rspeed = Speed;
  while (leftPulses/leftPulsesPerRotation < revs && rightPulses/rightPulsesPerRotation < revs) {
        if(rightRPS > (leftRPS+0.03)) {
          rspeed-=3;
        } else if(leftRPS > (rightRPS+0.03)) {
          rspeed+=3;
        } 
        if (leftPulses/leftPulsesPerRotation < revs) {
          analogWrite(motorOne_Enable, Speed);
        } else {
          digitalWrite(motorOne_InputOne, LOW);
          digitalWrite(motorOne_InputTwo, LOW);
        }
        if (rightPulses/rightPulsesPerRotation < revs) {
          analogWrite(motorTwo_Enable, rspeed);
        } else { 
          digitalWrite(motorTwo_InputOne, LOW);
          digitalWrite(motorTwo_InputTwo, LOW);
        }
    data();
    delay(124);
  }
stop();
leftPulses = 0;
rightPulses = 0;
}

void turnRight(int Speed) {
  analogWrite(motorOne_Enable, Speed);
  digitalWrite(motorTwo_Enable, HIGH);
  digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, HIGH);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, LOW); 
    while(leftPulses/leftPulsesPerRotation < 0.9) {}
  stop();
  leftPulses = 0;
  rightPulses = 0;
}

void turnLeft(int Speed) {
  analogWrite(motorOne_Enable, HIGH);
  digitalWrite(motorTwo_Enable, Speed);
  digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, LOW);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, HIGH); 
    while(rightPulses/rightPulsesPerRotation < 0.9) {}
  stop();
  leftPulses = 0;
  rightPulses = 0;
}
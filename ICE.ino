/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Kamil Gozalov
 * Last Modified 09/12/2023
 * By Josh Prentice
 * Version 2.0
 *
 *
 * This project aims to educate the user on how an Internal Combustion Engine 
 * funtions
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */
 
const int motorOne_InputOne = 4;
const int motorOne_InputTwo = 5;
const int motorOne_Enable = 6;

const int motorTwo_InputOne = 12;
const int motorTwo_InputTwo = 13;
const int motorTwo_Enable = 11;

int speed;
int outputPins[] = {4,5,6,11,12,13};

void setup() {
Serial.begin(9600);
  
  	for(int i = 0; i < 6; i++) //Assigns pinModes to the above pins
	{
	pinMode(outputPins[i], OUTPUT);
	}

digitalWrite(motorOne_Enable, HIGH);//Set enable pins to HIGH so that the motors would turn on
digitalWrite(motorTwo_Enable, HIGH);
}
 
void loop() {
  crankSpeed(255);
  valveSpeed(200);
}

void crankSpeed(int Speed) {
  analogWrite(motorOne_Enable, Speed);
  digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, HIGH);
}

void valveSpeed(int Speed, int time) {
  analogWrite(motorTwo_Enable, Speed);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, HIGH);
}

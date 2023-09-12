/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Chad Carney
 * Last Modified 09/12/2023
 * By Josh Prentice
 * Version 2.0
 *
 *
 * This project aims to educate the user on how two photocells can drive a car
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


const int rightSense = A1;
const int leftSense = A2;

int a;
int b;
int rightVal;
int leftVal;
//This setup section will be executed once
void setup() {
  //This initializes the serial monitors
  Serial.begin(9600);


  // Sets the enable pins to HIGH, turning on the motors
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(motorLeft_Enable, HIGH);
  digitalWrite(motorRight_Enable, HIGH);

   rightVal=analogRead(A1);
   leftVal=analogRead(A0);

  calibrate();



}

// This is the main loop the code will follow
void loop()

 {

   rightVal=analogRead(A1)/a;
   leftVal=analogRead(A0)/b;

   Serial.println(rightVal);
   Serial.println(leftVal);
  

  if(rightVal*.8>leftVal)
  {
    turnright();
  }
  else if(leftVal*.8>rightVal)
  {
    turnleft();
  }

  else
  {
    forward();
  }

  
}

void calibrate()
{
  rightVal=analogRead(A1);
  leftVal=analogRead(A0);

  if (rightVal>leftVal)
  {
    a=(rightVal/leftVal);
    b=1;
  }

  if (leftVal>rightVal)
  {
    b=(leftVal/rightVal);
    a=1;
  }

  if (a>5)
  {
    a=5;
  }

  if (b>5)
  {
    b=5;
  }

}

//Defines functions that will cause the robot to drive in different directions
void forward() {
  Serial.println("Forward.");
  digitalWrite(motorLeft_InputOne, HIGH);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, HIGH);
}



void turnright() {
  //Serial.println("Turn Right");
  digitalWrite(motorLeft_InputOne, HIGH);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, HIGH);
  digitalWrite(motorRight_InputTwo, LOW);

}

void turnleft() {
  //Serial.println("Turn Left");
  digitalWrite(motorLeft_InputOne, LOW);
  digitalWrite(motorLeft_InputTwo, HIGH);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, HIGH);

}

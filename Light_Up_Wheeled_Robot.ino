/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Digvijay Patil
 * Last Modified 07/25/2023 
 * By Kamil Gozalov
 * Version 2.1
 *
 *
 * This project aims to educate the user on how to connect
 * an LED and have it correlate to the motion of a 2WD car.
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */

//Pin declarations
int LED_GREEN = 3;
int LED_RED = 2;
const int motorLeft_InputTwo = 4;
const int motorLeft_InputOne = 5;
const int motorLeft_Enable = 6;
const int motorRight_Enable = 11;
const int motorRight_InputOne = 12;
const int motorRight_InputTwo = 13;

 // put your setup code here, to run once:
void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(motorLeft_Enable, HIGH);
  digitalWrite(motorRight_Enable, HIGH);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

// put your main code here, to run repeatedly:
void loop() {
  digitalWrite(LED_GREEN, HIGH); //green for forward
  forward();
  delay(1000);

  digitalWrite(LED_GREEN, LOW); //red for stoping
  digitalWrite(LED_RED, HIGH);
  pause();
  delay(1000);

  digitalWrite(LED_RED, LOW);
  turnleft();
  delay(1000);
  turnright();
  delay(1000);

  reverse(); //flashing green for reverse
  for(int i=0, i<=1000, i+=500) {
    digitalWrite(LED_GREEN, HIGH);
    delay(250);
    digitalWrite(LED_GREEN, LOW);
    delay(250);
  }
}

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

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
 * This project aims to educate the user on how an ultrasonic sensor can detect
 * different heights to drive a robot foward and backward
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */


//Pin Declarations

int trig = 7; // attach pin 7 to Trig
int echo = 8; //attach pin 8 to Echo

// Left and Right defined as if you were looking at car from back
const int motorRight_Enable = 6;
const int motorRight_InputOne = 4;
const int motorRight_InputTwo = 5;

void setup() {
// initialize serial communication:
Serial.begin(9600);

//Declares that all pins connected to the motors will be outputs
pinMode(motorRight_Enable, OUTPUT);
pinMode(motorRight_InputOne, OUTPUT);
pinMode(motorRight_InputTwo, OUTPUT);

//Turns on both of the motors by setting enable pins to HIGH
digitalWrite(motorRight_Enable, HIGH);
}

void loop() {

 long duration, inches, cm;
 pinMode(trig, OUTPUT);
//send a short LOW pulse first
 digitalWrite(trig, LOW);
 delayMicroseconds(2);

 //send a 5 microsecond HIGH pulse, specified by datasheet
 digitalWrite(trig, HIGH);
 delayMicroseconds(5);

 //end high pulse
 digitalWrite(trig, LOW);

 //now set the pingPin to the input mode and listens for echo, records in microseconds
 pinMode(echo,INPUT);
 
 duration = pulseIn(echo, HIGH);

 // convert the time into a distance
 inches = microsecondsToInches(duration);
 cm = microsecondsToCentimeters(duration);
 
 Serial.print(inches);
 Serial.print("in, ");
 Serial.print(cm);
 Serial.print("cm");
 Serial.println();
 delay(10);

//Commands robot to drive forward

 if (cm < 15) {
  reverse();
  delay(100);
 }

 if (cm < 30 && cm > 16)
 {
  forward();
  delay(100);
 }

 else
 {
  pause();
  delay(100);
 }
}

void forward(){
 //Commands one motor to rotate CW and the other to rotate CCW
 Serial.println("Forward.");
 digitalWrite(motorRight_InputOne, HIGH);
 digitalWrite(motorRight_InputTwo, LOW);
}

void pause() {
  Serial.println("Pause");
  digitalWrite(motorRight_InputOne, LOW); 
  digitalWrite(motorRight_InputTwo, LOW); 
}

void reverse() {
  Serial.println("Reverse");
  digitalWrite(motorRight_InputOne, LOW); 
  digitalWrite(motorRight_InputTwo, HIGH);
}

long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}

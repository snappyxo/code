/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Chad Carney
 * Last Modified 09/12/2023
 * Version 2.0
 *
 *
 * This project aims to educate the user on how two photocells and two servos can 
 * automatically launch a foam ball
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */
 
#include<Servo.h>
Servo servo1;
Servo servo2;

int angle1=0;
int angle2=5;

double a=1;
double b=1;


void setup() 
{
  
pinMode(3,OUTPUT); //red
pinMode(5,OUTPUT); //green
pinMode(6,OUTPUT); //blue

Serial.begin(9600);

servo1.attach(9);
servo2.attach(10);
servo1.write(angle1);
servo2.write(angle2);

Calibrate();

}


void loop() 
{
//standby
analogWrite(5,255);
analogWrite(3,0);
analogWrite(6,0);

//photocell measurements
int ambientLight=analogRead(A1)/a;
int lightVal=analogRead(A0)/b;

//Serial.print("Light");
//Serial.println(lightVal);
//Serial.print("Ambient");
//Serial.println(ambientLight);

 //Serial.println(a);
 //Serial.println(b);
 

int a1Light=analogRead(A1);
int b1Light=analogRead(A0);
delay(50);
int a2Light=analogRead(A1);
int b2Light=analogRead(A0);

//if both sensors detect a similar change at the same time, then the environment must have changed, so we recalibrate for it
if(abs(a1Light-a2Light) > 5 && abs(b1Light-b2Light) > 5 )  
{
  Calibrate();
  Calibrate();

  //calibrates twice for redundancy
}


  if (lightVal < (ambientLight/1.3))
  {
    
  //ball detected
  analogWrite(3, 110);
  analogWrite(6, 0);
  analogWrite(5,255);
  delay(1000);
  
 //recheck sensors to determine if ball is still in place
  int ambientLight1=analogRead(A1)/a;
  int lightVal1=analogRead(A0)/b;

  if(lightVal1 < (ambientLight1/1.3)) 
  {
    Launch();
    delay(500);
    Calibrate();
  }
}

}

void Calibrate()
{
  
 double ambientLight_a=analogRead(A1);
 double lightVal_a=analogRead(A0);
 
//calibration script

   if(lightVal_a<ambientLight_a)
   {
    
    b=1;
    a=ambientLight_a/lightVal_a;
      if(a>5)
        {
          a=5;
        }

   }
   if(ambientLight_a<lightVal_a)
   {
    
   a=1;
   b=lightVal_a/ambientLight_a;
   if(b>5)
        {
          b=5;
        }
   
   }
 //Serial.println("Calibrated");

}

void Launch()
 {
  analogWrite(3, 255);
  analogWrite(5, 0);
  analogWrite(6, 0);
  
  delay(500);
  servo1.write(180);
  delay(1000);
  servo2.write(80);

  //resetting
  delay(500);
  
  analogWrite(3, 0);
  analogWrite(5, 0);
  analogWrite(6, 255);
  
  delay(200);
  servo1.write(0);
  delay(1000);
  servo2.write(5);
  
  
 
 }

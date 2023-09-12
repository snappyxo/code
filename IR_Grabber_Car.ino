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
 * This project aims to educate the user on how two servos can pick up and move
 * a foam ball
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */
 
#include <IRremote.hpp>
#include <Arduino.h>
#include<Servo.h>

Servo servo1;
Servo servo2;
int angle1=180;
int angle=0;

int motorDelay = 70;


// MOTOR LEFT PINS
const int ENA = 6;
const int IN1 = 4;
const int IN2 = 5;

// MOTOR RIGHT PINS
const int ENB = 11;
const int IN3 = 12;
const int IN4 = 13;

  
void setup() 
{
servo1.attach(9);
servo2.attach(10);
angle1=180;
angle=0;

 Serial.begin(9600);
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENA,255);
  analogWrite(ENB,255);
  
   
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(3, DISABLE_LED_FEEDBACK);
  servo1.write(angle);
  servo2.write(angle1);
}

void loop() {

    if (IrReceiver.decode()) {

        IrReceiver.start();
    
        if (IrReceiver.decodedIRData.command == 0x45) 
        {
            
            servoUp();
           //1
        } 
       
        else if (IrReceiver.decodedIRData.command == 0x47) 
        {
            //3
             servoOpen();
        } 
        else if (IrReceiver.decodedIRData.command == 0x44) 
        {
            //4
            servoDown();
        }
     
        else if (IrReceiver.decodedIRData.command == 0x43) 
        {
           //6
             servoClose();
        }
      
        else if (IrReceiver.decodedIRData.command == 0x19)
        {
          
              angle=0;
              servo1.write(angle);
              angle1=180;
              servo2.write(angle1);
            
        }
         
        else if (IrReceiver.decodedIRData.command == 0x18) 
        {
          motorSetForward();
           
        }
        else if (IrReceiver.decodedIRData.command == 0x52) 
        {
          motorSetBackward();
            
        }
        else if (IrReceiver.decodedIRData.command == 0x8)
        {
          TurnLeft();
           
        }
        else if (IrReceiver.decodedIRData.command == 0x5A)
        {
          TurnRight();
            
        }

    }
}

void motorSetForward() 
{
 
  Serial.println("Forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(motorDelay);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Do not write the motor speeds on this function. It simply configures the motor controller.
}

void motorSetBackward() 
{
  Serial.println("Reverse");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(motorDelay);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  // Do not write the motor speeds on this function. It simply configures the motor controller.
}


void TurnLeft() 
{
  Serial.println("Left");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(motorDelay);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void TurnRight()
{
  Serial.println("Right");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(motorDelay);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void servoUp()
{
    angle=angle;
    angle=angle+3;
      servo1.write(angle);
      Serial.println(angle);
      delay(20);
     if(angle>100)
     {
       angle=100;
     }
}

void servoDown()
{
    angle=angle;
     angle=angle-3;
      servo1.write(angle);
      Serial.println(angle);
      delay(20);
    
    if (angle<0)
    {
      angle=0;
    } 
}


void servoOpen()
{
  angle1=angle1;
  angle1=angle1-3;
      servo2.write(angle1);
      Serial.println(angle1);
      delay(20);
        
    if(angle1<100)
    {
      angle1=100;
    }
    
}

void servoClose()
{
    angle1=angle1;
    angle1=angle1+3;
      servo2.write(angle1);
      Serial.println(angle1);
      delay(20);
        
    if(angle1>180)
    {
      angle1=180;
    }
     
}

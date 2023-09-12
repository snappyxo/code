/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Renix Calle
 * Last Modified 07/31/2023
 * Version 2.0
 *
 *
 * This project aims to educate the user on how to control a 2WD car 
 * using bluetooth as well as an excavator mechanism using finite servos.
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */

#include <IRremote.h>
#include <Servo.h>


//Declares Servos and Parameters
Servo arm;
Servo sweeper;
int sweeperAngle = 0;
int armAngle = 0;
const int increment = 10;
const int maxAngle = 180;
const int minAngle = 0;

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
}


void setup() {
	delay(500);

	// Begin serial communication with computer.
	Serial.begin(9600);

	// Set pin modes
	setPins();
  // Enables Left and Right Motors
  digitalWrite(ENA, HIGH);
	digitalWrite(ENB, HIGH);

  arm.attach(9);
  sweeper.attach(10);
  Serial.begin(9600);
  arm.write(armAngle);
  sweeper.write(sweeperAngle);


 IrReceiver.begin(8, DISABLE_LED_FEEDBACK);

 Serial.print(F("Ready to receive IR signals of protocols: "));
 printActiveIRProtocols(&Serial);
	Serial.println("SETUP COMPLETE");
}

// Configures the motor controller to stop the motors.
void Brake() {
  Serial.println ("Stop");
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
	
}

// Configures the motor controller to have the robot move forward.
void Forward() {
  Serial.println ("Forward");
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);
  delay(150);
  digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
	// Do not write the motor speeds on this function. It simply configures the motor controller.
}

// Configures the motor controller to have the robot move backwards.
void Reverse() {
  Serial.println ("Reverse");
  digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);
  delay(150);
  digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
	// Do not write the motor speeds on this function. It simply configures the motor controller.
}
/* TURN RIGHT */
void Right(){
  Serial.println ("Left");
  digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);
  delay(150);
  digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
}

/* TURN LEFT */
void Left(){
  Serial.println ("Turn Right") ;
  digitalWrite(IN1, LOW);
	digitalWrite(IN2, HIGH);
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);
  delay(150);
  digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
  
}

//Raises the arm servo up to the maximum angle 
void Raise(){
 if (armAngle < maxAngle) {
    armAngle += increment;
    if (armAngle > maxAngle) {
      armAngle = maxAngle;
    }
    arm.write(armAngle);
    Serial.println(armAngle);

}
}

//Lower arm servo to minimum angle.
void Lower(){
  if (armAngle > minAngle) {
    armAngle -= increment;
    if (armAngle < minAngle) {
      armAngle = minAngle;
    }
    arm.write(armAngle);
    Serial.println(armAngle);
 
}
}

// Opens sweeper Servo to maximum angle
void Open(){
  if (sweeperAngle < maxAngle) {
    sweeperAngle += increment;
    if (sweeperAngle > maxAngle) {
      sweeperAngle = maxAngle;
    }
    sweeper.write(sweeperAngle);
    Serial.println(sweeperAngle);
   
  }
}

//Closes sweeper Servo to minimum angle
void Close(){
  if (sweeperAngle > minAngle) {
    sweeperAngle -= increment;
    if (sweeperAngle < minAngle) {
      sweeperAngle = minAngle;
    }
    sweeper.write(sweeperAngle);
    Serial.println(sweeperAngle);

  }
}

// Main loop which detects users inputs and responds based on which button is pressed on the IR remote.
void loop() {
  // Decodes Infrared Signal from Remote
    if (IrReceiver.decode()) {
      // Enable receiving of the next value
        IrReceiver.resume(); 
        Serial.println(IrReceiver.decodedIRData.command);

  
        if (IrReceiver.decodedIRData.command == 0x45) {
            Serial.println(1);
            Raise();
        } 
        else if (IrReceiver.decodedIRData.command == 0x46) {
            Serial.println(2);
            Lower();
        } 
        else if (IrReceiver.decodedIRData.command == 0x47) {
            Serial.println(3);
            Open();
        } 
        else if (IrReceiver.decodedIRData.command == 0x44) {
            Serial.println(4);
            Close();
        }
        else if (IrReceiver.decodedIRData.command == 0x18) {
            Serial.println("Forward");
            Forward();

        }
        else if (IrReceiver.decodedIRData.command == 0x52) {
            Serial.println("Reverse");
            Reverse();
        }
        else if (IrReceiver.decodedIRData.command == 0x8) {
            Serial.println("Left");
            Left();
        }
        else if (IrReceiver.decodedIRData.command == 0x5A) {
            Serial.println("Right");
            Right();
        }
        else if (IrReceiver.decodedIRData.command == 0x1C) {
            Serial.println("OK");
            Brake();
        }

    }
    
}




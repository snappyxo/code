/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Joseph Traverso
 * Last Modified 09/12/2023 by Renix Calle
 * Version 2.1
 *
 *
 * This code aims to educate the user on how to use various sensors through 
 * an interactive game. User inputs affect the readings of each sensor and push the user 
 * to test their reaction time.
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */



String buttonState; String twistItState; String slideItState; String pinchItState;
float Temperature;
float Temperature_ambient;
float Temperature_pinch;
float Voltage_mv;
float Voltage_ambient;
float Voltage_pinch;
float Calibration;
float timestart = millis();
float timeend = timeend;
float Time = 2000;
bool lost = false;
int randomVar;
int ii = 0;
int Score;
void setup(){
 
 pinMode(13,INPUT);
 pinMode(12,INPUT);
 pinMode(11,INPUT);
 pinMode(A0,INPUT);
 pinMode(A1,INPUT);
 pinMode(A2,INPUT);
 pinMode(10,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(6,OUTPUT);
 Serial.begin(9600);
 
 
  Serial.println("Please ensure all buttons and switches are returned to the beginning orientation");
 
 
  while (digitalRead(13) == HIGH || digitalRead(12) == HIGH || digitalRead(11) == HIGH) {
 
 
  if (digitalRead(13) == HIGH){
    Serial.println("Please do not press the button while the game is being setup");
    digitalWrite(10,HIGH);
    delay(200);
    digitalWrite(10,LOW);
    delay(200);
    digitalWrite(10,HIGH);
    delay(200);
    digitalWrite(10,LOW);
    delay(200);
    digitalWrite(10,HIGH);
    delay(200);
    digitalWrite(10,LOW);
  }
  delay(1000);

  if (digitalRead(12) == HIGH) {
    Serial.println("Please rotate the potentiometer to the untwisted position");
    digitalWrite(9,HIGH);
    delay(200);
    digitalWrite(9,LOW);
    delay(200);
    digitalWrite(9,HIGH);
    delay(200);
    digitalWrite(9,LOW);
    delay(200);
    digitalWrite(9,HIGH);
    delay(200);
    digitalWrite(9,LOW);
  }
 
  delay(1000);
 
  if (digitalRead(11) == HIGH) {
    Serial.println("Please return the switch to the off position");
    digitalWrite(8,HIGH);
    delay(200);
    digitalWrite(8,LOW);
    delay(200);
    digitalWrite(8,HIGH);
    delay(200);
    digitalWrite(8,LOW);
    delay(200);
    digitalWrite(8,HIGH);
    delay(200);
    digitalWrite(8,LOW);
  }
   delay(1000);
   
  }
 
 Serial.println("Get Ready! The Game is starting in:");
 Serial.println("3");
 delay(1000);
 Serial.println("2");
 delay(1000);
 Serial.println("1");
 delay(1000);

}

void loop(){
 

  //Serial.println("Button is " + buttonState + "          " + "Potentiometer is " + twistItState + "        " + "Switch is " + slideItState + "              " + "Thermistor is " + pinchItState);
  //Serial.println(Temperature);
 
  if (lost==false){
    int randomNumber = random(1, 5);  // Generate a random number between 1 and 5
     if (randomNumber == 1) {
    pinchIt();
  } else if (randomNumber == 2) {
    twistIt();
  } else if (randomNumber == 3) {
    slideIt();
  } else if (randomNumber == 4) {
    pushIt();
  }
  ii = ii+1;
if (ii % 5 == 0){
Congratulations();
Serial.println("Nice Going! You beat the round");
delay(1000);
Serial.println("Get Ready!");
Time = Time*0.95;
}
 delay(1000);
  }
   
  }
  
  void Count(){
  
  }

  void pushIt(){
    Serial.println("Push it!");
   
    digitalWrite(10,HIGH);
    timestart = millis();
    timeend = millis();
   
    while(digitalRead(13) == LOW){
      timeend = millis();
      Timer();
      if ((timeend-timestart)> Time){
      lost = true;
      Serial.println("Too Slow! You Lost!");
        Lost_tone();
        delay(100);
        Serial.println(String("Final Score = ") + ii + " correct reactions");
        break;
      }
    }  
    digitalWrite(10,LOW);
  }
 
void twistIt(){
  Serial.println("Twist it!");
    digitalWrite(9,HIGH);
    timestart = millis();
    timeend = millis();
    while(digitalRead(12) == LOW){
      timeend = millis();
      Timer();
      if ((timeend-timestart)> Time){
      lost = true;
      Serial.println("Too Slow! You Lost!");
        Lost_tone();
        delay(100);
        Serial.println(String("Final Score = ") + ii + " correct reactions");
        break;
      }
    }
    digitalWrite(9,LOW);
  }

void slideIt(){
  Serial.println("Slide it!");
    digitalWrite(8,HIGH);
    timestart = millis();
    timeend = millis();
    while(digitalRead(11) == LOW){
      timeend = millis();
      Timer();
      if ((timeend-timestart)> Time){
      lost = true;
      Serial.println("Too Slow! You Lost!");
      Lost_tone();
      delay(100);
      Serial.println(String("Final Score = ") + ii + " correct reactions");
        break;
      }
    }
    digitalWrite(8,LOW);
  }

void pinchIt(){
  Serial.println("Pinch it!");
    digitalWrite(7,HIGH);
    timestart = millis();
    timeend = millis();
    while(analogRead(A2) > 0.90*analogRead(A1)){
      timeend = millis();
      Timer();
      if ((timeend-timestart)> Time){
      lost = true;
      Serial.println("Too Slow! You Lost!");
        Lost_tone();
        delay(100);
        Serial.println(String("Final Score = ") + ii + " correct reactions");
        break;
      }
    }
    delay(200);
    digitalWrite(7,LOW);
  }
 

void Lost_tone()
{
  tone(6,293.66);
  delay(400);
  tone(6,277.18);
  delay(400);
  tone(6,261.63);
  delay(400);
  tone(6,246.94);
  delay(400);
  noTone(6);
}


void Timer()
{
  tone(6, 1000);  // Turn on the buzzer at 1000 Hz
  delay(Time/6);  // Keep the buzzer on for 100 milliseconds
  noTone(6);  // Turn off the buzzer
  delay(Time/6);  // Delay between ticks
}



 void Congratulations() {
  tone(6, 523);  // C5
  delay(250);
  tone(6, 659);  // E5
  delay(250);
  tone(6, 783);  // G5
  delay(250);
  tone(6, 659);  // E5
  delay(250);
  tone(6, 783);  // G5
  delay(250);
  tone(6, 880);  // A5
  delay(500);
  noTone(6);
}

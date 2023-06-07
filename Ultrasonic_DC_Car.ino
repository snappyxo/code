

//Pin Declarations

int trig = 7; // attach pin 7 to Trig
int echo = 8; //attach pin 8 to Echo

// Left and Right defined as if you were looking at car from back
const int motorLeft_InputTwo = 4;
const int motorLeft_InputOne = 5;
const int motorLeft_Enable = 6;
const int motorRight_Enable = 11;
const int motorRight_InputOne = 12;
const int motorRight_InputTwo = 13;

void setup() {
// initialize serial communication:
Serial.begin(9600);

//Declares that all pins connected to the motors will be outputs
pinMode(motorLeft_InputTwo, OUTPUT);
pinMode(motorLeft_InputOne, OUTPUT);
pinMode(motorLeft_Enable, OUTPUT);
pinMode(motorRight_Enable, OUTPUT);
pinMode(motorRight_InputOne, OUTPUT);
pinMode(motorRight_InputTwo, OUTPUT);

\

//Turns on both of the motors by setting enable pins to HIGH
digitalWrite(motorLeft_Enable, HIGH); 
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
 forward();

 int randint = random(0,2);// // randomly choose whether to turn left or right if an obstacle is encountered; in this code, 0 is turning right and 1 is turning left

 

//When robot becomes to close to the obstacle; Robot will reverse, turn right, then continue forward
 if (inches < 7 && randint == 0) {
  reverse(); 
  delay(500); 
  pause();
  delay(500);
  turnright(); 
  delay(200); 
  forward();
}

//When robot becomes to close to the obstacle; Robot will reverse, turn left, then continue forward
 if (inches < 7 && randint == 1) {
  reverse(); 
  delay(500); 
  pause();
  delay(500);
  turnleft(); 
  delay(200); 
  forward();
}




}


void forward(){
 //Commands one motor to rotate CW and the other to rotate CCW
 Serial.println("Forward.");
 digitalWrite(motorLeft_InputOne, HIGH);
 digitalWrite(motorLeft_InputTwo, LOW);
 digitalWrite(motorRight_InputOne, HIGH);
 digitalWrite(motorRight_InputTwo, LOW);
}

void reverse() {
  Serial.println("Reverse");
  digitalWrite(motorLeft_InputOne, LOW); 
  digitalWrite(motorLeft_InputTwo, HIGH); 
  digitalWrite(motorRight_InputOne, LOW); 
  digitalWrite(motorRight_InputTwo, HIGH); 
  
}

void turnleft() {
  Serial.println("Turn Left");
  digitalWrite(motorLeft_InputOne, HIGH); 
  digitalWrite(motorLeft_InputTwo, LOW); 
  digitalWrite(motorRight_InputOne, LOW); 
  digitalWrite(motorRight_InputTwo, HIGH); 
  
}

void turnright() {
  Serial.println("Turn Right");
  digitalWrite(motorLeft_InputOne, LOW); 
  digitalWrite(motorLeft_InputTwo, HIGH); 
  digitalWrite(motorRight_InputOne, HIGH); 
  digitalWrite(motorRight_InputTwo, LOW); 
  
}

void pause() {
  Serial.println("Pause");
  digitalWrite(motorLeft_InputOne, LOW); 
  digitalWrite(motorLeft_InputTwo, LOW); 
  digitalWrite(motorRight_InputOne, LOW); 
  digitalWrite(motorRight_InputTwo, LOW); 
  
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

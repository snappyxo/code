const int trig = A0;
const int echo = A1;

const int motorOne_InputOne = 4;
const int motorOne_InputTwo = 5;
const int motorOne_Enable = 6;

const int motorTwo_InputOne = 12;
const int motorTwo_InputTwo = 13;
const int motorTwo_Enable = 11;

int speed;
int outputPins[] = {A0,4,5,6,11,12,13};

void setup()
{
Serial.begin(9600);
  
  	for(int i = 0; i < 7; i++) //Assigns pinModes to the above pins
	{
	pinMode(outputPins[i], OUTPUT);
	}
  pinMode(echo, INPUT);

digitalWrite(motorOne_Enable, HIGH);//Set enable pins to HIGH so that the motors would turn on
digitalWrite(motorTwo_Enable, HIGH);
}
 
void loop()
{
long duration, distance;
pulseIn(echo,LOW);

  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);

duration = pulseIn(echo,HIGH);
distance=microsecondsToInches(duration);

if(distance>3) {
    Go(255,0);
  } else {
    Serial.println("Object Detected");
    digitalWrite(motorOne_Enable, LOW);
    digitalWrite(motorTwo_Enable, LOW);
    delay(200);
  }
}
  
long microsecondsToInches(long microseconds) {
  return microseconds/74/2; }

void Go(int Speed, int time) {
analogWrite(motorOne_Enable, Speed);
analogWrite(motorTwo_Enable, Speed);
digitalWrite(motorOne_InputOne, HIGH);
digitalWrite(motorOne_InputTwo, LOW);
digitalWrite(motorTwo_InputOne, LOW);
digitalWrite(motorTwo_InputTwo, HIGH);
delay(time);
}
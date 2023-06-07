int LED_GREEN = 3;
int LED_RED = 2;
const int motorLeft_InputTwo = 4;
const int motorLeft_InputOne = 5;
const int motorLeft_Enable = 6;
const int motorRight_Enable = 11;
const int motorRight_InputOne = 12;
const int motorRight_InputTwo = 13;

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
  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);
  delay(500);

  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
  forward();
  
  // put your main code here, to run repeatedly:

}

void forward() {
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

void turnright() {
  Serial.println("Turn Right");
  digitalWrite(motorLeft_InputOne, HIGH);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, HIGH);

}

void turnleft() {
  Serial.println("Turn Left");
  digitalWrite(motorLeft_InputOne, LOW);
  digitalWrite(motorLeft_InputTwo, HIGH);
  digitalWrite(motorRight_InputOne, HIGH);
  digitalWrite(motorRight_InputTwo, LOW);

}

void pause() {
  Serial.println("PAUSE");
  digitalWrite(motorLeft_InputOne, LOW);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, LOW);
  digitalWrite(motorRight_InputTwo, LOW);

}


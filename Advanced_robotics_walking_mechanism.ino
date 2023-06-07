

//Pin Declarations


const int motorLeft_InputTwo = 4;
const int motorLeft_InputOne = 5;
const int motorLeft_Enable = 6;
const int motorRight_Enable = 11;
const int motorRight_InputOne = 12;
const int motorRight_InputTwo = 13;

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
}

// This is the main loop the code will follow
void loop() {
  



  forward();






}


//Defines forward functions that will cause the robot to walk forward
void forward() {
  Serial.println("Forward.");
  digitalWrite(motorLeft_InputOne, HIGH);
  digitalWrite(motorLeft_InputTwo, LOW);
  digitalWrite(motorRight_InputOne, HIGH);
  digitalWrite(motorRight_InputTwo, LOW);
}


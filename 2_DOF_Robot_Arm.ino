//Libraries
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include <Servo.h>

//Declares Servos
Servo shoulder;
Servo hand;



int shoulderPos = 0;
int handPos = 0;
int angle;

// The bluetooth tx and rx pins must be supported by software serial.
// Visit https://www.arduino.cc/en/Reference/SoftwareSerial for unsupported pins.
// Bluetooth TX -> Arduino D7
// Bluetooth RX -> Arduino D8
const int BLUETOOTH_TX_PIN = 7;
const int BLUETOOTH_RX_PIN = 8;

SoftwareSerial bluetooth(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
ArduinoBlue phone(bluetooth); // pass reference of bluetooth object to ArduinoBlue constructor.

int button;
bool grab;


void setup() {
  // Start serial monitor at 9600 bps.
  Serial.begin(9600);

  // Declares pins associated with servos
  shoulder.attach(9);
  hand.attach(10);

  // Start bluetooth serial at 9600 bps.
  bluetooth.begin(9600);

  // delay just in case bluetooth module needs time to "get ready".
  delay(100);


  Serial.println("setup complete");
  //shoulder.write(90);
  //hand.write(120);
  Serial.println("Attatch the arm so that its pointing upward");
  Serial.println("Attatch the hand so that it is at a fully open position");
  Serial.println("Ready to use");
}



void loop() {

  // Detects which button on ArduinoBlue app has been pressed
  button = phone.getButton();
  delay(10);
  Serial.println(button);


  // This will put the arm in a position where it is waiting to grab
  if (button == 1) {

    READYGRAB();

    button = 0 ;
  }
  //
  if (button == 2) {
    //    // This will execute the grabbing motion
    GRAB();
  }
  if (button == 3) {
    //    //This will raise the ball that has been grabbed upwards.
    RAISEARM();
  }
}


//Functions for different grabbing motions
void READYGRAB() {

  shoulder.write(180);
  delay(1000);
  hand.write(180) ;

}

void GRAB() {
  // This will execute the grabbing motion
  hand.write(100);

}

void RAISEARM() {
  //This will raise the ball that has been grabbed upwards.
  hand.write(100);
  delay(1000);
  shoulder.write(110);
}

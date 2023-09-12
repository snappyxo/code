/*
 ************************************************************************************
 * Mechanismic Inc.
 *
 * Created 2023
 * By Maximilian Blakely
 * Last Modified 08/2/2023
 * Version 2.0
 *
 *
 * This project aims to educate the user on how to connect use a PIR sensor and a 
 * Piezzo buzzer to detect a person and play a song when they're detected
 * 
 *
 * https://snappyxo.io/
 
 ************************************************************************************
 */

/* Example code to create an alarm system with HC-SR501 PIR motion sensor, buzzer and Arduino. More info: www.www.makerguides.com */
#include "Notes.h"

// Define connection pins:
int buzzerPin = 5;
int pirPin = 2;

// Create variables:
int val = 0;
int vall = 0;
bool motionState = false;
int valPrev =0;

void setup() 
{
  // Configure the pins as input or output:
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);

  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Serial.println("Calibrating");

  for (int i=0; i<10; i++){
    delay(1000);
  }

  Serial.println("Calibrated");
  randomSeed(analogRead(0));
}

void loop() 
{
   val = digitalRead(pirPin);
   Serial.println(val);
   delay(100);
   vall = digitalRead(pirPin);
   Serial.println(vall);

  if (val==1 && vall ==1) {

    Song2();

  // An addition to this projet would be to have the buzzer play a random assortment of songs that it cycles through whenever the PIR sensor detects someone

   /*  
  int r = random(1, 9);
   Serial.println(r);

   if  (r==1){
     Song1();
   }
   else if  (r==2){
     Song2();
   }
   else if  (r==3){
     Song3();
   }
  else if  (r==4){
     Song4();
   }
  else if  (r ==5 ){
     Song5();
   }
   else if  (r ==6 ){
     Song6();
   }
   else if  (r==7){
     Song7();
   }
  else if  (r==8){
     Song8();
   }
  */

   delay(1500);
   valPrev= val;
   }


if (val ==0 || vall ==0)
    noTone(buzzerPin); // Make sure no tone is played when no motion is detected.
    delay(250);
    valPrev = val;
}
void Song1() {
  // change this to make the song slower or faster
  int tempo = 105;

  int melody[] = {
   NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
};

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
// this calculates the duration of a whole note in ms
  int wholenote = (60000 * 2) / tempo;

  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}

void Song2() {
  // change this to make the song slower or faster
  int tempo = 110;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!

  int melody[] = {

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,

};
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 2) / tempo;

int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {

      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {

      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}

/* delete this to insert songs three through eight
void Song3 () {
  // change this to make the song slower or faster
  int tempo = ;

 // notes of the moledy followed by the duration.
 // a 4 means a quarter note, 8 an eighteenth, 16 sixteenth, so on
 // !!negative numbers are used to represent dotted notes,
 // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!

  int melody[] = {
   //Put your song using the nomenclature above
   //As an exampple:
   NOTE_E5, 4, NOTE_F3, 4, NOTE_G4, 8, NOTE_E7, 8
     };

  int notes = sizeof(melody)/sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 2) / tempo;

  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
 }

void Song4(){
  // change this to make the song slower or faster
  int tempo = 144;

  int melody[] = {
  REST, 2, NOTE_D4, 4, NOTE_G4, -4, NOTE_AS4, 8
  };

  int notes=sizeof(melody)/sizeof(melody[0])/2; 

  // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
}
}

void Song5() {
  // change this to make the song slower or faster 
  int  tempo = 180;
  int melody[] = {
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8,
};

  int notes=sizeof(melody)/sizeof(melody[0])/2; 

  // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo; 

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
}
}
void Song6() {
  // change this to make the song slower or faster
  int tempo = 140;

  int melody[] = {

  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8,

int notes=sizeof(melody)/sizeof(melody[0])/2; 

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}

void Song7(){
  // change this to make the song slower or faster
  int tempo = 105;
  int melody[] = {

  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,

};

  int notes=sizeof(melody)/sizeof(melody[0])/2; 

  // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}
void Song8() {
{
// change this to make the song slower or faster
  int tempo = 140;
  int melody[] = {
  NOTE_B4,-4, NOTE_E5,-4, NOTE_B4,-4, NOTE_E5,-4, 
   };
  int notes=sizeof(melody)/sizeof(melody[0])/2; 

  // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}
}
*/

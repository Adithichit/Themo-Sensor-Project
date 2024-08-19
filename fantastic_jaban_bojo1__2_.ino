#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
LiquidCrystal_I2C lcd(0x20,16,2);

int V_ADC = A0;
int Voltage_ADC;
int LEDPin = 3;
int tempo = 105;

// change this to whichever pin you want to use
int buzzer = 5;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Pacman
  // Score available at https://musescore.com/user/85429/scores/107109
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
  NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


void setup()
{
  Serial.begin(9600); 
  pinMode(LEDPin, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop()
{

  Voltage_ADC = analogRead(V_ADC);
  float Voltage = 5 * Voltage_ADC / 1023.0;
  float tC = (Voltage - .5) / .01;
  float tF = (tC * 9/5) + 32;
  lcd.setCursor(0,0);
  lcd.print("Temperature = ");
  lcd.setCursor(0,1);
  lcd.print(tF);
  delay(100);
  digitalWrite(LEDPin, LOW);
  digitalWrite(buzzer, LOW);

  if (tF < 70 || tF > 75){
    //warning buzzzing
    digitalWrite(LEDPin, HIGH);
    delay(100);//wait for 100ms
    digitalWrite(LEDPin, LOW);
    delay(100);//wait for 100ms
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
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
    //delay(1000); // ...for 1 sec
   // noTone(buzzer); // Stop sound...
    //delay(1000); // ...for 1sec
  }
  }
  else{
    //safe
    lcd.setCursor(0,0);
    lcd.print("Temperature (F) = ");
    lcd.setCursor(0,1);
    lcd.print(tF);
    delay(1000);
    digitalWrite(LEDPin, LOW);
    digitalWrite(buzzer, LOW);
  }
}
#include "pitches.h"

int bPins[6] = { 8, 9, 10, 11, 12, 13};
int bState[6] = { 0, 0, 0, 0, 0, 0};
int arraySize = sizeof(bPins) / sizeof(int);

int stbPin = 7;
int at1Pin = 5;
int at2Pin = 4;

int bzPin = 6;

int atv = 0;

void setup() {
  //PinMode setup
  for (int i = 0; i < arraySize; i++) {
    pinMode(bPins[i], INPUT_PULLUP);
  }

  pinMode(bzPin, OUTPUT);
  pinMode(stbPin, OUTPUT);
  pinMode(at1Pin, OUTPUT);
  pinMode(at2Pin, OUTPUT);

  digitalWrite(stbPin, HIGH);
  
  Serial.begin(9600);
  Serial.print("Start \n");
}

void loop() {
  //Read Buttons
  for (int i = 0; i < arraySize; i++) {
    bState[i] = digitalRead(bPins[i]);
  }

  if (atv == 0) {
    Serial.print("No activity \n");
    if(bState[0] == LOW) {
      digitalWrite(stbPin, LOW);

      Serial.print("Activity 1 Selected! \n");
      digitalWrite(at1Pin, HIGH);
      
      tone(bzPin, NOTE_C5, 200);
      delay(100);
      tone(bzPin, NOTE_B4, 200);
      delay(100);
      tone(bzPin, NOTE_E5, 200);
      delay(100);
      tone(bzPin, NOTE_F5, 200);

      atv = 1;
    } else if (bState[1] == LOW) {
      digitalWrite(stbPin, LOW);

      Serial.print("Activity 2 Selected! \n");
      digitalWrite(at2Pin, HIGH);

      tone(bzPin, NOTE_C6, 200);
      delay(100);
      tone(bzPin, NOTE_B5, 200);
      delay(100);
      tone(bzPin, NOTE_E6, 200);
      delay(100);
      tone(bzPin, NOTE_F6, 200);

      atv = 2;
    } else {
      Serial.print("Standby \n");
      delay(1000);
    }
  } else switch (atv) {
    case 1:
      //Atividade 1

      break;
    case 2:
      //Atividade 2

      break;
  }
}

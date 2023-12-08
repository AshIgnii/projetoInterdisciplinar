#include "pitches.h"
#include "Wire.h"
#include <LCD-I2C.h>

int bPins[7] = { 8, 9, 10, 11, 12, 13, 7};
int bState[7] = { 0, 0, 0, 0, 0, 0, 7};
int arraySize = sizeof(bPins) / sizeof(int);

int stbPin = 4;
int at1Pin = 3;
int at2Pin = 2;

int bzPin = 5;

int atv = 0;
int atv1ds = false;
int atv2ds = false;

LCD_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();

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

  lcd.begin();
  lcd.display();
  lcd.backlight();

  lcd.print("Selecione uma");
  lcd.setCursor(0, 1);
  lcd.print("atividade:");
}

void loop() {

  //Read Buttons
  for (int i = 0; i < arraySize; i++) {
    bState[i] = digitalRead(bPins[i]);
  }

  //Select Activity
  if (atv == 0) {
    Serial.print("No activity \n");
    if(bState[0] == LOW) {
      digitalWrite(stbPin, LOW);

      Serial.print("Activity 1 Selected! \n");
      digitalWrite(at1Pin, HIGH);
      
      tone(bzPin, NOTE_C6, 200);
      delay(200);
      tone(bzPin, NOTE_B5, 200);
      delay(200);
      tone(bzPin, NOTE_E6, 200);
      delay(200);
      tone(bzPin, NOTE_F6, 200);

      lcd.clear();
      lcd.print("Atividade 1");
      lcd.setCursor(0, 1);
      lcd.print("selecionada!");
      delay(2000);
      lcd.clear();

      atv = 1;
    } else if (bState[1] == LOW) {
      digitalWrite(stbPin, LOW);

      Serial.print("Activity 2 Selected! \n");
      digitalWrite(at2Pin, HIGH);

      tone(bzPin, NOTE_C6, 200);
      delay(200);
      tone(bzPin, NOTE_B5, 200);
      delay(200);
      tone(bzPin, NOTE_E6, 200);
      delay(200);
      tone(bzPin, NOTE_F6, 200);

      lcd.clear();
      lcd.print("Atividade 2");
      lcd.setCursor(0, 1);
      lcd.print("selecionada!");
      delay(2000);
      lcd.clear();

      atv = 2;
    } else {
      Serial.print("Standby \n");
      delay(500);
    }
  } else if (atv == 1) {
      char qs[] = "5 + 4 = ?";
      int rs[7] = { 9, 4, 3, 1, 6, 7, 0};
      int ra = 9;
      int rsSize = sizeof(rs) / sizeof(int);


      if (atv1ds == false) {
        

        lcd.clear();
        
        lcd.setCursor(0, 0);
        lcd.print(qs);

        for (int i = 0; i < rsSize; i++) {
          if (i == 0) {
            lcd.setCursor(0, 1);
          } else {
            lcd.setCursor(2*i, 1);
          }
          lcd.print(rs[i]);
        }

        atv1ds = true;
      }

      //Read Input
      for (int i = 0; i < arraySize; i++) {
        bState[i] = digitalRead(bPins[i]);
      }

      int sa = -1;
      for (int i = 0; i < arraySize; i++) {
        if (bState[i] == LOW) {
          sa = i;
        }
      }

      if (sa >= 0) {
        if (rs[sa] == ra) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Correto!");

          delay(10000);
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Incorreto!");

          delay(10000);
        }
      }
    } else if (atv == 2) {
      char qs2[] = "br_nquedo?";
      char rs2[] = "auoeily";
      char ra2 = 'i';
      int rsSize2 = (sizeof(rs2) / sizeof(char)) - 1;

      if (atv2ds == false) {
        lcd.clear();
        
        lcd.setCursor(0, 0);
        lcd.print("aperte na letra que");
        lcd.setCursor(0, 1);
        lcd.print("completa o termo:");

        delay(2000);

        lcd.clear();
        lcd.setCursor(0, 0);

        lcd.print(qs2);

        for (int i = 0; i < rsSize2; i++) {
          if (i == 0) {
            lcd.setCursor(0, 1);
          } else {
            lcd.setCursor(2*i, 1);
          }
          lcd.print(rs2[i]);
        }

        atv2ds = true;
      }

      //Read Input
      for (int i = 0; i < arraySize; i++) {
        bState[i] = digitalRead(bPins[i]);
      }

      int sa2 = -1;
      for (int i = 0; i < arraySize; i++) {
        if (bState[i] == LOW) {
          sa2 = i;
        }
      }

      if (sa2 >= 0) {
        if (rs2[sa2] == ra2) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Correto!");

          delay(10000);
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Incorreto!");
          
          delay(10000);
        }
      }
  }
}
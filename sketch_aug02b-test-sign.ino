#include "LiquidCrystal.h"
#include "pitches.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte futurelcd[32];
byte currentlcd[32];

byte steplcd() {
  byte changed = 0;
  byte j;
  for(byte i = 0; i<32; i++) {
    if(currentlcd[i] != futurelcd[i]) {
      currentlcd[i]++;
      if(currentlcd[i] == 91) {
        currentlcd[i] = 32;
      }
      if(i > 15) {
        j = 1;
      } else {
        j = 0;
      }
      lcd.setCursor(i-j*16, j);
      lcd.write(currentlcd[i]);
      changed++;
    }
  }
  return changed;
}



void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);
  lcd.clear();
  for(byte i = 0; i<32; i++) {
    currentlcd[i] = 32;
    futurelcd[i] = 32;
  }
}

void loop() {
  byte temp;
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(200);
    // clear the screen
    //lcd.clear();
    // read all the available characters
    for(byte i = 0; i < 32; i++) {
    
      if (Serial.available() > 0) {
        // display each character to the LCD
        temp = Serial.read();
        if(temp > 31 && temp < 91) {
          futurelcd[i] = temp;
        } else {
          futurelcd[i] = 32;
        }
      } else {
        futurelcd[i] = 32;
      }
    }
    while(Serial.available() > 0) {
      temp = Serial.read();
    }
  }
  if(steplcd()) {
    delay(110);
    digitalWrite(LED_BUILTIN, HIGH);
    tone(8, NOTE_C4, 10);
    delay(15);
    digitalWrite(LED_BUILTIN, LOW);
    noTone(8);
  }
}

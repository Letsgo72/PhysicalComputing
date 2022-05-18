#include <LiquidCrystal.h>

bool pressed = false;
bool flicked = false;
bool lcdOn = true;
int xVal = 0;
int yVal = 0;
LiquidCrystal lcd(10, 12, 5, 4, 3, 2);

void setup() {
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP); // Set pins for digital input
  Serial.begin(9600); // Begin serial
  lcd.begin(16,2); // Initialise LCD object
  lcd.clear(); // Ensure LCD is clear
  lcd.setCursor(0,0); // Ensure cursor is set to the top left of the LCD
}

void loop() {
  xVal = analogRead(A0);
  yVal = analogRead(A1); // Read from analog stick
  if(!pressed){ // If a button is not already pressed, check to see if any buttons are pressed
    if(digitalRead(9) == 1){
      Serial.println("~/bin/LockArtist"); // Write to serial command
      lcd.clear(); // Clear LCD
      lcd.print("Lock Artist"); // Write to LCD
      pressed = true; // Set pressed to true
    }
    if(digitalRead(8) == 1){
      Serial.println("~/bin/LockAlbum");
      lcd.clear();
      lcd.print("Lock Album");
      pressed = true;
    }
    if(digitalRead(7) == 1){
      Serial.println("~/bin/FullShuffle");
      lcd.clear();
      lcd.print("Full Shuffle");
      pressed = true;
    }
    if(digitalRead(6) == 1){
      lcd.clear();
      lcd.print("LCD On");
      if(lcdOn){ // If LCD on
        lcd.noDisplay(); // Turn off LCD
        lcdOn = false;
      }
      else{ // If LCD off
        lcd.display(); // Turn on LCD
        lcdOn = true;
      }
    pressed = true;
    }
    if(digitalRead(A2) == 0){
      Serial.println("mpc toggle");
      lcd.clear();
      lcd.print("Play/Pause");
      pressed = true;
    }
  }
  if(pressed){ // If buttons no longer pressed, set pressed to false to allow a new button to be pressed
    if(digitalRead(9) == 0 && digitalRead(8) == 0 && digitalRead(7) == 0 && digitalRead(6) == 0 && digitalRead(A2) == 1){
      pressed = false;
    }
  }
  if(!flicked){ // If analog stick not already moved in a direction test for input
    if(xVal > 950){
      Serial.println("mpc prev"); // Print command to serial
      lcd.clear(); // Clear LCD
      lcd.print("Previous Song"); // Print to LCD
      flicked = true;
    }
    if(xVal < 100){ 
      Serial.println("mpc next"); 
      lcd.clear(); 
      lcd.print("Next Song"); 
      flicked = true; 
    } 
    if(yVal > 950){
      Serial.println("mpc volume -5");
      lcd.clear();
      lcd.print("Volume Down");
      flicked = true;
    }
    if(yVal < 100){ 
      Serial.println("mpc volume +5"); 
      lcd.clear(); 
      lcd.print("Volume Up"); 
      flicked = true; 
    } 
  } 
  if(flicked){ // If Analog stick reset, set flicked to false to allow new input 
    if(analogRead(A0) > 450 && analogRead(A0) < 550 && analogRead(A1) > 450 && analogRead(A1) < 550){
      flicked = false;
    }
  }
}

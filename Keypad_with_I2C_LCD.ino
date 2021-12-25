/*
  Matrix Keypad with LCD Display Demo
  keypad-demo-lcd.ino
  Demonstrates use of 4x4 matrix membrane keypad with Arduino
  Results on LCD Display
  Display uses I2C backpack

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Include Arduino Wire library for I2C
#include <Wire.h> 
// Include LCD display library for I2C
#include <LiquidCrystal_I2C.h>
// Include Keypad library
#include <Keypad.h>

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Create LCD object
LiquidCrystal_I2C lcd(0x3F, 16, 2);  

void setup(){
  // Setup LCD with backlight and initialize
  lcd.backlight();
  //lcd.init(); 
  lcd.begin();
}

void loop(){
  // Get key value if pressed
  char customKey = customKeypad.getKey();
  
  if (customKey){
    // Clear LCD display and print character
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(customKey);
  }
}

/*
  Matrix Keypad Combination Lock Demo
  keypad-demo-lock.ino
  Combination lock using 4x4 matrix membrane keypad with Arduino
  Results on LCD display
  Drives relay

  DroneBot Workshop 2020
  https://dronebotworkshop.com

  Based upon code from https://www.circuitbasics.com/

*/

// Include Arduino Wire library for I2C
#include <Wire.h>
// Include LCD display library for I2C
#include <LiquidCrystal_I2C.h>
// Include Keypad library
#include <Keypad.h>

// Length of password + 1 for null character
#define Password_Length 8
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "123#567";// change Password

// Pin connected to lock relay input
int lockOutput = 13;

// Counter for character entries
byte data_count = 0;

// Character to hold key input
char customKey;

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
//LiquidCrystal_I2C lcd(0x3F, 16, 2);// use i2_scanner sketch to find the correct address of your I2C LCD display
LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup() {
  // Setup LCD with backlight and initialize
  lcd.backlight();
  lcd.begin();
  Serial.begin(9600);

  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);
}

void loop() {

  // Initialize LCD and print
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  //Serial.println("Enter Password:");
  //delay(500);
  //Serial.print(customKey);// comment out if you want to see the password
 
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    lcd.clear();

    if (!strcmp(Data, Master)) {
      // Password is correct
      lcd.print("PW is Correct");
      // Turn on relay for 5 seconds
      digitalWrite(lockOutput, HIGH);
      Serial.println("LOCK OPEND");
      delay(5000);
      digitalWrite(lockOutput, LOW);
      Serial.println("LOCK CLOSED");
    }
    else {
      // Password is incorrect
      lcd.print("PW Incorrect");
      delay(1000);
    }

    // Clear data and LCD display
    lcd.clear();
    clearData();
  }
}

void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

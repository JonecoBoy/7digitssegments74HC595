/*
  SevenSegmentDisplay74HC595 - Library for controlling 7 segments digits drived by 74hc595 shift registers.
  This library depends on ShiftRegister74HC595.h library
  Developed and maintained by Joneco, since May 2023.
  Additional information is available at https://joneco.com.br
  Released into the public domain.
*/

#include <SevenSegmentDisplay74HC595.h>

// Define the pins and number of digits
#define SDI 3
#define SCLK 2
#define LOAD 4

#define DIGITS 4 // number of digits / displays

SevenSegmentDisplay74HC595 display(SDI, SCLK, LOAD,DIGITS);

void setup() {
  Serial.begin(9600);
  // Serial.println(" (Ohm)");
}

void loop() {
  display.blinkString("JONE", 10,500,500);
  display.clear();
  display.scrollString("JONECO", true,500);
  display.scrollString("JONECO", false,500);
  delay(1000);
  display.clear();
  display.setString("AB"); // Change digit 3 to 'F'
  delay(1000);
  display.clear();
  display.setString("7-HF.");
  delay(1000);
  // digits are from left to right
  // 4 digits display [0][1][2][3]
  display.setDigit(0, 8); // Set digit 0 to 8
  display.setDigit(1, 1); // Set digit 1 to 5
  display.setDigit(2, '9'); // Set digit 2 to 9
  display.setDigit(3, 'C'); // Set digit 3 to 'C'
  delay(1000);
  display.clear();
  delay(1000);
  display.setDigit(3, '1'); // Set digit 2 to 9
  delay(1000);
  display.clear();
  display.setDigit(2, '2'); // Set digit 2 to 9
  delay(1000);
  display.clear();
  display.setDigit(1, '3'); // Set digit 2 to 9
  delay(1000);
  display.clear();
  display.setDigit(0, '4'); // Set digit 2 to 9
}

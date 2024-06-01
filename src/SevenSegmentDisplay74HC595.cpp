/*
  SevenSegmentDisplay74HC595.cpp - Library for controlling 7 segments digits drived by 74hc595 shift registers.
  Developed and maintained by Joneco, since May 2023.
  Additional information is available at https://joneco.com.br
  Released into the public domain.
*/

#include "SevenSegmentDisplay74HC595.h"

using namespace std;

// Constructor definition
SevenSegmentDisplay74HC595::SevenSegmentDisplay74HC595(uint8_t SDI, uint8_t SCLK, uint8_t LOAD, uint8_t DIGITS) 
: sr(SDI, SCLK, LOAD), DIGITS(DIGITS) {
  // Initialize the display to be blank initially
  currentDisplay = new uint8_t[DIGITS];
  clear();
  
}

// Destructor definition
SevenSegmentDisplay74HC595::~SevenSegmentDisplay74HC595() {
  delete[] currentDisplay;
}

void SevenSegmentDisplay74HC595::setString(String str) {
	while (str.length() < DIGITS) {
        str = " " + str;
    }
  for(uint8_t i = 0; i < str.length(); i++) {
    bool addDot=false;


    // Remove the dot if it's at position i + 1
    if (i < str.length() - 1 && str[i + 1] == '.') {
      str.remove(i + 1, 1);
	  addDot=true;
    }
	// if dot is not in the first character, will add the number + the dot in the current displa
	if (i < 1 || str[i] != '.') {
		if(addDot==false){
			setDigit(i, str[i]);
		}else{
			setDigitByCode(i, modifyFirstDigitToZero(getCode(str[i])));
		}
	}
  }
}

// Method to scroll the string through the display
void SevenSegmentDisplay74HC595::scrollString(String str, bool fullScroll, unsigned int delayMs) {
  int length = str.length();
  int maxValue = 0;
  if (!fullScroll) {
    maxValue = length + 4 - DIGITS;
  } else {
    maxValue = length + 4;
  }

  String displayStr = "    " + str + "    "; // Padding spaces for scrolling
  
  unsigned long previousMillis = 0; // Store the last time the display was updated
  int i = 0; // Index for the current position of the scrolling text

  while (i <= maxValue) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= delayMs) {
      previousMillis = currentMillis; // Update the last time the display was updated
      setString(displayStr.substring(i, i + DIGITS));
      i++; // Move to the next position
    }
    // Add a small delay to prevent the CPU from running too fast
    //delay(1);
  }
}

void SevenSegmentDisplay74HC595::blinkString(String str, int blinkCount, unsigned int blinkDelayMs, unsigned int blankDelayMs) {
  unsigned long previousMillis = 0; // Store the last time the display was updated
  int blinkState = 0; // 0 for showing text, 1 for blanking
  int currentBlink = 0; // Current blink cycle

  while (currentBlink < blinkCount) {
    unsigned long currentMillis = millis();
    if (blinkState == 0 && currentMillis - previousMillis >= blinkDelayMs) {
      previousMillis = currentMillis; // Update the last time the display was updated
      setString(str); // Display the string
      blinkState = 1; // Move to blanking state
    } else if (blinkState == 1 && currentMillis - previousMillis >= blankDelayMs) {
      previousMillis = currentMillis; // Update the last time the display was updated
      clear(); // Clear the display
      blinkState = 0; // Move to showing text state
      currentBlink++; // Increment the blink counter
    }
    // Add a small delay to prevent the CPU from running too fast
    //delay(1);
  }

  // Make sure to display the string again after the last blank
  setString(str);
}


String removeCharacter(String str, char charToRemove) {
  String result = "";
  for (int i = 0; i < str.length(); i++) {
    if (str[i] != charToRemove) {
      result += str[i];
    }
  }
  return result;
}

void SevenSegmentDisplay74HC595::clear() {
	for(uint8_t i=0; i< DIGITS; i++){
		setDigit(i, ' ');
	}
}

uint8_t SevenSegmentDisplay74HC595::modifyFirstDigitToZero(uint8_t value) {
    // Create a bitmask with 0 in the most significant bit and 1 in all other bits
    uint8_t mask = ~(1 << 7); // 0b01111111

    // Apply the mask using bitwise AND operator
    return value & mask;;
}

uint8_t SevenSegmentDisplay74HC595::getCode(char character) {
  if (character < '0' || character > '9') {
    switch (character) {
      case 'A':
      case 'a':
        return a;
      case 'B':
      case 'b':
        return b;
      case 'C':
      case 'c':
        return c;
      case 'D':
      case 'd':
        return d;
      case 'E':
      case 'e':
        return e;
      case 'F':
      case 'f':
        return f;
      case 'H':
      case 'h':
        return h;
      case 'L':
      case 'l':
        return l;
      case 'O':
      case 'o':
        return o;
      case 'P':
      case 'p':
        return p;
      case 'U':
      case 'u':
        return u;
	  case 'J':
      case 'j':
        return j;
	  case 'N':
      case 'n':
        return n;
      case '-':
        return dash;
      case '_':
        return underscore;
      case '.':
        return dot;
      case ' ':
        return blank;
      default:
        break;
    }
  } else {
    int newValue = character - '0';
    if (newValue >= 0 && newValue < 10) {
      return numbers[newValue];
    }
  }
  return 0; // Return 0 if character not recognized
}

// Modify the setDigit function to use getCode
void SevenSegmentDisplay74HC595::setDigit(uint8_t position, uint8_t value) {
  if (position < DIGITS) { // Ensure the position is within bounds
    if (value < 10) {
      currentDisplay[position] = numbers[value]; // Set digit value
    } else {
      currentDisplay[position] = getCode(value);
    }
    sr.setAll(currentDisplay); // Update the display
  }
}

void SevenSegmentDisplay74HC595::setDigitByCode(uint8_t position, uint8_t value) {
	currentDisplay[position] = value;
	sr.setAll(currentDisplay); // Update the display
}
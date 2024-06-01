/*
  SevenSegmentDisplay74HC595.h - Library for controlling 7 segments digits drived by 74hc595 shift registers.
  Developed and maintained by Joneco, since May 2023.
  Additional information is available at https://joneco.com.br
  Released into the public domain.
*/

#ifndef SevenSegmentDisplay74HC595_h
#define SevenSegmentDisplay74HC595_h

#include <Arduino.h>
#include <ShiftRegister74HC595.h>

class SevenSegmentDisplay74HC595 {
  public:
    SevenSegmentDisplay74HC595(uint8_t SDI, uint8_t SCLK, uint8_t LOAD, uint8_t DIGITS);
    ~SevenSegmentDisplay74HC595(); // Destructor to deallocate memory
    void setDigit(uint8_t position, uint8_t value);
	void setDigitByCode(uint8_t position,uint8_t value);
	void setString(String  str);
	void scrollString(String str, bool fullScroll, unsigned int delayMs);
	void blinkString(String str, int blinkCount, unsigned int blinkDelayMs, unsigned int blankDelayMs);
	void clear();
	
  private:
	//max number of chips = 8
    ShiftRegister74HC595<8> sr;
	uint8_t getCode(char character);
	uint8_t modifyFirstDigitToZero(uint8_t value);
	void modifyDigitToZero(uint8_t &value, uint8_t position);
    uint8_t numbers[10] = {B11000000, B11111001, B10100100, B10110000, B10011001, B10010010, B10000010, B11111000, B10000000, B10010000};
    uint8_t* currentDisplay; // Pointer to store the current state of each digit
    uint8_t DIGITS;
    uint8_t c = 0b11000110; // C
    uint8_t f = 0b10001110; // F
    uint8_t a = 0b10001000; // A
    uint8_t b = 0b10000011; // B
    uint8_t d = 0b10100001; // D
    uint8_t e = 0b10000110; // E
    uint8_t h = 0b10001001; // H
	uint8_t n = 0b10001001; // N
    uint8_t l = 0b11000111; // L
	uint8_t j = 0b11100001; // J
    uint8_t o = 0b11000000; // O
    uint8_t p = 0b10001100; // P
    uint8_t u = 0b11000001; // U
    uint8_t dash = 0b10111111; // -
    uint8_t underscore = 0b11101111; // _
    uint8_t blank = 0b11111111; // (blank)
	uint8_t dot = 0b01111111;
	
	
};

#endif

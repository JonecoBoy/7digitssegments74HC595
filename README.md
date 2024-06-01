# 7 Digits Segements with ShiftRegister 74HC595 Arduino Library

This library simplifies the usage of multi 7 digits displays driven by 74hc595 shift register: 

Reseting the entire display array
```
display.clear();
```

You can set individual digits by display.
display counts are from left to right
```
display.setDigit(0, 8); // Set digit 0 to 8
display.setDigit(1, 1); // Set digit 1 to 5
display.setDigit(2, '9'); // Set digit 2 to 9
display.setDigit(3, 'C'); // Set digit 3 to 'C'
```
NOTE: if you have a 4 digits and after that set just digits 2,3 the digits 0,1 will be the same as previous setted, unless you do a display.clear();

## String method
You can set a string:

```
display.setString("7-HF.");
```

if the first digit is ., it will be blank with the dot lighted up. if the other digits are followed by ., it will put a dot in the same digit of the previous digit.


display.setString("AB");

```
display.setString(".AB.C");  
```
will show

## Blink effect
You can set a blink effect
blinkString(String str, int blinkCount, unsigned int blinkDelayMs, unsigned int blankDelayMs);
```
display.blinkString("JONE", 10,500,500);
```
## Scrolling effect
Fro bigger strings instead of beeing cropped, you can set a rolling effect
scrollString(String str, bool fullScroll, unsigned int delayMs);
```
display.scrollString("JONECO", true,500);
display.scrollString("JONECO", false,500);
```
PS: if fullscroll is set as true it will scroll the entire characters until all have passed to the screen. If set to false it will scroll until the last character will be poisitioned at the last digit.

An **example** sketch can be found in this repository at [/examples/example/example.ino](https://github.com/JonecoBoy/7digitssegments74HC595/blob/master/examples/example/example.ino).

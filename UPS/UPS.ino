/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
//#include "ACS712.h"
#include "ZMPT101B.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 9, 6, 5, 4);
//ACS712  ACS(A0, 12.0, 1023, 100);
ZMPT101B voltageSensor(A1);

byte b1[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11111
};

byte b1f[8] = {
  0b11111,
  0b10000,
  0b10111,
  0b10111,
  0b10111,
  0b10111,
  0b10000,
  0b11111
};

byte b2[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};

byte b2f[8] = {
  0b11111,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b11111
};

byte b2f4[8] = {
  0b11111,
  0b00000,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b00000,
  0b11111
};

byte b2f3[8] = {
  0b11111,
  0b00000,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b00000,
  0b11111
};

byte b2f2[8] = {
  0b11111,
  0b00000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b00000,
  0b11111
};

byte b2f1[8] = {
  0b11111,
  0b00000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000,
  0b11111
};

byte b3[8] = {
  0b11100,
  0b00100,
  0b00111,
  0b00001,
  0b00001,
  0b00111,
  0b00100,
  0b11100
};

byte b3f[8] = {
  0b11100,
  0b00100,
  0b10111,
  0b10001,
  0b10001,
  0b10111,
  0b00100,
  0b11100
};

void getReadableTime(String &readableTime) {
  unsigned long currentMillis;
  unsigned long seconds;
  unsigned long minutes;
  unsigned long hours;
  unsigned long days;

  currentMillis = millis();
  seconds = currentMillis / 1000;
  minutes = seconds / 60;
  hours = minutes / 60;
  days = hours / 24;
  currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  if (days > 0) {
    readableTime = String(days) + " ";
  }

  if (hours > 0) {
    readableTime += String(hours) + ":";
  }

  if (minutes < 10) {
    readableTime += "0";
  }
  readableTime += String(minutes) + ":";

  if (seconds < 10) {
    readableTime += "0";
  }
  readableTime += String(seconds);
}

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.createChar(1, b1);
  lcd.createChar(2, b2);
  lcd.createChar(3, b3);
  lcd.createChar(4, b1f);
  lcd.createChar(5, b2f);
  lcd.createChar(6, b2f1);
  lcd.createChar(7, b2f2);
  lcd.createChar(8, b2f3);
  lcd.createChar(9, b2f4);
  lcd.createChar(10, b3f);
  lcd.begin(16, 2);
  //ACS.autoMidPoint();
  
  // Print a message to the LCD.
  lcd.write(4);
  lcd.write(5);
  lcd.write(8);
  lcd.write(3);
  lcd.print(" 12.59V");
 //ACS.setmVperAmp(30);
  //voltageSensor.setSensitivity(0.019);
  voltageSensor.calibrate();
}

void loop() {
 // int mA = ACS.mA_AC();
 float U = voltageSensor.getVoltageAC();

  String readableTime;
  getReadableTime(readableTime);
  
  lcd.setCursor(2, 0);
  lcd.write(random(7,9));
  delay(1000); 
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print(millis()/1000);
  lcd.print(U);
  lcd.print("V ");
  //lcd.print(ACS.getNoisemV());
  lcd.setCursor(11, 1);
  lcd.print(readableTime);
}

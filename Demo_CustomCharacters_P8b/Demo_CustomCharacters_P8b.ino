/*
 * Demo_CustomCharacters_P8b.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 *
 * Demonstrates how to add custom characters on an OLED display.  
 * This sketch prints "I <heart> Arduino!" and a little dancing man to the OLED.
 *
 * This sketch assumes the use of a 4x20 display; if different, the values of COLUMN_N and ROW_N 
 * must be set according to the display in use.
 * This example assumes that the display is connected to Arduino via 8-bit 6800 parallel interface.
 *
 * The circuit:
 * OLED pin 1 (Vss)    to Arduino pin ground
 * OLED pin 2 (VDD)    to Arduino pin 5V
 * OLED pin 3 (REGVDD) to Arduino pin 5V
 * OLED pin 4 (D/C)    to Arduino pin D2
 * OLED pin 5 (R/W)    to Vss ground (always write)
 * OLED pin 6 (E)      to Arduino pin D3
 * OLED pin 7 (DB0)    to Arduino pin D4
 * OLED pin 8 (DB1)    to Arduino pin D5
 * OLED pin 9 (DB2)    to Arduino pin D6
 * OLED pin 10 (DB3)   to Arduino pin D7
 * OLED pin 11 (DB4)   to Arduino pin D8
 * OLED pin 12 (DB5)   to Arduino pin D9
 * OLED pin 13 (DB6)   to Arduino pin D10
 * OLED pin 14 (DB7)   to Arduino pin D11
 * OLED pin 15 (/CS)   to Vss ground  (only one display)
 * OLED pin 16 (/RES)  to Arduino pin Reset or VDD 5V
 * OLED pin 17 (BS0)   to Vss ground
 * OLED pin 18 (BS1)   to Vss ground
 * OLED pin 19 (BS2)   to VDD 5V
 * OLED pin 20 (Vss)   to Vss ground
 *
 * Example created 21 Mar 2011 by Tom Igoe
 * Modified 11 Nov 2013 by Scott Fitzgerald
 * Modified 20 Jan 2015 by Pasquale D'Antini
 * Modified 20 May 2015 by Pasquale D'Antini
 *
 * This example code is in the public domain.
 */

#include <OLED_US2066.h>

const uint8_t COLUMN_N = 20;                    // Display columns number
const uint8_t ROW_N = 4;                        // Display rows number

OLED_US2066 oled(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);     // Set the Arduino pins corresponding to the oled pins
                                                      //  (DC, E, D0, D1, D2, D3, D4, D5, D6, D7)

byte heart[8] = {                               // Custom characters maps
   0b00000,
   0b01010,
   0b11111,
   0b11111,
   0b11111,
   0b01110,
   0b00100,
   0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup(void) 
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED (set up the number of columns and rows)
   
   oled.createChar(0, heart);                   // Creates 5 custom characters and
   oled.createChar(1, smiley);                  //  loads them in the first 5 memory locations
   oled.createChar(2, frownie);
   oled.createChar(3, armsDown);  
   oled.createChar(4, armsUp);  
   
   oled.home();
   oled.print("I ");                            // Prints the phrase "I love Arduino!"
   oled.write(byte(0));                         // when calling oled.write() '0' must be cast as a byte
   oled.print(" Arduino! ");
   oled.write(1);
}

void loop(void) 
{
   int sensorReading = analogRead(A0);          // Read the potentiometer on A0
   int delayTime = map(sensorReading, 0, 1023, 200, 1000);   // Map the result to 200 - 1000
   
   oled.setCursor(4, 1);                        // Set the cursor to the second row, 5th position
   oled.write(3);                               // Draw the little man, arms down
   delay(delayTime);
   
   oled.setCursor(4, 1);
   oled.write(4);                               // Draw him arms up
   delay(delayTime); 
}

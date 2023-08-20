/*
 * Test_P8b.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 * 
 * This sketch is a simple diagnostic test.
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
 * One button switch between Arduino pin D12 and pin ground
 *
 * Example written 21 June 2016 by Pasquale D'Antini
 *
 * This example code is in the public domain.
 */

#include <OLED_US2066.h>

const uint8_t COLUMN_N = 20;                    // Display columns number
const uint8_t ROW_N = 4;                        // Display rows number
uint8_t n = 0;

OLED_US2066 oled(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);     // Set the Arduino pins corresponding to the oled pins
                                                      //  (DC, E, D0, D1, D2, D3, D4, D5, D6, D7)

void setup(void) 
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED (set up the number of columns and rows)
   pinMode(12, INPUT_PULLUP);
}

void loop(void)
{
   n ++;
   oled.home();                                // Clears the screen
   char message[] = "Test ";
   
   for (byte i=0; i<5; i++)
   {
      oled.print(message[i]);                   // displays the string one character at a time
   }
   oled.print(n);
   
   delay(5000);
   while(digitalRead(12) == HIGH) {  }
}

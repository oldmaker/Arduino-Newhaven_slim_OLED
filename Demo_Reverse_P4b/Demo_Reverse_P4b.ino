/*
 * Demo_Reverse_P4b.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 * 
 * This sketch shows the use of reverse and noReverse commands.
 *
 * This sketch assumes the use of a 4x20 display; if different, the values of COLUMN_N and ROW_N 
 * must be set according to the display in use.
 * This example assumes that the display is connected to Arduino via 4-bit 6800 parallel interface.
 *
 * The circuit:
 * OLED pin 1 (Vss)    to Arduino pin ground
 * OLED pin 2 (VDD)    to Arduino pin 5V
 * OLED pin 3 (REGVDD) to Arduino pin 5V
 * OLED pin 4 (D/C)    to Arduino pin D2
 * OLED pin 5 (R/W)    to Vss ground (always write)
 * OLED pin 6 (E)      to Arduino pin D3
 * OLED pin 7 (DB0)    to Vss ground
 * OLED pin 8 (DB1)    to Vss ground
 * OLED pin 9 (DB2)    to Vss ground
 * OLED pin 10 (DB3)   to Vss ground
 * OLED pin 11 (DB4)   to Arduino pin D8
 * OLED pin 12 (DB5)   to Arduino pin D9
 * OLED pin 13 (DB6)   to Arduino pin D10
 * OLED pin 14 (DB7)   to Arduino pin D11
 * OLED pin 15 (/CS)   to Vss ground  (only one display)
 * OLED pin 16 (/RES)  to Arduino pin Reset or VDD 5V
 * OLED pin 17 (BS0)   to VDD 5V
 * OLED pin 18 (BS1)   to Vss ground
 * OLED pin 19 (BS2)   to VDD 5V
 * OLED pin 20 (Vss)   to Vss ground
 *
 * Example written 22 May 2015 by Pasquale D'Antini
 * Modified 4 May 2016 by Pasquale D'Antini
 *
 * This example code is in the public domain.
 */
 
#include <OLED_US2066.h>

const uint8_t COLUMN_N = 20;                    // Display columns number
const uint8_t ROW_N = 4;                        // Display rows number
int rev = 1;

OLED_US2066 oled(2, 3, 8, 9, 10, 11);           // Set the Arduino pins corresponding to the oled pins
                                                //  (DC, E, D4, D5, D6, D7)

void setup(void)
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED
   oled.cursor();
   oled.blink();
}

void loop(void)
{
   byte i = 65;                                 // ASCII table index
   byte c = 0;                                  // Column index
   byte r = 0;                                  // Row index
   
   if (rev > 0)                                 // Alternates between reverse and noReverse
      oled.noReverse();
   else
      oled.reverse();
   rev *= -1;
   
   oled.clear();                                // Clears the screen
   
   for (r=0; r<ROW_N; r++)                      // For each row,
   {
      oled.setCursor(0, r);                     //  positions the cursor at the beginning of the row
      for (c=0; c<COLUMN_N; c++)                // For each column,
      {
         oled.write(i);                         //  prints a character from the ASCII table,
         i++;                                   //  increments ASCII table index
         delay(100);
      }
   }
   delay(3000);
}

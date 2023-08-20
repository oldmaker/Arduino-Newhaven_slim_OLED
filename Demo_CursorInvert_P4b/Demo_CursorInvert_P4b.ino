/*
 * Demo_CursorInvert_P4b.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 * 
 * This sketch shows the use of cursorInvert and noCursorInvert commands.
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
 * Example written 23 May 2015 by Pasquale D'Antini
 * Modified 4 May 2016 by Pasquale D'Antini
 *
 * This example code is in the public domain.
 */
 
#include <OLED_US2066.h>

const uint8_t COLUMN_N = 20;                    // Display columns number
const uint8_t ROW_N = 4;                        // Display rows number
byte c = 0;                                     // Column index
byte r = 0;                                     // Row index
int del = 0;                                    // Delay time (scroll speed)

OLED_US2066 oled(2, 3, 8, 9, 10, 11);           // Set the Arduino pins corresponding to the oled pins
                                                //  (DC, E, D4, D5, D6, D7)

void setup(void)
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED
   
   byte i = 65;                                 // ASCII table index
   for (r=1; r<ROW_N; r++)                      // For each row,
   {
      oled.setCursor(0, r);                     //  positions the cursor at the beginning of the row
      for (c=0; c<COLUMN_N; c++)                // For each column,
      {
         oled.write(i);                         //  prints a character from the ASCII table,
         i++;                                   //  increments ASCII table index
      }
   }
}

void cursorMove(void)
{
   del = 5000;
   for (r=1; r<ROW_N; r++)                      // For each row,
   {
      oled.setCursor(0, r);                     //  positions the cursor at the beginning of the row
      for (c=0; c<COLUMN_N; c++)                // For each column,
      {
         delay(del);
         oled.scrollCursorRight();              //  scrolls right the cursor
         if (del > 50)
            del = del - del / 4;                // Progressively reduces the delay
      }
   }
   delay(del);
}

void loop(void)
{
   oled.home();
   oled.print("cursor+NOinverse");
   oled.cursor();
   cursorMove();
   
   oled.home();
   oled.print("cursor+inverse  ");
   oled.cursorInvert();
   cursorMove();
   oled.noCursorInvert();
   oled.noCursor();
   
   oled.home();
   oled.print("blink+NOinverse ");
   oled.blink();
   cursorMove();
   
   oled.home();
   oled.print("blink+inverse   ");
   oled.cursorInvert();
   cursorMove();
   oled.noCursorInvert();
   oled.noBlink();   
   
   oled.home();
   oled.print("cur+blin+NOinver");
   oled.cursor();
   oled.blink();
   cursorMove();
   
   oled.home();
   oled.print("curs+blink+inver");
   oled.cursorInvert();
   cursorMove();
   oled.noCursorInvert();
   oled.noCursor();
   oled.noBlink();   
   
   oled.home();
   oled.print("noCur+noBlin+inv");
   oled.cursorInvert();
   cursorMove();
   oled.noCursorInvert(); //*/
   /*
   oled.cursor();
   oled.setCursor(8, 1);
   delay(1000);
   oled.cursorInvert();
   delay(2000);
   oled.setCursor(14, 1);
   delay(1000);
   oled.cursorInvert();
   delay(2000);
   oled.noCursorInvert();
  
   oled.noCursor();
   oled.setCursor(10, 2);
   delay(1000);
   oled.cursorInvert();
   delay(2000);
   oled.setCursor(15, 2);
   delay(1000);
   oled.cursorInvert();
   delay(2000);
   oled.noCursorInvert(); */
}

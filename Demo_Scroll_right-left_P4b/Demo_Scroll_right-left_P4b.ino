/*
 * Demo_Scroll_right-left_P4b.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 * 
 * This sketch shows the use of scrollDisplayRight/Left and scrollCursorRight/Left commands; 
 * display shifts right or left without changing DDRAM or address counter.
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
 * Example written 24 Jan 2015 by Pasquale D'Antini
 * Modified 4 May 2016 by Pasquale D'Antini
 *
 * This example code is in the public domain.
 */
 
#include <OLED_US2066.h>

const uint8_t COLUMN_N = 20;                    // Display columns number
const uint8_t ROW_N = 4;                        // Display rows number
byte del = 500;                                 // Delay time (scroll speed)

OLED_US2066 oled(2, 3, 8, 9, 10, 11);           // Set the Arduino pins corresponding to the oled pins
                                                //  (DC, E, D4, D5, D6, D7)
// _______________________________________________________________________________________
   
void setup(void)
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED (set up the number of columns and rows)
   oled.blink();
   oled.setCursor(2, 0);
   oled.print("scroll ");                       // Print a message in the first row of the OLED
}
// _______________________________________________________________________________________

void goRight(byte k, char mode)                 // SUBROUTINE: SCROLLS RIGHT THE DISPLAY/CURSOR
{
   oled.setCursor(9, 0);                        // PLEASE NOTE: the display scrolling doesn't modify
                                                //  the cursor position index (DDRAM doesn't change)
   if (mode == 'd')
      oled.print("display");                    // Modify the message in the first row of the OLED
   else
      oled.print("CURSOR ");
      
   oled.setCursor(5, 1);
   oled.print("right->");                       // Modify the message in the second row of the OLED

   delay(2000);
   for (byte x=0; x<k ; x++)                    // k times, one character at a time,
   {
      delay(del);
      if (mode == 'd')
         oled.scrollDisplayRight();             //  scrolls right the display
      else
         oled.scrollCursorRight();              //  scrolls right the cursor
   }
   delay(2000);
}
// _______________________________________________________________________________________

void goLeft(byte k, char mode)                  // SUBROUTINE: SCROLLS LEFT THE DISPLAY/CURSOR
{
   oled.setCursor(9, 0);                        // PLEASE NOTE: the display scrolling doesn't modify
                                                //  the cursor position index (DDRAM doesn't change)
   if (mode == 'd')
      oled.print("display");                    // Modify the message in the first row of the OLED
   else
      oled.print("CURSOR ");
      
   oled.setCursor(5, 1);
   oled.print("<-left ");                       // Modify the message in the second row of the OLED

   delay(2000);
   
   for (byte x=0; x<k ; x++)                    // k times, one character at a time,
   {
      delay(del);
      if (mode == 'd')
         oled.scrollDisplayLeft();              //  scrolls right the display
      else
         oled.scrollCursorLeft();               //  scrolls right the cursor
   }
   delay(2000);
}
// _______________________________________________________________________________________

void loop(void)
{
   goRight(6, 'd');                             // Calls right-scrolling subroutine for display (4 positions)
   goLeft(10, 'd');                             // Calls left-scrolling subroutine for display (8 positions)
   goRight(4, 'd');                             // Calls right-scrolling subroutine for display (4 positions)
   
   goRight(10, 'c');                            // Calls right-scrolling subroutine for cursor (4 positions)
   goLeft(14, 'c');                             // Calls left-scrolling subroutine for cursor (8 positions)
   goRight(4, 'c');                             // Calls right-scrolling subroutine for cursor (4 positions)
}

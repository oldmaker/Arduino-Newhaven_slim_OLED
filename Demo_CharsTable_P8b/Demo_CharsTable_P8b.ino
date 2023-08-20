/*
 * Demo_CharsTable_P8b.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 * 
 * This sketch shows how to create custom characters and displays all the characters table.
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
 * Example originally written 8 Dec 2011 by Mario H.
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

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};      // Custom characters maps
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
  
void setup(void)
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED (set up the number of columns and rows)
   
   oled.createChar(0, bell);                    // Creates 8 custom characters and 
   oled.createChar(1, note);                    //  loads them in the first 8 memory locations
   oled.createChar(2, clock);
   oled.createChar(3, heart);
   oled.createChar(4, duck);
   oled.createChar(5, check);
   oled.createChar(6, cross);
   oled.createChar(7, retarrow);
}

void loop(void)
{
   byte r = 0;                                  // Row index for cursor positioning on the OLED
   
   oled.clear();                                // Clears the screen
   oled.print("Hello world...");                // Print a message
   
   oled.setCursor(0, 1);                        // Positions the cursor at the beginning of the second row
   oled.print(" i ");                           // Prints the phrase "i love arduinos"
   oled.write(3);                               // Prints custom character 3 (heart) for "love"
   oled.print(" arduinos!");
   delay(5000);
   
   for (int i=0; i<=255; i+=16)                 // Scans the ASCII table, 16 characters at a time
   {
      oled.clear();                             // Clears the screen
      r = 0;
      oled.setCursor(0, r);                     // On the first row, 
      oled.print("Codes 0x");                   //  prints the character-codes range (16 chars)
      oled.print(i, HEX);
      oled.write(126);
      oled.print("0x");
      oled.print(i+15, HEX);
      
      if (ROW_N > 2)                            // If the OLED has more than 2 rows,
      {
         r ++;
         oled.setCursor(0, r);                  //  on the next row,
         oled.print("decimal ");                //  prints the same range in decimal
         oled.print(i, DEC);
         oled.write(126);
         oled.print(i+15, DEC);
      }
      
      r ++;
      oled.setCursor(0, r);                     // On the next row,
      for (uint8_t j=0; j<=15; j++)             //  prints the 16 characters included in the range
      {
         oled.write(i+j);
      }
      
      if (i == 0)  { delay(5000); }             // Extra pause for custom characters
      else  { delay(2000); }
   }
   delay(1000);
}

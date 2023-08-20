/*
 * Demo_Autoscroll_I2C.ino
 * 
 * Example sketch for use of OLED_US2066 library on Arduino.
 * OLED_US2066 is a library for character OLED display based on controller US2066, e.g. Newhaven 
 * character OLED slim display family: NHD0420CW-Ax3, NHD0220CW-Ax3, NHD0216CW-Ax3, ecc.
 * US2066 is partially compatible with the classic Hitachi HD44780 LCD controller.
 * 
 * This sketch shows the use of autoscroll and noAutoscroll commands; autoscroll means that display 
 * shifts with DDRAM address, instead of cursor.
 *
 * This sketch assumes the use of a 4x20 display; if different, the values of COLUMN_N and ROW_N 
 * must be set according to the display in use.
 * This example assumes that the display is connected to Arduino via I2C bus interface.
 * 
 * The circuit:
 * OLED pin 1 (Vss)    to Arduino pin ground
 * OLED pin 2 (VDD)    to Arduino pin 5V
 * OLED pin 3 (REGVDD) to Arduino pin 5V
 * OLED pin 4 (SA0)    to Vss ground (address 0x3C; connect to VDD 5V to assign I2C address 0x3D)
 * OLED pin 5 and 6    to Vss ground
 * OLED pin 7 (SCL)    to Arduino pin A5 (SCL); 10K pull-up resistor on OLED pin
 * OLED pin 8 (SDAin)  to Arduino pin A4 (SDA); 10K pull-up resistor on OLED pin
 * OLED pin 9 (SDAout) tie together with OLED pin 8 (SDAin)
 * OLED pin 10 to 15   to Vss ground
 * OLED pin 16 (/RES)  to Arduino pin Reset or VDD 5V
 * OLED pin 17 (BS0)   to Vss ground
 * OLED pin 18 (BS1)   to VDD 5V
 * OLED pin 19 (BS2)   to Vss ground
 * OLED pin 20 (Vss)   to Vss ground
 *
 * Example written 15 June 2016 by Pasquale D'Antini
 *
 * This example code is in the public domain.
 */

#include <OLED_US2066.h>

const uint8_t COLUMN_N = 20;                    // Display columns number
const uint8_t ROW_N = 4;                        // Display rows number

OLED_US2066 oled(0x3C);                         // Set the I2C bus address corresponding to the oled
                                                //  (in 7-bit form: 0x3C if SA0=LOW, 0x3D if SA0=HIGH)

void setup(void) 
{
   oled.begin(COLUMN_N, ROW_N);                 // Initialize the OLED (set up the number of columns and rows)
   oled.blink();
}

void noScroll(byte c, byte r)                   // SUBROUTINE: displays a string without autoscroll
{
   char message[] = "noAutoscroll";
   
   oled.noAutoscroll();                         // Disable autoscroll
   oled.setCursor(c, r);                        // Position the cursor in (c, r)
   for (byte i=0; i<12; i++)
   {
      oled.print(message[i]);                   // displays the string one character at a time
      delay(350);
   }
   delay(1000);
}

void scroll(byte c, byte r)                     // SUBROUTINE: displays a string with autoscroll
{
   char message[] = "Autoscroll";
   
   oled.autoscroll();                           // Set autoscroll
   oled.setCursor(c, r);                        // Position the cursor in (c, r)
   for (byte i=0; i<10; i++)
   {
      oled.print(message[i]);                   // displays the string one character at a time
      delay(350);
   }
   delay(1000);
}

void loop(void)
{
   byte c = COLUMN_N / 2;                       // Center column index
   
   oled.clear();                                // Clears the screen
   noScroll(8, 0);                              // Displays a string without autoscroll in the center of the row
   scroll(8, 1);                                // Displays a string with autoscroll in the center of the row
   noScroll(8, 2);                              // Displays a string without autoscroll in the center of the row
   scroll(8, 3);                                // Displays a string with autoscroll in the center of the row
   delay(5000);
}

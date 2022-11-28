#include <msp430.h>
#include "LCD_Utilities.h"
const unsigned char lcd_num[10] = {  0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE4, 0xFF, 0xF7 };
//   0         1       2         3        4        5        6        7        8       9  
void main()  {
 WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer
 PM5CTL0 &= ~LOCKLPM5;// Clear locked IO Pins
     LCDInit();
     LCDM10  =  lcd_num[5];      // Display "5" on A1
     LCDM11  =  0x1;                  // Display  A1 Decimal Point
     LCDM6    =  lcd_num[7];      // Display "7" on A2
     LCDM4    =  lcd_num[2];      // Display "2" on A3
     LCDM19  =  lcd_num[4];      // Display "4" on A4
     LCDM15  =  lcd_num[3];      // Display "3" on A5
     LCDM8    =  lcd_num[0];      // Display "0" on A6
    _BIS_SR (LPM3_bits | GIE); 
}

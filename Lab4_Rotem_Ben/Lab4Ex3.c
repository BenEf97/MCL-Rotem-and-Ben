#include <msp430.h>
#include "LCD_Utilities.h"
const unsigned char lcd_num[10] = {  0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE4, 0xFF, 0xF7 };
//   0         1       2         3        4        5        6        7        8       9  
void main()  {
 WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer
 PM5CTL0 &= ~LOCKLPM5;// Clear locked IO Pins
     LCDInit();
     A1_6;      
     A2_6;
     A3_6;
    _BIS_SR (LPM3_bits | GIE); 
}


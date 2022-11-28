#include <msp430.h>
#include "LCD_Utilities.h"
char RnB=1;
const unsigned char lcd_num[10] = {  0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE4, 0xFF, 0xF7 };
//   0         1       2         3        4        5        6        7        8       9  
void main()  {
 WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer
 PM5CTL0 &= ~LOCKLPM5;// Clear locked IO Pins
     LCDInit();
     init_Button();
    _BIS_SR (LPM3_bits | GIE); 
}


#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void) {
  wait(3);

    //check for S1 Rotem
    if ((P1IFG&BIT1)&& !(P1IN & BIT1))   
  {
    if (RnB==1)
    {
    Display_Number(773601); 	// Display Rotem's ID
    P1IFG &=~BIT1; //turn off the flag
    RnB=0;
    }
    else
    {
    Display_Number(1319); 	// display Ben's ID is 001319, the compiler thinks it's an octal base instead of decimal.
    P1IFG &=~BIT1; //turn off the flag
    RnB=1;
    }
  }
  
  
  //check for S1 Ben
  if ((P1IFG&BIT1)&& !(P1IN & BIT1))   
  {

  }
  

}
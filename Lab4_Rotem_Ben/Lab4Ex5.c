#include <msp430.h>
#include "LCD_Utilities.h"
char RnB=1;
const unsigned char lcd_num[10] = { 0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE4, 0xFF, 0xF7 };
//   0         1       2         3        4        5        6        7        8       9
/*const unsigned int lcd_char[26] = {
 
  0x00EF, // A=0
  0x50F1, // B=1
  0x009C, // C=2
  0x50F0, // D=3
  0x009F, // E=4
  0x008F, // F=5
  0x00BD, // G=6
  0x006F, // H=7
  0x5090, // I=8
  0x0078, // J=9
  0x220E, // K=10
  0x001C, // L=11
  0xA06C, // M=12
  0x826C, // N=13
  0x00FC, // O=14
  0x00CF, // P=15
  0x02FC, // Q=16
  0x02CF, // R=17
  0x80B1, // S=18
  0x5080, // T=19
  0x007C, // U=20
  0x280C, // V=21
  0x0A6C, // W=22
  0xAA00, // X=23
  0x1047, // Y=24
  0x2890  // Z=25
};*/

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
    LCD_All_Off(); 
    Display_Char('R',1);
    Display_Char('O',2);
    Display_Char('T',3);
    Display_Char('E',4);
    Display_Char('M',5);
    P1IFG &=~BIT1; //turn off the flag
    RnB=0;
    }
    else
    {
    LCD_All_Off();  
    Display_Char('B',1);
    Display_Char('E',2);
    Display_Char('N',3);
    P1IFG &=~BIT1; //turn off the flag
    RnB=1;
    }
  }
  
  
  //check for S1 Ben
  if ((P1IFG&BIT1)&& !(P1IN & BIT1))   
  {

  }
  

}
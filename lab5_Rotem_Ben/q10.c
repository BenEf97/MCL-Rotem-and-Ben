#include "msp430.h"
#include "LCD_Utilities.h"
int checker=0;
const unsigned char lcd_num[10] = {  0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE4, 0xFF, 0xF7 };
//   0         1       2         3        4        5        6        7        8       9  
int res=0;
void main(){
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  P1DIR |= BIT0;			// Set P1.0 to output direction
  P9DIR |= BIT7;			// Set P9.7 to output direction
  TA0R = 0x0000;  
	//ACLK               Up/Down mode    Clear TA0R    No-Divide  Enable Int
  TA0CTL = TASSEL__ACLK + MC__CONTINUOUS  +  TACLR    +  ID__8    +   TAIE;
  TA0CCR0 = 32768;

  
  
  LCDInit();
  //Reset
  P1OUT &= ~BIT0;
  P9OUT &= ~BIT7;
  
  //setup S1 button
  P1DIR &=~BIT1; //set S1 to input
  P1REN  |= BIT1;  //p1.1 connect ressistor.
  P1OUT |= BIT1; // connect port to pull ups
  P1IES &= ~BIT1; //recon low to high transmisstion.
  P1IE |= BIT1; //enable interrupt for p1.1
  
  //setup S2 button
  P1DIR &=~BIT2; //set S2 to input
  P1REN  |= BIT2;  //p1.2 connect ressistor.
  P1OUT |= BIT2; // connect port to pull ups
  P1IES &= ~BIT2; //recon low to high transmisstion.
  P1IE |= BIT2; //enable interrupt for p1.2
  P1IFG = 0x00;			// Reset IFG
  
   _BIS_SR (LPM3_bits + GIE);

}


#pragma vector = PORT1_VECTOR
__interrupt void port_1 (void)
{
 wait(10); 
  switch(P1IV)
  {
    //s1 is pressed, turn on led and start to count
    case(0x04):
    LCD_All_Off(); 
    checker=1;
    TA0R = 0x0000; //reset counter
    P1OUT |= BIT0;
    break;
    case(0x06):
    //reset both leds to start together
     if (checker)
     {
      P1OUT &= ~BIT0;
      Display_Number(TA0R/4); 
     }
     else 
     {
    LCD_All_Off(); 
    Display_Char('E',1);
    Display_Char('R',2);
    Display_Char('R',3);
    Display_Char('O',4);
    Display_Char('R',5);
     }
    break;
  }
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer (void) {  
  if (TA0IV == 0x0E)
        {
          //
        }
}

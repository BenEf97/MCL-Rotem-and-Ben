#include "msp430.h"

void main(){
  WDTCTL = WDTPW | WDTHOLD;		        // Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		        // Clear locked IO Pins
 
  P1DIR |= BIT0;                                                          // Set P1.0 to output direction
  P1REN  |= 0xFE;                                                       // Enable P1.1 to p1.7 Resistor
  P1OUT |= 0xFE;                                                       // and connect them to pull ups
  
  while (1) {
   if (P1IN & BIT2) P1OUT &= ~BIT0; //if p1.1in==1 in then p1.0out=0
   else P1OUT |= BIT0; //p1.0out=1 press button
  }
}

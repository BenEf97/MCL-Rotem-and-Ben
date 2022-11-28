#include "msp430.h"
void wait(int ms);
void main(){
  WDTCTL = WDTPW | WDTHOLD;		        // Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		        // Clear locked IO Pins
 
  P1DIR |= BIT0;                                                          // Set P1.0 to output direction
  P1REN  |= 0xFE;                                                       // Enable P1.1 to p1.7 Resistor
  P1OUT &= 0xFE;                                                        // and connect them to pull ups

  while(1)
  {
    while (P1IN & BIT1) //while s1 is pressed
    {
      P1OUT ^= BIT0; //swtich on and off
      wait(200);
    }
       P1OUT &= 0xFE;  //turn off

  }
}

   
   
void wait(int ms) {
	int i, j;
	for(i=0; i<ms; i++)
          for(j=0; j<200; j++);     }
#include "msp430.h"

void wait(int ms);

void main(){
  WDTCTL = WDTPW | WDTHOLD;		        // Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		        // Clear locked IO Pins
 
  
    //setup green led
  P9DIR = BIT7; //set led to output
  P9OUT &=~BIT7; //reset p9.7
  
  
  //setup S1 button
  P1DIR &=~BIT1; //set S1 to input
  P1REN  |= BIT1;  //p1.1 connect ressistor.
  P1OUT |= BIT1; // connect port to pull ups
  P1IES |= BIT1; //recon High to Low transmisstion.
  P1IE |= BIT1; //enable interrupt for p1.1
  
  //setup red led
  P1DIR = BIT0; //set red led to output
  P1OUT &=~BIT0; //reset p1.0
  
  
  //setup S2 button
  P1DIR &=~BIT2; //set S2 to input
  P1REN  |= BIT2;  //p1.2 connect ressistor.
  P1OUT |= BIT2; // connect port to pull ups
  P1IES |= BIT2; //recon High to Low transmisstion.
  
  P1IE |= BIT2; //enable interrupt for p1.2
  P1IFG = 0x00;			// Reset IFG
  _BIS_SR (LPM3_bits | GIE); //enable GIE
  
}


void wait(int ms) {
	int static i, j;
	for(i=ms; i>0; i--)
	 	for(j=200; j>=0; j--);
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void) {
  wait(3);
  
  //check for S2 red led
  if ((P1IFG&BIT2)&& !(P1IN & BIT2))   
  {
    P1OUT ^= BIT0; 	// Toggle P1.0
    P1IFG &=~BIT2; //turn off the flag
  }
  
  //check for S1 green led
    if ((P1IFG&BIT1)&& !(P1IN & BIT1))   
  {
    P9OUT ^= BIT7; 	// Toggle P1.0
    P1IFG &=~BIT1; //turn off the flag
  }
}

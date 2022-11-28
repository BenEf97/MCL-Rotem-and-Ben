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
  if ((P1IV == 0x04)&& !(P1IN & BIT1))   P9OUT ^= BIT7; 	// Toggle P1.0
}

#include "msp430.h"
void main(){
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  P1DIR |= BIT0;			// Set P1.0 to output direction
  TA0R = 0x0000;  
	//ACLK               Up mode    Clear TA0R    No-Divide  Enable Int
  TA0CTL = TASSEL__ACLK + MC__UP +  TACLR    +  ID__1    +   TAIE;
  TA0CCR0 = 32768;			// setting upper limit
  TA0CCR0*=0.25; //faster by 4 times.
  _BIS_SR (LPM3_bits + GIE);
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer (void) {
	if (TA0IV == 0x0E) P1OUT ^= BIT0;// Toggle P1.0
}

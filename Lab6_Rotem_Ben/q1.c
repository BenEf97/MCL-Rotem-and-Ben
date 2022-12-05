#include "msp430.h"
void main(){
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  P1DIR |= BIT0; // Set P1.0 to output direction
  //P1OUT &= ~BIT0;
  TA0R = 0x0000;  
	//ACLK               Up mode    Clear TA0R    No-Divide  Enable Int
  TA0CTL = TASSEL__ACLK + MC__UP +  TACLR    +  ID__1    ;
  TA0CCTL0=CCIE;
  TA0CCR0 = 32768;
  _BIS_SR (LPM3_bits + GIE);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer (void) {
          P1OUT ^= BIT0;// Toggle P1.
          

}



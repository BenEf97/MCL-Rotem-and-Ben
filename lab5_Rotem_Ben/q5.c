#include "msp430.h"
void main(){
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  P1DIR |= BIT0;			// Set P1.0 to output direction
  P9DIR |= BIT7;			// Set P9.7 to output direction
  TA0R = 0x0000;  
	//ACLK               Up/Down mode    Clear TA0R    No-Divide  Enable Int
  TA0CTL = TASSEL__ACLK + MC_3 +  TACLR    +  ID__1    +   TAIE;
  TA0CCR0 = 32768;			// setting upper limit
  _BIS_SR (LPM3_bits + GIE);
  P1OUT |= BIT0;
  P9OUT &= ~BIT7;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer (void) {
	if (TA0IV == 0x0E)
        {
          P1OUT ^= BIT0;// Toggle P1.0
          P9OUT ^= BIT7;// Toggle P9.7
        }
}
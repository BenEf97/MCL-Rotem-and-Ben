#include "msp430.h"
void main(){
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  
   //Teritery moudle fucntion is selected.
  P1SEL0 =BIT7; 
  P1SEL1 =BIT7;

  P1DIR |=BIT7;	 //set LED DIR

  TA0CTL = TASSEL__ACLK | MC__UP | TACLR;	//  ACLK, UPMODE
  TA0CCR0 = 32768/1000;				//  1m second cycle time
  TA0CCTL2 = OUTMOD_2;			//  Set reset
  TA0CCR2 = TA0CCR0>>2;			//  25% duty cycle

  _BIS_SR (LPM3_bits + GIE);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer (void) {
          P1OUT ^= BIT0;// Toggle P1.

}



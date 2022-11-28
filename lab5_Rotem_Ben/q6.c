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
  TA0CCR0/=8;
  
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



void wait(int ms) {
	int static i, j;
	for(i=ms; i>0; i--)
	 	for(j=200; j>=0; j--);
}

#pragma vector = PORT1_VECTOR
__interrupt void port_1 (void)
{
 wait(10); 
  switch(P1IV)
  {
    //reset both leds to start together
    case(0x04):
    P1OUT &= ~BIT0;
    P9OUT &= ~BIT7; 
    break;
    case(0x06):
    //reset both leds to start together
    P1OUT |= BIT0;
    P9OUT &= ~BIT7; 
    break;
  }
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer (void) {  
  if (TA0IV == 0x0E)
        {
          P1OUT ^= BIT0;// Toggle P1.0
          P9OUT ^= BIT7;// Toggle P9.7
        }
}

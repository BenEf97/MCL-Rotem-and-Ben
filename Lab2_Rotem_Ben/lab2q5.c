
#include "msp430.h"
 void wait(int ms);

void main(){
  WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  
  //red led
  P1DIR |= BIT0;				// Set P1.0 to output direction
  P1REN  |= 0xFE;                                                //Enable P1.1 to p1.7 Resistor
  P1OUT |= 0xFE;                                               // and connect them to pull ups
  
  //green led
  P9DIR |= BIT7;				// Set P1.0 to output direction
  P9REN  |= ~BIT7;                                                //Enable P1.1 to p1.7 Resistor
  P9OUT |= ~BIT7;                                               // and connect them to pull ups
  while (1) {
P9OUT ^=BIT7; //g on
wait (1000);
P9OUT ^=BIT7; //g off
P1OUT ^=BIT0; //r on
wait (1000);
P9OUT ^=BIT7; //g on
wait (1000);
P9OUT ^=BIT7; //g off
P1OUT ^=BIT0; //r off
wait (1000); //no lights
  }
}
void wait(int ms) {
	int i, j;
	for(i=0; i<ms; i++)
          for(j=0; j<200; j++);     }

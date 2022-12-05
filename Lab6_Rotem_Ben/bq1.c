#include "msp430.h"
/*#define SI0 2085
#define DO 2001
#define RE 1786
#define MI 1584
#define FA 1496
#define SOL 1332
#define LA 1194
#define SI 1044
#define DO2 1001
#define MUTE 0		// no signal at all*/

#define SI0 65
#define DO 62   
#define RE 55
#define MI 49
#define FA 46
#define SOL 41
#define LA 37
#define SI 32
#define DO2 31
#define MUTE 0		// no signal at all
unsigned int space[] =  {SOL, MI,MI, MUTE, FA, RE, RE, MUTE, DO,RE,MI,FA,SOL,SOL,SOL, MUTE};  // play Do, Re, Me, etc
int idx=0;
  
  
void main(){
  WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;		// Clear locked IO Pins
  
   //Teritery moudle fucntion is selected.
  P1SEL0 =BIT7; 
  P1SEL1 =BIT7;

  P1DIR |=BIT7;	 //set LED DIR

  TA1CTL = TASSEL__ACLK | MC__UP | TACLR+ ID__1                + TAIE;
  TA1CCR0 = 32768;				
  
  TA0CTL = TASSEL__ACLK | MC__UP | TACLR;	//  ACLK, UPMODE
  TA0CCR0 = 0;				//  1m second cycle time
  TA0CCTL2 = OUTMOD_2;			//  Set reset
  TA0CCR2 = TA0CCR0>>1;			//  50% duty cycle

  _BIS_SR (LPM3_bits + GIE);
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer (void) {
  if(TA1IV == 0x0E) {
       TA0CCR0 = space[idx];				
  TA0CCTL2 = OUTMOD_2;			
  TA0CCR2 = TA0CCR0>>1;
  if (idx==16) idx=0;
  else idx++;
           // P1OUT ^= BIT0;// Toggle P1.
  }
}



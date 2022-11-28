#include "LCD_Utilities.h"
const unsigned int lcd_char[26] = {
 
  0x00EF, // A=0
  0x50F1, // B=1
  0x009C, // C=2
  0x50F0, // D=3
  0x009F, // E=4
  0x008F, // F=5
  0x00BD, // G=6
  0x006F, // H=7
  0x5090, // I=8
  0x0078, // J=9
  0x220E, // K=10
  0x001C, // L=11
  0xA06C, // M=12
  0x826C, // N=13
  0x00FC, // O=14
  0x00CF, // P=15
  0x02FC, // Q=16
  0x02CF, // R=17
  0x80B1, // S=18
  0x5080, // T=19
  0x007C, // U=20
  0x280C, // V=21
  0x0A6C, // W=22
  0xAA00, // X=23
  0x1047, // Y=24
  0x2890  // Z=25
};

void LCDInit ()
{
    PJSEL0 = BIT4 | BIT5;                   // For LFXT

    // Initialize LCD segments 0 - 21; 26 - 43
    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure LFXT 32kHz crystal
    CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
    CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
    do
    {
      CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
      SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
    CSCTL0_H = 0;                           // Lock CS registers

    // Initialize LCD_C
    // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;

    // VLCD generated internally,
    // V2-V4 generated internally, v5 to ground
    // Set VLCD voltage to 2.60v
    // Enable charge pump and select internal reference for it
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;

    LCDCCPCTL = LCDCPCLKSYNC;               // Clock synchronization enabled

    LCDCMEMCTL = LCDCLRM;                   // Clear LCD memory
      LCDCCTL0 |= LCDON;

 }

void LCD_All_On(){

	int i; //init idx
	char *ptr = 0; //ptr->0
	ptr += 0x0A20;		// LCD memory starts at 0x0A20
	for (i = 0;i<21;i++) //for every segment
		*ptr++ = 0xFF; //turn 1

}



void LCD_All_Off(){

	int i;
	char *ptr = 0;
	ptr += 0x0A20;		// LCD memory starts at 0x0A20
	for (i = 0;i<21;i++)
		*ptr++ = 0x0;
}


void Display_Number(long n){

int i=0;
  const unsigned char lcd_num[10] = { 0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE4,  0xFF, 0xF7};
    char *Ptr2Num[6] = {0};
    Ptr2Num[0] +=0xA29;
    Ptr2Num[1] +=0xA25;
    Ptr2Num[2] +=0xA23;
    Ptr2Num[3] +=0xA32;
    Ptr2Num[4] +=0xA2E;
    Ptr2Num[5] +=0xA27;
     LCD_All_Off();
     if(n<0){
    	n=-n;
    	SIGN_LESS_ON;
     }  
     if (n>999999){
    	SIGN_ERR_ON;
    	return;
     }
   do
   {
        *Ptr2Num[5-i] = lcd_num[n%10];
         i++;
         n = n/10;  // wastefull!!
    }
    while ( n );
}


void wait(int ms) {
	int static i, j;
	for(i=ms; i>0; i--)
	 	for(j=200; j>=0; j--);
}

void init_Button()
{
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
  //_BIS_SR (LPM3_bits | GIE); //enable GIE
}


void Display_Char(char c,int pose){
  //find the char in the array
  int idx=c-65; //offset for the position in the char array.
  unsigned int low=lcd_char[idx]<<8; //keep only the lower bits
  unsigned int high=lcd_char[idx]>>8; //get the higher bits
  unsigned int *PosLed;
  //find memory for position
  switch (pose)
  {
  case 1:
    PosLed=(unsigned int*)0x0A29; //A1 led
    break;
  case 2:
    PosLed=(unsigned int*)0x0A25; //A2 led
    break;
  case 3:
    PosLed=(unsigned int*)0x0A23; //A3 led
    break;
  case 4:
    PosLed=(unsigned int*)0x0A32; //A4 led
    break;
  case 5:
    PosLed=(unsigned int*)0x0A2E; //A5 led
    break;
  case 6:
    PosLed=(unsigned int*)0x0A27; //A6 led
    break;
  }
  *PosLed=low;
  PosLed++;
  *PosLed=high;
  PosLed++;

}
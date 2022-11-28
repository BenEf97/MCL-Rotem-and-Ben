#include "msp430.h"
#ifndef INC
#define INC
#define HRT_ON  (LCDM3 |= BIT2);
#define HRT_OFF (LCDM3 &= ~BIT2);
#define SIGN_LESS_ON (LCDM11 |= NEG);
#define SIGN_LESS_OFF (LCDM11 &= ~NEG);
#define SIGN_ERR_ON (LCDM8 = ERR);

#define NEG 0x04
#define ERR  0x9F

//define A1
#define A1_0 LCDM10  =  lcd_num[0];      // A1=0
#define A1_1 LCDM10  =  lcd_num[1];      // A1=1
#define A1_2 LCDM10  =  lcd_num[2];      // A1=2
#define A1_3 LCDM10  =  lcd_num[3];      // A1=3
#define A1_4 LCDM10  =  lcd_num[4];      // A1=4
#define A1_5 LCDM10  =  lcd_num[5];      // A1=5
#define A1_6 LCDM10  =  lcd_num[6];      // A1=6
#define A1_7 LCDM10  =  lcd_num[7];      // A1=7
#define A1_8 LCDM10  =  lcd_num[8];      // A1=8
#define A1_9 LCDM10  =  lcd_num[9];      // A1=9


//define A2
#define A2_0 LCDM6  =  lcd_num[0];      // A2=0
#define A2_1 LCDM6  =  lcd_num[1];      // A2=1
#define A2_2 LCDM6  =  lcd_num[2];      // A2=2
#define A2_3 LCDM6  =  lcd_num[3];      // A2=3
#define A2_4 LCDM6  =  lcd_num[4];      // A2=4
#define A2_5 LCDM6  =  lcd_num[5];      // A2=5
#define A2_6 LCDM6  =  lcd_num[6];      // A2=6
#define A2_7 LCDM6  =  lcd_num[7];      // A2=7
#define A2_8 LCDM6  =  lcd_num[8];      // A2=8
#define A2_9 LCDM6  =  lcd_num[9];      // A2=9

//define A3
#define A3_0 LCDM4  =  lcd_num[0];      // A3=0
#define A3_1 LCDM4  =  lcd_num[1];      // A3=1
#define A3_2 LCDM4  =  lcd_num[2];      // A3=2
#define A3_3 LCDM4  =  lcd_num[3];      // A3=3
#define A3_4 LCDM4  =  lcd_num[4];      // A3=4
#define A3_5 LCDM4  =  lcd_num[5];      // A3=5
#define A3_6 LCDM4  =  lcd_num[6];      // A3=6
#define A3_7 LCDM4  =  lcd_num[7];      // A3=7
#define A3_8 LCDM4  =  lcd_num[8];      // A3=8
#define A3_9 LCDM4  =  lcd_num[9];      // A3=9


//define A4
#define A4_0 LCDM19  =  lcd_num[0];      // A4=0
#define A4_1 LCDM19  =  lcd_num[1];      // A4=1
#define A4_2 LCDM19  =  lcd_num[2];      // A4=2
#define A4_3 LCDM19  =  lcd_num[3];      // A4=3
#define A4_4 LCDM19  =  lcd_num[4];      // A4=4
#define A4_5 LCDM19  =  lcd_num[5];      // A4=5
#define A4_6 LCDM19  =  lcd_num[6];      // A4=6
#define A4_7 LCDM19  =  lcd_num[7];      // A4=7
#define A4_8 LCDM19  =  lcd_num[8];      // A4=8
#define A4_9 LCDM19  =  lcd_num[9];      // A4=9


//define A5
#define A5_0 LCDM15  =  lcd_num[0];      // A5=0
#define A5_1 LCDM15  =  lcd_num[1];      // A5=1
#define A5_2 LCDM15  =  lcd_num[2];      // A5=2
#define A5_3 LCDM15  =  lcd_num[3];      // A5=3
#define A5_4 LCDM15  =  lcd_num[4];      // A5=4
#define A5_5 LCDM15  =  lcd_num[5];      // A5=5
#define A5_6 LCDM15  =  lcd_num[6];      // A5=6
#define A5_7 LCDM15  =  lcd_num[7];      // A5=7
#define A5_8 LCDM15  =  lcd_num[8];      // A5=8
#define A5_9 LCDM15  =  lcd_num[9];      // A5=9


//define A6
#define A6_0 LCDM8  =  lcd_num[0];      // A6=0
#define A6_1 LCDM8  =  lcd_num[1];      // A6=1
#define A6_2 LCDM8  =  lcd_num[2];      // A6=2
#define A6_3 LCDM8  =  lcd_num[3];      // A6=3
#define A6_4 LCDM8  =  lcd_num[4];      // A6=4
#define A6_5 LCDM8  =  lcd_num[5];      // A6=5
#define A6_6 LCDM8  =  lcd_num[6];      // A6=6
#define A6_7 LCDM8  =  lcd_num[7];      // A6=7
#define A6_8 LCDM8  =  lcd_num[8];      // A6=8
#define A6_9 LCDM8  =  lcd_num[9];      // A6=9


void LCDInit ();
void LCD_All_On();
void LCD_All_Off();
void Display_Number(long n);
void wait(int ms);
void init_Button();
void Display_Char(char c,int pose);
#endif
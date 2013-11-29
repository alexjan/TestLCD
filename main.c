#include "MacroDef.h"



void DelayuS(unsigned char);
void DelaymS(unsigned char);
void FirstINIFunc(void);
void putst(unsigned char *);
void putch (unsigned char);
void LcdWR(unsigned char, unsigned char);
void InitLCD(void);
void ClrScrn (void);
void PutBCDlong (unsigned long);
unsigned char Keyboard(void);
unsigned char  scanch(void);

bit LineLCD = 0;

void main(void){
	SP = HEAD_Stack;
  	FirstINIFunc();
	InitLCD();
	while(1);  
}

void TimerFunc (void) interrupt Timer0 using 2{

}


#include "MacroDef.h"

 bit LineLCD;

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
unsigned char mSecond;
							 /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
unsigned char code Kyrilica[]={						 															\
					/* 0 */		0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,\
					/* 1 */		0xA8,0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,\
					/* 2 */		0xB1,0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,\
					/* 3 */		0x6F,0xBE,0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,\
					/* 4 */		0xC6,0xC7};
					/* 0	   	А    Б    В    Г    Д    Е    Ж    З    И    Й    К    Л    М    Н    О
					 * 1	  	П    Р    С    Т    У    Ф    Х    Ц    Ч    Ш    Щ    Ъ    Ы    Ь    Э    Ю
					 * 2	   	Я    а    б    в    г    д    е    ж    з    и    й    к    л    м    н
					 * 3	 	о    п    р    с    т    у    ф    х    ц    ч    ш    щ    ъ    ы    ь    э
					 * 4	 	ю    я                                                                          */

unsigned char code *TestString = "Отладка кнопок!\n",			\
					*TestString2 ="Push any Buttom.\n" ;

void main(void){
  	unsigned char counter,Var;
	LineLCD = false;
	SP = HEAD_Stack;
  	FirstINIFunc();
	InitLCD();
	putst(TestString);
	counter = 4;
	while(counter--)DelaymS(250);
	putst(TestString2);
	while(++counter < 5)DelaymS(250);
	ClrScrn();
	while(1){
		switch (Var = Keyboard())
		{
			case 'A':
				putst ("Litry\n");
				break;
			case 'B':
				putst ("Summa\n");
				break;
			case 'C':
				putst ("Sbros\n");
				break;
			case 'D':
				putst ("Pusk\n");
				break;
			case 'E':
				putst ("Stop\n");
				break;
			case 'F':
				putst ("Gun\n");
				break;
			default: putch(Var);
		}
	}  
}

void TimerFunc (void) interrupt Timer0 using 2{

}


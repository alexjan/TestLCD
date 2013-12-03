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
void LcdSetPosition(unsigned char);
unsigned char mSecond;
							 /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
unsigned char code Kyrilica[]={						 															\
					/* 0 */		0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,\
					/* 1 */		0xA8,0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,\
					/* 2 */		0xB1,0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,\
					/* 3 */		0x6F,0xBE,0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,\
					/* 4 */		0xC6,0xC7};
					/* 0	   	�    �    �    �    �    �    �    �    �    �    �    �    �    �    �
					 * 1	  	�    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
					 * 2	   	�    �    �    �    �    �    �    �    �    �    �    �    �    �    �
					 * 3	 	�    �    �    �    �    �    �    �    �    �    �    �    �    �    �    �
					 * 4	 	�    �                                                                          */

unsigned char code *Header_str1 = "  ����  ������\n",			\
				   *Header_str2 = "   ������ 1.0\n" ;

void main(void){
  	unsigned char counter,Var;
	di();
	LineLCD = false;
	SP = HEAD_Stack;
  	FirstINIFunc();
	TR0 = true;
	ET0 = true;
	InitLCD();
	ei();
	putst(Header_str1);
	putst(Header_str2);
	counter = 10;
	while(--counter)DelaymS(200);
    ClrScrn();

	while(1){	
		
		switch (Var = Keyboard())
		{
			case 'A':
				putst ("    ������.\n");
				while(Var != 'C'){
					counter = 10;
					while(--counter)DelaymS(200);
// 					putch('\n');
					LcdSetPosition(0);
					putst ("������� �������������� �������.\n");
					Var = Keyboard();
					ClrScrn();
// 					LcdSetPosition(0);
					switch (Var)
					{
						case '1': putst("������������ ������.\n");
							break;
						case '2': putst("���./����. ������� �� �������.\n");
							break;
						case '3': putst("��������� ������� �������.\n");	
							break;
						case '4': putst("���./����. ������.\n");
							break;
						case '5': putst("���./����. ����� ���.\n");
							break;
						case '6': putst("���./����. ����� ��������.\n");
							break;
						case '7': putst("��������� ����� �����.\n");
							break;
						case '8': putst("�������� �������� �����.\n");
							break;
						case 'C': ;
							break;
						default : putst("�� ������������.\n");					
					}													
				};
            				
				break;
			case 'B': putst ("Summa\n");
				break;
			case 'C': putst ("Sbros\n");
				break;
			case 'D': putst ("  ���� \n");
				
				
				
				
				
				
				break;
			case 'E':
				putst ("Stop \n");
				break;
			case 'F':
				putst ("Gun  \n");
				break;
			default: putst("1-keyb 2-on/off power \n");
		}
	}  
}

void TimerFunc (void) interrupt Timer0 {
	static unsigned char Counter;
	if(++Counter > 2)	{
		Counter = 0;
		CLRWDT();
	}

}

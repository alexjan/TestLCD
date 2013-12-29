#include "MacroDef.h"



void DelayuS(unsigned char);
void DelaymS(unsigned char);
void FirstINIFunc(void);
void putst(unsigned char *);
void putch (unsigned char);
void LcdWR(unsigned char, unsigned char);
void InitLCD(void);
void SetAdr (unsigned char);
void ClrScrn (void);
void PutBCDlong (unsigned long);
unsigned char Keyboard(void);
unsigned char  scanch(void);
void LcdSetPosition(unsigned char);
void PutBCDint(unsigned int);
unsigned int HextoBcd(unsigned int);
unsigned int HexBcd(unsigned int);
unsigned char mSecond, DelayT1, CharK, ImpWidth;
unsigned int CountIn, CountOut;
static bit LOWFlagOut, HIFlagIn, HIFlagOut, Gun, RefreshBit, RunOutImp,WRimp;
bit BreakFlag;

							 /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F  */
unsigned char code Kyrilica[]={						 															\
					/* 0 */		0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,\
					/* 1 */		0xA8,0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,\
					/* 2 */		0xB1,0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,\
					/* 3 */		0x6F,0xBE,0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,\
					/* 4 */		0xC6,0xC7};
					/* 0	   	À    Á    Â    Ã    Ä    Å    Æ    Ç    È    É    Ê    Ë    Ì    Í    Î
					 * 1	  	Ï    Ð    Ñ    Ò    Ó    Ô    Õ    Ö    ×    Ø    Ù    Ú    Û    Ü    Ý    Þ
					 * 2	   	ß    à    á    â    ã    ä    å    æ    ç    è    é    ê    ë    ì    í
					 * 3	 	î    ï    ð    ñ    ò    ó    ô    õ    ö    ÷    ø    ù    ú    û    ü    ý
					 * 4	 	þ    ÿ                                                                          */

unsigned char code *Header_str1 = "Out ->\n",			\
				   *Header_str2 = " In ->\n" ;

void main(void){
//   	unsigned char counter,Var;
	di();
    CountIn = 0;
	SP = HEAD_Stack;
  	FirstINIFunc();
	TR0 = true;
	ET0 = true;
    TR1 = true;
 	ET1 = true;
    InitLCD();
	ei();
	putst(Header_str1);
    putst(Header_str2);
    SetAdr(6);
    PutBCDint(CountOut);
    SetAdr(22);
    PutBCDint(CountIn);
    SetAdr(13); 
    if(Gun) putst("Off\n");
    else putst("On \n");
     GunDetect = true;
     InputCNT = true;
	while(1){
       switch(CharK = Keyboard()){
            case '6':     
                RunOutImp = !RunOutImp;
                break;
            case '8':
                SetAdr(6);
                PutBCDint(CountOut = HextoBcd(CountOut += 0x10));
                break;
            case '3': 
                SetAdr(13); 
                if(Gun = !Gun) putst("Off\n");
                else putst("On \n");
                break;  
             default :
                 SetAdr(6);
                 PutBCDint(CountOut = HexBcd(CountOut));
                 SetAdr(22);
                 PutBCDint(CountIn = HextoBcd(CountIn));
                 SetAdr(29);
                 if(GunDetect) putst("Off\n");
                 else putst("On \n");
                 
            }
            
            if (RunOutImp){
                if (CountOut){
                    if(WRimp){
                        OutputCNT = true;
//                         CountOut = HextoBcd(CountOut--);
                        CountOut--;
                        WRimp = false;
                        DelaymS(5);
                    }
                    else { 
                        OutputCNT = false;
                        WRimp = true;
                        DelaymS(5);
                    }
                }
                else {
                    RunOutImp = false;
                    CountIn = 0;
                }
            }
            
    }	  
}

void TimerFunc1 (void) interrupt Timer0 {
	static unsigned char Counter;
    if(++Counter > 2)	{
		Counter = 0;      
        CLRWDT();
	}
}

void TimerFunc2 (void) interrupt Timer1 {
    static bit RDimp;
    if(++DelayT1 > 38)	{
        
        if(RDimp && InputCNT){
            CountIn++;
            RDimp = false;
        }
        else if (!InputCNT) RDimp = true;
//         WRimp = true;
        GunOutput = Gun;
        BreakFlag = true;
		DelayT1 = 0;
//         HIFlagOut = true;
    }
}


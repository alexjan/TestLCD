#include "MacroDef.h"

void InitLCD(void);
void LcdWR(unsigned char, unsigned char);
void DelaymS(unsigned char);
void DelayuS(unsigned char);
void ClrScrn(void);
unsigned char scanch(void);
void SetAdr (unsigned char);
// void PutBCDlong(unsigned long);
unsigned int HextoBcd(unsigned int);
                            /*   5   lit  sto   2   sbr   3    4    1    0   sum  pus   7   gun   8    9    6  empty */						                                                                                          
unsigned char code KeyCode[] = {'5', 'A', 'E', '2', 'C', '3', '4', '1', '0', 'B', 'D', '7', 'F', '8', '9', '6', 'Z'};
                            

extern unsigned char code Kyrilica[];
static unsigned char CharPos;
extern  bit BreakFlag;

void FirstINIFunc(void) {

    P3 = 11111111;
    //   |||||||+-----> RxD
    //   ||||||+------> TxD
    //   |||||+-------> PowerDown
    //   ||||+--------> CashInput
    //   |||+---------> WDT ---> Data0
    //   ||+----------> CashOutput
    //   |+-----------> ----------
    //   +------------> LedValve
	
    P1 = 11111111;
    //   |||||||+-----> PowerTRK
    //   ||||||+------> Pump
    //   |||||+-------> CLK for 4015
    //   ||||+--------> RS ---> Data1
    //   |||+---------> WR
    //   ||+----------> BackLight LCDmodul
    //   |+-----------> KeybLine1
    //   +------------> KeybLine0


    PSW = 0;

    TCON = 0x10;        //     00010000;
                        //     |||||||+--->  IT0
                        //     ||||||+---->  IE0
                        //     |||||+----->  IT1
                        //     ||||+------>  IE1
                        //     |||+------->  TR0
                        //     ||+-------->  TF0
                        //     |+--------->  TR1
                        //     +---------->  TF1

    SCON = 0xC0;        //     11000000;
                        //     |||||||+--->  RI
                        //     ||||||+---->  TI
                        //     |||||+----->  RB8
                        //     ||||+------>  TB8
                        //     |||+------->  REN
                        //     ||+-------->  SM2
                        //     |+--------->  SM1
                        //     +---------->  SM0

    TMOD = 0x21;            //     00100001;
                            //     |||||||+--->  T0/M0
                            //     ||||||+---->  T0/M1
                            //     |||||+----->  T0/CT
                            //     ||||+------>  T0/GATE
                            //     |||+------->  T1/M0
                            //     ||+-------->  T1/M1
                            //     |+--------->  T1/CT
                            //     +---------->  T1/GATE

    PCON = 0x80;            //     10000000;
                            //     |||||||+--->  IDL
                            //     ||||||+---->  STOP
                            //     |||||+----->  EWT
                            //     ||||+------>  EPFW
                            //     |||+------->  WTR
                            //     ||+-------->  PFW
                            //     |+--------->  POR
                            //     +---------->  SMOD
//
    IP = 00000000;
    //   |||||||+----->  PX0
    //   ||||||+------>  PT0
    //   |||||+------->  PX1
    //   ||||+-------->  PT1
    //   |||+--------->  PS
    //   ||+---------->
    //   |+----------->
    //   +------------>
//
    IE = 0x12;                  //   00010010;
                                //   |||||||+-----> EX0
                                //   ||||||+------> ET0
                                //   |||||+-------> EX1
                                //   ||||+--------> ET1
                                //   |||+---------> ES
                                //   ||+----------> ET2
                                //   |+----------->
                                //   +------------> EA
//
    TH1 = 0xC8;            //~100 uS 
    TL1 = 0xC8;
    TH0 = 0x80;



}

void InitLCD(void) {
    DelaymS(16);
    LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7, Command);
    DelaymS(5);
    LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7, Command);
    DelayuS(100);
    LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7, Command);
    ClrScrn();
    LcdWR(DispControl & DisplOn & CursLineOff & CursSquOff, Command);
    LcdWR(ModeSet & IncCount & ShiftDis, Command);
    LcdWR(DispCursShift & CursorShift & RightShift, Command);
    //	LcdWR(SetAdressCGRAM & 0x40,Command);			// Not USE Function
    LcdWR(SetAdressDDRAM & 0x80, Command);
}

void LcdWR(unsigned char DataVar, unsigned char mode) {
    unsigned char cnt, DataVarLo,SaveWDT;
	SaveWDT = Dta4015InLo;
    DataVarLo = DataVar << 4;
    for (cnt = 0; cnt < 4; cnt++) {
        DataVarLo <<= 1;
        Dta4015InLo = CY;
        DataVar <<= 1;
        Dta4015InHi = CY;
        Clock4015 = false;
        Clock4015 = true;
    }
    CmdDtaLcd = mode;
    StrobLcd = true;
    StrobLcd = false;
	Dta4015InLo = SaveWDT;
}

void SetAdr (unsigned char adr){
//     unsigned char Adres;
//     CharPos = adr;
    CharPos = adr | 0x20;                         //001SAAAAB
    CharPos &= 0xF0;                              //001S0000B
    CharPos <<= 2;                                //1S000000B
    CharPos |= adr & 0x0F;                        //1S00AAAAB
    LcdWR(CharPos,Command);                       //
    CharPos = adr;
}


void putch(unsigned char Char) {
    if (Char == '\n') {
        if(CharPos < 16) CharPos = 16;
        else CharPos = 0;
        SetAdr(CharPos);
    } 
	else {
        if (Char > 0x7F) Char = Kyrilica[Char - 0xC0];
		LcdWR(Char, Data);
        switch(++CharPos){
            case 16 : SetAdr(16);
                break;
            case 32 : SetAdr(0);
                      CharPos = 0;  
                break;
            default : ;
        }
        
	}
}

void DelayuS(unsigned char num) {
    while (--num);
}

void DelaymS(unsigned char number) {
    unsigned char i;
    do {
        for (i = 4; i > 0; --i)
            DelayuS(246);
    } while (--number);
}

void ClrScrn(void) {
    LcdWR(ClrScreen, Command);
    CharPos = 0;
    DelaymS(5);
}

// void PutBCDlong(unsigned long VarBCD) {
//     if (VarBCD & 0xF00000) putch((unsigned char) ((VarBCD >> 20) & 0x0F) + 0x30);
//     else putch(' ');
//     if (VarBCD & 0x0F0000) putch((unsigned char) ((VarBCD >> 16) & 0x0F) + 0x30);
//     else putch(' ');
//     if (VarBCD & 0x00F000) putch((unsigned char) ((VarBCD >> 12) & 0x0F) + 0x30);
//     else putch(' ');
//     putch(((unsigned char) ((VarBCD >> 8) & 0x0F)) + 0x30);
//     putch('.');
//     putch(((unsigned char) ((VarBCD >> 4) & 0x0F)) + 0x30);
//     putch(((unsigned char) (VarBCD & 0x0F)) + 0x30);
// //     putch('\n');
// }
void PutBCDint(unsigned int VarBCDint) {
    bit Show = false;
    if (VarBCDint & 0xF000) {
        putch((unsigned char) ((VarBCDint >> 12) & 0x0F) + 0x30);
        Show = true;
    }
    else putch(' ');
    
    if (VarBCDint & 0x0F00 || Show) {
        putch((unsigned char) ((VarBCDint >> 8) & 0x0F) + 0x30);
        Show = true;
    } 
    else putch(' ');
    
    if (VarBCDint & 0x00F0 || Show) putch((unsigned char) ((VarBCDint >> 4) & 0x0F) + 0x30);
    else putch(' ');
    
    putch(((unsigned char) (VarBCDint & 0x0F)) + 0x30);
//     putch('\n');
}

unsigned int HextoBcd(unsigned int dat){
    unsigned char cnt = 0;
    do{
        if((dat >> (cnt << 2) & (unsigned int)0x0F) > 9) dat += (unsigned int)0x06 << (cnt << 2);
    }while(++cnt < 4);
    return dat;
}
unsigned int HexBcd(unsigned int dat){
    unsigned char cnt = 0;
    do{
        if((dat >> (cnt << 2) & (unsigned int)0x0F) > 9) dat -= (unsigned int)0x06 << (cnt << 2);
    }while(++cnt < 4);
    return dat;
}

void putst(unsigned char *string) {
	do {
		putch(*(string++));
	} while (*string != '\n');
		putch('\n');
}

unsigned char Keyboard(void) {
    unsigned char Buttom,TimeCnt = 0;
	while ((Buttom = scanch()) == KeyCode[empty]) {
        DelaymS(20);
        if(BreakFlag){
            BreakFlag = false;
            return Buttom;
        }
        
    }        
	DelaymS(20);
	while (Buttom == scanch()){
        if(++TimeCnt < 15)DelaymS(20);
        else return Buttom;
    }
	return Buttom;
}

unsigned char scanch(void) {
    unsigned char cnt,  ScanCnt, SaveWDT;
    bit PushButtom = false;
	SaveWDT = Dta4015InLo;
    ScanCnt = 0;
    StrobLcd = false;
    Dta4015InLo = true;
    Dta4015InHi = true;
    cnt = 3;
    do {
        Clock4015 = false;
        Clock4015 = true;
    } while (--cnt);

    Dta4015InLo = false;
    Clock4015 = false;
    Clock4015 = true;
    Dta4015InLo = true;

    do {
        cnt = 0;
        do {
            if (KeybLine1) {
                if (KeybLine0) {
                    Clock4015 = false;
                    Clock4015 = true;
                } else {
					Dta4015InLo = SaveWDT;
					return KeyCode[cnt + (ScanCnt << 2) + 8];
				}
            } else {
				Dta4015InLo = SaveWDT;
				return KeyCode[cnt + (ScanCnt << 2)];
			}
        } while (++cnt < 4);

        Dta4015InHi = false;
        Clock4015 = false;
        Clock4015 = true;
        Dta4015InHi = true;

    } while (++ScanCnt < 2);
	Dta4015InLo = SaveWDT;
    return KeyCode[empty];
}


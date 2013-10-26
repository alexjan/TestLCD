#include "MacroDef.h"

void InitLCD(void);
void LcdWR(unsigned char, unsigned char);
void DelaymS(unsigned char);
void DelayuS(unsigned char);
void ClrScrn (void);
void PutBCDlong(unsigned long);

unsigned char code KeyCode[2][2][4] = {{'1','2','3','4'},{0,0,0,0,},{0,0,0,0},{0,0,0,0}};


extern bit LineLCD;
extern unsigned char code Kyrilica[];

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
while(cnt--){
		Clock4015 = false;
		Clock4015 = true;
	}
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

//     TCON = 00000001;
//     //     |||||||+--->  IT0
//     //     ||||||+---->  IE0
//     //     |||||+----->  IT1
//     //     ||||+------>  IE1
//     //     |||+------->  TR0
//     //     ||+-------->  TF0
//     //     |+--------->  TR1
//     //     +---------->  TF1

//     SCON = 11000000;
//     //     |||||||+--->  RI
//     //     ||||||+---->  TI
//     //     |||||+----->  RB8
//     //     ||||+------>  TB8
//     //     |||+------->  REN
//     //     ||+-------->  SM2
//     //     |+--------->  SM1
//     //     +---------->  SM0

//     TMOD = 00100001;
//     //     |||||||+--->  TO/M0
//     //     ||||||+---->  T0/M1
//     //     |||||+----->  TO/CT
//     //     ||||+------>  TO/GATE
//     //     |||+------->  T1/M0
//     //     ||+-------->  T1/M1
//     //     |+--------->  T1/CT
//     //     +---------->  T1/GATE

//     PCON = 10000000;
//     //     |||||||+--->  IDL
//     //     ||||||+---->  STOP
//     //     |||||+----->  EWT
//     //     ||||+------>  EPFW
//     //     |||+------->  WTR
//     //     ||+-------->  PFW
//     //     |+--------->  POR
//     //     +---------->  SMOD
//     
//     IP = 00000001;
//     //   |||||||+----->  PX0
//     //   ||||||+------>  PT0
//     //   |||||+------->  PX1
//     //   ||||+-------->  PT1
//     //   |||+--------->  PS
//     //   ||+---------->
//     //   |+----------->
//     //   +------------>
//     
//     IE = 00010011;
//     //   |||||||+-----> EX0
//     //   ||||||+------> ET0
//     //   |||||+-------> EX1
//     //   ||||+--------> ET1
//     //   |||+---------> ES
//     //   ||+----------> ET2
//     //   |+----------->
//     //   +------------>
//     
//     TH1 = 0xF3;
//     TL1 = 0xF3;
//     TH0 = 0x80;

    	 

}

void InitLCD(void){
	DelaymS(16);
	LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7,Command);
	DelaymS(5);
	LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7,Command);
	DelayuS(100);
	LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7,Command);
	ClrScrn();		
	LcdWR(DispControl & DisplOn & CursLineOff & CursSquOff,Command);
	LcdWR(ModeSet & IncCount & ShiftDis,Command);	
	LcdWR(DispCursShift & CursorShift & RightShift,Command);
//	LcdWR(SetAdressCGRAM & 0x40,Command);			// Not USE Function
	LcdWR(SetAdressDDRAM & 0x80,Command);
}

void LcdWR(unsigned char DataVar,unsigned char mode){
 	unsigned char cnt, DataVarLo;
	DataVarLo = DataVar << 4;
	for(cnt=0;cnt<4;cnt++){
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
}

void putch(unsigned char Char){
	if(Char > 0x7F) Char = Kyrilica[Char - 0xC0];
	if(Char == '\n') {
		LineLCD = ~LineLCD;
		LineLCD ? LcdWR(SetAdressDDRAM & 0xC0,Command) : LcdWR(SetAdressDDRAM & 0x80,Command);
	}
	else LcdWR(Char,Data);
}

void DelayuS(unsigned char num){
	while (--num);
}

void DelaymS(unsigned char number){
	unsigned char i;
	do{
		for(i=4;i>0;--i)
			DelayuS(246);
	}while(--number);
}

void ClrScrn (void){
	LcdWR(ClrScreen,Command);
	DelaymS(5);
}

void PutBCDlong(unsigned long VarBCD){
	if(VarBCD & 0xF00000)	putch((unsigned char)((VarBCD >> 20) & 0x0F) + 0x30);	
	else putch(' ');
	if(VarBCD & 0x0F0000)	putch((unsigned char)((VarBCD >> 16) & 0x0F) + 0x30);	
	else putch(' ');
	if(VarBCD & 0x00F000)	putch((unsigned char)((VarBCD >> 12) & 0x0F) + 0x30);	
	else putch(' ');
	putch(((unsigned char)((VarBCD >> 8) & 0x0F)) + 0x30);	
	putch('.');
	putch(((unsigned char)((VarBCD >> 4) & 0x0F)) + 0x30);	
	putch(((unsigned char)(VarBCD  & 0x0F))+ 0x30);	
}

void putst(unsigned char *string){
	unsigned char CharCnt = 0;
	bit EndOfString = true; 
	do{
		if(*string == '\n') EndOfString = false;
		putch(*(string++));
		if(++CharCnt > 15) {
			CharCnt = 0;
			LineLCD = ~LineLCD;
			LineLCD ? LcdWR(SetAdressDDRAM & 0xC0,Command) : LcdWR(SetAdressDDRAM & 0x80,Command);
		}	
	}
	while(EndOfString);
}

unsigned char scanch(void){
	unsigned char cnt, Vari, ScanCnt;
	bit PushButtom = false;
	ScanCnt = 0;
	StrobLcd = true;
	Dta4015InLo = true;
	Dta4015InHi = true;
	cnt = 3;
	while(cnt--){		
		Clock4015 = false;
		Clock4015 = true;
	}
	Dta4015InLo = false;
	Clock4015 = false;
	Clock4015 = true;
	Dta4015InLo = true;
		
	do{
		cnt = 0;	
		do{
			if(KeybLine0) {
				Vari = KeyCode[cnt + ScanCnt];
				PushButtom = true;
			}
			if(KeybLine1 && !PushButtom) {
				Vari = KeyCode[cnt + ScanCnt + 4];
				PushButtom = true;
			}
			Clock4015 = false;
			Clock4015 = true;
		}while((++cnt < 4) && !PushButtom);

		Dta4015InHi = false;
		Clock4015 = false;
		Clock4015 = true;
		Dta4015InHi = true;

	}while(++ScanCnt < 2);
	return Vari;
}

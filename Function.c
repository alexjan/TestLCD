#include <MacroDef.h>


void InitLCD(void);
void LcdWR(unsigned char, unsigned char);
void DelaymS(unsigned char);
void DelayuS(unsigned char);

const unsigned char Message1 = 1;


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

    SP = HEAD_Stack;

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

     InitLCD();
}

void InitLCD(void){
	LcdWR(ClrScreen,Command);
	DelaymS(50);
	LcdWR(FunctionSet & DataLenght8b & Num2lStr & Size5x7,Command);	
	LcdWR(DispControl & DisplOn & CursLineOff & CursSquOff,Command);
	LcdWR(ModeSet & IncCount & ShiftDis,Command);	
	LcdWR(DispCursShift & CursorShift & RightShift,Command);
	LcdWR(SetAdressCGRAM & 0x40,Command);
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
// 	while(1);
}

void putch(unsigned char Char){
	LcdWR(Char,Data);
}

// void putst(unsigned char *string){
// 	static unsigned char CharCnt;
// 	while (*string != '\n')	{
// 		putch(*(++string));
// 			if(++CharCnt & 0x1F > 15)	{
// 				LcdWR(CharCnt ^= 0x40, Command);
// 				CharCnt = 0;
// 			}
// 		}
// }

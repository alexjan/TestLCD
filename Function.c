#include <Atmel/AT89x051.h>
//#include <htc.h>

// #define _AT89C2051
#define HEAD_Stack 			0x70
#define Command 			0
#define Data 				1
/* List Command for LCD 44780*/

#define ClrScreen   		0x01		// 0b00000001

#define ReturnHome    		0x03		// 0b00000011

#define ModeSet		  		0x07		// 0b00000111
/* SubCommnads */
#define IncCount 			0xFF		// 0b11111111
#define DecCount 			0xFD		// 0b11111101
#define ShiftEn  			0xFF		// 0b11111111
#define ShiftDis 			0xFE        // 0b11111110 

#define DispControl   		0x0F		// 0b00001111
/* SubCommnads */
#define DisplOn				0xFF	    // 0b11111111  	
#define DisplOff			0xF3		// 0b11111011
#define CursLineOn			0xFF		// 0b11111111
#define CursLineOff			0xFD		// 0b11111101
#define CursSquOn			0xFF		// 0b11111111
#define CursSquOff 			0xFE		// 0b11111110

#define DispCursShift 		0x1F		// 0b00011111
/* SubCommnads */
#define ScreenShift   		0xFF		// 0b11111111
#define CursorShift   		0xF7		// 0b11110111
#define RightShift	  		0xFF		// 0b11111111
#define LeftShift     		0xFB		// 0b11111011

#define FunctionSet   		0x3F		// 0b00111111
/* SubCommnads */
#define DataLenght8b  		0xFF		// 0b11111111
#define DataLenght4b  		0xEF		// 0b11101111
#define Num2lStr    		0xFF		// 0b11111111
#define NumHiStr			0xF7		// 0b11110111
#define Size5x7				0xFF		// 0b11111111
#define Size5x10    		0xFB        // 0b11111011

#define SetAdressCGRAM 		0x7F		// 0b01111111

#define SetAdressDDRAM 		0xFF		// 0b11111111

#define DispStrAdr1str 		0x80	
#define DispStrAdr2str 		0xC0

#define true 1
#define false 0
#define Clock4015 P1_2  
#define CmdDtaLcd P1_3				//Registr Select  0 --> registr command, 1 --> registr data  
#define StrobLcd P1_4				// Chip select 4015 --> strobe exec for 1 -> 0
#define Dta4015InLo P3_4
#define Dta4015InHi P1_3



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

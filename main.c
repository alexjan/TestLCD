#include <Atmel/AT892051.h>
//#include <htc.h>
			
#define ClrScreen   		0x01		// 0b00000001
#define Command 			0
#define Data 				1

#define true 1
#define false 0
#define Clock4015 P1_2  
#define CmdDtaLcd P1_3				//Registr Select  0 --> registr command, 1 --> registr data  
#define StrobLcd P1_4				// Chip select 4015 --> strobe exec for 1 -> 0
#define Dta4015InLo P3_4
#define Dta4015InHi P1_3

void DelayuS(unsigned char);
void DelaymS(unsigned char);
void FirstINIFunc(void);
void putst(unsigned char *);
void putch (unsigned char);
void LcdWR(unsigned char, unsigned char);
void InitLCD(void);


void main(void){
 	unsigned char counter;
	
// 	DelaymS(100);
// 	FirstINIFunc();
//   	InitLCD();
//  	for(counter=0;counter < 0x80;counter++){
// 		LcdWR('8',1);
// 		DelaymS(100);
	LcdWR(0xC6,Command);
	counter = 16;
	while(counter--){
		putch('2');
	}
// 	}
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



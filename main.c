#include <MacroDef.h>

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



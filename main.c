//#include <Atmel/AT892051.h>
#include <htc.h>
			


#define true 1
#define false 0


void DelayuS(unsigned char);
void DelaymS(unsigned char);
void FirstINIFunc(void);
void putst(unsigned char *);


void main(void){
	FirstINIFunc();
	putst("Hello\n");
	
	while (true){
		DelaymS(10);
//		if(true);
	}
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



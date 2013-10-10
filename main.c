#include <Atmel/AT892051.h>
//#include <htc.h>
			


#define true 1
#define false 0


void DelayuS(unsigned char);
void DelaymS(unsigned char);

void main(void){
	while (true){
		DelaymS(10);
//		if(true);
	}
}

void DelayuS(unsigned char number){
	while (--number);
}

void DelaymS(unsigned char number){
	unsigned char i;
	do{
		for(i=4;i>0;--i)
			DelayuS(246);
	}while(--number);
}



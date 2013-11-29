#define Keil //HI-TECH

#ifdef Keil 
	#include <Atmel/AT892051.h>
	
	#define CtrlPowerMCU	P1_0
	#define Pump			P1_1
	#define Clock4015 		P1_2  
	#define CmdDtaLcd 		P1_3				//Registr Select  0 --> registr command, 1 --> registr data  
	#define Dta4015InHi 	P1_3
	#define StrobLcd 		P1_4				// Chip select 4015 --> strobe exec for 1 -> 0
	#define LightLCD		P1_5
	#define Gun				P1_5
	#define KeybLine1 		P1_6
	#define KeybLine0 		P1_7
	
	#define CtrlPowerInput	P3_2
	#define KassaRxD		P3_3
	#define Dta4015InLo 	P3_4
	#define ResetWDT		P3_4
	#define KassaTxD		P3_5
	#define ClapanLed		P3_7

#else
	#ifdef HI-TECH 
		#include <htc.h>
		
		#define CtrlPowerMCU	P10
		#define Pump			P11
		#define Clock4015 		P12  
		#define CmdDtaLcd 		P13				//Registr Select  0 --> registr command, 1 --> registr data  
		#define Dta4015InHi 	P13
		#define StrobLcd 		P14				// Chip select 4015 --> strobe exec for 1 -> 0
		#define LightLCD		P15
		#define Gun				P15
		#define KeybLine1 		P16
		#define KeybLine0 		P17
		
		#define CtrlPowerInput	P32
		#define KassaRxD		P33
		#define Dta4015InLo 	P34
		#define ResetWDT		P34
		#define KassaTxD		P35
		#define ClapanLed		P37

		
	#endif
#endif	

#define HEAD_Stack 			0x70

#define empty				0x11

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

#define true 				1
#define false 				0

#define Command 			false
#define Data 				true

/* Defination of iunterrupt number */

#define INT0 		0
#define Timer0 		1
#define INT1 		2
#define Timer1 		3
#define USART 		4

#define CursorOn()	LcdWR(DispControl & DisplOn & CursLineOn & CursSquOff, Command)
#define CursorOff()	LcdWR(DispControl & DisplOn & CursLineOff & CursSquOff, Command)





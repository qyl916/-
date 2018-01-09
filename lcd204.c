#include"lcd204.h"

#include<reg51.h>

sbit rs = P1 ^ 0;
sbit rw = P1 ^ 1;
sbit en = P1 ^ 2;

static void delay(LCD_UInt t){
	int t0 = (int)t * 120;
	while(t0-- > 0);
}

#define __WRITE_INS(__ins) do{\
	delay(5);\
	P0 = (__ins);\
	rw = 0, rs = 0, en = 1;\
	en = 1;\
}while(0)

#define __WRITE_DATA(__x) do{\
	delay(5);\
	P0 = (__x);\
	rw = 0, rs = 1, en = 1;\
	en = 1;\
}while(0)

void LCD_Init(void){
	P0 = 0xFF;
	rw = 1, rs = 1, en = 1;
	delay(15);
	__WRITE_INS(0x38);
	__WRITE_INS(0x38);
	__WRITE_INS(0x08);
	__WRITE_INS(0x01);
	__WRITE_INS(0x06);
	__WRITE_INS(0x0C);
}

void LCD_Put_Char(LCD_UInt x, LCD_UInt y, LCD_Char ch){
	LCD_UInt vec = 0x80 | ((x & 1) << 6) ;
	vec |= y + ((x & 0x20) ? 20 : 0);
	__WRITE_INS(vec);
	__WRITE_DATA(ch);
}

void LCD_Shift(void){
	__WRITE_INS(0x18);
}
	

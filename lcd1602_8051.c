#include"lcd1602.h"

#include<reg51.h>

sbit rs = P1 ^ 0;
sbit rw = P1 ^ 1;
sbit en = P1 ^ 2;

static LCD_Byte __mode;
static LCD_Byte __display;

static void delay(unsigned n){
	while(n-- > 0);
}

#define WAIT() do{\
	P0 = 0xFF;\
	rs =  0, rw = 1;\
	en = 1;\
	while(P0 & 0x80);\
	en = 0;\
}while(0)

#define __WRITE_DATA(data) do{\
	rs = 1, rw = 0;\
	P0 = (data);\
	en = 1;\
	en = 0;\
}while(0)

#define __WRITE_INS(cmd) do{\
	rs = 0, rw = 0; P0 = cmd;\
	en = 1; en = 0;\
}while(0)

#define WRITE_DATA(data) do{\
	WAIT(); __WRITE_DATA((data));\
}while(0)

#define WRITE_INS(cmd) do{\
	WAIT(); __WRITE_INS((cmd));\
}while(0)


#define __LCD_CLEAR				0x01
#define __LCD_ENTRY_MODE		0x06
#define __LCD_DISPLAY			0x08
#define __LCD_CURSOR_SHIFT		0x10
#define __LCD_DISPLAY_SHIFT		0x18
#define __LCD_FUNCTION			0x30
#define __LCD_CGRAM_ADDR		0x40
#define __LCD_DDRAM_ADDR		0x80



void LCD_Init(LCD_Byte mode){
	__mode = mode;
	__display = __LCD_DISPLAY;
	rs = 1, rw = 1, en = 1;
	P0 = 0xFF;
	delay(600);
	__WRITE_INS(mode);
	delay(200);
	__WRITE_INS(mode);
	__WRITE_INS(__LCD_DISPLAY);
	__WRITE_INS(__LCD_CLEAR);
	__WRITE_INS(__LCD_ENTRY_MODE);
}


void LCD_Set_Glyph(LCD_UInt id, LCD_Bytes data){
	LCD_UInt len =  (__mode == LCD_MODE_1LINE_5X10DOT ? 10 : 7);
	id &= (__mode == LCD_MODE_1LINE_5X10DOT ? 0x03 : 0x07);
	WRITE_INS((id << 3) | __LCD_CGRAM_ADDR);
	while(len-- > 0) WRITE_DATA(*data++);
}

void LCD_Put_Char(LCD_Vector pos, LCD_Char ch){
	WRITE_INS(pos | __LCD_DDRAM_ADDR);
	WRITE_DATA(ch);
}

void LCD_Put_String(LCD_Vector pos, LCD_String str, LCD_UInt num){
	LCD_UInt maxn = 40 - LCD_VECTOR_X(pos);
	if(num > maxn) num = maxn;
	WRITE_INS(pos | __LCD_DDRAM_ADDR);
	while(num-- > 0) WRITE_DATA(*str++);
}

void LCD_Clear(void){
	WRITE_INS(__LCD_CLEAR);
}

void LCD_Shift_Cursor(LCD_Byte direction){
	WRITE_INS(__LCD_CURSOR_SHIFT | (direction & 0x04));
}

void LCD_Shift_Display(LCD_Byte direction){
	WRITE_INS(__LCD_DISPLAY_SHIFT | (direction & 0x04));
}

void LCD_Display_Switch(LCD_Byte mode){
	__display &= mode;
	WRITE_INS(__LCD_DISPLAY | __display);
}

void LCD_Set_Cursor_Mode(LCD_Byte flags){
	__display &= flags;
	WRITE_INS(__LCD_DISPLAY | __display);
}

void LCD_Set_Cursor_Position(LCD_Vector pos){
	WRITE_INS(pos | __LCD_DDRAM_ADDR);
}


	


#ifndef __LCD204_H__
#define __LCD204_H__


typedef unsigned char		LCD_Byte;
typedef const LCD_Byte*		LCD_Bytes;
typedef char				LCD_Int;
typedef signed char			LCD_SInt;
typedef unsigned char		LCD_UInt;
typedef char				LCD_Char;
typedef const char*			LCD_String;
typedef unsigned char		LCD_Vector;

#define LCD_BLACK_BLOCK 0xFF
#define LCD_WHITE_BLOCK ' '

void LCD_Put_Char(LCD_UInt x, LCD_UInt y, LCD_Char ch);
void LCD_Init(void);
void LCD_Shift(void);


#endif

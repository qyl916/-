/***************************************************************************/
/*                                                                         */
/* lcd1602.h                                                               */
/*   提供lcd1602的部分功能的程序接口。                                     */
/*                                                                         */
/*   lcd1602有80*8 bits的显存，而显示到屏幕的是其中的一部分。其内部已      */
/* 存储有部分字符的点阵数据，同时也支持自定义少量点阵数据。同时它也可      */
/* 以显示光标，有下划线和闪烁两种模式。                                    */
/*                                                                         */
/***************************************************************************/
#ifndef __LCD1602_H
#define __LCD1602_H

#ifdef __cplusplus
extern "C"{
#endif

  /*************************************************************************/
  /*                                                                       */
  /*  <Section>                                                            */
  /*    一些基本类型                                                       */
  /*                                                                       */
  /*************************************************************************/
typedef unsigned char		LCD_Byte;
typedef const LCD_Byte*		LCD_Bytes;
typedef char				LCD_Int;
typedef signed char			LCD_SInt;
typedef unsigned char		LCD_UInt;
typedef char				LCD_Char;
typedef const char*			LCD_String;

  /*************************************************************************/
  /*                                                                       */
  /*  <Type>                                                               */
  /*    LCD_Vector                                                         */
  /*  <Description>                                                        */
  /*    表示一个二维坐标，坐标原点为屏幕左上角，x表示行，y表示列。         */
  /*                                                                       */
typedef unsigned char		LCD_Vector;

  /*************************************************************************/
  /*                                                                       */
  /*  <Macro>                                                              */
  /*    LCD_MAKE_VECTOR                                                    */
  /*  <Description>                                                        */
  /*    将两个坐标x和y打包为一个位置坐标。                                 */
  /*                                                                       */
#define LCD_MAKE_VECTOR(x, y)			\
	(LCD_Vector)						\
	(	(((LCD_Byte)(x) & 1) << 6)	|	\
		((LCD_Byte)(y) & 0x3F)		)

  /*************************************************************************/
  /*                                                                       */
  /*  <Macro>                                                              */
  /*    LCD_VECTOR_X                                                       */
  /*    LCD_VECTOR_Y                                                       */
  /*  <Description>                                                        */
  /*    从LCD_Vector中取出x、y的值。                                       */
  /*                                                                       */
#define LCD_VECTOR_X(v) (((LCD_Vector)(v) >> 6) & 1)
#define LCD_VECTOR_Y(v) ((LCD_Vector)(v) & 0x3F)



  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*     LCD_Init                                                          */
  /*  <Description>                                                        */
  /*     初始化屏幕。                                                      */
  /*  <Input>                                                              */
  /*     mode  :: 控制屏幕行数和字符点阵大小，可选模式如下：               */
  /*                  LCD_MODE_1LINE_5X07DOT  :: 一行，5*7点阵             */
  /*                  LCD_MODE_1LINE_5X10DOT  :: 一行，5*10点阵            */
  /*                  LCD_MODE_2LINE_5X07DOT  :: 两行，5*7点阵             */
  /*                                                                       */
#define LCD_MODE_1LINE_5X07DOT	0x30
#define LCD_MODE_1LINE_5X10DOT	0x34
#define LCD_MODE_2LINE_5X07DOT	0x38
void LCD_Init(LCD_Byte mode);


  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Set_Glyph                                                      */
  /*  <Description>                                                        */
  /*    设置自定义点阵。                                                   */
  /*  <Input>                                                              */
  /*    index :: 自定义点阵id，取值范围在5*7模式下为0-7，5*10模式          */
  /*             下为0-3                                                   */
  /*    glyph :: 指向点阵数据的指针                                        */
  /*  <Note>                                                               */
  /*    点阵数据中，每个字节（8位）数据表示一行，其中低5位为有效数         */
  /*    据，例如0x09表示该行为“ *  *”。此函数依据初始化时设定的显          */
  /*    示模式取前数字节内容。                                             */
  /*                                                                       */
void LCD_Set_Glyph(LCD_UInt index, LCD_Bytes glyph);

  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Put_Char                                                       */
  /*  <Description>                                                        */
  /*    在显存指定位置写入字符。                                           */
  /*  <Input>                                                              */
  /*    pos   :: 写入字符的位置                                            */
  /*    ch    :: 要写入的字符id                                            */
  /*  <Note>                                                               */
  /*    在显示过程中光标位置会改变，若不希望这一现象发生可以先关闭         */
  /*    光标显示，待结束后恢复光标位置并开启光标。                         */
  /*                                                                       */
void LCD_Put_Char(LCD_Vector pos, LCD_Char ch);


  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Put_String                                                     */
  /*  <Description>                                                        */
  /*    在显存指定位置写入字符串。                                         */
  /*  <Input>                                                              */
  /*    pos   :: 写入字符串的位置                                          */
  /*    string:: 要写入的串，每字节为字符id                                */
  /*    num   :: 字符串长度                                                */
  /*  <Note>                                                               */
  /*    由于0也可以表示自定的字符id，故不表示字符串的结尾。                */
  /*    超过显存大小部分被截断。                                           */
  /*    在显示过程中光标位置会改变，若不希望这一现象发生可以先关闭         */
  /*    光标显示，待结束后恢复光标位置并开启光标。                         */
  /*                                                                       */
void LCD_Put_String(LCD_Vector pos, LCD_String string, LCD_UInt num);


  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Clear                                                          */
  /*  <Description>                                                        */
  /*    清空显存，清空屏幕，光标归位。                                     */
  /*                                                                       */
void LCD_Clear(void);



  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Shift_Cursor                                                   */
  /*    LCD_Shift_Display                                                  */
  /*  <Description>                                                        */
  /*    将光标/显示区域向左/右移动一位                                     */
  /*  <Input>                                                              */
  /*    direction :: 移动方向，LCD_LEFT或LCD_RIGHT                         */
  /*  <Note>                                                               */
  /*    显示区域的移动是循环的。                                           */
  /*                                                                       */
#define LCD_LEFT	0x00
#define LCD_RIGHT	0x04

void LCD_Shift_Cursor(LCD_Byte direction);
void LCD_Shift_Display(LCD_Byte direction);


  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Display_Switch                                                 */
  /*  <Description>                                                        */
  /*    开关显示。                                                         */
  /*  <Input>                                                              */
  /*    mode  :: 可选项: LCD_DISPLAY_ON、LCD_DISPLAY_OFF                   */
  /*                                                                       */
#define LCD_DISPLAY_ON	0x0F
#define LCD_DISPLAY_OFF	0x0B

void LCD_Display_Switch(LCD_Byte mode);



  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Set_Cursor_Mode                                                */
  /*  <Description>                                                        */
  /*    设置光标模式。                                                     */
  /*  <Input>                                                              */
  /*    mode_flags :: 可选标志                                             */
  /*                    LCD_CURSOR_OFF    不显示光标                       */
  /*                    LCD_CURSOR_UNDER  光标所在位置下划线               */
  /*                    LCD_CURSOR_BLINK  光标所在位置闪烁                 */
  /*                                                                       */
#define LCD_CURSOR_OFF		0x08
#define LCD_CURSOR_UNDER	0x0A
#define LCD_CURSOR_BLINK	0x09

void LCD_Set_Cursor_Mode(LCD_Byte mode_flags);


  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    LCD_Set_Cursor_Position                                            */
  /*  <Description>                                                        */
  /*    改变光标位置。                                                     */
  /*  <Input>                                                              */
  /*    pos   :: 光标位置                                                  */
  /*                                                                       */
void LCD_Set_Cursor_Position(LCD_Vector pos);

#ifdef __cplusplus
}
#endif

#endif

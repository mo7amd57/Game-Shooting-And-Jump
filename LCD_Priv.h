/*
 * LCD_Priv.h
 *
 * Created: 12/17/2023 3:57:22 PM
 *  Author: Mohamed Ramadan
 */ 


#ifndef   LCD_PRIV_H_
#define   LCD_PRIV_H_
#include "LCD_Init.h"

#define  LCD_CLEAR       0x01
#define  LCD_OFFDISPLAY  0x0A
#define  LCD_MAXNUM    3

#define  LCD_8Bit_2Lines_5x7Dot_MODE   0x38
#define  LCD_8Bit_2Lines_5x10Dot_MODE  0x3c

#define  LCD_4Bit_2Lines_5x7Dot_MODE   0x28
#define  LCD_4Bit_2Lines_5x10Dot_MODE  0x2c

#define SET_CG_RAM_ADD   0x40
#define SET_DD_RAM_ADD   0x80

//extern LCD_t LCD [LCD_MAXNUM];


#define  LCD_2x16   1
#define  LCD_2x32   2
#define  LCD_2x40   3
#define  LCD_4x20   4
#define  LCD_4x16   5


typedef enum
{
	LCD_4_BITMODE,
	LCD_8_BITMODE,
	
}LCD_BitMode_t;

typedef enum
{
	LCD_Cell5x7Dot,
	LCD_Cell5x10Dot,
	
}LCD_CellDotNum_t;


typedef enum
{
	LCD_CURSOR_BLINK=0x0F,
	LCD_CURSOR_NOTBLINK=0x0E,
	LCD_CURSOR_OFF=0x0C,
	
}LCD_CursorSett_t;


typedef enum
{
	
	LCD_IncreaseAddressDisplay=0x06,
	LCD_DecreaseAddressDisplay=0x04,
	
	LCD_ShiftLeftDisplay=0x07,
	LCD_ShiftRightDisplay=0x05,
	
}LCD_DisplayMoveDirection_t;


typedef struct
{
  DIO_Port_t LCD_8Bit_Port;
  
}LCD_8Bit_t;

typedef struct
{
	DIO_Pin_t LCD_4Bit_D4Pin;
	DIO_Pin_t LCD_4Bit_D5Pin;
	DIO_Pin_t LCD_4Bit_D6Pin;
	DIO_Pin_t LCD_4Bit_D7Pin;
	
}LCD_4Bit_t;

typedef struct
{
	LCD_Line_t Line;
	LCD_Cell_t Cell;
	
}LCD_Postion_t;

typedef struct
{
	DIO_Pin_t LCD_RS_Pin;
	DIO_Pin_t LCD_En_Pin;
	LCD_BitMode_t BitMode;
	
	LCD_8Bit_t LCD_8Bit;
	
	LCD_4Bit_t LCD_4Bit;
	
	LCD_Postion_t Position;
	
}LCD_t;


	
	
	
	
	
/////////////// Function to Dispaly On And Off








extern const LCD_BitMode_t    LcdMode[LCD_MAXNUM];

extern const LCD_CellDotNum_t LcdCellDot[LCD_MAXNUM];

extern const LCD_CursorSett_t LcdCursorSetting[LCD_MAXNUM];

extern const LCD_CellDotNum_t LcdCellDot[LCD_MAXNUM];

extern const LCD_DisplayMoveDirection_t LcdMoveDirection[LCD_MAXNUM];

extern const LCD_8BitConnect_t LCD8BitConnect[LCD_MAXNUM];

extern const LCD_4BitConnect_t LCD4BitConnect[LCD_MAXNUM];













#endif /* LCD_PRIV_H_ */
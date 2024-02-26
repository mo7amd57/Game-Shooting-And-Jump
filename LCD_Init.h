/*
 * LCD_Init.h
 *
 * Created: 12/17/2023 3:56:56 PM
 *  Author: Mohamed Ramadan
 */ 


#ifndef LCD_INIT_H_
#define LCD_INIT_H_




typedef struct
{
	DIO_Pin_t LCD_RS_PIN;
	DIO_Pin_t LCD_EN_PIN;
	DIO_Port_t LCD_PORT;
	
}LCD_8BitConnect_t;


typedef struct
{
	DIO_Pin_t LCD_RS_PIN;
	DIO_Pin_t LCD_EN_PIN;
	
	DIO_Pin_t LCD_D4_PIN;
	DIO_Pin_t LCD_D5_PIN;
	DIO_Pin_t LCD_D6_PIN;
	DIO_Pin_t LCD_D7_PIN;
	
}LCD_4BitConnect_t;

typedef enum
{
	LCD1,
	LCD2,
	LCD3,
	LCD_TOTALNUM,
}LCD_Number_t;




typedef enum
{
	Line1,
	Line2,
	Line3,
	Line4,
	
}LCD_Line_t;

typedef enum
{
	Cell_1,
	Cell_2,
	Cell_3,
	Cell_4,
	Cell_5,
	Cell_6,
	Cell_7,
	Cell_8,
	Cell_9,
	Cell_10,
	Cell_11,
	Cell_12,
	Cell_13,
	Cell_14,
	Cell_15,
	Cell_16,
	Cell_17,
	Cell_18,
	Cell_19,
	Cell_20,
	Cell_21,
	Cell_22,
	Cell_23,
	Cell_24,
	Cell_25,
	Cell_26,
	Cell_27,
	Cell_28,
	Cell_29,
	Cell_30,
	Cell_31,
	Cell_32,
	Cell_33,
	Cell_34,
	Cell_35,
	Cell_36,
	Cell_37,
	Cell_38,
	Cell_39,
	Cell_40,
	TOTALCELL,
	
}LCD_Cell_t;



typedef enum
{
	ADD1,
	ADD2,
	ADD3,
	ADD4,
	ADD5,
	ADD6,
	ADD7,
	ADD8,
	
}LCD_CG_address_t;


typedef enum
{
	Pressed,
	Unpresed,
	Float,
	
}ButtonStatus_t;




void LCD_init (void);


void LCD_WriteChar(LCD_Number_t lcdnum,u8 ch);

void LCD_WriteChar2(LCD_Number_t lcdnum,u8 ch);


void LCD_WriteString (LCD_Number_t lcdnum,u8* str);


void LCD_WriteString2 (LCD_Number_t lcdnum,u8* str);

//void LCD_WriteFloatNumber(LCD_Number_t lcdnum,f64 Num);



void LCD_WriteIntegerNumber(LCD_Number_t lcdnum,s32 num);


void LCD_ClearDisplay(LCD_Number_t lcdnum);

void LCD_OFFDisplay(LCD_Number_t lcdnum);

void LCD_ONDisplay(LCD_Number_t lcdnum);

void LCD_SetCursor(LCD_Number_t lcdnum,LCD_Line_t Line , LCD_Cell_t Cell);

void LCD_WriteBinary(LCD_Number_t lcdnum, u8 num);

void LCD_ClearCell(LCD_Number_t lcdnum,LCD_Line_t Linecell , LCD_Cell_t Cellnum);

void LCD_WriteHexa(LCD_Number_t lcdnum, u8 num);

void LCD_WriteNum_4Digit(LCD_Number_t lcdnum, u16 num);

void LCD_SaveCustomerPattern(LCD_Number_t lcdnum,u8 *pattern , LCD_CG_address_t pattaddress);

void LCD_WriteCustomerPattern(LCD_Number_t lcdnum, LCD_CG_address_t pattaddress);


void LCD_CursorPosition(LCD_Number_t lcdnum,LCD_Line_t *Linecell , LCD_Cell_t* Cellnum);

void LCD_ClearLineDisplay(LCD_Number_t lcdnum,LCD_Line_t Linecell);


void LCD_WriteNumber(LCD_Number_t lcdnum,f64 Num);


#endif /* LCD_INIT_H_ */
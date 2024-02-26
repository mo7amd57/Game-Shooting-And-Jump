#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Init.h"

#define  F_CPU  8000000UL
#include <util/delay.h>
#include "Utils.h"

#include "GAME_Int.h"


LCD_Line_t Linecell; 
LCD_Cell_t Cellnum;

 u8 pattstop[8] = {
	0b01110,
	0b01110,
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b01010,
	0b01010
};

 u8 pattshot[8] = {
	0b01110,
	0b01110,
	0b10101,
	0b01110,
	0b00100,
	0b00100,
	0b01010,
	0b10001
};

 u8 pattgun[8] = {
	 
		0b00000,
		0b01100,
		0b00010,
		0b00011,
		0b00010,
		0b01100,
		0b00000,
		0b00000
};

u8 pattgun2[8] = {
	0b00000,
	0b00110,
	0b01000,
	0b11000,
	0b01000,
	0b00110,
	0b00000,
	0b00000
};

u8 LastWin[8] = {
	0B01110,
	0B01110,
	0B00100,
	0B10100,
	0B01110,
	0B00101,
	0B01110,
	0B01010
};
u8 p1killed[] = {
	   0B00000,
	   0B01000,
	   0B00111,
	   0B01011,
	   0B00111,
	   0B01011,
	   0B00100,
	   0B01000

};

u8 p2killed[] = {
	0B00010,
	0B11100,
	0B11010,
	0B11100,
	0B11010,
	0B00100,
	0B00010,
	0B00001

};


u8 pwin[] = {
	0B01110,
	0B01110,
	0B10101,
	0B01110,
	0B00100,
	0B00100,
	0B01010,
	0B10001

};

void GAME_Init(void)
{
	LCD_SaveCustomerPattern(LCD1,pattstop,ADD1);
	LCD_SaveCustomerPattern(LCD1,pattshot,ADD2);
	LCD_SaveCustomerPattern(LCD1,pattgun,ADD3);
	LCD_SaveCustomerPattern(LCD1,pattgun2,ADD4);
	LCD_SaveCustomerPattern(LCD1,LastWin,ADD5);
	LCD_SaveCustomerPattern(LCD1,p1killed,ADD6);
	LCD_SaveCustomerPattern(LCD1,p2killed,ADD7);
	LCD_SaveCustomerPattern(LCD1,pwin,ADD8);
	
	GAME_intro(LCD1);

	
}

void GAME_intro(LCD_Number_t lcdnum)
{
	u8 welcom[]="WelcomeTo";
	u8 str[]="My Game ^_^ ";
	LCD_Cell_t cell=0;
	
	for (cell=Cell_1;cell<=Cell_16;cell++)
	{
		LCD_SetCursor(lcdnum,Line1,cell);
		LCD_WriteString(lcdnum,welcom);
		_delay_ms(100);
		LCD_ClearCell(lcdnum,Line1,cell);
	
		LCD_CursorPosition(lcdnum,&Linecell,&Cellnum);
		
		if (Cellnum==Cell_6)
		{
			LCD_SetCursor(lcdnum,Line1,cell);
			LCD_WriteChar(lcdnum,'W');
			break;
		}
		
	}
	for (cell=Cell_1;cell<=Cell_16;cell++)
	{
		LCD_SetCursor(lcdnum,Line2,cell);
		LCD_WriteString(lcdnum,str);
		_delay_ms(100);
		LCD_ClearCell(lcdnum,Line2,cell);
	  
		LCD_CursorPosition(lcdnum,&Linecell,&Cellnum);
		
		if (Cellnum==Cell_6)
		{
			LCD_SetCursor(lcdnum,Line2,cell);
			LCD_WriteChar(lcdnum,'M');
			break;
		}
		
	}

 _delay_ms(1000);
// LCD_ClearDisplay(lcdnum);
	
	
	for (cell=Cell_5;cell<=Cell_16;cell++)
	{
		LCD_SetCursor(lcdnum,Line1,cell);
		LCD_WriteString(lcdnum,welcom);
		_delay_ms(100);
		LCD_ClearCell(lcdnum,Line1,cell);
		LCD_CursorPosition(lcdnum,&Linecell,&Cellnum);
		if (Cellnum>Cell_16)
		{
			break;
		}
		
	}
	for (cell=Cell_5;cell<=Cell_16;cell++)
	{
		LCD_SetCursor(lcdnum,Line2,cell);
		LCD_WriteString(lcdnum,str);
		_delay_ms(100);
		LCD_ClearCell(lcdnum,Line2,cell);
		LCD_CursorPosition(lcdnum,&Linecell,&Cellnum);
		if (Cellnum>Cell_16)
		{
			break;
		}
		
	}

	_delay_ms(500);
	LCD_ClearDisplay(lcdnum);
}

void GAME_Scores(u8 Play1score , u8 Play2score)
{
	u8 str[]="Plyer1 Score Max";
	u8 str1[]="Plyer2 Score Max";
	LCD_SetCursor(LCD2,Line1,Cell_1);
	LCD_WriteString(LCD2,str);
	
	
	LCD_SetCursor(LCD2,Line2,Cell_6);
	LCD_WriteChar(LCD2,'|');
	LCD_ClearCell(LCD2,Line2,Cell_7);
	LCD_ClearCell(LCD2,Line2,Cell_8);
	LCD_SetCursor(LCD2,Line2,Cell_9);
	LCD_WriteChar(LCD2,((Play1score/10)+'0'));
	LCD_SetCursor(LCD2,Line2,Cell_10);
	LCD_WriteChar(LCD2,((Play1score%10)+'0'));
	LCD_ClearCell(LCD2,Line2,Cell_11);
	
	LCD_SetCursor(LCD2,Line2,Cell_12);
	LCD_WriteChar(LCD2,'|');
	
	LCD_ClearCell(LCD2,Line2,Cell_13);
	LCD_SetCursor(LCD2,Line2,Cell_14);
	LCD_WriteChar(LCD2,((MAXSCORE/10)+'0'));
	LCD_SetCursor(LCD2,Line2,Cell_15);
	LCD_WriteChar(LCD2,((MAXSCORE%10)+'0'));
	LCD_ClearCell(LCD2,Line2,Cell_16);
	
	LCD_SetCursor(LCD3,Line1,Cell_1);
	LCD_WriteString(LCD3,str1);
	
	LCD_SetCursor(LCD3,Line2,Cell_6);
	LCD_WriteChar(LCD3,'|');
	LCD_ClearCell(LCD3,Line2,Cell_7);
	LCD_ClearCell(LCD3,Line2,Cell_8);
	LCD_SetCursor(LCD3,Line2,Cell_9);
	LCD_WriteChar(LCD3,((Play2score/10)+'0'));
	LCD_SetCursor(LCD3,Line2,Cell_10);
	LCD_WriteChar(LCD3,((Play2score%10)+'0'));
	LCD_ClearCell(LCD3,Line2,Cell_11);
	
	LCD_SetCursor(LCD3,Line2,Cell_12);
	LCD_WriteChar(LCD3,'|');
	
	LCD_ClearCell(LCD3,Line2,Cell_13);
	LCD_SetCursor(LCD3,Line2,Cell_14);
	LCD_WriteChar(LCD3,((MAXSCORE/10)+'0'));
	LCD_SetCursor(LCD3,Line2,Cell_15);
	LCD_WriteChar(LCD3,((MAXSCORE%10)+'0'));
	LCD_ClearCell(LCD3,Line2,Cell_16);
	
}

void GAME_GameMode(LCD_Number_t lcdnum,GAME_Mode_t mode)
{
	u8 str[]="Game Mode is";
	u8 str1[]="Player1 Attack ";
	u8 str2[]="Player2 Attack ";
	static u8 flag=1;
	LCD_SetCursor(lcdnum,Line1,Cell_2);
	LCD_WriteString(lcdnum,str);
	_delay_ms(100);
	switch(mode)
	{
		case PLAYER1_ATTACK :
		LCD_SetCursor(lcdnum,Line2,Cell_2);
		LCD_WriteString(lcdnum,str1);
		break;
		case  PLAYER2_ATTACK :
		LCD_SetCursor(lcdnum,Line2,Cell_2);
		LCD_WriteString(lcdnum,str2);
		break;
	}
	
	
	
	 _delay_ms(1600);
	if (flag)
	{
		GAME_Scores(0,0);
		flag=0;
	} 
	 LCD_ClearLineDisplay(lcdnum,Line1);
	 _delay_ms(250);
	 LCD_ClearLineDisplay(lcdnum,Line2);
	 _delay_ms(250);
	
}

void GAME_PlayerPositionMode1(void)
{
	LCD_SetCursor(LCD1,Line2,Cell_1);
	LCD_WriteChar(LCD1,PATTSTOPADDRESS);
	
	//LCD_SetCursor(LCD1,Line2,Cell_2);
	//LCD_WriteChar(LCD1,PATTGUNADDRESS);
	
	LCD_SetCursor(LCD1,Line2,Cell_15);
	LCD_WriteChar(LCD1,PATTSTOPADDRESS);
}



void GAME_PlayerPositionMode2(void)
{
	LCD_SetCursor(LCD1,Line2,Cell_2);
	LCD_WriteChar(LCD1,PATTSTOPADDRESS);
	
	//LCD_SetCursor(LCD1,Line2,Cell_2);
	//LCD_WriteChar(LCD1,PATTGUNADDRESS);
	
	LCD_SetCursor(LCD1,Line2,Cell_16);
	LCD_WriteChar(LCD1,PATTSTOPADDRESS);
}





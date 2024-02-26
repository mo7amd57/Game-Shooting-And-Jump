
#include "StdTypes.h"
#include "DIO_Int.h"


#include "LCD_Init.h"
#include "LCD_Cfg.h"
#include "LCD_Priv.h"

#define  F_CPU  8000000UL
#include <util/delay.h>
#include "Utils.h"

LCD_Number_t LCDNum=LCD_NUM;


LCD_t LCD [LCD_MAXNUM];



#if (LCDNum>LCD_TOTALNUM)
LCDNum=LCD_MAXNUM
#else

#endif


/************************************************************************************/


#if  (LCD_TYPE==LCD_2x16 || LCD_TYPE==LCD_4x16)

   u8  MAXCell=16; 
	 
#elif LCD_TYPE==LCD_2x32

    u8 MAXCell=32;
	 
#elif LCD_TYPE==LCD_2x40	 

	 u8 MAXCell=40;
	 
#elif LCD_TYPE==LCD_4x20

   u8 MAXCell=20;
   
#endif



/**********************************************************/



void LCD_MyInitialize (void)
{
	for (LCD_Number_t i=LCD1 ; i<LCDNum ; i++)
	{
		LCD[i].Position.Line=Line1;
		LCD[i].Position.Cell=Cell_1;
		
		if (LcdMode[i]==LCD_8_BITMODE)
		{
			LCD[i].BitMode=LCD_8_BITMODE;
			LCD[i].LCD_RS_Pin=LCD8BitConnect[i].LCD_RS_PIN;
			LCD[i].LCD_En_Pin=LCD8BitConnect[i].LCD_EN_PIN;
			LCD[i].LCD_8Bit.LCD_8Bit_Port=LCD8BitConnect[i].LCD_PORT;
		}
		else if (LcdMode[i]==LCD_4_BITMODE)
		{
			LCD[i].BitMode=LCD_4_BITMODE;
			LCD[i].LCD_RS_Pin=LCD4BitConnect[i].LCD_RS_PIN;
			LCD[i].LCD_En_Pin=LCD4BitConnect[i].LCD_EN_PIN;
			LCD[i].LCD_4Bit.LCD_4Bit_D4Pin=LCD4BitConnect[i].LCD_D4_PIN;
			LCD[i].LCD_4Bit.LCD_4Bit_D5Pin=LCD4BitConnect[i].LCD_D5_PIN;
			LCD[i].LCD_4Bit.LCD_4Bit_D6Pin=LCD4BitConnect[i].LCD_D6_PIN;
			LCD[i].LCD_4Bit.LCD_4Bit_D7Pin=LCD4BitConnect[i].LCD_D7_PIN;
		}
	}
}


static void LCD_WriteInstruction(LCD_Number_t lcdnum,u8 inst)
{
	if (LCD[lcdnum].BitMode==LCD_8_BITMODE)
	{
		DIO_enuWritePin(LCD[lcdnum].LCD_RS_Pin,LOW);
		DIO_enuWritePort(LCD[lcdnum].LCD_8Bit.LCD_8Bit_Port,inst);
		
		DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,HIGH);
		_delay_ms(1);
		DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,LOW);
		_delay_ms(1);
	}
	
	
	else if ((LCD[lcdnum].BitMode==LCD_4_BITMODE))
	{
		
	   DIO_enuWritePin(LCD[lcdnum].LCD_RS_Pin,LOW);
	   
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D7Pin,READ_BIT(inst,7));
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D6Pin,READ_BIT(inst,6));
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D5Pin,READ_BIT(inst,5));
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D4Pin,READ_BIT(inst,4));
	   
	   DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,HIGH);
	   _delay_ms(1);
	   DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,LOW);
	   _delay_ms(1);
	   
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D7Pin,READ_BIT(inst,3));
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D6Pin,READ_BIT(inst,2));
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D5Pin,READ_BIT(inst,1));
	   DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D4Pin,READ_BIT(inst,0));
	   
	   DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,HIGH);
	   _delay_ms(1);
	   DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,LOW);
	   _delay_ms(1);
	   
	}
}


static void LCD_WriteData(LCD_Number_t lcdnum,u8 data)
{
	if (LCD[lcdnum].BitMode==LCD_8_BITMODE)
	{
		DIO_enuWritePin(LCD[lcdnum].LCD_RS_Pin,HIGH);
		DIO_enuWritePort(LCD[lcdnum].LCD_8Bit.LCD_8Bit_Port,data);
		
		DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,HIGH);
		_delay_ms(1);
		DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,LOW);
		_delay_ms(1);
	}
	
	
	else if ((LCD[lcdnum].BitMode==LCD_4_BITMODE))
	{
		
		 DIO_enuWritePin(LCD[lcdnum].LCD_RS_Pin,HIGH);
		 
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D7Pin,READ_BIT(data,7));
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D6Pin,READ_BIT(data,6));
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D5Pin,READ_BIT(data,5));
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D4Pin,READ_BIT(data,4));
		 
		 DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,HIGH);
		 _delay_ms(1);
		 DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,LOW);
		 _delay_ms(1);
		 
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D7Pin,READ_BIT(data,3));
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D6Pin,READ_BIT(data,2));
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D5Pin,READ_BIT(data,1));
		 DIO_enuWritePin(LCD[lcdnum].LCD_4Bit.LCD_4Bit_D4Pin,READ_BIT(data,0));
		 
		 DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,HIGH);
		 _delay_ms(1);
		 DIO_enuWritePin(LCD[lcdnum].LCD_En_Pin,LOW);
		 _delay_ms(1);
		
	}
}


void LCD_init (void)
{
	LCD_MyInitialize();
	 _delay_ms(50);
	 
	for (LCD_Number_t i=LCD1 ; i<LCDNum ; i++)
	{
		if (LCD[i].BitMode==LCD_8_BITMODE)
		{
			switch (LcdCellDot[i])
			{
				case LCD_Cell5x7Dot :
				LCD_WriteInstruction(i,LCD_8Bit_2Lines_5x7Dot_MODE);
				break;
				case LCD_Cell5x10Dot :
				LCD_WriteInstruction(i,LCD_8Bit_2Lines_5x10Dot_MODE);
				break;
			}
			LCD_WriteInstruction(i,LcdCursorSetting[i]);
			LCD_WriteInstruction(i,LCD_CLEAR);
			_delay_ms(1);
			LCD_WriteInstruction(i,LcdMoveDirection[i]);
			
		}
		else if (LCD[i].BitMode==LCD_4_BITMODE)
		{
			LCD_WriteInstruction(i,0x02);
			
			switch (LcdCellDot[i])
			{
				case LCD_Cell5x7Dot :
				LCD_WriteInstruction(i,LCD_4Bit_2Lines_5x7Dot_MODE);
				break;
				case LCD_Cell5x10Dot :
				LCD_WriteInstruction(i,LCD_4Bit_2Lines_5x10Dot_MODE);
				break;
			}
			LCD_WriteInstruction(i,LcdCursorSetting[i]);
			LCD_WriteInstruction(i,LCD_CLEAR);
			_delay_ms(1);
			LCD_WriteInstruction(i,LcdMoveDirection[i]);
			
			
		}
		
	}
	
}



/*====================================================================================*/


#if ( LCD_TYPE==LCD_2x16 || LCD_TYPE==LCD_2x32 || LCD_TYPE==LCD_2x40)



void LCD_SetCursor(LCD_Number_t lcdnum,LCD_Line_t Line , LCD_Cell_t Cell)
{
	LCD[lcdnum].Position.Line=Line;
	LCD[lcdnum].Position.Cell=Cell;
	switch(Line)
	{
		case Line1 :
		LCD_WriteInstruction(lcdnum,(SET_DD_RAM_ADD|Cell));
		break;
		
		case Line2 :
		LCD_WriteInstruction(lcdnum,((SET_DD_RAM_ADD|0x40)|Cell));
		break;
		
		
		case Line3 :
		LCD_WriteInstruction(lcdnum,(SET_DD_RAM_ADD|Cell));
		break;
		
		case Line4 :
		LCD_WriteInstruction(lcdnum,((SET_DD_RAM_ADD|0x40)|Cell));
		break;
	}
}



#elif  ( LCD_TYPE==LCD_4x20 || LCD_TYPE==LCD_4x16 )


	  #if LCD_TYPE==LCD_4x16
	  
	  LCD_Cell_t MaxCell=Cell_17;
	  
	  #elif LCD_TYPE==LCD_4x20
	  
	 LCD_Cell_t MaxCell=Cell_21;

	  #endif
	  

	  
void LCD_SetCursor(LCD_Number_t lcdnum,LCD_Line_t Line , LCD_Cell_t Cell)
{
	LCD[lcdnum].Position.Line=Line;
	LCD[lcdnum].Position.Cell=Cell;
	
	switch(Line)
	{
		case Line1 :
		
		LCD_WriteInstruction(lcdnum,(SET_DD_RAM_ADD|Cell));
		break;
		
		case Line2 :
		LCD_WriteInstruction(lcdnum,((SET_DD_RAM_ADD|0x40)|Cell));
		break;
		
		case Line3 :
		
		LCD_WriteInstruction(lcdnum,(SET_DD_RAM_ADD|(Cell+MaxCell)));
		break;
		
		case Line4 :
		LCD_WriteInstruction(lcdnum,((SET_DD_RAM_ADD|0x40)|(Cell+MaxCell)));
		break;
	}
}


#endif



/*************************************************************************/



void LCD_WriteChar(LCD_Number_t lcdnum,u8 ch)
{
	LCD_WriteData(lcdnum,ch);
	
	(LCD[lcdnum].Position.Cell)++;
}


void LCD_WriteChar2(LCD_Number_t lcdnum,u8 ch)
{
	LCD_WriteData(lcdnum,ch);
	
	(LCD[lcdnum].Position.Cell)++;
	
	
	#if LCD_TYPE==LCD_2x16
	
	
	if (LCD[lcdnum].Position.Cell>Cell_16 &&LCD[lcdnum].Position.Line==Line1)
	{
		LCD_SetCursor(lcdnum,Line2,Cell_1);
		LCD[lcdnum].Position.Line=Line2;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	if (LCD[lcdnum].Position.Cell>Cell_16 &&LCD[lcdnum].Position.Line==Line2)
	{
		LCD_SetCursor(lcdnum,Line1,Cell_1);
		LCD[lcdnum].Position.Line=Line1;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	
	#elif LCD_TYPE==LCD_2x32
	
	
	if (LCD[lcdnum].Position.Cell>Cell_32 &&LCD[lcdnum].Position.Line==Line1)
	{
		LCD_SetCursor(lcdnum,Line2,Cell_1);
		LCD[lcdnum].Position.Line=Line2;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	if (LCD[lcdnum].Position.Cell>Cell_32 &&LCD[lcdnum].Position.Line==Line2)
	{
		LCD_SetCursor(lcdnum,Line1,Cell_1);
		LCD[lcdnum].Position.Line=Line1;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	#elif LCD_TYPE==LCD_2x40
	
	
	if (LCD[lcdnum].Position.Cell>Cell_40 &&LCD[lcdnum].Position.Line==Line1)
	{
		LCD_SetCursor(lcdnum,Line2,Cell_1);
		LCD[lcdnum].Position.Line=Line2;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	if (LCD[lcdnum].Position.Cell>Cell_40 &&LCD[lcdnum].Position.Line==Line2)
	{
		LCD_SetCursor(lcdnum,Line1,Cell_1);
		LCD[lcdnum].Position.Line=Line1;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	
	#elif LCD_TYPE==LCD_4x16
	
	
	if (LCD[lcdnum].Position.Cell>Cell_16 &&LCD[lcdnum].Position.Line==Line1)
	{
		LCD_SetCursor(lcdnum,Line2,Cell_1);
		LCD[lcdnum].Position.Line=Line2;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	if (LCD[lcdnum].Position.Cell>Cell_16 &&LCD[lcdnum].Position.Line==Line2)
	{
		LCD_SetCursor(lcdnum,Line3,Cell_1);
		LCD[lcdnum].Position.Line=Line3;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	if (LCD[lcdnum].Position.Cell>Cell_16 &&LCD[lcdnum].Position.Line==Line3)
	{
		LCD_SetCursor(lcdnum,Line4,Cell_1);
		LCD[lcdnum].Position.Line=Line4;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	if (LCD[lcdnum].Position.Cell>Cell_16 &&LCD[lcdnum].Position.Line==Line4)
	{
		LCD_SetCursor(lcdnum,Line1,Cell_1);
		LCD[lcdnum].Position.Line=Line1;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	
	#elif LCD_TYPE==LCD_4x20
	
	
	
	if (LCD[lcdnum].Position.Cell>Cell_20 &&LCD[lcdnum].Position.Line==Line1)
	{
		LCD_SetCursor(lcdnum,Line2,Cell_1);
		LCD[lcdnum].Position.Line=Line2;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	if (LCD[lcdnum].Position.Cell>Cell_20 &&LCD[lcdnum].Position.Line==Line2)
	{
		LCD_SetCursor(lcdnum,Line3,Cell_1);
		LCD[lcdnum].Position.Line=Line3;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	if (LCD[lcdnum].Position.Cell>Cell_20 &&LCD[lcdnum].Position.Line==Line3)
	{
		LCD_SetCursor(lcdnum,Line4,Cell_1);
		LCD[lcdnum].Position.Line=Line4;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	if (LCD[lcdnum].Position.Cell>Cell_20 &&LCD[lcdnum].Position.Line==Line4)
	{
		LCD_SetCursor(lcdnum,Line1,Cell_1);
		LCD[lcdnum].Position.Line=Line1;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	
	
	
	/*
	if (LCD[lcdnum].Position.Cell>Cell_20 &&LCD[lcdnum].Position.Line==Line1)
	{
		LCD_SetCursor(lcdnum,Line2,Cell_1);
		LCD[lcdnum].Position.Line=Line2;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	if (LCD[lcdnum].Position.Cell>Cell_20 &&LCD[lcdnum].Position.Line==Line2)
	{
		LCD_SetCursor(lcdnum,Line1,Cell_1);
		LCD[lcdnum].Position.Line=Line1;
		LCD[lcdnum].Position.Cell=Cell_1;
	}
	
	*/
	
	#endif
	
	
}





void LCD_WriteString (LCD_Number_t lcdnum,u8* str)
{
	u8 i=0;
	if (str!=NULL_PTR)
	{
		
		for (i=0 ;str[i];i++)
		{
			LCD_WriteChar(lcdnum,str[i]);
		}
	}
}

void LCD_WriteString2 (LCD_Number_t lcdnum,u8* str)
{
	u8 i=0;
	if (str!=NULL_PTR)
	{
		
		for (i=0 ;str[i];i++)
		{
			LCD_WriteChar2(lcdnum,str[i]);
		}
	}
}

 void LCD_WriteIntegerNumber(LCD_Number_t lcdnum,s32 num)
{
	u8 str[16],i=0;
	s8 j;
	if (num==0)
	{
		LCD_WriteChar(lcdnum,'0');
		return;
	}
	if (num<0)
	{
		LCD_WriteChar(lcdnum,'-');
		num=num*-1;
	}
	while(num)
	{
		str[i]=num%10+'0';
		num=num/10;
		i++;
	}
	
	for (j=i-1;j>=0;j--)
	{
		LCD_WriteChar(lcdnum,str[j]);
	}
	
}



static void LCD_WriteFloatNumber(LCD_Number_t lcdnum,f64 Num)
{
	s32 fric;
	LCD_WriteIntegerNumber(lcdnum,(s32)Num);
	if (Num<0)
	{
		Num=-Num;
	}
	LCD_WriteChar(lcdnum,'.');
	
    fric=((Num)-((s32)Num))*100;
 
    LCD_WriteIntegerNumber(lcdnum,fric);
	
}



void LCD_WriteNumber(LCD_Number_t lcdnum,f64 Num)
{
	u32 realValue=Num;
	f32 fricValue=Num-realValue;
	
	if (fricValue>(f32)0)
	{
		LCD_WriteFloatNumber(lcdnum,Num);
	}
	else
	{
		LCD_WriteIntegerNumber(lcdnum,realValue);
	}
	
}



void LCD_ClearDisplay(LCD_Number_t lcdnum)
{
	LCD_WriteInstruction(lcdnum,LCD_CLEAR);
	LCD[lcdnum].Position.Line=Line1;
	LCD[lcdnum].Position.Cell=Cell_1;
}



void LCD_OFFDisplay(LCD_Number_t lcdnum)
{
	LCD_WriteInstruction(lcdnum,LCD_OFFDISPLAY);
}


void LCD_ONDisplay(LCD_Number_t lcdnum)
{
	LCD_WriteInstruction(lcdnum,LcdCursorSetting[lcdnum]);
}




void LCD_WriteBinary(LCD_Number_t lcdnum, u8 num)
{
	u8 i;
	for (i=0 ; i<8 ; i++)
	{
		LCD_WriteChar(lcdnum,READ_BIT(num,(7-i))+'0');
	}
}


void LCD_ClearCell(LCD_Number_t lcdnum,LCD_Line_t Linecell , LCD_Cell_t Cellnum)
{
	LCD_SetCursor(lcdnum,Linecell,Cellnum);
	LCD_WriteChar(lcdnum,' ');
}

void LCD_WriteHexa(LCD_Number_t lcdnum, u8 num)
{
	u8 HB=(num&0xf0)>>4;
	u8 LB=num&0x0f;
	
	LCD_WriteChar(lcdnum,'0');
	LCD_WriteChar(lcdnum,'X');
	
	if (HB<10)
	{
		LCD_WriteChar(lcdnum,(HB+'0'));
	}
	else  // H>10
	{
		LCD_WriteChar(lcdnum,(HB+'A'-10));
	}
	
	if (LB<10)
	{
		LCD_WriteChar(lcdnum,(LB+'0'));
	}
	else  // L>10
	{
		LCD_WriteChar(lcdnum,(LB+'A'-10));
	}
	
	
}


void LCD_WriteNum_4Digit(LCD_Number_t lcdnum, u16 num)
{
	num=num%10000;
	LCD_WriteChar(lcdnum,((num/1000)+'0'));
	num=num%1000;
	LCD_WriteChar(lcdnum,((num/100)+'0'));
	num=num%100;
	LCD_WriteChar(lcdnum,((num/10)+'0'));
	num=num%10;
	LCD_WriteChar(lcdnum,((num)+'0'));
}


/*************************************************************************************************/

void LCD_SaveCustomerPattern(LCD_Number_t lcdnum,u8 *pattern , LCD_CG_address_t pattaddress)
{
	LCD_WriteInstruction(lcdnum,(SET_CG_RAM_ADD+pattaddress*8));
	
	for(u8 i=0 ; i<8 ; i++)
	{
		LCD_WriteData(lcdnum,pattern[i]);
	} 
	LCD_WriteInstruction (lcdnum,(SET_DD_RAM_ADD));
}

void LCD_WriteCustomerPattern(LCD_Number_t lcdnum, LCD_CG_address_t pattaddress)
{
	LCD_WriteChar(lcdnum,pattaddress);
}


/*************************************************************************************************************/

void LCD_CursorPosition(LCD_Number_t lcdnum,LCD_Line_t *Linecell , LCD_Cell_t* Cellnum)
{
	*Linecell=LCD[lcdnum].Position.Line;
	* Cellnum=LCD[lcdnum].Position.Cell;
}

void LCD_ClearLineDisplay(LCD_Number_t lcdnum,LCD_Line_t Linecell)
{
	

	LCD_Cell_t Cell;
	for (Cell=Cell_1 ; Cell<MAXCell ; Cell++)
	{
		LCD_SetCursor(lcdnum,Linecell,Cell);
		LCD_WriteChar(lcdnum,' ');
	}
	
}



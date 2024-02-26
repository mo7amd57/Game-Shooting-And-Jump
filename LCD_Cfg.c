
#include "StdTypes.h"
#include "DIO_Int.h"


#include "LCD_Init.h"
#include "LCD_Cfg.h"
#include "LCD_Priv.h"






/* Hint................My LCD Drive Can Drive 3 LCDs As Max Parallel*/
/* Hint................If You Not Complete Setting it Set By Default*/


 /*>>>>>>>>>  Define Num Of Lcd that you want to use in  Cfg.h  <<<<<<<<<<<<< */


const LCD_BitMode_t LcdMode[LCD_MAXNUM]=
{
	LCD_4_BITMODE,   /* Mode Of LCD1 */   
	LCD_4_BITMODE,   /* Mode Of LCD2 */   
	LCD_8_BITMODE,   /* Mode Of LCD3 */   
};




/*      If Used 8Bit Mode  ====>> Chose Any LCD is 8Bit Mode From your Lcd and Setting it    */

const LCD_8BitConnect_t LCD8BitConnect[LCD_MAXNUM]=
{
	/*Connection Of LCD1 if it on  8BitMode*/
	{
		PINA0,   /*RS Connect Pin*/  /* Pins from PINA0 to PIND7*/
		PINA1,   /*EN Connect Pin*/
		PORT_B,  /*Port To send Data  */  /* Must Be PORT */
	},
	
	
		/*Connection Of LCD2 if it on  8BitMode*/
	{
		PINA2,  /*RS Connect Pin*/
		PINA3,  /*EN Connect Pin*/
		PORT_D, /*Port To send Data  */
	},
	
	
	/*Connection Of LCD3 if it on  8BitMode*/
	{
		PINC2,  /*RS Connect Pin*/
		PINC3,  /*EN Connect Pin*/
		PORT_B, /*Port To send Data  */
	},
	
};



/*    If Used 4Bit Mode  ====>> Chose Any LCD is 4Bit Mode From your Lcd and Setting it    */


const LCD_4BitConnect_t LCD4BitConnect[LCD_MAXNUM]=
{
	/*Connection Of LCD1 if it on  4BitMode*/
	{
		PINA1,   /*RS Connect Pin*/  /* Pins from PINA0 to PIND7*/
		PINA2,   /*EN Connect Pin*/
		
		/*Data PINS*/ 
		
		PINA3,   /* D4 Pin*/
		PINA4,   /* D4 Pin*/
		PINA5,   /* D4 Pin*/
		PINA6,   /* D4 Pin*/
	},
	
	/*Connection Of LCD2 if it on  4BitMode*/
	{
		PIND6,   /*RS Connect Pin*/  /* Pins from PINA0 to PIND7*/
		PIND7,   /*EN Connect Pin*/
		
		/*Data PINS*/
		
		PINB1,   /* D4 Pin*/
		PINB2,   /* D5 Pin*/
		PINB3,   /* D6 Pin*/
		PINC6,   /* D7 Pin*/
	},
	
	
	/*Connection Of LCD3 if it on  4BitMode*/
	{
		PINA4,   /*RS Connect Pin*/  /* Pins from PINA0 to PIND7*/
		PINA5,   /*EN Connect Pin*/
		
		/*Data PINS*/
		
		PIND4,   /* D4 Pin*/
		PIND5,   /* D5 Pin*/
		PIND6,   /* D6 Pin*/
		PIND7,   /* D7 Pin*/
	},
};



const LCD_CursorSett_t LcdCursorSetting[LCD_MAXNUM]=
{
	LCD_CURSOR_OFF,       /*Cursor Setting For LCD1 */
	LCD_CURSOR_OFF,     /*Cursor Setting For LCD2  */
	LCD_CURSOR_OFF,  /*Cursor Setting For LCD3  */
	
	// Options 
	/*
	  LCD_CURSOR_BLINK
	  LCD_CURSOR_NOTBLINK
	  LCD_CURSOR_OFF
	*/
};



 const LCD_DisplayMoveDirection_t LcdMoveDirection[LCD_MAXNUM]=
 {
	 LCD_IncreaseAddressDisplay,  /*Move Direction at Display On LCD1*/
	 LCD_IncreaseAddressDisplay,  /*Move Direction at Display On LCD2*/
	 LCD_IncreaseAddressDisplay,   /*Move Direction at Display On LCD3*/
	 
	 /*LCD_ShiftRightDisplay,*/   /* you can use it too by replace any one after by it  */
	 
	 /* Options 
	 LCD_IncreaseAddressDisplay
	 LCD_DecreaseAddressDisplay
	 
	 LCD_ShiftLeftDisplay
	 LCD_ShiftRightDisplay
	 
	 */
 };



const LCD_CellDotNum_t LcdCellDot[LCD_MAXNUM]=
{
	LCD_Cell5x7Dot,   /* Cell DotType Of LCD1 */  
	LCD_Cell5x7Dot,   /* Cell DotType Of LCD2 */ 
	LCD_Cell5x7Dot,  /* Cell DotType Of LCD3 */ 
};





/*===========================>>   Setting Finshed   <<================================================*/


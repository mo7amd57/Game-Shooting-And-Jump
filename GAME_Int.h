/*
 * GAME_Int.h
 *
 * Created: 12/20/2023 10:43:09 AM
 *  Author: Mohamed Ramadan
 */ 


#ifndef GAME_INT_H_
#define GAME_INT_H_

/*******************************  CFG  ***********************************/
#define MAXSCORE 7
#define DELLAY  100

#define DLLAY_WIN  10



/*******************************************************************************/


#define CHANGEMODEBUTTON  PIND2 
#define PLAYERONEBUTTON   PIND3 
#define PLAYERTWOBUTTON   PIND4 

/*************************************************************************/



#define  PATTSTOPADDRESS  ADD1
#define  PATTSHOTADDRESS  ADD2
#define  PATTGUNADDRESS   ADD3
#define  PATTGUNADDRESS2  ADD4
#define  LAST_WINDDRESS   ADD5
#define  PONE_KILLEDADD   ADD6
#define  PTWO_KILLEDADD   ADD7
#define  PLAYE_WINDADD    ADD8


typedef enum
{
	PLAYER1_ATTACK,
	PLAYER2_ATTACK
}GAME_Mode_t;

typedef enum
{
	DOWN,
	UP,	
}GAME_Position_t;

void GAME_Init(void);

void GAME_intro(LCD_Number_t lcdnum);

void GAME_GameMode(LCD_Number_t lcdnum,GAME_Mode_t mode);

void GAME_Scores(u8 Play1score , u8 Play2score);

void GAME_PlayerPositionMode1(void);

void GAME_PlayerPositionMode2(void);

ButtonStatus_t Button_CheckStatus(DIO_Pin_t PinButton);


#endif /* GAME_INT_H_ */
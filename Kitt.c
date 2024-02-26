
#include "main.h"


extern LCD_Line_t Linecell;
extern LCD_Cell_t Cellnum;

static Flag_t flag={0,0,0,0,0,0};

u8 Play1Score=0;
u8 Play2score=0;

u8 count=0;
GAME_Position_t position=DOWN;




int main(void)
{
	
	GAME_Mode_t FlagMode=PLAYER1_ATTACK;
	
	u8 youwin[]="You Win (^ ^)";
	u8 gameover[]="Game Over";

	DIO_InitDirection();
	LCD_init();
	
	GAME_Init();


	
	LCD_Cell_t Cell=Cell_2;
	LCD_Cell_t Cell2=Cell_15;
	
	
	while (1)
	{
		if (flag.f6==1)
		{
			GAME_Scores(Play1Score,Play2score);
			flag.f6=0;
		}
		
		
		if (FlagMode==PLAYER1_ATTACK)
		{
			if (flag.f3==0)
			{
				LCD_ClearDisplay(LCD1);
				GAME_GameMode(LCD1,PLAYER1_ATTACK);
				flag.f3=1;
			}
			GAME_PlayerPositionMode1();
			
			LCD_SetCursor(LCD1,Line2,Cell);
			LCD_WriteChar(LCD1,PATTGUNADDRESS);
			_delay_ms(DELLAY);
			
			if (Button_CheckStatus(PLAYERONEBUTTON)==Pressed)
			{
				flag.f1=1;
				while(Button_CheckStatus(PLAYERONEBUTTON)==Pressed);
			}
			
			
			
			if (flag.f1==1)
			{
				LCD_ClearCell(LCD1,Line2,Cell);
				Cell++;
				if (Cell>Cell_15)
				{
					Cell=Cell_2;
					flag.f1=0;
				}
			}
			
			
			
			
			if(Button_CheckStatus(PLAYERTWOBUTTON)==Pressed)
			{
				while(Button_CheckStatus(PLAYERTWOBUTTON)==Pressed)
				{
					
					if (Button_CheckStatus(CHANGEMODEBUTTON)==Pressed)
					{
						flag.f4=0;
						FlagMode=PLAYER2_ATTACK;
						while(Button_CheckStatus(CHANGEMODEBUTTON)==Pressed);
					}
					
					
					/************************>> Continue  <<***********************************/
					LCD_SetCursor(LCD1,Line2,Cell);
					LCD_WriteChar(LCD1,PATTGUNADDRESS);
					_delay_ms(DELLAY);
					if (flag.f1==1)
					{
						LCD_ClearCell(LCD1,Line2,Cell);
						Cell++;
						if (Cell>Cell_15)
						{
							Cell=Cell_2;
							flag.f1=0;
						}
					}
					
					
					/*********************>>  Check Killing <<*******************/
					
					LCD_CursorPosition(LCD1,&Linecell,&Cellnum);
					
					if (Linecell==Line2 && Cellnum >=Cell_15 &&position==DOWN&&flag.f1==1)
					{
						
						Play1Score++;
						
						
						
						
						
						LCD_ClearCell(LCD1,Line2,Cell_15);
						LCD_SetCursor(LCD1,Line2,Cell_16);
						LCD_WriteChar(LCD1,PTWO_KILLEDADD);
						LCD_SetCursor(LCD1,Line2,Cell_15);
						LCD_WriteChar(LCD1,PATTGUNADDRESS);
						
						for (u8 i=0 ; i<4 ; i++)
						{
							LCD_SetCursor(LCD1,Line2,Cell_1);
							LCD_WriteChar(LCD1,PLAYE_WINDADD);
							_delay_ms(DLLAY_WIN);
							LCD_SetCursor(LCD1,Line2,Cell_1);
							LCD_WriteChar(LCD1,PATTSTOPADDRESS);
							_delay_ms(DLLAY_WIN);
							if (i==1)
							{
								LCD_ClearCell(LCD1,Line2,Cell_15);
							}
							if (i==2)
							{
								LCD_ClearCell(LCD1,Line2,Cell_16);
							}
							
						}
						//LCD_ClearCell(LCD1,Line2,Cell_16);
						
						
						
						
						
						
						
						LCD_SetCursor(LCD2,Line2,Cell_9);
						LCD_WriteChar(LCD2,((Play1Score/10)+'0'));
						LCD_SetCursor(LCD2,Line2,Cell_10);
						LCD_WriteChar(LCD2,((Play1Score%10)+'0'));
					}
					else if (Linecell==Line2 && Cellnum >=Cell_15 &&position==UP &&flag.f1==1)
					{
						Play2score++;
						
						LCD_SetCursor(LCD3,Line2,Cell_9);
						LCD_WriteChar(LCD3,((Play2score/10)+'0'));
						LCD_SetCursor(LCD3,Line2,Cell_10);
						LCD_WriteChar(LCD3,((Play2score%10)+'0'));
						
						
						
						
					}
					
					
					
					/***********************>>   UP    <<************************************/
					if (count<2)
					{
						LCD_ClearCell(LCD1,Line2,Cell_15);
						LCD_SetCursor(LCD1,Line1,Cell_15);
						LCD_WriteChar(LCD1,PATTSHOTADDRESS);
						position=UP;
						count++;
					}
					else
					{
						LCD_ClearCell(LCD1,Line1,Cell_15);
						LCD_SetCursor(LCD1,Line2,Cell_15);
						LCD_WriteChar(LCD1,PATTSTOPADDRESS);
						position=DOWN;
					}
					
				}
				
				
				
				
				/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
				
				if (Play1Score>=MAXSCORE)
				{
					LCD_ClearDisplay(LCD1);
					LCD_ClearDisplay(LCD2);
					LCD_ClearDisplay(LCD3);
					LCD_WriteString(LCD2,youwin);
					LCD_WriteString(LCD3,gameover);
					LCD_WriteString(LCD1,"Player One Win");
					
					for (u8 i =0 ; i<8 ; i++)
					{
						LCD_SetCursor(LCD1,Line2,Cell_8);
						LCD_WriteChar(LCD1,PATTSTOPADDRESS);
						_delay_ms(DLLAY_WIN);
						LCD_SetCursor(LCD1,Line2,Cell_8);
						LCD_WriteChar(LCD1,LAST_WINDDRESS);
						_delay_ms(DLLAY_WIN);
						
						LCD_SetCursor(LCD1,Line2,Cell_8);
						LCD_WriteChar(LCD1,PLAYE_WINDADD);
						_delay_ms(DLLAY_WIN);
					}
					
					
					LCD_ClearDisplay(LCD1);
					LCD_ClearDisplay(LCD2);
					LCD_ClearDisplay(LCD3);
					Play1Score=0;
					Play2score=0;
					flag.f3=0;
					flag.f6=1;
					
				}
				else if (Play2score>=MAXSCORE)
				{
					LCD_ClearDisplay(LCD1);
					LCD_ClearDisplay(LCD2);
					LCD_ClearDisplay(LCD3);
					
					LCD_WriteString(LCD3,youwin);
					LCD_WriteString(LCD2,gameover);
					LCD_WriteString(LCD1," Player Two Win");
					
					for (u8 i =0 ; i<8 ; i++)
					{
						LCD_SetCursor(LCD1,Line2,Cell_8);
						LCD_WriteChar(LCD1,PATTSTOPADDRESS);
						_delay_ms(DLLAY_WIN);
						LCD_SetCursor(LCD1,Line2,Cell_8);
						LCD_WriteChar(LCD1,LAST_WINDDRESS);
						_delay_ms(DLLAY_WIN);
						
						LCD_SetCursor(LCD1,Line2,Cell_8);
						LCD_WriteChar(LCD1,PLAYE_WINDADD);
						_delay_ms(DLLAY_WIN);
					}
					
					
					LCD_ClearDisplay(LCD1);
					LCD_ClearDisplay(LCD2);
					LCD_ClearDisplay(LCD3);
					Play1Score=0;
					Play2score=0;
					flag.f3=0;
					flag.f6=1;
				}
				
				
				
				/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
				
				/*>>>>>>>>>>>>>>> Button be unpressed <<<<<<<<<<<<<<<<<<<<<*/
				
				LCD_ClearCell(LCD1,Line1,Cell_15);
				//position=DOWN;
				count=0;
			}
			
			LCD_CursorPosition(LCD1,&Linecell,&Cellnum);
			if (Linecell==Line2 && Cellnum >=Cell_15 &&position==DOWN &&flag.f1==1)
			{
				
				Play1Score++;
				
				
				
				
				LCD_ClearCell(LCD1,Line2,Cell_15);
				LCD_SetCursor(LCD1,Line2,Cell_16);
				LCD_WriteChar(LCD1,PTWO_KILLEDADD);
				LCD_SetCursor(LCD1,Line2,Cell_15);
				LCD_WriteChar(LCD1,PATTGUNADDRESS);
				
				for (u8 i=0 ; i<4 ; i++)
				{
					LCD_SetCursor(LCD1,Line2,Cell_1);
					LCD_WriteChar(LCD1,PLAYE_WINDADD);
					_delay_ms(DLLAY_WIN);
					
					LCD_SetCursor(LCD1,Line2,Cell_1);
					LCD_WriteChar(LCD1,PATTSTOPADDRESS);
					_delay_ms(DLLAY_WIN);
					
					if (i==1)
					{
						LCD_ClearCell(LCD1,Line2,Cell_15);
					}
					if (i==2)
					{
						LCD_ClearCell(LCD1,Line2,Cell_16);
					}
					
				}
			//	LCD_ClearCell(LCD1,Line2,Cell_16);
				
				
				
				
				LCD_SetCursor(LCD2,Line2,Cell_9);
				LCD_WriteChar(LCD2,((Play1Score/10)+'0'));
				LCD_SetCursor(LCD2,Line2,Cell_10);
				LCD_WriteChar(LCD2,((Play1Score%10)+'0'));
			}
			else if (Linecell==Line2 && Cellnum >=Cell_15 &&position==UP &&flag.f1==1)
			{
				
				Play2score++;
				
				LCD_SetCursor(LCD3,Line2,Cell_9);
				LCD_WriteChar(LCD3,((Play2score/10)+'0'));
				LCD_SetCursor(LCD3,Line2,Cell_10);
				LCD_WriteChar(LCD3,((Play2score%10)+'0'));
			}
			
			/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
			
			if (Play1Score>=MAXSCORE)
			{
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				LCD_WriteString(LCD2,youwin);
				LCD_WriteString(LCD3,gameover);
				LCD_WriteString(LCD1," Player One Win");
				
				for (u8 i =0 ; i<8 ; i++)
				{
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PATTSTOPADDRESS);
					_delay_ms(DLLAY_WIN);
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,LAST_WINDDRESS);
					_delay_ms(DLLAY_WIN);
					
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PLAYE_WINDADD);
					_delay_ms(DLLAY_WIN);
				}
				
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				Play1Score=0;
				Play2score=0;
				flag.f3=0;
				flag.f6=1;
			}
			else if (Play2score>=MAXSCORE)
			{
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				
				LCD_WriteString(LCD3,youwin);
				LCD_WriteString(LCD2,gameover);
				LCD_WriteString(LCD1," Player Two Win");
				
				
				for (u8 i =0 ; i<8 ; i++)
				{
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PATTSTOPADDRESS);
					_delay_ms(DLLAY_WIN);
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,LAST_WINDDRESS);
					_delay_ms(DLLAY_WIN);
					
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PLAYE_WINDADD);
					_delay_ms(DLLAY_WIN);
				}
				
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				Play1Score=0;
				Play2score=0;
				flag.f3=0;
				flag.f6=1;
			}
			
			
			
			/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
			

			
			
			if (Button_CheckStatus(CHANGEMODEBUTTON)==Pressed)
			{
				flag.f4=0;
				FlagMode=PLAYER2_ATTACK;
				while(Button_CheckStatus(CHANGEMODEBUTTON)==Pressed);
			}
			
			
			
		}
		else
		{
			
			
			
			
			
			if (flag.f4==0)
			{
				LCD_ClearDisplay(LCD1);
				GAME_GameMode(LCD1,PLAYER2_ATTACK);
				flag.f4=1;
			}
			GAME_PlayerPositionMode2();
			
			LCD_SetCursor(LCD1,Line2,Cell2);
			LCD_WriteChar(LCD1,PATTGUNADDRESS2);
			_delay_ms(DELLAY);
			
			if (Button_CheckStatus(PLAYERTWOBUTTON)==Pressed)
			{
				flag.f2=1;
				while(Button_CheckStatus(PLAYERTWOBUTTON)==Pressed);
			}
			
			
			if (flag.f2==1)
			{
				LCD_ClearCell(LCD1,Line2,Cell2);
				Cell2--;
				if (Cell2<Cell_2)
				{
					Cell2=Cell_15;
					flag.f2=0;
				}
			}
			
			
			
			if(Button_CheckStatus(PLAYERONEBUTTON)==Pressed)
			{
				while(Button_CheckStatus(PLAYERONEBUTTON)==Pressed)
				{
					
					if (Button_CheckStatus(CHANGEMODEBUTTON)==Pressed)
					{
						flag.f3=0;
						FlagMode=PLAYER1_ATTACK;
						while(Button_CheckStatus(CHANGEMODEBUTTON)==Pressed);
					}
					
					
					/************************>> Continue  <<***********************************/
					
					LCD_SetCursor(LCD1,Line2,Cell2);
					LCD_WriteChar(LCD1,PATTGUNADDRESS2);
					_delay_ms(DELLAY);
					if (flag.f2==1)
					{
						LCD_ClearCell(LCD1,Line2,Cell2);
						Cell2--;
						if (Cell2<Cell_2)
						{
							Cell2=Cell_15;
							flag.f2=0;
						}
					}
					
					
					/*********************>>  Check Killing <<*******************/
					
					
					LCD_CursorPosition(LCD1,&Linecell,&Cellnum);
					
					if (Linecell==Line2 && Cellnum <=Cell_4 &&position==UP&&flag.f2==1)
					{
						
						Play1Score++;
						
						
						
						
						
						
						LCD_SetCursor(LCD2,Line2,Cell_9);
						LCD_WriteChar(LCD2,((Play1Score/10)+'0'));
						LCD_SetCursor(LCD2,Line2,Cell_10);
						LCD_WriteChar(LCD2,((Play1Score%10)+'0'));
					}
					else if (Linecell==Line2 && Cellnum <=Cell_4 &&position==DOWN &&flag.f2==1)
					{
						Play2score++;
						
						
						
						LCD_ClearCell(LCD1,Line2,Cell_2);
						LCD_SetCursor(LCD1,Line2,Cell_1);
						LCD_WriteChar(LCD1,PONE_KILLEDADD);
						LCD_SetCursor(LCD1,Line2,Cell_2);
						LCD_WriteChar(LCD1,PATTGUNADDRESS2);
						
						for (u8 i=0 ; i<4 ; i++)
						{
							LCD_SetCursor(LCD1,Line2,Cell_16);
							LCD_WriteChar(LCD1,PLAYE_WINDADD);
							_delay_ms(DLLAY_WIN);
							LCD_SetCursor(LCD1,Line2,Cell_16);
							LCD_WriteChar(LCD1,PATTSTOPADDRESS);
							_delay_ms(DLLAY_WIN);
							if (i==1)
							{
								LCD_ClearCell(LCD1,Line2,Cell_2);
							}
							if (i==2)
							{
								LCD_ClearCell(LCD1,Line2,Cell_1);
							}
							
						}
					
						
						
						
						
						
						
						
						
						
						
						
						LCD_SetCursor(LCD3,Line2,Cell_9);
						LCD_WriteChar(LCD3,((Play2score/10)+'0'));
						LCD_SetCursor(LCD3,Line2,Cell_10);
						LCD_WriteChar(LCD3,((Play2score%10)+'0'));
						
					}
					
					
					
					
					/***********************>>   UP    <<************************************/
					
					if (count<2)
					{
						LCD_ClearCell(LCD1,Line2,Cell_2);
						LCD_SetCursor(LCD1,Line1,Cell_2);
						LCD_WriteChar(LCD1,PATTSHOTADDRESS);
						position=UP;
						count++;
					}
					else
					{
						LCD_ClearCell(LCD1,Line1,Cell_2);
						LCD_SetCursor(LCD1,Line2,Cell_2);
						LCD_WriteChar(LCD1,PATTSTOPADDRESS);
						position=DOWN;
					}
					
					/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
					
					if (Play1Score>=MAXSCORE)
					{
						LCD_ClearDisplay(LCD1);
						LCD_ClearDisplay(LCD2);
						LCD_ClearDisplay(LCD3);
						LCD_WriteString(LCD2,youwin);
						LCD_WriteString(LCD3,gameover);
						LCD_WriteString(LCD1," Player One Win");
						
						
						
						for (u8 i =0 ; i<8 ; i++)
						{
							LCD_SetCursor(LCD1,Line2,Cell_8);
							LCD_WriteChar(LCD1,PATTSTOPADDRESS);
							_delay_ms(DLLAY_WIN);
							LCD_SetCursor(LCD1,Line2,Cell_8);
							LCD_WriteChar(LCD1,LAST_WINDDRESS);
							_delay_ms(DLLAY_WIN);
							
							LCD_SetCursor(LCD1,Line2,Cell_8);
							LCD_WriteChar(LCD1,PLAYE_WINDADD);
							_delay_ms(DLLAY_WIN);
						}
						
						
						
						
						
						
						LCD_ClearDisplay(LCD1);
						LCD_ClearDisplay(LCD2);
						LCD_ClearDisplay(LCD3);
						Play1Score=0;
						Play2score=0;
						flag.f4=0;
						flag.f6=1;
					}
					else if (Play2score>=MAXSCORE)
					{
						LCD_ClearDisplay(LCD1);
						LCD_ClearDisplay(LCD2);
						LCD_ClearDisplay(LCD3);
						
						LCD_WriteString(LCD3,youwin);
						LCD_WriteString(LCD2,gameover);
						LCD_WriteString(LCD1," Player Two Win");
						
						for (u8 i =0 ; i<8 ; i++)
						{
							LCD_SetCursor(LCD1,Line2,Cell_8);
							LCD_WriteChar(LCD1,PATTSTOPADDRESS);
							_delay_ms(DLLAY_WIN);
							LCD_SetCursor(LCD1,Line2,Cell_8);
							LCD_WriteChar(LCD1,LAST_WINDDRESS);
							_delay_ms(DLLAY_WIN);
							
							LCD_SetCursor(LCD1,Line2,Cell_8);
							LCD_WriteChar(LCD1,PLAYE_WINDADD);
							_delay_ms(DLLAY_WIN);
						}
						
						
						LCD_ClearDisplay(LCD1);
						LCD_ClearDisplay(LCD2);
						LCD_ClearDisplay(LCD3);
						Play1Score=0;
						Play2score=0;
						flag.f4=0;
						flag.f6=1;
					}
					
					
					
					/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
					
				}
				
				/*>>>>>>>>>>>>>>> Button be unpressed <<<<<<<<<<<<<<<<<<<<<*/
				
				LCD_ClearCell(LCD1,Line1,Cell_2);
				//position=DOWN;
				count=0;
			}
			
			
			
			
			
			LCD_CursorPosition(LCD1,&Linecell,&Cellnum);
			if (Linecell==Line2 && Cellnum <=Cell_4 &&position==UP &&flag.f2==1)
			{
				Play1Score++;
				
				LCD_SetCursor(LCD2,Line2,Cell_9);
				LCD_WriteChar(LCD2,((Play1Score/10)+'0'));
				LCD_SetCursor(LCD2,Line2,Cell_10);
				LCD_WriteChar(LCD2,((Play1Score%10)+'0'));
			}
			else if (Linecell==Line2 && Cellnum <=Cell_4 &&position==DOWN &&flag.f2==1)
			{
				Play2score++;
				
				
				
				
				
				
				
				
				LCD_ClearCell(LCD1,Line2,Cell_2);
				LCD_SetCursor(LCD1,Line2,Cell_1);
				LCD_WriteChar(LCD1,PONE_KILLEDADD);
				LCD_SetCursor(LCD1,Line2,Cell_2);
				LCD_WriteChar(LCD1,PATTGUNADDRESS2);
				
				for (u8 i=0 ; i<4 ; i++)
				{
					LCD_SetCursor(LCD1,Line2,Cell_16);
					LCD_WriteChar(LCD1,PLAYE_WINDADD);
					_delay_ms(DLLAY_WIN);
					LCD_SetCursor(LCD1,Line2,Cell_16);
					LCD_WriteChar(LCD1,PATTSTOPADDRESS);
					_delay_ms(DLLAY_WIN);
					if (i==1)
					{
						LCD_ClearCell(LCD1,Line2,Cell_2);
					}
					if (i==2)
					{
						LCD_ClearCell(LCD1,Line2,Cell_1);
					}
					
				}
					
				
				
				
				
				
				
				
				LCD_SetCursor(LCD3,Line2,Cell_9);
				LCD_WriteChar(LCD3,((Play2score/10)+'0'));
				LCD_SetCursor(LCD3,Line2,Cell_10);
				LCD_WriteChar(LCD3,((Play2score%10)+'0'));
			}

			
			
			if (Button_CheckStatus(CHANGEMODEBUTTON)==Pressed)
			{
				FlagMode=PLAYER1_ATTACK;
				flag.f3=0;
				while(Button_CheckStatus(CHANGEMODEBUTTON)==Pressed);
			}
			
			/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
			
			if (Play1Score>=MAXSCORE)
			{
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				LCD_WriteString(LCD2,youwin);
				LCD_WriteString(LCD3,gameover);
				LCD_WriteString(LCD1," Player One Win");
				
				
				
				for (u8 i =0 ; i<8 ; i++)
				{
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PATTSTOPADDRESS);
					_delay_ms(DLLAY_WIN);
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,LAST_WINDDRESS);
					_delay_ms(DLLAY_WIN);
					
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PLAYE_WINDADD);
					_delay_ms(DLLAY_WIN);
				}
				
				
				
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				Play1Score=0;
				Play2score=0;
				flag.f4=0;
				flag.f6=1;
			}
			else if (Play2score>=MAXSCORE)
			{
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				
				LCD_WriteString(LCD3,youwin);
				LCD_WriteString(LCD2,gameover);
				LCD_WriteString(LCD1," Player Two Win");
				
				for (u8 i =0 ; i<8 ; i++)
				{
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PATTSTOPADDRESS);
					_delay_ms(DLLAY_WIN);
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,LAST_WINDDRESS);
					_delay_ms(DLLAY_WIN);
					
					LCD_SetCursor(LCD1,Line2,Cell_8);
					LCD_WriteChar(LCD1,PLAYE_WINDADD);
					_delay_ms(DLLAY_WIN);
				}
				
				
				
				LCD_ClearDisplay(LCD1);
				LCD_ClearDisplay(LCD2);
				LCD_ClearDisplay(LCD3);
				Play1Score=0;
				Play2score=0;
				flag.f4=0;
				flag.f6=1;
			}
			/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
		}
		
	}
}

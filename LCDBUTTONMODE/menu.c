
#include "menu.h"

unsigned int debag = 0;

MENU_StateTypeDef menu_state = MENU_STATE_IDLE;
Set_ParametrsTypeDef parametrs_state = None;
Manual_State Manual_Set = 0;
unsigned char ShowManual = 0;

void ShowParametrs ()
{
	switch(parametrs_state)
	{
		case BootelSpaising:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("BootelSpaising");
			setpos(4,1);
			str_lcd_int(Bottle_Spaising);
			parametrs_state = None;
		}
		break;
		case InBootleDelau:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("InBootleDelau");
			setpos(4,1);
			str_lcd_int(In_Bottle_Delay);
			parametrs_state = None;
		}
		break;
		case ValyeDelay:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("ValyeDelay");
			setpos(4,1);
			str_lcd_int(Valye_Delay);
			parametrs_state = None;
		}
		break;
		case liftdownDelay:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("liftdownDelay");
			setpos(4,1);
			str_lcd_int(lift_down_Delay);
			parametrs_state = None;
		}
		break;
		case BottleOutDelay:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("BottleOutDelay");
			setpos(4,1);
			str_lcd_int(Bottle_Out_Delay);
			parametrs_state = None;
		}
		break;
		case AfterLiftUpDelay:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("AfterLiftUpDelay");
			setpos(4,1);
			str_lcd_int(After_LiftUp_Delay);
			parametrs_state = None;
		}
		break;
		case AfterLiftDownDelay:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("AfterLiftDownDelay");
			setpos(4,1);
			str_lcd_int(After_Lift_Down_Delay);
			parametrs_state = None;
		}
		break;
		case None:
		{
			
		}
		break;
	}
}

void MenuProcess(void)
{
	switch (menu_state)
	{
		//старт программы-------------------------------
		case MENU_STATE_IDLE: 
		{
			clearlcd();
			str_lcd("Welkom Roman");
			ProgramStop();
			menu_state = MENU_STATE_WAIT;
		}
		break;
		//ждем запуска главного меню----------------------------------
		case MENU_STATE_WAIT: 
		{
			if (ShowCount > 0)
			{
				setpos(0,1);
				str_lcd("Count ");
				setpos(6,1);
				str_lcd_uint16(Count_Value);
				ShowCount = 0;
			}
			if (PINB&(1<<Cover))
			{
				PORTB |= 1<<0;
			}
			
			if (button_state[Button_Right]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Right,ST_LOCKED);
				ResetButtonState(Button_Right,ST_UNPRESSURE);
				SetButtonState(Button_Right,ST_PRESSURE);
				clearlcd();
				setpos(0,0);
				str_lcd("ButtonRinght");
				ResetButtonState(Button_Right,ST_LOCKED);
			}
			if (button_state[Button_Up]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Up,ST_LOCKED);
				ResetButtonState(Button_Up,ST_UNPRESSURE);
				SetButtonState(Button_Up,ST_PRESSURE);
				EEPROM_write_2bit(15,0);
				Count_Value = EEPROM_read_2bit(15);
				clearlcd();
				setpos(0,0);
				str_lcd("Welkom Roman");
				setpos(0,1);
				str_lcd("Count ");
				setpos(6,1);
				str_lcd_uint16(Count_Value);
				ShowCount = 1;
				ResetButtonState(Button_Up,ST_LOCKED);
			}
			if (button_state[Button_Down]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Down,ST_LOCKED);
				ResetButtonState(Button_Down,ST_UNPRESSURE);
				SetButtonState(Button_Down,ST_PRESSURE);
				clearlcd();
				setpos(0,0);
				str_lcd("ButtonDown");
				ResetButtonState(Button_Down,ST_LOCKED);
			}
			if (button_state[Button_Left]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Left,ST_LOCKED);
				ResetButtonState(Button_Left,ST_UNPRESSURE);
				SetButtonState(Button_Left,ST_PRESSURE);
				clearlcd();
				setpos(0,0);
				str_lcd("ButtonLeft");
				ResetButtonState(Button_Left,ST_LOCKED);
			}
			if (button_state[Button_Menu]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Menu,ST_LOCKED);
				ResetButtonState(Button_Menu,ST_UNPRESSURE);
				SetButtonState(Button_Menu,ST_PRESSURE);
				menu_state = MENU_STATE_SETING;
				clearlcd();
				setpos(0,0);
				str_lcd("< Seting >");
				ResetButtonState(Button_Menu,ST_LOCKED);
			}
			if (button_state[Button_Start]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Start,ST_LOCKED);
				ResetButtonState(Button_Start,ST_UNPRESSURE);
				SetButtonState(Button_Start,ST_PRESSURE);
				menu_state = MENU_STATE_STARTING;
				ResetButtonState(Button_Start,ST_LOCKED);
			}
		}
		break;
		
		//машына стартует--------------------------------------------
		case MENU_STATE_STARTING:
		{
			clearlcd();
			setpos(0,0);
			str_lcd("Started");
			ShowCount = 1;
			ProgramStop();
			menu_state = MENU_STATE_STARTED;
		}
		break;
		
		//машына работает--------------------------------------------
		case MENU_STATE_STARTED:
		{
			if (ShowCount > 0)
			{
				setpos(0,1);
				str_lcd("Count ");
				setpos(6,1);
				str_lcd_uint16(Count_Value);
				ShowCount = 0;
			}
			
			if (PINB&(1<<Cover))
			{
				PORTB &= ~(1<<0);
			}
			
			ProgramStart ();
			if (button_state[Button_Start]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Start,ST_LOCKED);
				ResetButtonState(Button_Start,ST_UNPRESSURE);
				SetButtonState(Button_Start,ST_PRESSURE);
				menu_state = MENU_STATE_WAIT;
				ShowCount = 1;
				ProgramStop();
				clearlcd();
				setpos(0,0);
				str_lcd("Welkom Roman");
				setpos(0,1);
				str_lcd("Count ");
				setpos(6,1);
				str_lcd_uint16(Count_Value);
				ResetButtonState(Button_Start,ST_LOCKED);
			}
		}
		break;
		
		//запуск главного меню--------------------------------------------
		
		case MENU_STATE_SETING: 
		{
			if (button_state[Button_Right]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Right,ST_LOCKED);
				ResetButtonState(Button_Right,ST_UNPRESSURE);
				SetButtonState(Button_Right,ST_PRESSURE);
				if (setingNavigation < 7)
					setingNavigation++;
				else
					setingNavigation = 1;				
				parametrs_state = setingNavigation;
				ResetButtonState(Button_Right,ST_LOCKED);
			}
		
			if (button_state[Button_Left]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Left,ST_LOCKED);
				ResetButtonState(Button_Left,ST_UNPRESSURE);
				SetButtonState(Button_Left,ST_PRESSURE);
				if (setingNavigation > 1)
					setingNavigation--;
				else
					setingNavigation = 7;			
				parametrs_state = setingNavigation;
				ResetButtonState(Button_Left,ST_LOCKED);
			}
		
			if (button_state[Button_Up]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Up,ST_LOCKED);
				ResetButtonState(Button_Up,ST_UNPRESSURE);
				SetButtonState(Button_Up,ST_PRESSURE);
				switch(setingNavigation)
				{
					case 0://0 None = 0,
					{
					
					}
					break;
				
					case 1://1 BootelSpaising,
					{
						Bottle_Spaising += 100;
						EEPROM_write_2bit(1,Bottle_Spaising);
					}
					break;
				
					case 2://2 InBootleDelau,
					{
						In_Bottle_Delay += 100;
						EEPROM_write_2bit(3,In_Bottle_Delay);
					}
					break;
				
					case 3://3 ValyeDelay,
					{
						Valye_Delay += 100;
						EEPROM_write_2bit(5,Valye_Delay);
					}
					break;
				
					case 4://4 liftdownDelay,
					{
						lift_down_Delay += 100;
						EEPROM_write_2bit(7,lift_down_Delay);
					}
					break;
				
					case 5://5 BottleOutDelay,
					{
						Bottle_Out_Delay += 100;
						EEPROM_write_2bit(9,Bottle_Out_Delay);
					}
					break;
				//
					case 6://7 AfterLiftUpDelay,
					{
						After_LiftUp_Delay += 100;
						EEPROM_write_2bit(11,After_LiftUp_Delay);
					}
					break;
					case 7://7 AfterLiftDownDelay,
					{
						After_Lift_Down_Delay += 100;
						EEPROM_write_2bit(13,After_Lift_Down_Delay);
					}
					break;
				}
				parametrs_state =setingNavigation;
				ResetButtonState(Button_Up,ST_LOCKED);
			}
			if (button_state[Button_Down]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Down,ST_LOCKED);
				ResetButtonState(Button_Down,ST_UNPRESSURE);
				SetButtonState(Button_Down,ST_PRESSURE);
				switch(setingNavigation)
				{	
					case 0://0 None = 0,
					{
					
					}
					break;
				
					case 1://1 BootelSpaising,
					{
						Bottle_Spaising -= 100;
						EEPROM_write_2bit(1,Bottle_Spaising);
					}
					break;
				
					case 2://2 InBootleDelau,
					{
						In_Bottle_Delay -= 100;
						EEPROM_write_2bit(3,In_Bottle_Delay);
					}
					break;
				
					case 3://3 ValyeDelay,
					{
						Valye_Delay -= 100;
						EEPROM_write_2bit(5,Valye_Delay);
					}
					break;
				
					case 4://4 liftdownDelay,
					{
						lift_down_Delay -= 100;
						EEPROM_write_2bit(7,lift_down_Delay);
					}
					break;
				
					case 5://5 BottleOutDelay,
					{
						Bottle_Out_Delay -= 100;
						EEPROM_write_2bit(9,Bottle_Out_Delay);
					}
					break;
				
					case 6://7 AfterLiftUpDelay,
					{
						After_LiftUp_Delay -= 100;
						EEPROM_write_2bit(11,After_LiftUp_Delay);
					}
					break;
					case 7://7 AfterLiftDownDelay,
					{
						After_Lift_Down_Delay -= 100;
						EEPROM_write_2bit(13,After_Lift_Down_Delay);
					}
					break;
				}
				parametrs_state =setingNavigation;
				ResetButtonState(Button_Down,ST_LOCKED);
			}
			ShowParametrs();
			if (button_state[Button_Menu]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Menu,ST_LOCKED);
				ResetButtonState(Button_Menu,ST_UNPRESSURE);
				SetButtonState(Button_Menu,ST_PRESSURE);
				menu_state = MENU_STATE_MANUAL;
				ResetButtonState(Button_Menu,ST_LOCKED);
			}
		}
		
		break;
		
		//настройка машини
		case MENU_STATE_MANUAL:
		{
			if (ShowManual == 0)
			{
				switch(Manual_Set)
				{
					case RinghtSeparator_On:
					{
						clearlcd();
						setpos(0,0);
						str_lcd("RighSeparator_on");
						if(PINC&(1<<RinghtSeparator))
						{
							setpos(6,1);
							str_lcd("OF");
						}
						else
						{
							setpos(6,1);
							str_lcd("ON");
						}
						ShowManual = 1;
					}
					break;
					case LeftSeparator_On:
					{
						clearlcd();
						setpos(0,0);
						str_lcd("LeftSeparator_on");
						if(PINC&(1<<LeftSeparator))
						{
							setpos(6,1);
							str_lcd("OF");
						}
						else
						{
							setpos(6,1);
							str_lcd("ON");
						}
						ShowManual = 1;
					}
					break;
					case Lift_On:
					{
						clearlcd();
						setpos(0,0);
						str_lcd("Lift_on");
						if(PINC&(1<<Lift))
						{
							setpos(6,1);
							str_lcd("OF");
						}
						else
						{
							setpos(6,1);
							str_lcd("ON");
						}
						ShowManual = 1;
					}
					break;
					case Value_On:
					{
						clearlcd();
						setpos(0,0);
						str_lcd("Value_on");
						if(PINC&(1<<Value))
						{
							setpos(6,1);
							str_lcd("OF");
						}
						else
						{
							setpos(6,1);
							str_lcd("ON");
						}
						ShowManual = 1;
					}
					break;
					case Cover_On:
					{
						clearlcd();
						setpos(0,0);
						str_lcd("Cover_on");
						if(PINB&(1<<Cover))
						{
							setpos(6,1);
							str_lcd("OF");
						}
						else
						{
							setpos(6,1);
							str_lcd("ON");
						}
						ShowManual = 1;
					}
					break;
				}
			}
		}
		
		if (button_state[Button_Menu]&ST_UNPRESSURE)
		{
			SetButtonState(Button_Menu,ST_LOCKED);
			ResetButtonState(Button_Menu,ST_UNPRESSURE);
			SetButtonState(Button_Menu,ST_PRESSURE);
			menu_state = MENU_STATE_IDLE;
			ShowCount = 1;
			ShowManual = 0;
			ResetButtonState(Button_Menu,ST_LOCKED);
		}
		if (button_state[Button_Up]&ST_UNPRESSURE)
		{
			SetButtonState(Button_Up,ST_LOCKED);
			ResetButtonState(Button_Up,ST_UNPRESSURE);
			SetButtonState(Button_Up,ST_PRESSURE);
			switch(Manual_Set)
			{
				case RinghtSeparator_On:
				{
					PORTC &= ~(1<<RinghtSeparator);
					ShowManual = 0;
				}
				break;
				case LeftSeparator_On:
				{
					PORTC &= ~(1<<LeftSeparator);
					ShowManual = 0;
				}
				break;
				case Lift_On:
				{
					PORTC &= ~(1<<Lift);
					ShowManual = 0;
				}
				break;
				case Value_On:
				{
					setpos(6,1);
					str_lcd("ON");
					PORTC &= ~(1<<Value);
					_delay_ms(400);
					PORTC |= 1<<Value;
					setpos(6,1);
					str_lcd("OF");
					ShowManual = 0;
				}
				break;
				case Cover_On:
				{
					PORTB &= ~(1<<Cover);
					ShowManual = 0;
				}
				break;
			}
			ResetButtonState(Button_Up,ST_LOCKED);
		}
		if (button_state[Button_Down]&ST_UNPRESSURE)
		{
			SetButtonState(Button_Down,ST_LOCKED);
			ResetButtonState(Button_Down,ST_UNPRESSURE);
			SetButtonState(Button_Down,ST_PRESSURE);
			switch(Manual_Set)
			{
				case RinghtSeparator_On:
				{
					PORTC |= 1<<RinghtSeparator;
					ShowManual = 0;
				}
				break;
				case LeftSeparator_On:
				{
					PORTC |= 1<<LeftSeparator;
					ShowManual = 0;
				}
				break;
				case Lift_On:
				{
					PORTC |= 1<<Lift;
					ShowManual = 0;
				}
				break;
				case Value_On:
				{
					PORTC |= 1<<Value;
					ShowManual = 0;
				}
				break;
				case Cover_On:
				{
					PORTB |= 1<<Cover;
					ShowManual = 0;
				}
				break;
			}
			ResetButtonState(Button_Down,ST_LOCKED);
		}
		if (button_state[Button_Right]&ST_UNPRESSURE)
		{
			SetButtonState(Button_Right,ST_LOCKED);
			ResetButtonState(Button_Right,ST_UNPRESSURE);
			SetButtonState(Button_Right,ST_PRESSURE);
			if (Manual_Set > 0)
			{
				Manual_Set--;
			}
			else
			{
				Manual_Set = 4;
			}
			ShowManual = 0;
			ResetButtonState(Button_Right,ST_LOCKED);
		}
		if (button_state[Button_Left]&ST_UNPRESSURE)
		{
			SetButtonState(Button_Left,ST_LOCKED);
			ResetButtonState(Button_Left,ST_UNPRESSURE);
			SetButtonState(Button_Left,ST_PRESSURE);
			if (Manual_Set < 4)
			{
				Manual_Set++;
			}
			else
			{
				Manual_Set = 0;
			}
			ShowManual = 0;
			ResetButtonState(Button_Left,ST_LOCKED);
		}
		break;
		
	}
	_delay_ms(50);
}
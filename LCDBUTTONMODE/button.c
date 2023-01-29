#include "button.h"
//-----------------------------------------
static unsigned char button_cnt[6]={0};
//-----------------------------------------
void Read_Button_State (unsigned char b);
//-----------------------------------------
void init_button_timer(void)
{
	TIMSK0 |= (1<<TOIE0);	//устанавливаем бит разрешения прерывания 0-ого счетчика по переполнению
	TCCR0B |= (0<<CS02)|(1<<CS01)|(1<<CS00); // устанавливаем предделитель 64
	//тем самым получаем - частота тактирования / предделитель / 256 = 976,5625 (около милисекунды)
	//делим на 256, так как таймер нулевой всегда считает от 0x00 до 0xFF и это не регулируется никак
}
//-----------------------------------------
ISR (TIMER0_OVF_vect)
{
	switch(menu_state)
	{
		case MENU_STATE_WAIT:
		{
			Read_Button_State(Button_Menu);
			Read_Button_State(Button_Start);
			Read_Button_State(Button_Up);
		}
		break;
		case MENU_STATE_SETING:
		{
			Read_Button_State(Button_Right);
			Read_Button_State(Button_Up);
			Read_Button_State(Button_Down);
			Read_Button_State(Button_Left);
			Read_Button_State(Button_Menu);
		}
		break;
		case MENU_STATE_STARTED:
		{
			Read_Button_State(Button_Start);
		}
		break;
		case MENU_STATE_IDLE:
		{
			
		}
		break;
		case MENU_STATE_STARTING:
		{
			
		}
		break;
		case MENU_STATE_MANUAL:
		{
			Read_Button_State(Button_Right);
			Read_Button_State(Button_Up);
			Read_Button_State(Button_Down);
			Read_Button_State(Button_Left);
			Read_Button_State(Button_Menu);
		}
		break;
	}
}
//-----------------------------------------
unsigned char Read_Button_Press (unsigned char b)
{
	switch (b)
	{
		case Button_Right:
		if(adc_value<25) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Up:
		if((adc_value>25)&&(adc_value<65)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Down:
		if((adc_value>65)&&(adc_value<115)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Left:
		if((adc_value>115)&&(adc_value<160)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Menu:
		if((adc_value>165)&&(adc_value<195)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
		case Button_Start:
		if((adc_value>200)&&(adc_value<220)) return ST_PRESSED;
		else return ST_UNPRESSED;
		break;
	}
	return ST_ERROR;
}
//-----------------------------------------
void Read_Button_State (unsigned char b)
{
	if ((button_state[b]&ST_LOCKED)!=0) return;
	if (Read_Button_Press(b)==ST_UNPRESSED)
	{
		if (button_cnt[b]>0)
		{
			button_cnt[b]--;
		}
		else
		{
			if((button_state[b]&ST_PRESSED)!=0)
			{
				button_state[b] |= ST_UNPRESSURE;
				button_state[b] &= ~ST_PRESSED;
				button_state[b] |= ST_UNPRESSED;
			}
		}
	}
	else
	{
		if (button_cnt[b]<6)
		{
			button_cnt[b]++;
		}
		else
		{
			if((button_state[b]&ST_UNPRESSED)!=0)
			{
				button_state[b] |= ST_PRESSURE;
				button_state[b] &= ~ST_UNPRESSED;
				button_state[b] |= ST_PRESSED;
			}
		}
	}
}
//-----------------------------------------
void ResetButtonState(unsigned char b, unsigned char st)
{
	button_state[b]&=~st;
}
//-----------------------------------------
void SetButtonState(unsigned char b, unsigned char st)
{
	button_state[b]|=st;
}
//-----------------------------------------
void Button_ini(void)
{
	unsigned char i;
	//сбросим статусы кнопок
	for (i=0;i<6;i++)
	{
		button_state[i]=ST_UNPRESSED;
	}
	//запустим таймер
	init_button_timer();
}

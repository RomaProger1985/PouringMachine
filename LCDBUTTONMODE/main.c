#include "main.h"
//----------------------------------------
uint16_t counter = 0;
uint16_t IsRunCounter = 0;
char bootleFul = 1;

void port_ini(void)
{
	DDRD=0b11111100;
	PORTD=0x00;
	DDRC = 0b11111110;
	PORTC = 0xFF;
	PORTC &= ~(1<<5);
	DDRB |= 1<<0;
	PORTB |= 1<<0;
}
//----------------------------------------

void timer_delay(uint16_t ms)
{
	counter = ms;
	TIMSK2 |= 1<<TOIE2;// запуск таймера по переполнению
}

ISR (TIMER2_OVF_vect)
{
	if (counter <= 0)
	{
		TIMSK2 &= ~(1<<TOIE2);// остановка таймера
		counter = 0;
	}
	else
	{
		counter -- ;
	}
}

ISR (TIMER1_OVF_vect)
{
	speed ++;
}

void ProgramStop ()
{
	PORTC |= 1<<1;
	PORTC |= 1<<2;
	PORTC |= 1<<3;
	PORTC |= 1<<4;
	PORTB |= 1<<0;
	ValueState = VALUE_STATE_Wait;
}

void ProgramStart ()
{
	if (bootleFul)
	{
		bootleFul = 0;
	}
	if(MENU_STATE_STARTED)
	{
		switch(ValueState)
		{
			
			case VALUE_STATE_Wait:
			{
				speed = 0;
				PORTC &= ~(1<<RinghtSeparator);
				if (PINC&0b00100000)
				{
					ValueState = VALUE_STATE_In_Bottle_Delay;
				}
			}
			break;
			case VALUE_STATE_In_Bottle_Delay:
			{
				if(!IsRunCounter)
				{
					timer_delay(In_Bottle_Delay);
					IsRunCounter = 1;
				}
				if (counter <=0)
				{
					PORTC &= ~(1<<LeftSeparator);
					ValueState = VALUE_STATE_lift_down_Delay;
					IsRunCounter = 0;
				}
			}
			break;
			case VALUE_STATE_lift_down_Delay:
			{
				if(!IsRunCounter)
				{
					timer_delay(lift_down_Delay);
					IsRunCounter =1;
				}
				if (counter <=0)
				{
					PORTC &= ~(1<<Lift);
					ValueState = VALUE_STATE_After_lift_down_Delay;
					IsRunCounter = 0;
					
				}
			}
			break;
			case VALUE_STATE_After_lift_down_Delay:
			{
				if(!IsRunCounter)
				{
					timer_delay(After_Lift_Down_Delay);
					IsRunCounter = 1;
				}
				if (counter <= 0)
				{
					PORTC &= ~(1<<Value);
					IsRunCounter = 0;
					ValueState = VALUE_STATE_Start_Value_Delau;
				}
			}
			break;
			case VALUE_STATE_Start_Value_Delau:
			{
				PORTC &= ~(1<<Value);
				if(!IsRunCounter)
				{
					timer_delay(300);
					IsRunCounter = 1;
				}
				if (counter <= 0)
				{
					PORTC |= 1<<Value;
					ValueState = VALUE_STATE_Value_Delau;
					Count_Value++;
					EEPROM_write_2bit(15,Count_Value);
					clearlcd();
					setpos(0,0);
					str_lcd("Started");
					setpos(0,1);
					str_lcd("Count ");
					setpos(6,1);
					str_lcd_uint16(Count_Value);
					ShowCount = 1;
					IsRunCounter = 0;
				}
			}
			break;
			case VALUE_STATE_Value_Delau:
			{
				if(!IsRunCounter)
				{
					timer_delay(Valye_Delay-300);
					IsRunCounter = 1;
				}
				if (counter <= 0)
				{
					PORTC |= 1<<Lift;
					ValueState = VALUE_STATE_After_lift_Up_Delay;
					IsRunCounter = 0;
				}
			}
			break;
			case VALUE_STATE_After_lift_Up_Delay:
			{
				if(!IsRunCounter)
				{
					timer_delay(After_LiftUp_Delay);
					IsRunCounter = 1;
				}
				if (counter <= 0)
				{
					PORTC |= 1<<RinghtSeparator;
					ValueState = VALUE_STATE_Bottle_Out_Delay;
					IsRunCounter = 0;
				}
			}
			break;
			case VALUE_STATE_Bottle_Out_Delay:
			{
				if(!IsRunCounter)
				{
					timer_delay(Bottle_Out_Delay);
					IsRunCounter = 1;
				}
				if (counter <= 0)
				{
					PORTC &= ~(1<<RinghtSeparator);
					ValueState = VALUE_STATE_Bottle_Speising;
					IsRunCounter = 0;
				}
			}
			break;
			case VALUE_STATE_Bottle_Speising:
			{
				if(!IsRunCounter)
				{
					timer_delay(Bottle_Spaising);
					IsRunCounter = 1;
				}
				if (counter <= 0)
				{
					PORTC |= 1<<LeftSeparator;
					ValueState = VALUE_STATE_Wait;
					IsRunCounter = 0;
				}
				if (!bootleFul)
				{
					bootleFul = 1;
					setpos(11,0);
					str_lcd("speed");
					setpos(11,1);
					str_lcd("    ");
					setpos(11,1);
					str_lcd_uint16(867052/speed);
				}
			}
			break;
		}
	}
}

void set_param ()
{
		Bottle_Spaising = EEPROM_read_2bit(1);
		In_Bottle_Delay = EEPROM_read_2bit(3);
		Valye_Delay = EEPROM_read_2bit(5);
		lift_down_Delay = EEPROM_read_2bit(7);
		Bottle_Out_Delay = EEPROM_read_2bit(9);
		After_LiftUp_Delay = EEPROM_read_2bit(11);
		After_Lift_Down_Delay = EEPROM_read_2bit(13);
		Count_Value = EEPROM_read_2bit(15);
}

void init_timer_02(void)
{
	TIMSK2 &= ~(1<<TOIE2);	//cбрасываем бит разрешения прерывания 2-ого счетчика по переполнению
	TCCR2B |= (1<<CS22)|(1<<CS20); // устанавливаем предделитель 64
	TCCR2B &= ~(1<<CS20);
}

void init_timer_01(void)
{
	TIMSK1 |= 1<<TOIE1;	// бит разрешения прерывания 1-ого счетчика по переполнению
	TCCR1B |= (1<<CS10);//|(1<<CS10); // устанавливаем предделитель 1024
}

int main(void)
{
	port_ini(); //инициализируем порты
	set_param();
	LCD_ini();  //инициализируем дисплей
	ADC_Init(); //инициализируем АЦП
	Button_ini(); //инициализируем состояние кнопок
	init_timer_02();
	init_timer_01();
	sei(); //включим глобальные прерывания
	menu_state = MENU_STATE_IDLE;
	
	ShowCount = 1;
	while(1)
	{
		MenuProcess();
	}
}

#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL

#define RinghtSeparator PINC1
#define Lift PINC2
#define Value PINC3
#define LeftSeparator PINC4
#define IsBottle PINC5
#define Cover PINB0

#include <avr/io.h>
#include <avr/interrupt.h>
#define __DELAY_BACKWARD_COMPATIBLE__//для вызова задержки с переменными
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "adc.h"
#include "button.h"
#include "menu.h"
#include "eeprom.h"

unsigned int adc_value,adc_counter,adc_tmp;

unsigned int Bottle_Spaising,Valye_Delay,In_Bottle_Delay,
lift_down_Delay,Bottle_Out_Delay,After_Lift_Down_Delay,After_LiftUp_Delay,Count_Value;
unsigned char ShowCount;
unsigned int speed;

typedef enum {
	VALUE_STATE_Wait = 0,//1 очикування
	VALUE_STATE_In_Bottle_Delay,//2 чекаєм на бутилку
	VALUE_STATE_lift_down_Delay,//3 опускаєм ліфт
	VALUE_STATE_After_lift_down_Delay,//4 пауза після того як ліфт опустився
	VALUE_STATE_Start_Value_Delau,//5 час наливання
	VALUE_STATE_Value_Delau,//6 час наливання
	VALUE_STATE_After_lift_Up_Delay,//7 пауза після піднятя ліфта
	VALUE_STATE_Bottle_Out_Delay,//8 чекаєм поки бутилка виїде
	VALUE_STATE_Bottle_Speising,//9 спейсінг запускаєм наступну бутилку
}VALUE_StateValue;

VALUE_StateValue ValueState ;

void ProgramStart ();
void ProgramStop ();

#endif /* MAIN_H_ */
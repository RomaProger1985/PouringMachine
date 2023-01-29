#ifndef BUTTON_H_
#define BUTTON_H_
//--------------------------------------
#include "main.h"
//--------------------------------------
unsigned char button_state[6];
//--------------------------------------
#define Button_Right 0x00
#define Button_Up 0x01
#define Button_Down 0x02
#define Button_Left 0x03
#define Button_Menu 0x04
#define Button_Start 0x05
//--------------------------------------
#define ST_PRESSED 0b00000001//кнопка нажата
#define ST_UNPRESSED 0b00000010//кнопка отжата
#define ST_ERROR 0b00000100 //не удалось считать статус
#define ST_PRESSURE 0b00001000 //процесс нажатия кнопки
#define ST_UNPRESSURE 0b00010000 //процесс отжатия кнопки
#define ST_LOCKED 0b00100000//кнопка недоступна
//--------------------------------------
void Button_ini(void);
void ResetButtonState(unsigned char b, unsigned char st);
void SetButtonState(unsigned char b, unsigned char st);
//--------------------------------------
#endif /* BUTTON_H_ */
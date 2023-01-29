#include "lcd.h"

//----------------------------------------
void sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1; //включаем линию Е
	_delay_us(50);
	PORTD&=0b00001111; //стираем информацию на входах DB4-DB7, остальное не трогаем
	PORTD|=c;
	e0; //выключаем линию Е
	_delay_us(50);
}
//----------------------------------------
void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) rs0;
	else         rs1;
	unsigned char hc=0;
	hc=c>>4;
	sendhalfbyte(hc); sendhalfbyte(c);
}
//----------------------------------------
void sendchar(unsigned char c)
{
	sendbyte(c,1);
}
//----------------------------------------
void setpos(unsigned char x, unsigned y)
{
	char adress;
	adress=(0x40*y+x)|0b10000000;
	sendbyte(adress, 0);
}
//----------------------------------------
void LCD_ini(void)
{
	_delay_ms(15); //Ждем 15 мс (стр 45)
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); //4бит-режим (DL=0) и 2 линии (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); //включаем изображение на дисплее (D=1), курсоры никакие не включаем (C=0, B=0)
	_delay_ms(1);
	sendbyte(0b00000110, 0); //курсор (хоть он у нас и невидимый) будет двигаться влево
	_delay_ms(1);
}
//----------------------------------------
void clearlcd()
{
	sendbyte(0b00000001, 0);
	_delay_us(1500);
}
//----------------------------------------
void str_lcd (char str1[])
{  
	wchar_t n;
	for(n=0;str1[n]!='\0';n++)
	sendchar(str1[n]);
}
//----------------------------------------
void str_lcd_int (uint16_t num)
{
	if (num >= 10000)
	{
		char str_char[5];
		str_char[0] = num/10000+0x30;
		str_char[1] = (num%10000)/1000+0x30;
		str_char[2] = '.';
		str_char[3] = (num%1000)/100+0x30;
		str_char[4] = '\0';
		str_lcd(str_char);
		//char str_char[6];
		//str_char[0] = num/10000+0x30;
		//str_char[1] = (num%10000)/1000+0x30;
		//str_char[2] = (num%1000)/100+0x30;
		//str_char[3] = (num%100)/10+0x30;
		//str_char[4] = num%10+0x30;
		//str_char[5] = '\0';
		//str_lcd(str_char);
	}
	//if (num >= 1000 && num < 10000)
	if (num < 10000)
	{
		char str_char[4];
		str_char[0] = num/1000+0x30;
		str_char[1] = '.';
		str_char[2] = (num%1000)/100+0x30;
		str_char[3] = '\0';
		str_lcd(str_char);
		//char str_char[5];		
		//str_char[0] = num/1000+0x30;
		//str_char[1] = (num%1000)/100+0x30;
		//str_char[2] = (num%100)/10+0x30;
		//str_char[3] = num%10+0x30;
		//str_char[4] = '\0';
		//str_lcd(str_char);
	}
	if (num >= 100 && num < 1000)
	{
		//char str_char[4];
		//str_char[0] = (num%1000)/100+0x30;
		//str_char[1] = (num%100)/10+0x30;
		//str_char[2] = num%10+0x30;
		//str_char[3] = '\0';
		//str_lcd(str_char);
	}
	if (num >= 10 && num < 100)
	{
		//char str_char[3];
		//str_char[0] = (num%100)/10+0x30;
		//str_char[1] = num%10+0x30;
		//str_char[2] = '\0';
		//str_lcd(str_char);
	}
	if (num < 10)
	{
		//char str_char[2];
		//str_char[0] = num%10+0x30;
		//str_char[1] = '\0';
		//str_lcd(str_char);
	}
}

void str_lcd_uint16 (uint16_t num)
{
	if (num >= 10000)
	{
		char str_char[6];
		str_char[0] = num/10000+0x30;
		str_char[1] = (num%10000)/1000+0x30;
		str_char[2] = (num%1000)/100+0x30;
		str_char[3] = (num%100)/10+0x30;
		str_char[4] = num%10+0x30;
		str_char[5] = '\0';
		str_lcd(str_char);
	}
	if (num >= 1000 && num < 10000)
	{
		char str_char[5];
		str_char[0] = num/1000+0x30;
		str_char[1] = (num%1000)/100+0x30;
		str_char[2] = (num%100)/10+0x30;
		str_char[3] = num%10+0x30;
		str_char[4] = '\0';
		str_lcd(str_char);
	}
	if (num >= 100 && num < 1000)
	{
		char str_char[4];
		str_char[0] = (num%1000)/100+0x30;
		str_char[1] = (num%100)/10+0x30;
		str_char[2] = num%10+0x30;
		str_char[3] = '\0';
		str_lcd(str_char);
	}
	if (num >= 10 && num < 100)
	{
		char str_char[3];
		str_char[0] = (num%100)/10+0x30;
		str_char[1] = num%10+0x30;
		str_char[2] = '\0';
		str_lcd(str_char);
	}
	if (num < 10)
	{
		char str_char[2];
		str_char[0] = num%10+0x30;
		str_char[1] = '\0';
		str_lcd(str_char);
	}
}
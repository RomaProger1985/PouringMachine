#include "adc.h"
//----------------------------------------
extern unsigned int adc_value,adc_counter,adc_tmp;
//----------------------------------------
char high_adc=0,low_adc=0;
//----------------------------------------
ISR(ADC_vect)
{
	low_adc = ADCL;
	high_adc = ADCH;//Старшая часть регистра ADC должна быть считана последней, иначе не продолжится преобразование
	if(adc_counter<20) {adc_tmp+=high_adc;adc_counter++;}
	else {adc_value=adc_tmp/20;adc_counter=0;adc_tmp=0;}
}
//----------------------------------------
void ADC_Init(void)
{
	ADCSRA |= (1<<ADEN) // Разрешение использования АЦП
	|(1<<ADSC)//Запуск преобразования
	|(1<<ADATE)//Непрерывный режим работы АЦП
	|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)//Делитель 128 = 128 кГц
	|(1<<ADIE);//Разрешение прерывания от АЦП
	ADMUX |= (1<<ADLAR)|(0<<REFS1)|(1<<REFS0); //Внутренний Источник ОН 5в, вход ADC0
}

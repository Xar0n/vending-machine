#define F_CPU 16000000
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "lcd/LCD.h"
#include "uart/UART.h"
#include "servo/Servo.h"
#include "function/Function.h"
#define buf_size 2

unsigned int target_money = 0; //Количество денег необходимое для покупки товара
unsigned int credits = 0; //Количество вложенных денег
unsigned int item_number = 0; //Номер выбранного товара
char buf[buf_size]; //Буфер для считывания номера товара выбранного пользователем
bool click_pay_1 = true; //Положен 1 рубль монетоприемник
bool click_pay_2 = true; //Положено 2 рубля монетоприемник
bool click_pay_5 = true; //Положено 5 рубль монетоприемник
bool click_pay_10 = true; //Положено 10 рублей монетоприемник
bool click_buy = true; //Нажата кнопка покупки товара
bool chose_item = true; //Выбран товар

void waitMoney();
void sensorFall();
void buyItem();

ISR (TIMER0_COMPA_vect){
	item_number = ats(buf);
	if(item_number == 1)
	{
		if(chose_item) {
			lcdPrintStart("Stoit 5 rub", 0);
			target_money = 5;
		}
		buyItem();
		chose_item = false;
		item_number = 0;
		credits = 0;
	} else if (item_number == 2)
	{
		if(chose_item) {
			lcdPrintStart("Stoit 2 rub", 0);
			target_money = 2;
		}
		buyItem();
		chose_item = false;
		item_number = 0;
		credits = 0;
	} else chose_item = true;	 
}


int main(void)
{  	
   SERVO_INIT();
   UART_init(103);
   lcdInit();
   lcdClear();
   lcdSetDisplay(LCD_DISPLAY_ON);
   lcdSetCursor(LCD_CURSOR_OFF);
   lcdPrintStart("Vvedite nomer", 0);
   lcdPrintStart("tovara (1-10)", 1);
   
   //НУЖНО НАПИСАТЬ ХРАНЕНИЕ КОЛИЧЕСТВО КОПЕЕК В EEPROM
   
   //Включение на вход ножек для кнопки купить и датчика падения
   DDRD |= (0<<PD2)|(0<<PD3);
   PORTD |= (1<<PD2)|(1<<PD3);
   
   //Включение на вход ножек для кнопок кидания копеек
   DDRC |= (0<<PC0)|(0<<PC1)|(0<<PC2)|(0<<PC3);
   PORTC |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);
   
   //Работа с прерываниями
   TCCR0A=(1<<WGM01);
   TCCR0B=(1<<CS00)|(1<<CS02);
   TCNT0=0x00;
   OCR0A=1;
   TIMSK0=(1<<OCIE0A);
   sei();
  while(1)
  {  
	if(item_number == 0) {
		UART_puts("Nomer tovara(1-10):");
		UART_getLine(buf, buf_size);
		item_number = ats(buf);
		chose_item = true;
	}
  }
}


//Процедура отвечающая за оплату товара
void waitMoney()
{
	while(credits < target_money) {
		//1 рубль
		if(!(PINC&0b00000001)) {
			if(click_pay_1) {
				credits = credits + 1;
				char* cred_disp = convertIntegerToChar(credits);
				lcdPrintStart(cred_disp, 1);
			}
			click_pay_1 = false;
		} else click_pay_1 = true;
		//2 рубля
		if(!(PINC&0b00000010)) {
			 
		}
		//5 рублей
		if(!(PINC&0b00000100)) {
			
		}
		//10 рублей
		if(!(PINC&0b00001000)) {
			
		}
	}
}

//Процедура отвечающая за датчик падения
void sensorFall()
{
	while(1) {
		if(!(PIND&0b00001000)) {
			break;
		}
	}
}

//Процедура отвечающая за покупку товара
void buyItem()
{
	//Нажата кнопка купить
	if(!(PIND&0b00000100)) {
		if(click_buy) {
			waitMoney();
			//Работа устройства сдвига товара
			if(item_number == 1) {
				OCR1B=316;
				Wait();
			} else if(item_number == 2) {
				
			} else if(item_number == 3) {
				
			} else if (item_number == 4) {
				
			} else if (item_number == 5) {
				
			}
			//РАБОТАЕТ ДАТЧИК ПАДЕНИЯ!!! ВСЕМ НА ПОЛ!
			sensorFall();
			//ВЫДАЧА СДАЧИ
			lcdPrintStart("Spasibo za", 0);
			lcdPrintStart("pokupku!", 0);
			click_buy = false;
		} else click_buy = true;
	}
}



/*//Сервопривод(устройство сдвига товара)
	OCR1A=97;   //0 degree
	OCR1B=97;   //0 degree
	Wait();
	OCR1A=316;  //90 degree
	OCR1B=316;  //90 degree
	Wait();
	OCR1A=425;  //135 degree
	OCR1B=425;  //135 degree
	Wait();
	OCR1A=535;  //180 degree
	OCR1B=535;  //180 degree
	Wait();*/
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

unsigned int target_money = 0; //Количество денег необходимое для покупки товара
unsigned int credits = 0; //Количество вложенных денег
unsigned int item_number = 0; //Номер выбранного товара
bool click_pay_1 = true; //Положена копейка в монетоприемник
bool click_buy = true; //Нажата кнопка покупки товара
bool chose_item = true; //Выбран товар

ISR (TIMER0_COMPA_vect){	 
	//Сервопривод(устройство сдвига товара)
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
	Wait();
}

//Процедура отвечающая за оплату товара
void waitMoney()
{
	while(credits < target_money) {
		//Положили копейку в монетоприемник, по аналогии сделать остальные копейки
		if(!(PINC&0b00000001)) {
			if(click_pay_1) {
				credits = credits + 1;
				char* cred_disp = convertIntegerToChar(credits);
				lcdPrintStart(cred_disp, 0);
			}
			click_pay_1 = false;
		} else click_pay_1 = true;
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
void buyItem(int servo) 
{
	//Нажата кнопка купить
	if(!(PIND&0b00000100)) {
		if(click_buy) {
			waitMoney();
			//Работа устройства сдвига товара
			if(servo == 1) {
				OCR1B=316;
				Wait();
			} else if(servo == 2) {
				
			} else if(servo == 3) {
				
			} else if (servo == 4) {
				
			} else if (servo == 5) {
				
			}
			//РАБОТАЕТ ДАТЧИК ПАДЕНИЯ!!! ВСЕМ НА ПОЛ!
			sensorFall();
			//ВЫДАЧА СДАЧИ
			lcdPrintStart("Good luck, boy!", 0);
			click_buy = false;
		} else click_buy = true;
	}
}

int main(void)
{
   uint8_t bufSize = 2;
   char buf[bufSize];	
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
   DDRC |= (0<<PC0);
   PORTC |= (1<<PC0);
   
   /*//Работа с прерываниями
   TCCR0A=(1<<WGM01);
   TCCR0B=(1<<CS00)|(1<<CS02);
   TCNT0=0x00;
   OCR0A=1;
   TIMSK0=(1<<OCIE0A);
   sei();*/
  
  while(1)
  {  
	if(item_number == 0) {
		UART_puts("Nomer tovara(1-10):");
		UART_getLine(buf, bufSize);
	}  
	item_number = ats(buf);
	if(item_number == 1)
	{
		if(chose_item) {
			lcdPrintStart("Stoit 5 rub", 0);
			target_money = 5;
		}
		buyItem(1);
		chose_item = false;
	} else if (item_number == 2)
	{
		lcdPrintStart("Stoit 2 rub", 0);
	} else chose_item = true;
  }
	
}



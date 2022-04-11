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

int main(void)
{
   input_number = 1;
   uint8_t bufSize = 2;
   char buf[bufSize];	
   SERVO_INIT();
   UART_init(103);
   lcdInit();
   lcdClear();
   lcdSetDisplay(LCD_DISPLAY_ON);
   lcdSetCursor(LCD_CURSOR_OFF);
   lcdGotoXY(0, 0);
   lcdPuts("Vvedite nomer");
   lcdGotoXY(1, 0);
   lcdPuts("tovara (1-10)");
   
   //Включение на вход ножек для кнопки купить и датчика падения
   DDRD |= (0<<PD2)|(0<<PD3);
   PORTD |= (1<<PD2)|(1<<PD3);
   
   /*//Работа с прерываниями
   TCCR0A=(1<<WGM01);
   TCCR0B=(1<<CS00)|(1<<CS02);
   TCNT0=0x00;
   OCR0A=1;
   TIMSK0=(1<<OCIE0A);
   sei();*/
  
  while(1)
  {  
	UART_puts("Nomer tovara(1-10):");
	UART_getLine(buf, bufSize);
	unsigned int item_number = atoi(buf);
	if(item_number == 1)
	{
		lcdClear();
		lcdGotoXY(0, 0);
		lcdPuts("Stoit 65 rub");
		item_number = 0;
		//Нажата кнопка купить
		if(!(PIND&0b00000100)) {
			//ОПЛАТА
			
			//Работа устройства сдвига товара
			
			//Сработал датчик падения
			if(!(PIND&0b00000100)) {
				//ВЫДАЧА СДАЧИ
			}
		}
	}  
}



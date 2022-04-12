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

unsigned int target_money = 0; //���������� ����� ����������� ��� ������� ������
unsigned int credits = 0; //���������� ��������� �����
unsigned int item_number = 0; //����� ���������� ������
bool click_pay_1 = true; //�������� ������� � ��������������
bool click_buy = true; //������ ������ ������� ������
bool chose_item = true; //������ �����

ISR (TIMER0_COMPA_vect){	 
	//�����������(���������� ������ ������)
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

//��������� ���������� �� ������ ������
void waitMoney()
{
	while(credits < target_money) {
		//�������� ������� � ��������������, �� �������� ������� ��������� �������
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

//��������� ���������� �� ������ �������
void sensorFall()
{
	while(1) {
		if(!(PIND&0b00001000)) {
			break;
		}
	}
}

//��������� ���������� �� ������� ������
void buyItem(int servo) 
{
	//������ ������ ������
	if(!(PIND&0b00000100)) {
		if(click_buy) {
			waitMoney();
			//������ ���������� ������ ������
			if(servo == 1) {
				OCR1B=316;
				Wait();
			} else if(servo == 2) {
				
			} else if(servo == 3) {
				
			} else if (servo == 4) {
				
			} else if (servo == 5) {
				
			}
			//�������� ������ �������!!! ���� �� ���!
			sensorFall();
			//������ �����
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
   
   //����� �������� �������� ���������� ������ � EEPROM
   
   //��������� �� ���� ����� ��� ������ ������ � ������� �������
   DDRD |= (0<<PD2)|(0<<PD3);
   PORTD |= (1<<PD2)|(1<<PD3);
   
   //��������� �� ���� ����� ��� ������ ������� ������
   DDRC |= (0<<PC0);
   PORTC |= (1<<PC0);
   
   /*//������ � ������������
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



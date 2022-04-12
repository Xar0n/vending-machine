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

unsigned int target_money = 0; //���������� ����� ����������� ��� ������� ������
unsigned int credits = 0; //���������� ��������� �����
unsigned int item_number = 0; //����� ���������� ������
char buf[buf_size]; //����� ��� ���������� ������ ������ ���������� �������������
bool click_pay_1 = true; //������� 1 ����� ��������������
bool click_pay_2 = true; //�������� 2 ����� ��������������
bool click_pay_5 = true; //�������� 5 ����� ��������������
bool click_pay_10 = true; //�������� 10 ������ ��������������
bool click_buy = true; //������ ������ ������� ������
bool chose_item = true; //������ �����

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
   
   //����� �������� �������� ���������� ������ � EEPROM
   
   //��������� �� ���� ����� ��� ������ ������ � ������� �������
   DDRD |= (0<<PD2)|(0<<PD3);
   PORTD |= (1<<PD2)|(1<<PD3);
   
   //��������� �� ���� ����� ��� ������ ������� ������
   DDRC |= (0<<PC0)|(0<<PC1)|(0<<PC2)|(0<<PC3);
   PORTC |= (1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3);
   
   //������ � ������������
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


//��������� ���������� �� ������ ������
void waitMoney()
{
	while(credits < target_money) {
		//1 �����
		if(!(PINC&0b00000001)) {
			if(click_pay_1) {
				credits = credits + 1;
				char* cred_disp = convertIntegerToChar(credits);
				lcdPrintStart(cred_disp, 1);
			}
			click_pay_1 = false;
		} else click_pay_1 = true;
		//2 �����
		if(!(PINC&0b00000010)) {
			 
		}
		//5 ������
		if(!(PINC&0b00000100)) {
			
		}
		//10 ������
		if(!(PINC&0b00001000)) {
			
		}
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
void buyItem()
{
	//������ ������ ������
	if(!(PIND&0b00000100)) {
		if(click_buy) {
			waitMoney();
			//������ ���������� ������ ������
			if(item_number == 1) {
				OCR1B=316;
				Wait();
			} else if(item_number == 2) {
				
			} else if(item_number == 3) {
				
			} else if (item_number == 4) {
				
			} else if (item_number == 5) {
				
			}
			//�������� ������ �������!!! ���� �� ���!
			sensorFall();
			//������ �����
			lcdPrintStart("Spasibo za", 0);
			lcdPrintStart("pokupku!", 0);
			click_buy = false;
		} else click_buy = true;
	}
}



/*//�����������(���������� ������ ������)
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
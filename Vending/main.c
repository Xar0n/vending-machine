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
   
   //��������� �� ���� ����� ��� ������ ������ � ������� �������
   DDRD |= (0<<PD2)|(0<<PD3);
   PORTD |= (1<<PD2)|(1<<PD3);
   
   /*//������ � ������������
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
		//������ ������ ������
		if(!(PIND&0b00000100)) {
			//������
			
			//������ ���������� ������ ������
			
			//�������� ������ �������
			if(!(PIND&0b00000100)) {
				//������ �����
			}
		}
	}  
}



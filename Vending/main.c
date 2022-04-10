#define F_CPU 16000000
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "LCD.h"
#include "UART.h"
#include "Servo.h"

int main(void)
{
   SERVO_INIT();
   UART_init(103);
   lcdInit();
   lcdClear();
   lcdSetDisplay(LCD_DISPLAY_ON);
   lcdSetCursor(LCD_CURSOR_OFF);
   char text[17];
   lcdGotoXY(0, 0);
   lcdPuts("Vvedite nomer");
   lcdGotoXY(1, 0);
   lcdPuts("tovara (1-10)");
  while(1)
  {  
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
}



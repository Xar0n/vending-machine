#define F_CPU 16000000
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

void checkPay()
{
	/*while(1) {
		if(!(PINC&0b00000001)) {
		if(click) {
			 credits = credits + 1;
			 char* cred_disp = convertIntegerToChar(credits);
			 UART_puts(cred_disp);
		}
		click = false;
	} else click = true;
	}*/
}

int ats(char *str)
{
	int result;
	int puiss;

	result = 0;
	puiss = 1;
	while (('-' == (*str)) || ((*str) == '+'))
	{
		if (*str == '-')
		puiss = puiss * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result = (result * 10) + ((*str) - '0');
		str++;
	}
	return (result * puiss);
}

char* convertIntegerToChar(int N)
{
	// Count digits in number N
	int m = N;
	int digit = 0;
	while (m) {
		
		// Increment number of digits
		digit++;
		
		// Truncate the last
		// digit from the number
		m /= 10;
	}
	
	// Declare char array for result
	char* arr;
	
	// Declare duplicate char array
	char arr1[digit];
	
	// Memory allocation of array
	arr = (char*)malloc(digit);
	
	// Separating integer into digits and
	// accommodate it to character array
	int index = 0;
	while (N) {
		
		// Separate last digit from
		// the number and add ASCII
		// value of character '0' is 48
		arr1[++index] = N % 10 + '0';
		
		// Truncate the last
		// digit from the number
		N /= 10;
	}
	
	// Reverse the array for result
	int i;
	for (i = 0; i < index; i++) {
		arr[i] = arr1[index - i];
	}
	
	// Char array truncate by null
	arr[i] = '\0';
	
	// Return char array
	return (char*)arr;
}
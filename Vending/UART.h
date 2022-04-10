#ifndef UART_H_
#define UART_H_
void UART_init(uint16_t ubrr);
void UART_puts(char* s);
unsigned char UART_getc(void);
void UART_putc(unsigned char data);
void UART_getLine(char* buf, uint8_t n);

#endif /* UART_H_ */
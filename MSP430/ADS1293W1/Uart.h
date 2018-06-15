
#ifndef __UART_H
#define __UART_H

char UartInit(long baud,char parity,char dataBits,char stopBits);
void UartWriteChar(char c);
void UartWriteint(uint8_t c);
void UartWriteStr(char *s);
char UartReadChar();
void UartWritearray(uint8_t *s);

#endif /* __UART_H */
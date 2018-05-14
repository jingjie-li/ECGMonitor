
#ifndef __UART_H
#define __UART_H

char UartInit(long baud,char parity,char dataBits,char stopBits);
void UartWriteChar(char c);
void UartWriteStr(char *s);
char UartReadChar();

#endif /* __UART_H */
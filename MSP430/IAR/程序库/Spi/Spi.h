
#ifndef __SPI_H
#define __SPI_H

char SpiMasterInit(long baud,char dataBits,char mode,char clkMode);
char SpiWriteData(char c);

#endif /* __SPI_H */
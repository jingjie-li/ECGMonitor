#ifndef MSP430_SPI_H
#define MSP430_SPI_H

#include <msp430x14x.h>

#define CS              P1OUT
#define CS_ENABLED      0xf0
#define CS_DISABLED     0xff
         
void TI_ADS1293_SPIWriteReg(uint8 addr, uint8 value);
uint8 TI_ADS1293_SPIReadReg(uint8 addr);
void TI_ADS1293_SPIAutoIncWriteReg(uint8 addr, uint8 *buffer, uint8 count);
void TI_ADS1293_SPIAutoIncReadReg(uint8 addr, uint8 *buffer, uint8 count);
void TI_ADS1293_SPIStreamReadReg(uint8 *buffer, uint8 count);
void TI_ADS1293_WriteRegSettings(void);
//***********************************************************************************
#endif                                                                         // MSP430_SPI_H

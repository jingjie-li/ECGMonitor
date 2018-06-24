#ifndef MSP430_SPI_H
#define MSP430_SPI_H

#include <msp430x14x.h>

#define CS2              P1OUT
#define CS2_ENABLED      0xfd
#define CS2_DISABLED     0xff
         
void TI_AFE4400_SPIWriteReg(uint8_t addr, uint8_t value);
uint8_t TI_AFE4400_SPIReadReg(uint8_t addr);
void TI_AFE4400_SPIAutoIncWriteReg(uint8_t addr, unsigned long value, uint8_t count);
unsigned long TI_AFE4400_SPIAutoIncReadReg(uint8_t addr, uint8_t count);
void TI_AFE4400_SPIStreamReadReg(uint8_t addr, uint8_t *buffer, uint8_t count);
void TI_AFE4400_WriteRegSettings(void);
//***********************************************************************************
#endif                                                                         // MSP430_SPI_H

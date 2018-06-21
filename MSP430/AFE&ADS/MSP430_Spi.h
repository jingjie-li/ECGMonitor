#ifndef MSP430_SPI_H
#define MSP430_SPI_H

#include <msp430x14x.h>

#define CS1              P1OUT
#define CS1_ENABLED      0xfe
#define CS1_DISABLED     0xff
         
void TI_ADS1293_SPIWriteReg(uint8_t addr, uint8_t value);
uint8_t TI_ADS1293_SPIReadReg(uint8_t addr);
void TI_ADS1293_SPIAutoIncWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count);
void TI_ADS1293_SPIAutoIncReadReg(uint8_t addr, uint8_t *buffer, uint8_t count);
void TI_ADS1293_SPIStreamReadReg(uint8_t *buffer, uint8_t count);
void TI_ADS1293_WriteRegSettings(void);
//***********************************************************************************
#endif                                                                         // MSP430_SPI_H

#ifndef __MSP430_SPI_H
#define __MSP430_SPI_H

#include <msp430x14x.h>

#define CS              P1OUT
#define CS_ENABLED      0xfe
#define CS_DISABLED     0xff
         
void TI_ADS1293_SPIWriteReg(uint8_t addr, uint8_t value);
uint8_t TI_ADS1293_SPIReadReg(uint8_t addr);
void TI_ADS1293_SPIAutoIncWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count);
void TI_ADS1293_SPIAutoIncReadReg(uint8_t addr, uint8_t *buffer, uint8_t count);
void TI_ADS1293_SPIStreamReadReg(uint8_t *buffer, uint8_t count);
void TI_ADS1293_WriteRegSettings(void);
void SET3(void);
void SET5(void);
//***********************************************************************************
#endif                                                                         // MSP430_SPI_H

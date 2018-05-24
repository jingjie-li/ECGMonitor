//------------------------------------------------------------------------------
//  Description:  Header file for TI_MSP430_spi_*.c
//
//  MSP430/ADS1293 Interface Code Library v1.1
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   February 2012
//   Built with CCE Version: 4.2 and IAR Embedded Workbench Version:  5.3x
//------------------------------------------------------------------------------
// Change Log:
//------------------------------------------------------------------------------
// Version:  1.00
// Comments: Initial Release Version
//------------------------------------------------------------------------------

#ifndef HEADER_FILE_TI_MSP430_SPI_H
#define HEADER_FILE_TI_MSP430_SPI_H

void TI_ADS1293_SPISetup(void);
void TI_ADS1293_SPIWriteReg(uint8_t, uint8_t);
uint8_t TI_ADS1293_SPIReadReg(uint8_t);
void TI_ADS1293_SPIAutoIncWriteReg(uint8_t, uint8_t *, uint8_t);
void TI_ADS1293_SPIAutoIncReadReg(uint8_t, uint8_t *, uint8_t);
void TI_ADS1293_SPIStreamReadReg(uint8_t *, uint8_t);

#endif                                                                         // HEADER_FILE_TI_MSP430_SPI_H

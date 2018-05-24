//******************************************************************************
//  Description:  This file contains functions that allow the MSP430 device to
//  access the SPI interface of the ADS1293.  There are multiple
//  instances of each function; the one to be compiled is selected by the
//  system variable TI_ADS1293_SER_INTF, defined in "TI_ADS1293_hardware_board.h".
//
//  MSP430/ADS1293 Interface Code Library v1.0
// 
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   February 2012
//   Built with CCE Version: 4.2 and IAR Embedded Workbench Version:  5.3x
//******************************************************************************
// Change Log:
//******************************************************************************
// Version:  1.00
// Comments: Initial Release Version
//******************************************************************************
/*  Copyright 2011-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user who
  downloaded the software, his/her employer (which must be your employer) and
  Texas Instruments Incorporated (the "License"). You may not use this Software
  unless you agree to abide by the terms of the License. The License limits your
  use, and you acknowledge, that the Software may not be modified, copied or
  distributed unless embedded on a Texas Instruments microcontroller which is 
  integrated into your product. Other than for the foregoing purpose, you may 
  not use, reproduce, copy, prepare derivative works of, modify, distribute, 
  perform, display or sell this Software and/or its documentation for any 
  purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL TEXAS
  INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL
  EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT
  LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL
  DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
  TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT
  LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
*******************************************************************************/

#include <stdint.h>
#include "TI_ADS1293.h"
#include "TI_MSP430.h"
#include "TI_MSP430_hardware_board.h"
#include "TI_MSP430_spi.h"


//******************************************************************************
// Support for 449x USART1
//******************************************************************************
#if TI_ADS1293_SER_INTF == TI_ADS1293_SER_INTF_USART1
//------------------------------------------------------------------------------
//  void TI_ADS1293_SPISetup(void)
//
//  DESCRIPTION:
//  Configures the assigned interface to function as a SPI port and
//  initializes it.
//------------------------------------------------------------------------------
void TI_ADS1293_SPISetup(void)
{
  TI_ADS1293_CSn_PxOUT |= TI_ADS1293_CSn_PIN;
  TI_ADS1293_CSn_PxDIR |= TI_ADS1293_CSn_PIN;                                  // /CS disable

  ME1 |= USPIE1;                                                               // Enable USART1 SPI mode
  UCTL1 = SWRST;                                                               // Disable USART state machine
  UCTL1 |= CHAR + SYNC + MM;                                                   // 8-bit SPI Master **SWRST**
  UTCTL1 |= CKPL + SSEL1 + SSEL0 + STC;                                        // SMCLK, 3-pin mode
  UBR01 = 0x02;                                                                // UCLK/2
  UBR11 = 0x00;                                                                // 0
  UMCTL1 = 0x00;                                                               // No modulation
  TI_ADS1293_SPI_USART1_PxSEL |= TI_ADS1293_SPI_USART1_SIMO
                          | TI_ADS1293_SPI_USART1_SOMI
                          | TI_ADS1293_SPI_USART1_UCLK;
                                                                               // SPI option select
  TI_ADS1293_SPI_USART1_PxDIR |= TI_ADS1293_SPI_USART1_SIMO 
                                  + TI_ADS1293_SPI_USART1_UCLK;                // SPI TX out direction

}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIWriteReg(uint8_t addr, uint8_t value)
//
//  DESCRIPTION:
//  Writes "value" to a single configuration register at address "addr". 
//------------------------------------------------------------------------------
void TI_ADS1293_SPIWriteReg(uint8_t addr, uint8_t value)
{
  uint8_t inst;
 

  TI_ADS1293_CSn_PxOUT &= ~TI_ADS1293_CSn_PIN;                                 // /CS enable 
  
  inst = ADS1293_WRITE_BIT & addr;                                             // register address
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = inst;                                                              // Send address
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 
 
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = value;                                                             // Send value
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 
 
  TI_ADS1293_CSn_PxOUT |= TI_ADS1293_CSn_PIN;                                  // /CS disable
  
}

//------------------------------------------------------------------------------
//  uint8_t TI_ADS1293_SPIReadReg(uint8_t addr)
//
//  DESCRIPTION:
//  Reads a single configuration register at address "addr" and returns the
//  value read. 
//------------------------------------------------------------------------------
uint8_t TI_ADS1293_SPIReadReg(uint8_t addr)
{
  uint8_t x, inst;
  
  TI_ADS1293_CSn_PxOUT &= ~TI_ADS1293_CSn_PIN;                                 // /CS enable
 
  inst = ADS1293_READ_BIT | addr;                                              // register address
  
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = inst;                                                              // Send addr
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 
  
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = 0;                                                                 // Send dummy value for read
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 
  
  x = U1RXBUF;                                                                 // Read data
  
  TI_ADS1293_CSn_PxOUT |= TI_ADS1293_CSn_PIN;                                  // /CS disable

  return x;
}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIAutoIncWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially (within the ADS1293 and MSP430
//  respectively) until "count" writes have been performed. 
//------------------------------------------------------------------------------
void TI_ADS1293_SPIAutoIncWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
  uint8_t inst, i;

  TI_ADS1293_CSn_PxOUT &= ~TI_ADS1293_CSn_PIN;                                 // /CS enable
  
  inst = ADS1293_WRITE_BIT & addr;                                             // register address
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = inst;                                                              // Send address
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 
  
  for(i= 0; i < count; i++)
  {
    while (!(IFG2 & UTXIFG1));                                                 // Wait for TXBUF ready
    IFG2 &= ~URXIFG1;                                                          // clear flag
    U1TXBUF = *(buffer+i);                                                     // Send data
    while (!(IFG2 & URXIFG1));                                                 // wait for tx to finish 
  }
  
  TI_ADS1293_CSn_PxOUT |= TI_ADS1293_CSn_PIN;                                  // /CS disable
  
}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIAutoIncReadReg(uint8_t addr, unit8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Reads multiple configuration registers, the first register being at address
//  "addr".  Values read are deposited sequentially starting at address
//  "buffer", until "count" registers have been read.
//------------------------------------------------------------------------------
void TI_ADS1293_SPIAutoIncReadReg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
  uint8_t i, inst;
  
  TI_ADS1293_CSn_PxOUT &= ~TI_ADS1293_CSn_PIN;                                 // /CS enable
 
  inst = ADS1293_READ_BIT | addr;                                              // register address
  
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = inst;                                                              // Send address
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 
  
  for(i=0; i < count; i++)
  {
    while (!(IFG2 & UTXIFG1));                                                 // Wait for TXBUF ready
    IFG2 &= ~URXIFG1;                                                          // clear flag
    U1TXBUF = 0;                                                               // Send dummy value
    while (!(IFG2 & URXIFG1));                                                 // wait for tx to finish 
    *(buffer+i) = U1RXBUF;                                                     // Read data
  }
  TI_ADS1293_CSn_PxOUT |= TI_ADS1293_CSn_PIN;                                  // /CS disable

}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIStreamReadReg(uint8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Special read function for reading status, pace and ecg data registers of selected
//  channels. Channels to be read must be selected in CH_CNFG before calling this function. 
//  Data Loop Register read is extended "count+1" times where "count" is number of source bytes 
//  enabled in CH_CNFG. Data read are deposited sequentially starting at address "buffer" 
//  until "count" bytes have been read.
//------------------------------------------------------------------------------
void TI_ADS1293_SPIStreamReadReg(uint8_t *buffer, uint8_t count)
{
  uint8_t i, inst;
  
  TI_ADS1293_CSn_PxOUT &= ~TI_ADS1293_CSn_PIN;                                 // /CS enable
 
  inst = ADS1293_READ_BIT | TI_ADS1293_DATA_LOOP_REG;                          // read from data loop register
  
  while (!(IFG2 & UTXIFG1));                                                   // Wait for TXBUF ready
  IFG2 &= ~URXIFG1;                                                            // clear flag
  U1TXBUF = inst;                                                              // Send address
  while (!(IFG2 & URXIFG1));                                                   // wait for tx to finish 

  for(i=0; i<count; i++)
  {
    while (!(IFG2 & UTXIFG1));                                                 // Wait for TXBUF ready
    IFG2 &= ~URXIFG1;                                                          // clear flag
    U1TXBUF = 0;                                                               // Send dummy value
    while (!(IFG2 & URXIFG1));                                                 // wait for tx to finish 
    *(buffer+i) = U1RXBUF;                                                     // Read register data    
  }
    
  TI_ADS1293_CSn_PxOUT |= TI_ADS1293_CSn_PIN;                                  // /CS disable
  
    
}
//------------------------------------------------------------------------------
#endif


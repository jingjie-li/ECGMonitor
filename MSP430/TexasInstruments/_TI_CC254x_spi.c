//******************************************************************************
//  Description:  This file contains functions that allow the CC254x device to
//  access the SPI interface of the ADS1293.  There are multiple
//  instances of each function; the one to be compiled is selected by the
//  system variable TI_ADS1293_SER_INTF, defined in "TI_ADS1293_hardware_board.h".
//
//  CC254x/ADS1293 Interface Code Library v1.0
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

#include "TI_ADS1293.h"
#include "TI_CC254x.h"
#include "TI_CC254x_hardware_board.h"
#include "TI_CC254x_spi.h"
#include "TI_ADS1293_register_settings.h"

//***********************************************************************************
// Function prototypes
void spiWriteByte(uint8 write);
void spiReadByte(uint8 *read, uint8 write);
//------------------------------------------------------------------------------
//  void TI_ADS1293_SPISetup(void)
//
//  DESCRIPTION:
//  Configures the assigned interface to function as a SPI port and
//  initializes it.
//------------------------------------------------------------------------------
void TI_ADS1293_SPISetup(void)
{
    //*** Setup USART 0 SPI at alternate location 2 ***

    // USART 0 at alternate location 2
    PERCFG |= 0x01;
    // Peripheral function on SCK, MISO and MOSI (P1_3-5)
    P1SEL |= 0x38;
    // Configure CS (P1_2) as output
    P1DIR |= 0x04;
    CS = CS_DISABLED;

    //*** Setup the SPI interface ***
    // SPI master mode
    U0CSR = 0x00;
    // Negative clock polarity, Phase: data out on CPOL -> CPOL-inv
    //                                 data in on CPOL-inv -> CPOL
    // MSB first
    U0GCR = 0x20;
    // SCK frequency = 480.5kHz (max 500kHz)
    // U0GCR |= 0x0D;
    // U0BAUD = 0xEC;
    // SCK frequency = 4MHz (F/8)assuming 32MHz crystal
    U0GCR |= 0x11;
    U0BAUD = 0x0;    

}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIWriteReg(uint8_t addr, uint8_t value)
//
//  DESCRIPTION:
//  Writes "value" to a single configuration register at address "addr". 
//------------------------------------------------------------------------------
void TI_ADS1293_SPIWriteReg(uint8 addr, uint8 value)
{
  uint8 inst;
 

  CS = CS_ENABLED;                                                             // /CS enable 
  
  inst = ADS1293_WRITE_BIT & addr;                                             // register address
  spiWriteByte(inst);                                                          // Send register address
  
  spiWriteByte(value);                                                         // Send data value  

  CS = CS_DISABLED;                                                            // /CS disable      
  
}

//------------------------------------------------------------------------------
//  uint8_t TI_ADS1293_SPIReadReg(uint8_t addr)
//
//  DESCRIPTION:
//  Reads a single configuration register at address "addr" and returns the
//  value read. 
//------------------------------------------------------------------------------
uint8 TI_ADS1293_SPIReadReg(uint8 addr)
{
  uint8 pVal, inst;
  
  CS = CS_ENABLED;                                                             // /CS enable
 
  inst = ADS1293_READ_BIT | addr;                                              // register address
  
//  WAIT_1_3US(2);                                                               // Wait 
  spiWriteByte(inst);                                                          // Send lower register address  
  
  spiReadByte(&pVal, 0xFF);                                                     // Read data
  
  CS = CS_DISABLED;                                                            // /CS disable

  return pVal;    
          
}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIAutoIncWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially (within the ADS1293 and CC254x
//  respectively) until "count" writes have been performed. 
//------------------------------------------------------------------------------
void TI_ADS1293_SPIAutoIncWriteReg(uint8 addr, uint8 *buffer, uint8 count)
{
  uint8 inst, i;

  CS = CS_ENABLED;                                                             // /CS enable
  
  inst = ADS1293_WRITE_BIT & addr;                                             // register address
  spiWriteByte(inst);                                                          // Send register address
   
  for(i= 0; i < count; i++)
    spiWriteByte(*(buffer+i));                                                 // Send data value  

  CS = CS_DISABLED;                                                            // /CS disable
  
}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIAutoIncReadReg(uint8_t addr, unit8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Reads multiple configuration registers, the first register being at address
//  "addr".  Values read are deposited sequentially starting at address
//  "buffer", until "count" registers have been read.
//------------------------------------------------------------------------------
void TI_ADS1293_SPIAutoIncReadReg(uint8 addr, uint8 *buffer, uint8 count)
{
  uint8 i, inst;
  
  CS = CS_ENABLED;                                                             // /CS enable
 
  inst = ADS1293_READ_BIT | addr;                                              // register address
  
  spiWriteByte(inst);                                                          // Send register address  
  
  for(i=0; i < count; i++)
    spiReadByte((buffer+i), 0xFF);                                             // Read data 
  
  CS = CS_DISABLED;                                                            // /CS disable

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
void TI_ADS1293_SPIStreamReadReg(uint8 *buffer, uint8 count)
{
  uint8 i, inst;
//  static uint32 tst_count = 0;
//  static uint8 toggle = 0;
  
  CS = CS_ENABLED;                                                             // /CS enable
 
  inst = ADS1293_READ_BIT | TI_ADS1293_DATA_LOOP_REG;                          // read from data loop register
  
  spiWriteByte(inst);                                                          // Send register address
  
  for(i=0; i < count; i++)
    spiReadByte((buffer+i), 0xFF);                                             // Read data
/*  
  *(buffer) = (tst_count & 0xFF0000) >>16;
  *(buffer+1) = (tst_count & 0x00FF00) >>8;
  *(buffer+2) = (tst_count & 0xFF);
 
  for(i=0; i < count-3;i++)
    *(buffer+3+i) = i;
  tst_count=tst_count+10000;
 
  if (toggle)
  {
    tst_count++;
    toggle =  0;
  } else
    toggle = 1;
*/ 
  CS = CS_DISABLED;                                                            // /CS disable
      
}
//------------------------------------------------------------------------------
/** \brief	Write one byte to SPI interface
*
* Write one byte to SPI interface
*
* \param[in]       write
*     Value to write
*/
//------------------------------------------------------------------------------
void spiWriteByte(uint8 write)
{
        U0CSR &= ~0x02;                 // Clear TX_BYTE
        U0DBUF = write;
        while (!(U0CSR & 0x02));        // Wait for TX_BYTE to be set
}
//------------------------------------------------------------------------------
/** \brief	Read one byte from SPI interface
*
* Read one byte from SPI interface
*
* \param[in]       read
*     Read out value
* \param[in]       write
*     Value to write
*/
//------------------------------------------------------------------------------
void spiReadByte(uint8 *read, uint8 write)
{
        U0CSR &= ~0x02;                 // Clear TX_BYTE
        U0DBUF = write;
        while (!(U0CSR & 0x02));        // Wait for TX_BYTE to be set
        *read = U0DBUF;
}
//------------------------------------------------------------------------------
//******************************************************************************
//  void TI_ADS1293_WriteRegSettings(void)
//
//  DESCRIPTION:
//  ADS1293 registers are configured to the values defined ADS1293_register_settings.h
//  These register settings can easily be obtained from the "Register configuration file"  
//  saved from Sensor AFE Software
//
//  ARGUMENTS:
//       
//******************************************************************************

void TI_ADS1293_WriteRegSettings(void)
{

  TI_ADS1293_SPIWriteReg(TI_ADS1293_CONFIG_REG, 
                          TI_ADS1293_CONFIG_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_FLEX_CH1_CN_REG, 
                          TI_ADS1293_FLEX_CH1_CN_REG_VALUE);    
  TI_ADS1293_SPIWriteReg(TI_ADS1293_FLEX_CH2_CN_REG, 
                          TI_ADS1293_FLEX_CH2_CN_REG_VALUE);  
  TI_ADS1293_SPIWriteReg(TI_ADS1293_FLEX_CH3_CN_REG, 
                          TI_ADS1293_FLEX_CH3_CN_REG_VALUE);   
  TI_ADS1293_SPIWriteReg(TI_ADS1293_FLEX_PACE_CN_REG, 
                          TI_ADS1293_FLEX_PACE_CN_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_FLEX_VBAT_CN_REG, 
                          TI_ADS1293_FLEX_VBAT_CN_REG_VALUE);             
  TI_ADS1293_SPIWriteReg(TI_ADS1293_LOD_CN_REG, 
                          TI_ADS1293_LOD_CN_REG_VALUE);              
  TI_ADS1293_SPIWriteReg(TI_ADS1293_LOD_EN_REG, 
                          TI_ADS1293_LOD_EN_REG_VALUE);                
  TI_ADS1293_SPIWriteReg(TI_ADS1293_LOD_CURRENT_REG, 
                          TI_ADS1293_LOD_CURRENT_REG_VALUE);            
  TI_ADS1293_SPIWriteReg(TI_ADS1293_LOD_AC_CN_REG, 
                          TI_ADS1293_LOD_AC_CN_REG_VALUE);              
  TI_ADS1293_SPIWriteReg(TI_ADS1293_CMDET_EN_REG, 
                          TI_ADS1293_CMDET_EN_REG_VALUE);             
  TI_ADS1293_SPIWriteReg(TI_ADS1293_CMDET_CN_REG, 
                          TI_ADS1293_CMDET_CN_REG_VALUE);       
  TI_ADS1293_SPIWriteReg(TI_ADS1293_RLD_CN_REG, 
                          TI_ADS1293_RLD_CN_REG_VALUE);          
  TI_ADS1293_SPIWriteReg(TI_ADS1293_WILSON_EN1_REG, 
                          TI_ADS1293_WILSON_EN1_REG_VALUE);              
  TI_ADS1293_SPIWriteReg(TI_ADS1293_WILSON_EN2_REG, 
                          TI_ADS1293_WILSON_EN2_REG_VALUE);               
  TI_ADS1293_SPIWriteReg(TI_ADS1293_WILSON_EN3_REG, 
                          TI_ADS1293_WILSON_EN3_REG_VALUE);                
  TI_ADS1293_SPIWriteReg(TI_ADS1293_WILSON_CN_REG, 
                          TI_ADS1293_WILSON_CN_REG_VALUE);            
 
  TI_ADS1293_SPIWriteReg(TI_ADS1293_REF_CN_REG, 
                          TI_ADS1293_REF_CN_REG_VALUE);             
  
  TI_ADS1293_SPIWriteReg(TI_ADS1293_OSC_CN_REG, 
                          TI_ADS1293_OSC_CN_REG_VALUE);            
  TI_ADS1293_SPIWriteReg(TI_ADS1293_AFE_RES_REG, 
                          TI_ADS1293_AFE_RES_REG_VALUE);            
  TI_ADS1293_SPIWriteReg(TI_ADS1293_AFE_SHDN_CN_REG, 
                          TI_ADS1293_AFE_SHDN_CN_REG_VALUE);            
  TI_ADS1293_SPIWriteReg(TI_ADS1293_AFE_FAULT_CN_REG, 
                          TI_ADS1293_AFE_FAULT_CN_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_AFE_DITHER_EN_REG, 
                          TI_ADS1293_AFE_DITHER_EN_REG_VALUE);          
  TI_ADS1293_SPIWriteReg(TI_ADS1293_AFE_PACE_CN_REG, 
                          TI_ADS1293_AFE_PACE_CN_REG_VALUE);     
  
  TI_ADS1293_SPIWriteReg(TI_ADS1293_R2_RATE_REG, 
                          TI_ADS1293_R2_RATE_REG_VALUE);         
  TI_ADS1293_SPIWriteReg(TI_ADS1293_R3_RATE1_REG, 
                          TI_ADS1293_R3_RATE1_REG_VALUE);         
  TI_ADS1293_SPIWriteReg(TI_ADS1293_R3_RATE2_REG, 
                          TI_ADS1293_R3_RATE2_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_R3_RATE3_REG, 
                          TI_ADS1293_R3_RATE3_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_P_DRATE_REG, 
                          TI_ADS1293_P_DRATE_REG_VALUE);            
  TI_ADS1293_SPIWriteReg(TI_ADS1293_DIS_EFILTER_REG, 
                          TI_ADS1293_DIS_EFILTER_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_DRDYB_SRC_REG, 
                          TI_ADS1293_DRDYB_SRC_REG_VALUE);             
  TI_ADS1293_SPIWriteReg(TI_ADS1293_SYNCOUTB_SRC_REG, 
                          TI_ADS1293_SYNCOUTB_SRC_REG_VALUE);           
  TI_ADS1293_SPIWriteReg(TI_ADS1293_MASK_DRDYB_REG, 
                          TI_ADS1293_MASK_DRDYB_REG_VALUE);             
  TI_ADS1293_SPIWriteReg(TI_ADS1293_MASK_ERR_REG, 
                          TI_ADS1293_MASK_ERR_REG_VALUE);              
  TI_ADS1293_SPIWriteReg(TI_ADS1293_ALARM_FILTER_REG, 
                          TI_ADS1293_ALARM_FILTER_REG_VALUE);            
  TI_ADS1293_SPIWriteReg(TI_ADS1293_CH_CNFG_REG, 
                          TI_ADS1293_CH_CNFG_REG_VALUE);          
  
}
//******************************************************************************



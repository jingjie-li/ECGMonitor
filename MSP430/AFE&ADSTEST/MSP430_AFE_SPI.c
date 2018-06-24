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

*******************************************************************************/
#include <stdint.h>
#include "Spi.h"
#include "MSP430_AFE_SPI.h"
#include "TI_AFE4400.h" 
#include "TI_AFE4400_setting.h"
//***********************************************************************************

#define TI_ADS1293_CONFIG_REG                         (0x00) 
                 /* Main Configuration */
//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIWriteReg(uint8_t_t addr, uint8_t_t value)
//
//  DESCRIPTION:
//  Writes "value" to a single configuration register at address "addr". 
//------------------------------------------------------------------------------
void TI_AFE4400_SPIWriteReg(uint8_t addr, uint8_t value)
{
  uint8_t inst;
 

  CS2 = CS2_ENABLED;                                                             // /CS enable 
  
  inst = AFE4400_WRITE_BIT & addr;                                             // register address
  SpiWriteData(inst);                                                          // Send register address
  
  SpiWriteData(value);                                                         // Send data value  

  CS2 = CS2_DISABLED;                                                            // /CS disable      
  
}

//------------------------------------------------------------------------------
//  uint8_t_t TI_ADS1293_SPIReadReg(uint8_t_t addr)
//
//  DESCRIPTION:
//  Reads a single configuration register at address "addr" and returns the
//  value read. 
//------------------------------------------------------------------------------
uint8_t TI_AFE4400_SPIReadReg(uint8_t addr)
{
  uint8_t pVal, inst;
  
  CS2 = CS2_ENABLED;                                                             // /CS enable
 
  inst = addr;                                              // register address
  
//  WAIT_1_3US(2);                                                               // Wait 
  SpiWriteData(inst);                                                          // Send lower register address  
  
  pVal = SpiWriteData(0xFF);                                                     // Read data
  
  CS2 = CS2_DISABLED;                                                            // /CS disable

  return pVal;    
          
}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIAutoIncWriteReg(uint8_t_t addr, uint8_t_t *buffer, uint8_t_t count)
//
//  DESCRIPTION:
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially (within the ADS1293 and CC254x
//  respectively) until "count" writes have been performed. 
//------------------------------------------------------------------------------
void TI_AFE4400_SPIAutoIncWriteReg(uint8_t addr, unsigned long value, uint8_t count)
{
  uint8_t inst, i;
  unsigned long a;

  CS2 = CS2_ENABLED;                                                             // /CS enable
  
  inst = AFE4400_WRITE_BIT & addr;                                             // register address

  uint8_t write_buf[3];
  a = value & 0xFF;
  write_buf[2] = (unsigned int) a;
  a = (value>>8) & 0xFF;
  write_buf[1] = (unsigned int) a;
  a = (value>>16) & 0xFF;
  write_buf[0] = (unsigned int) a;
  SpiWriteData(inst);                                                          // Send register address
  
  for(i= 0; i < count; i++)
  {
    SpiWriteData(write_buf[i]);
  }// Send data value  

  CS2 = CS2_DISABLED;                                                            // /CS disable
  
}

//------------------------------------------------------------------------------
//  void TI_ADS1293_SPIAutoIncReadReg(uint8_t_t addr, unit8_t *buffer, uint8_t_t count)
//
//  DESCRIPTION:
//  Reads multiple configuration registers, the first register being at address
//  "addr".  Values read are deposited sequentially starting at address
//  "buffer", until "count" registers have been read.
//------------------------------------------------------------------------------
unsigned long TI_AFE4400_SPIAutoIncReadReg(uint8_t addr, uint8_t count)
{
  unsigned long value = 0;
  uint8_t i, inst;
  uint8_t write_buf[3];
  
  CS2 = CS2_ENABLED;                                                             // /CS enable
 
  inst = addr;                                              // register address
  
  SpiWriteData(inst);                                                          // Send register address  
  
  for(i=0; i < count; i++)
  {
    write_buf[i] = SpiWriteData(0xFF);                                             // Read data 
  }
  value = value | write_buf[0];
  value = value<<8;
  value = value | write_buf[1];
  value = value<<8;
  value = value | write_buf[2];
  
  CS2 = CS2_DISABLED;                                                            // /CS disable
  
  return value;

}


//  void TI_ADS1293_SPIStreamReadReg(uint8_t_t *buffer, uint8_t_t count)
//
//  DESCRIPTION:
//  Special read function for reading status, pace and ecg data registers of selected
//  channels. Channels to be read must be selected in CH_CNFG before calling this function. 
//  Data Loop Register read is extended "count+1" times where "count" is number of source bytes 
//  enabled in CH_CNFG. Data read are deposited sequentially starting at address "buffer" 
//  until "count" bytes have been read.
//------------------------------------------------------------------------------
void TI_AFE4400_SPIStreamReadReg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
  uint8_t i, inst;
//  static uint32 tst_count = 0;
//  static uint8_t toggle = 0;
  
  CS2 = CS2_ENABLED;                                                             // /CS enable
 
  inst = AFE4400_READ_BIT | addr;                          // read from data loop register
  
  SpiWriteData(inst);                                                          // Send register address
  
  for(i=0; i < count; i++)
    *(buffer+i) = SpiWriteData(0xFF);                                           // Read data

  CS2 = CS2_DISABLED;                                                            // /CS disable
      
}


//******************************************************************************
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

void TI_AFE4400_WriteRegSettings(void)
{

  TI_AFE4400_SPIAutoIncWriteReg(LED2STC, 
                          TI_AFE4400_LED2STC_REG_VALUE, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(LED2ENDC, 
                          TI_AFE4400_LED2ENDC_REG_VALUE, 3);    
  TI_AFE4400_SPIAutoIncWriteReg(LED2LEDSTC, 
                          TI_AFE4400_LED2LEDSTC_REG_VALUE, 3);  
  TI_AFE4400_SPIAutoIncWriteReg(LED2LEDENDC, 
                          TI_AFE4400_LED2LEDENDC_REG_VALUE, 3);   
  TI_AFE4400_SPIAutoIncWriteReg(ALED2STC, 
                          TI_AFE4400_ALED2STC_REG_VALUE, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(ALED2ENDC, 
                          TI_AFE4400_ALED2ENDC_REG_VALUE, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(LED1STC, 
                          TI_AFE4400_LED1STC_REG_VALUE, 3);              
  TI_AFE4400_SPIAutoIncWriteReg(LED1ENDC, 
                          TI_AFE4400_LED1ENDC_REG_VALUE, 3);                
  TI_AFE4400_SPIAutoIncWriteReg(LED1LEDSTC, 
                          TI_AFE4400_LED1LEDSTC_REG_VALUE, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(LED1LEDENDC, 
                          TI_AFE4400_LED1LEDENDC_REG_VALUE, 3);              
  TI_AFE4400_SPIAutoIncWriteReg(ALED1STC, 
                          TI_AFE4400_ALED1STC_REG_VALUE, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(ALED1ENDC, 
                          TI_AFE4400_ALED1ENDC_REG_VALUE, 3);       
  TI_AFE4400_SPIAutoIncWriteReg(LED2CONVST, 
                          TI_AFE4400_LED2CONVST_REG_VALUE, 3);          
  TI_AFE4400_SPIAutoIncWriteReg(LED2CONVEND, 
                          TI_AFE4400_LED2CONVEND_REG_VALUE, 3);              
  TI_AFE4400_SPIAutoIncWriteReg(ALED2CONVST, 
                          TI_AFE4400_ALED2CONVST_REG_VALUE, 3);               
  TI_AFE4400_SPIAutoIncWriteReg(ALED2CONVEND, 
                          TI_AFE4400_ALED2CONVEND_REG_VALUE, 3);                
  TI_AFE4400_SPIAutoIncWriteReg(LED1CONVST, 
                          TI_AFE4400_LED1CONVST_REG_VALUE, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(LED1CONVEND, 
                          TI_AFE4400_LED1CONVEND_REG_VALUE, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(ALED1CONVST, 
                          TI_AFE4400_ALED1CONVST_REG_VALUE, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(ALED1CONVEND, 
                          TI_AFE4400_ALED1CONVEND_REG_VALUE, 3);   
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT0, 
                          TI_AFE4400_ADCRSTSTCT0_REG_VALUE, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT0, 
                          TI_AFE4400_ADCRSTENDCT0_REG_VALUE, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT1, 
                          TI_AFE4400_ADCRSTSTCT1_REG_VALUE, 3);          
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT1, 
                          TI_AFE4400_ADCRSTENDCT1_REG_VALUE, 3);     
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT2, 
                          TI_AFE4400_ADCRSTSTCT2_REG_VALUE, 3);         
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT2, 
                          TI_AFE4400_ADCRSTENDCT2_REG_VALUE, 3);         
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT3, 
                          TI_AFE4400_ADCRSTSTCT3_REG_VALUE, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT3, 
                          TI_AFE4400_ADCRSTENDCT3_REG_VALUE, 3);     
  TI_AFE4400_SPIAutoIncWriteReg(PRPCOUNT, 
                          TI_AFE4400_PRPCOUNT_REG_VALUE, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(CONTROL1, 
                          TI_AFE4400_CONTROL1_REG_VALUE, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(TIA_AMB_GAIN, 
                          TI_AFE4400_TIA_AMB_GAIN_REG_VALUE, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(LEDCNTRL, 
                          TI_AFE4400_LEDCNTRL_REG_VALUE, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(CONTROL2, 
                          TI_AFE4400_CONTROL2_REG_VALUE, 3);             
         
  
}
//******************************************************************************




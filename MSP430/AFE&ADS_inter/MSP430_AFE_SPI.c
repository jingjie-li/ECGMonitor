/*----------------------------------------------------------------
 * Copyright (C) 2018 西安交通大学 生命学院 李金铭
 * 版权所有。 
 * 
 * 文件名： MSP430_AFE_SPI.c
 * 
 * 文件功能描述：   
 *          完成AFE4400初始化
 *   
**----------------------------------------------------------------*/
#include <stdint.h>
#include "Spi.h"
#include "MSP430_AFE_SPI.h"
#include "TI_AFE4400.h" 
#include "TI_AFE4400_setting.h"
//***********************************************************************************

#define TI_ADS1293_CONFIG_REG                         (0x00) 

//------------------------------------------------------------------------------
//  void TI_AFE4400_SPIWriteReg(uint8_t addr, uint8_t value)
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
//  uint8_t_t TI_AFE4400_SPIReadReg(uint8_t addr)
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
  SpiWriteData(inst);                                                          // Send lower register address
  pVal = SpiWriteData(0xFF);                                                     // Read data
  CS2 = CS2_DISABLED;                                                            // /CS disable
  return pVal;
}

//------------------------------------------------------------------------------
//  void TI_AFE4400_SPIAutoIncWriteReg(uint8_t addr, uint8_t *buffer, uint8_t count)
//
//  DESCRIPTION:
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially until "count" writes have been performed. 
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
//  void TI_AFE4400_SPIAutoIncReadReg(uint8_t addr, unit8_t *buffer, uint8_t count)
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


//******************************************************************************
//------------------------------------------------------------------------------
//******************************************************************************
//  void TI_AFE4400_WriteRegSettings(void)
//
//  DESCRIPTION:
//  ADS1293 registers are configured to the values defined TI_AFE4400_setting.h
//  These register settings can easily be obtained from the "Register configuration file"  
//  saved from Sensor AFE Software
//
//  ARGUMENTS:
//       
//******************************************************************************

void TI_AFE4400_WriteRegSettings(void)
{

  TI_AFE4400_SPIAutoIncWriteReg(LED2STC, 
                          LED2STC_VAL, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(LED2ENDC, 
                          LED2ENDC_VAL, 3);    
  TI_AFE4400_SPIAutoIncWriteReg(LED2LEDSTC, 
                          LED2LEDSTC_VAL, 3);  
  TI_AFE4400_SPIAutoIncWriteReg(LED2LEDENDC, 
                          LED2LEDENDC_VAL, 3);   
  TI_AFE4400_SPIAutoIncWriteReg(ALED2STC, 
                          ALED2STC_VAL, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(ALED2ENDC, 
                          ALED2ENDC_VAL, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(LED1STC, 
                          LED1STC_VAL, 3);              
  TI_AFE4400_SPIAutoIncWriteReg(LED1ENDC, 
                          LED1ENDC_VAL, 3);                
  TI_AFE4400_SPIAutoIncWriteReg(LED1LEDSTC, 
                          LED1LEDSTC_VAL, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(LED1LEDENDC, 
                          LED1LEDENDC_VAL, 3);              
  TI_AFE4400_SPIAutoIncWriteReg(ALED1STC, 
                          ALED1STC_VAL, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(ALED1ENDC, 
                          ALED1ENDC_VAL, 3);       
  TI_AFE4400_SPIAutoIncWriteReg(LED2CONVST, 
                          LED2CONVST_VAL, 3);          
  TI_AFE4400_SPIAutoIncWriteReg(LED2CONVEND, 
                          LED2CONVEND_VAL, 3);              
  TI_AFE4400_SPIAutoIncWriteReg(ALED2CONVST, 
                          ALED2CONVST_VAL, 3);               
  TI_AFE4400_SPIAutoIncWriteReg(ALED2CONVEND, 
                          ALED2CONVEND_VAL, 3);                
  TI_AFE4400_SPIAutoIncWriteReg(LED1CONVST, 
                          LED1CONVST_VAL, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(LED1CONVEND, 
                          LED1CONVEND_VAL, 3);             
  TI_AFE4400_SPIAutoIncWriteReg(ALED1CONVST, 
                          ALED1CONVST_VAL, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(ALED1CONVEND, 
                          ALED1CONVEND_VAL, 3);   
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT0, 
                          ADCRSTSTCT0_VAL, 3);            
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT0, 
                          ADCRSTENDCT0_VAL, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT1, 
                          ADCRSTSTCT1_VAL, 3);          
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT1, 
                          ADCRSTENDCT1_VAL, 3);     
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT2, 
                          ADCRSTSTCT2_VAL, 3);         
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT2, 
                          ADCRSTENDCT2_VAL, 3);         
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTSTCT3, 
                          ADCRSTSTCT3_VAL, 3);           
  TI_AFE4400_SPIAutoIncWriteReg(ADCRSTENDCT3, 
                          ADCRSTENDCT3_VAL, 3);     
  TI_AFE4400_SPIAutoIncWriteReg(PRPCOUNT, 
                          PRP, 3);            
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




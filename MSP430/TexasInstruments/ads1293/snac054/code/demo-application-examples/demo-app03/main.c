//******************************************************************************
//  Demo Application03 for MSP430/ADS1293 Interface Code Library v1.0
//  Stream Read ADC Data with interrupt
//
//                MSP430F5529
//             -----------------
//         /|\|              XIN|-
//          | |                 |  
//          --|RST          XOUT|-
//            |                 |
//            |    P4.4/UCA1SIMO|--> SDI 
//            |    P4.5/UCA1SOMI|<-- SDO 
//            |     P4.0/UCA1CLK|--> CLK 
//            |             P2.0|--> CSB 
//            |             P2.4|<-- DRDYB 
//            |                 | 
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   April 2013
//   Built with IAR Embedded Workbench Version:  5.5x
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
#include "TI_ADS1293_register_settings.h"
#include "TI_MSP430.h"
#include "TI_MSP430_hardware_board.h"
#include "TI_MSP430_spi.h"

void TI_ADS1293_WriteRegSettings(void);                                        // Configure ADS1293 registers
void process_adc_output(uint32_t *);                                           // dummy adc data process function: toggles LED
volatile uint8_t ADS1293_ADCDataReady = 0;                                     // set to 1 in DRDYB interrupt service routine
#define SAMPLE_ARRAY_SIZE 10                                                   // Store last 10 ecg samples for processing
#define CH_DATA_SIZE 6                                                         // 6 bytes: ch1 ecg + ch2 ecg
uint32_t adc_sample_array[SAMPLE_ARRAY_SIZE];
//******************************************************************************
void main(void)
{
  uint8_t count, i;
  uint8_t read_buf[CH_DATA_SIZE]; 
  uint32_t adc_data;

  
  WDTCTL = WDTPW+WDTHOLD;                                                      // Stop WDT
  
  TI_ADS1293_LED_PxOUT |= TI_ADS1293_LED_PIN;                                  // Set LED ON
  TI_ADS1293_LED_PxDIR |= TI_ADS1293_LED_PIN;                                  // Set pin direction is output
  
  // configure Port Pin to handle Data Ready Bar Output (DRDYB) from ADS1293
  TI_ADS1293_DRDYB_PxDIR &= ~TI_ADS1293_DRDYB_PIN;                             // Set up port pin for DRDYB
  TI_ADS1293_DRDYB_PxIES |= TI_ADS1293_DRDYB_PIN;                              // Interrupt Edge Select
  TI_ADS1293_DRDYB_PxIFG &= ~TI_ADS1293_DRDYB_PIN;                             // Clear Interrupt Flag
  TI_ADS1293_DRDYB_PxIE |= TI_ADS1293_DRDYB_PIN;                               // Enable Port interrupt  
  
  TI_ADS1293_SPISetup();                                                       // Initilaize MSP430 SPI Block 

  TI_ADS1293_WriteRegSettings();                                               // Set up ADS1293 for Channel Scan

  count = CH_DATA_SIZE;                                                        // bytes to read: ADC_DOUT2 - ADCDOUT0
  i = 0;
  TI_ADS1293_SPIWriteReg(TI_ADS1293_CONFIG_REG, 
                          TI_ADS1293_CONFIG_REG_VALUE | ADS1293_START_CONV);   // start conversion  
  while (1)
  {
    if (ADS1293_ADCDataReady)
    {
      ADS1293_ADCDataReady = 0;                                                // clear flag      
      TI_ADS1293_SPIStreamReadReg(read_buf, count);                            // read adc output into read_buf
      
      adc_data = ((uint32_t) read_buf[0] << 16) 
                 | ((uint16_t) read_buf[1] << 8) | read_buf[2];                // form raw adc output data  
      adc_sample_array[i] = adc_data;
      if (++i == SAMPLE_ARRAY_SIZE)                                            // sample array is full
      {
        process_adc_output(adc_sample_array);                                  // dummy app function: no error toggles led
        i = 0;
      }
    }
    __bis_SR_register(LPM0_bits + GIE);                                        // Enter LPM0, enable interrupts
    __no_operation();                                                          // For debugger 
  } 
}
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
//  void process_adc_output(uint32_t *)
//
//  DESCRIPTION:
//  Dummy ADC data process function: Toggles LED
//******************************************************************************
void process_adc_output(uint32_t *data)
{ 
    TI_ADS1293_LED_PxOUT ^= TI_ADS1293_LED_PIN;                                // Toggle LED 
}
//******************************************************************************
// TI_ADS1293_SPI_DRDYB_PIN interrupt service routine
#pragma vector=TI_ADS1293_DRDYB_VECTOR
__interrupt void TI_ADS1293_DRDY_PORTx(void)
{
  TI_ADS1293_DRDYB_PxIFG &= ~TI_ADS1293_DRDYB_PIN;                             //  IFG cleared
  ADS1293_ADCDataReady = 1;                                                    // set flag
  __bic_SR_register_on_exit(LPM0_bits);                                        // Exit active CPU  
}
//******************************************************************************
//EOF

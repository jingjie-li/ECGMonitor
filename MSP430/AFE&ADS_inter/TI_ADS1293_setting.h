//----------------------------------------------------------------------------
//  Description:  This file contains the initialization values for the 
//  ADS1293 registers.
//
//  MSP430/ADS1293 Interface Code Library v1.0
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   October 2011
//   Built with CCE Version: 4.2 and IAR Embedded Workbench Version:  5.3x
//------------------------------------------------------------------------------
// Change Log:
//------------------------------------------------------------------------------
// Version:  1.00
// Comments: Initial Release Version
//------------------------------------------------------------------------------
#ifndef HEADER_FILE_TI_ADS1293_REGISTER_SETTINGS_H

#define HEADER_FILE_TI_ADS1293_REGISTER_SETTINGS_H

/************************************************************
* TI ADS1293 REGISTER SET INITIALIZATION VALUES
************************************************************/

/************************************************************
* Stops data conversion
************************************************************/
#define TI_ADS1293_CONFIG_REG_VALUE                         (0x00)                  /* Main Configuration */

/************************************************************
* 5-Lead ECG Application ** Input Channel Selection Registers
************************************************************/
#define TI_ADS1293_FLEX_CH1_CN_REG_VALUE                    (0x11)                  /* Flex Routing Swich Control for Channel 1 */
#define TI_ADS1293_FLEX_CH2_CN_REG_VALUE                    (0x19)                  /* Flex Routing Swich Control for Channel 2 */
#define TI_ADS1293_FLEX_CH3_CN_REG_VALUE                    (0x2E)                  /* Flex Routing Swich Control for Channel 3 */
#define TI_ADS1293_FLEX_CH3_CN_3_REG_VALUE                  (0x00)
#define TI_ADS1293_FLEX_PACE_CN_REG_VALUE                   (0x00)                  /* Flex Routing Swich Control for Pace Channel */
#define TI_ADS1293_FLEX_VBAT_CN_REG_VALUE                   (0x00)                  /* Flex Routing Swich Control for Battery Monitoriing */

/************************************************************
* Lead-Off Detect Control Registers
************************************************************/
#define TI_ADS1293_LOD_CN_REG_VALUE                         (0x00)                  /* Lead Off Detect Control */
#define TI_ADS1293_LOD_EN_REG_VALUE                         (0x3F)                  /* Lead Off Detect Enable */
#define TI_ADS1293_LOD_CURRENT_REG_VALUE                    (0xFF)                  /* Lead Off Detect Current */
#define TI_ADS1293_LOD_AC_CN_REG_VALUE                      (0x00)                  /* AC Lead Off Detect Current */

/************************************************************
* Common-Mode Detection and 
* Right-Leg Drive Common-Mode Feedback Control Registers
************************************************************/
#define TI_ADS1293_CMDET_EN_REG_VALUE                       (0x07)                  /* Common Mode Detect Enable */
#define TI_ADS1293_CMDET_CN_REG_VALUE                       (0x00)                  /* Commond Mode Detect Control */
#define TI_ADS1293_RLD_CN_REG_VALUE                         (0x04)                  /* Right Leg Drive Control */

/************************************************************
* Wilson Control Registers
************************************************************/
#define TI_ADS1293_WILSON_EN1_REG_VALUE                     (0x01)                  /* Wilson Reference Input one Selection */
#define TI_ADS1293_WILSON1_REG_VALUE                        (0x00)
#define TI_ADS1293_WILSON_EN2_REG_VALUE                     (0x02)                  /* Wilson Reference Input two Selection */
#define TI_ADS1293_WILSON2_REG_VALUE                        (0x00)
#define TI_ADS1293_WILSON_EN3_REG_VALUE                     (0x03)                  /* Wilson Reference Input three Selection */
#define TI_ADS1293_WILSON3_REG_VALUE                        (0x00)
#define TI_ADS1293_WILSON_CN_REG_VALUE                      (0x01)                  /* Wilson Reference Input Control */
#define TI_ADS1293_WILSON_REG_VALUE                         (0x00)

/************************************************************
* Reference Registers
************************************************************/
#define TI_ADS1293_REF_CN_REG_VALUE                         (0x00)                  /* Internal Reference Voltage Control */

/************************************************************
* OSC Control Registers
************************************************************/
#define TI_ADS1293_OSC_CN_REG_VALUE                         (0x04)                  /* Clock Source and Output Clock Control */

/************************************************************
* AFE Control Registers
************************************************************/
#define TI_ADS1293_AFE_RES_REG_VALUE                        (0x00)                  /* Analog Front-End Frequency and Resolution */
#define TI_ADS1293_AFE_SHDN_CN_REG_VALUE                    (0x00)                  /* Analog Front-End Shutdown Control */
#define TI_ADS1293_AFE_SHDN_CN_3_REG_VALUE                  (0x24)
#define TI_ADS1293_AFE_FAULT_CN_REG_VALUE                   (0x00)                  /* Analog Front-End Fault Detection Control */
#define TI_ADS1293_AFE_DITHER_EN_REG_VALUE                  (0x00)                  /* Enable Dithering in Signma-Delta */
#define TI_ADS1293_AFE_PACE_CN_REG_VALUE                    (0x05)                  /* Analog Pace Channel Output Routing Control */

/************************************************************
* Digital Registers
************************************************************/
#define TI_ADS1293_R2_RATE_REG_VALUE                        (0x02)                  /* R2 Decimation Rate */
#define TI_ADS1293_R3_RATE1_REG_VALUE                       (0x20)                  /* vishy:R3 Decimation Rate for Channel 1 */
#define TI_ADS1293_R3_RATE2_REG_VALUE                       (0x20)                  /* R3 Decimation Rate for Channel 2 */
#define TI_ADS1293_R3_RATE3_REG_VALUE                       (0x20)                  /* R3 Decimation Rate for Channel 3 */
#define TI_ADS1293_R1_DRATE_REG_VALUE                       (0x00)                  /* 2x Pace Data Rate for all channels */
#define TI_ADS1293_P_DRATE_REG_VALUE                        (0x00)                  /*  */
#define TI_ADS1293_DIS_EFILTER_REG_VALUE                    (0x00)                  /* ECG Filters Disabled */
#define TI_ADS1293_DRDYB_SRC_REG_VALUE                      (0x08)                  /* Data Ready Pin Source */
#define TI_ADS1293_SYNCOUTB_SRC_REG_VALUE                   (0x00)                  /* Sync Out Pin Source */
#define TI_ADS1293_MASK_DRDYB_REG_VALUE                     (0x00)                  /* Optional Mask Control for DRDYB Output */
#define TI_ADS1293_MASK_ERR_REG_VALUE                       (0xF0)                  /* Mask Error on ALARMB Pin */
#define TI_ADS1293_ALARM_FILTER_REG_VALUE                   (0x33)                  /* Digital Filter for Analog Alarm Signals */
#define TI_ADS1293_CH_CNFG_REG_VALUE                        (0x20)                  /* vishy: 3channels, no status */  //70


#define TI_ADS1293_REVID_REG_VALUE                          (0x40)                  /* Revision ID */
#define TI_ADS1293_DATA_LOOP_REG_VALUE                      (0x50)                  /* Loop Read Back Address */

// Useful definitions
#define ADS1293_START_CONV                                  (0x01)                  // Start Conversion Bit
#define ADS1293_STOP_CONV                                   (0xFE)
#endif                                                        // HEADER_FILE_TI_ADS1293_REGISTER_SETTINGS_H

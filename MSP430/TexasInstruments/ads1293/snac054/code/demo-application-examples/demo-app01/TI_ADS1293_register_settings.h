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

#define TI_ADS1293_CONFIG_REG_VALUE                         (0x00)                  /* Main Configuration */

#define TI_ADS1293_FLEX_CH1_CN_REG_VALUE                    (0x0A)                  /* Flex Routing Swich Control for Channel 1 */
#define TI_ADS1293_FLEX_CH2_CN_REG_VALUE                    (0x1A)                  /* Flex Routing Swich Control for Channel 2 */
#define TI_ADS1293_FLEX_CH3_CN_REG_VALUE                    (0x00)                  /* Flex Routing Swich Control for Channel 3 */
#define TI_ADS1293_FLEX_PACE_CN_REG_VALUE                   (0x00)                  /* Flex Routing Swich Control for Pace Channel */
#define TI_ADS1293_FLEX_VBAT_CN_REG_VALUE                   (0x00)                  /* Flex Routing Swich Control for Battery Monitoriing */

#define TI_ADS1293_LOD_CN_REG_VALUE                         (0x08)                  /* Lead Off Detect Control */
#define TI_ADS1293_LOD_EN_REG_VALUE                         (0x00)                  /* Lead Off Detect Enable */
#define TI_ADS1293_LOD_CURRENT_REG_VALUE                    (0x00)                  /* Lead Off Detect Current */
#define TI_ADS1293_LOD_AC_CN_REG_VALUE                      (0x00)                  /* AC Lead Off Detect Current */

#define TI_ADS1293_CMDET_EN_REG_VALUE                       (0x07)                  /* Common Mode Detect Enable */
#define TI_ADS1293_CMDET_CN_REG_VALUE                       (0x00)                  /* Commond Mode Detect Control */
#define TI_ADS1293_RLD_CN_REG_VALUE                         (0x04)                  /* Right Leg Drive Control */

#define TI_ADS1293_WILSON_EN1_REG_VALUE                     (0x00)                  /* Wilson Reference Input one Selection */
#define TI_ADS1293_WILSON_EN2_REG_VALUE                     (0x00)                  /* Wilson Reference Input two Selection */
#define TI_ADS1293_WILSON_EN3_REG_VALUE                     (0x00)                  /* Wilson Reference Input three Selection */
#define TI_ADS1293_WILSON_CN_REG_VALUE                      (0x00)                  /* Wilson Reference Input Control */

#define TI_ADS1293_REF_CN_REG_VALUE                         (0x00)                  /* Internal Reference Voltage Control */

#define TI_ADS1293_OSC_CN_REG_VALUE                         (0x04)                  /* Clock Source and Output Clock Control */

#define TI_ADS1293_AFE_RES_REG_VALUE                        (0x00)                  /* Analog Front-End Frequency and Resolution */
#define TI_ADS1293_AFE_SHDN_CN_REG_VALUE                    (0x00)                  /* Analog Front-End Shutdown Control */
#define TI_ADS1293_AFE_FAULT_CN_REG_VALUE                   (0x00)                  /* Analog Front-End Fault Detection Control */
#define TI_ADS1293_AFE_DITHER_EN_REG_VALUE                  (0x00)                  /* Enable Dithering in Signma-Delta */
#define TI_ADS1293_AFE_PACE_CN_REG_VALUE                    (0x05)                  /* Analog Pace Channel Output Routing Control */

//#define TI_ADS1293_ERROR_LOD_REG_VALUE                      (0x00)                  /* Lead Off Detect Error Status */
//#define TI_ADS1293_ERROR_STATUS_REG_VALUE                   (0x72)                  /* Other Error Status */
//#define TI_ADS1293_ERROR_RANGE1_REG_VALUE                   (0x12)                  /* Channel 1 Amplifier Out of Range Status */
//#define TI_ADS1293_ERROR_RANGE2_REG_VALUE                   (0x12)                  /* Channel 1 Amplifier Out of Range Status */
//#define TI_ADS1293_ERROR_RANGE3_REG_VALUE                   (0x36)                  /* Channel 1 Amplifier Out of Range Status */
//#define TI_ADS1293_ERROR_SYNC_REG_VALUE                     (0x00)                  /* Synchronization Error */


#define TI_ADS1293_R2_RATE_REG_VALUE                        (0x02)                  /* R2 Decimation Rate */
#define TI_ADS1293_R3_RATE1_REG_VALUE                       (0x02)                  /* R3 Decimation Rate for Channel 1 */
#define TI_ADS1293_R3_RATE2_REG_VALUE                       (0x02)                  /* R3 Decimation Rate for Channel 2 */
#define TI_ADS1293_R3_RATE3_REG_VALUE                       (0x02)                  /* R3 Decimation Rate for Channel 3 */
#define TI_ADS1293_P_DRATE_REG_VALUE                        (0x00)                  /* 2x Pace Data Rate for all channels */
#define TI_ADS1293_DIS_EFILTER_REG_VALUE                    (0x00)                  /* ECG Filters Disabled */
#define TI_ADS1293_DRDYB_SRC_REG_VALUE                      (0x08)                  /* Data Ready Pin Source */
#define TI_ADS1293_SYNCOUTB_SRC_REG_VALUE                   (0x00)                  /* Sync Out Pin Source */
#define TI_ADS1293_MASK_DRDYB_REG_VALUE                     (0x00)                  /* Optional Mask Control for DRDYB Output */
#define TI_ADS1293_MASK_ERR_REG_VALUE                       (0x00)                  /* Mask Error on ALARMB Pin */

#define TI_ADS1293_ALARM_FILTER_REG_VALUE                   (0x33)                  /* Digital Filter for Analog Alarm Signals */
#define TI_ADS1293_CH_CNFG_REG_VALUE                        (0x30)                  /* Configure Channel for Loop Read Back Mode */

//#define TI_ADS1293_DATA_STATUS_REG_VALUE                    (0x00)                  /* ECG and Pace Data Ready Status */
//#define TI_ADS1293_DATA_CH1_PACE_H_REG_VALUE                (0x00)                  /* Channel1 Pace Data High [15:8] */
//#define TI_ADS1293_DATA_CH1_PACE_L_REG_VALUE                (0x00)                  /* Channel1 Pace Data Low [7:0] */
//#define TI_ADS1293_DATA_CH2_PACE_H_REG_VALUE                (0x00)                  /* Channel2 Pace Data High [15:8] */
//#define TI_ADS1293_DATA_CH2_PACE_L_REG_VALUE                (0x00)                  /* Channel2 Pace Data Low [7:0] */
//#define TI_ADS1293_DATA_CH3_PACE_H_REG_VALUE                (0x00)                  /* Channel3 Pace Data High [15:8] */
//#define TI_ADS1293_DATA_CH3_PACE_L_REG_VALUE                (0x00)                  /* Channel3 Pace Data Low [7:0] */
//#define TI_ADS1293_DATA_CH1_ECG_H_REG_VALUE                 (0x00)                  /* Channel1 ECG Data High [23:16] */
//#define TI_ADS1293_DATA_CH1_ECG_M_REG_VALUE                 (0x00)                  /* Channel1 ECG Data Medium [15:8] */
//#define TI_ADS1293_DATA_CH1_ECG_L_REG_VALUE                 (0x00)                  /* Channel1 ECG Data Low [7:0] */
//#define TI_ADS1293_DATA_CH2_ECG_H_REG_VALUE                 (0x00)                  /* Channel2 ECG Data High [23:16] */
//#define TI_ADS1293_DATA_CH2_ECG_M_REG_VALUE                 (0x00)                  /* Channel2 ECG Data Medium [15:8] */
//#define TI_ADS1293_DATA_CH2_ECG_L_REG_VALUE                 (0x00)                  /* Channel2 ECG Data Low [7:0] */
//#define TI_ADS1293_DATA_CH3_ECG_H_REG_VALUE                 (0x00)                  /* Channel3 ECG Data High [23:16] */
//#define TI_ADS1293_DATA_CH3_ECG_M_REG_VALUE                 (0x00)                  /* Channel3 ECG Data Medium [15:8] */
//#define TI_ADS1293_DATA_CH3_ECG_L_REG_VALUE                 (0x00)                  /* Channel3 ECG Data Low [7:0] */

//#define TI_ADS1293_REVID_REG_VALUE                          (0x40)                  /* Revision ID */
//#define TI_ADS1293_DATA_LOOP_REG_VALUE                      (0x50)                  /* Loop Read Back Address */


#endif                                                        // HEADER_FILE_TI_ADS1293_REGISTER_SETTINGS_H

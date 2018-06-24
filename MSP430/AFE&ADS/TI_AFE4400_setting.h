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
#ifndef HEADER_FILE_TI_AFE4400_REGISTER_SETTINGS_H

#define HEADER_FILE_TI_AFE4400_REGISTER_SETTINGS_H

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
#define TI_AFE4400_LED2STC_REG_VALUE                    (6050ul)                /* Flex Routing Swich Control for Channel 1 */
#define TI_AFE4400_LED2ENDC_REG_VALUE                   (7998ul)                /* Flex Routing Swich Control for Channel 2 */
#define TI_AFE4400_LED2LEDSTC_REG_VALUE                 (6000ul)                /* Flex Routing Swich Control for Channel 3 */
#define TI_AFE4400_LED2LEDENDC_REG_VALUE                (7999ul)                /* Flex Routing Swich Control for Pace Channel */
#define TI_AFE4400_ALED2STC_REG_VALUE                   (50ul)                  /* Flex Routing Swich Control for Battery Monitoriing */
#define TI_AFE4400_ALED2ENDC_REG_VALUE                  (1998ul)                /* Lead Off Detect Control */
#define TI_AFE4400_LED1STC_REG_VALUE                    (2050ul)                /* Lead Off Detect Enable */
#define TI_AFE4400_LED1ENDC_REG_VALUE                   (3998ul)                /* Lead Off Detect Current */
#define TI_AFE4400_LED1LEDSTC_REG_VALUE                 (2000ul)                /* AC Lead Off Detect Current */
#define TI_AFE4400_LED1LEDENDC_REG_VALUE                (3999ul)                /* Common Mode Detect Enable */
#define TI_AFE4400_ALED1STC_REG_VALUE                   (4050ul)                /* Commond Mode Detect Control */
#define TI_AFE4400_ALED1ENDC_REG_VALUE                  (5998ul)                /* Right Leg Drive Control */
#define TI_AFE4400_LED2CONVST_REG_VALUE                 (4ul)                   /* Wilson Reference Input one Selection */
#define TI_AFE4400_LED2CONVEND_REG_VALUE                (1999ul)                /* Wilson Reference Input two Selection */
#define TI_AFE4400_ALED2CONVST_REG_VALUE                (2004ul)                /* Wilson Reference Input three Selection */
#define TI_AFE4400_ALED2CONVEND_REG_VALUE               (3999ul)                /* Wilson Reference Input Control */
#define TI_AFE4400_LED1CONVST_REG_VALUE                 (4004ul)                /* Internal Reference Voltage Control */
#define TI_AFE4400_LED1CONVEND_REG_VALUE                (5999ul)                /* Clock Source and Output Clock Control */
#define TI_AFE4400_ALED1CONVST_REG_VALUE                (6004ul)                /* Analog Front-End Frequency and Resolution */
#define TI_AFE4400_ALED1CONVEND_REG_VALUE               (7999ul)                /* Analog Front-End Shutdown Control */
#define TI_AFE4400_ADCRSTSTCT0_REG_VALUE                (0ul)                   /* Analog Front-End Fault Detection Control */
#define TI_AFE4400_ADCRSTENDCT0_REG_VALUE               (3ul)                   /* Enable Dithering in Signma-Delta */
#define TI_AFE4400_ADCRSTSTCT1_REG_VALUE                (2000ul)                /* Analog Pace Channel Output Routing Control */
#define TI_AFE4400_ADCRSTENDCT1_REG_VALUE               (2003ul)                /* R2 Decimation Rate */
#define TI_AFE4400_ADCRSTSTCT2_REG_VALUE                (4000ul)                /* vishy:R3 Decimation Rate for Channel 1 */
#define TI_AFE4400_ADCRSTENDCT2_REG_VALUE               (4003ul)                /* R3 Decimation Rate for Channel 2 */
#define TI_AFE4400_ADCRSTSTCT3_REG_VALUE                (6000ul)                /* R3 Decimation Rate for Channel 3 */
#define TI_AFE4400_ADCRSTENDCT3_REG_VALUE               (6003ul)                /* 2x Pace Data Rate for all channels */
#define TI_AFE4400_PRPCOUNT_REG_VALUE                   (7999ul)                /*  */
#define TI_AFE4400_CONTROL1_REG_VALUE                   (0x100ul)                 /* ECG Filters Disabled */
#define TI_AFE4400_TIA_AMB_GAIN_REG_VALUE               (0x004141ul)              /* Data Ready Pin Source */
#define TI_AFE4400_LEDCNTRL_REG_VALUE                   (0x8F8Ful)                /* Sync Out Pin Source */
#define TI_AFE4400_CONTROL2_REG_VALUE                   (0x100ul)                 /* Optional Mask Control for DRDYB Output */


#endif                                                        // HEADER_FILE_TI_AFE4400_REGISTER_SETTINGS_H

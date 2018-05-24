//----------------------------------------------------------------------------
//  Description:  This file contains definitions specific to the hardware board.
//  Specifically, the definitions include hardware connections with the
//  ADS1293 connector port, LEDs, and switches.
//
//  MSP430/ADS1293 Interface Code Library v1.0
//
//   Vishy Natarajan
//   Texas Instruments Inc.
//   April 2013
//   Built with IAR Embedded Workbench Version:  5.5x
//------------------------------------------------------------------------------
// Change Log:
//------------------------------------------------------------------------------
// Version:  1.00
// Comments: Initial Release Version
//------------------------------------------------------------------------------
#ifndef HEADER_TI_MSP430_HARDWARE_BOARD_H

#define HEADER_FILE_TI_MSP430_HARDWARE_BOARD_H

// Note LED pin is not connected on the EVM
#define TI_ADS1293_LED_PxOUT            P8OUT
#define TI_ADS1293_LED_PxDIR            P8DIR
#define TI_ADS1293_LED_PIN              BIT0

#define TI_ADS1293_DRDY_PORTx           PORT_2
#define TI_ADS1293_DRDYB_PxDIR          P2DIR
#define TI_ADS1293_DRDYB_PxIE           P2IE
#define TI_ADS1293_DRDYB_PxIES          P2IES
#define TI_ADS1293_DRDYB_PxIFG          P2IFG
#define TI_ADS1293_DRDYB_PxREN          P2REN
#define TI_ADS1293_DRDYB_PxOUT          P2OUT
#define TI_ADS1293_DRDYB_PIN            BIT4
#define TI_ADS1293_DRDYB_VECTOR         PORT2_VECTOR

#define TI_ADS1293_CSn_PxOUT            P2OUT
#define TI_ADS1293_CSn_PxDIR            P2DIR
#define TI_ADS1293_CSn_PIN              BIT0


//----------------------------------------------------------------------------
// Select which port will be used for interface to ADS1293
//----------------------------------------------------------------------------
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIA0_5xx        // 5xx, 6xx family USCIA0 SPI Interface to ADS1293
#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIA1_5xx        // 5xx, 6xx family USCIA1 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIA2_5xx        // 5xx, 6xx family USCIA2 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIA3_5xx        // 5xx, 6xx family USCIA3 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIB0_5xx        // 5xx, 6xx family USCIB0 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIB1_5xx        // 5xx, 6xx family USCIB1 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIB2_5xx        // 5xx, 6xx family USCIB2 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIB3_5xx        // 5xx, 6xx family USCIB3 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USART0            // USART0 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USART1            // USART1 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIA0            // 2xx, 4xx family USCIA0 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIA1            // 2xx, 4xx family USCIA1 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIB0            // 2xx, 4xx family USCIB0 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USCIB1            // 2xx, 4xx family USCIB1 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_USI               // G2xx value seris SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_BITBANG           // GPIO BITBANG
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_eUSCIA0_FR57xx    // FRAM 57xx family eUSCIA0 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_eUSCIA1_FR57xx    // FRAM 57xx family eUSCIA1 SPI Interface to ADS1293
//#define TI_ADS1293_SER_INTF            TI_ADS1293_SER_INTF_eUSCIB0_FR57xx    // FRAM 57xx family eUSCIB0 SPI Interface to ADS1293
#endif                                                                         // HEADER_FILE_TI_MSP430_HARDWARE_BOARD_H

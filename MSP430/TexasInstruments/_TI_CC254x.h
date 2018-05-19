//******************************************************************************
//  Description:  This file contains definitions specific to the specific CC254x
//  chosen for this implementation.  CC254x has multiple interfaces capable
//  of interfacing to the SPI port; each of these is defined in this file.
//
//  The source labels for the definitions (i.e., "P3SEL") can be found in
//  msp430xxxx.h.
//
//  CC254x/ADS1293 Interface Code Library v1.0
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
#ifndef HEADER_TI_ADS1293_CC254x_H

#define HEADER_FILE_TI_ADS1293_CC254x_H

#include "hal_types.h"

#ifdef CC2541
#include <ioCC2541.h>
#else // CC2540
#include <ioCC2540.h>
#endif // CC2541

//***********************************************************************************
// Macros

// Wait 1+1/3*t [us]
#define WAIT_1_3US(t)                   \
    do{                                 \
        for (uint8 i = 0; i<t; i++)     \
            asm("NOP");                 \
    }while(0)



//***********************************************************************************

//******************************************************************************
// SPI port definitions
// Adjust the values for the chosen interfaces, according to the pin
// assignments indicated in the chosen CC254x device datasheet.
//******************************************************************************
// SPI port definitions 

//***********************************************************************************
// Defines

// ADS1293 connected at:
// P1_3 = SCK
// P1_4 = MISO
// P1_5 = MOSI


#define SCK             P1_3
#define MISO            P1_4
#define MOSI            P1_5




//***********************************************************************************
#endif                                                                         // HEADER_FILE_TI_ADS1293_CC254x_H

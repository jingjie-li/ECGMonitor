/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/* 
 * ======== UsbMscReq.c ========
 */
#include <descriptors.h>

#ifdef _MSC_

#include "../USB_Common/types.h"    //Basic Type declarations
#include "../USB_Common/device.h"
#include "../USB_Common/defMSP430USB.h"
#include "../USB_Common/usb.h"      //USB-specific Data Structures
#include "../USB_MSC_API/UsbMscScsi.h"
#include "../USB_MSC_API/UsbMscReq.h"
#include "../USB_MSC_API/UsbMsc.h"

extern __no_init tEDB __data16 tInputEndPointDescriptorBlock[];
extern __no_init tEDB __data16 tOutputEndPointDescriptorBlock[];
extern struct _MscState MscState;

/*----------------------------------------------------------------------------+
 | Functions                                                                   |
 +----------------------------------------------------------------------------*/
BYTE USBMSC_reset (VOID)
{
    Msc_ResetStateMachine();
    Msc_ResetFlags();
    Msc_ResetStruct();
    MscState.isMSCConfigured = TRUE;

    MscState.bMscResetRequired = FALSE;
    tInputEndPointDescriptorBlock[stUsbHandle[MSC0_INTFNUM].edb_Index].bEPCNF
        &= ~(EPCNF_STALL | EPCNF_TOGGLE );
    tOutputEndPointDescriptorBlock[stUsbHandle[MSC0_INTFNUM].edb_Index].bEPCNF
        &= ~(EPCNF_STALL  | EPCNF_TOGGLE );
    usbSendZeroLengthPacketOnIEP0();    //status stage for control transfer

    return (FALSE);
}

//----------------------------------------------------------------------------
BYTE Get_MaxLUN (VOID)
{
    BYTE maxLunNumber = MSC_MAX_LUN_NUMBER - 1;

    wBytesRemainingOnIEP0 = 1;
    MscState.isMSCConfigured = TRUE;
    usbSendDataPacketOnEP0((PBYTE)&maxLunNumber);

    return (FALSE);
}

#endif //_MSC_
/*----------------------------------------------------------------------------+
 | End of source file                                                          |
 +----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

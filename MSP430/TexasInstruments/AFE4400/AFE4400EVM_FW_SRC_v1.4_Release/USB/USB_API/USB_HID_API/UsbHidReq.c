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
 * ======== UsbHidReq.c ========
 */
#include "../USB_Common/device.h"
#include "../USB_Common/types.h"                            //Basic Type declarations
#include "../USB_Common/defMSP430USB.h"
#include "../USB_Common/usb.h"                              //USB-specific Data Structures
#include "UsbHid.h"
#include "UsbHidReq.h"
#include <descriptors.h>

#ifdef _HID_

VOID usbClearOEP0ByteCount (VOID);
VOID usbSendDataPacketOnEP0 (PBYTE pbBuffer);
VOID usbReceiveDataPacketOnEP0 (PBYTE pbBuffer);

extern const BYTE report_desc_size[HID_NUM_INTERFACES];
extern const PBYTE report_desc[HID_NUM_INTERFACES];         //KLQ
extern BYTE hidProtocol[];
extern BYTE hidIdleRate[];
extern WORD wUsbHidEventMask;

#ifdef NON_COMPOSITE_MULTIPLE_INTERFACES
extern const struct abromConfigurationDescriptorGroupHID abromConfigurationDescriptorGroupHID;
#endif

//Local Macros
#define INTERFACE_OFFSET(X)   (X - HID0_REPORT_INTERFACE)   //Get the HID offset

BYTE usbGetHidDescriptor (VOID)
{
    usbClearOEP0ByteCount();
    wBytesRemainingOnIEP0 = 9;
#ifdef NON_COMPOSITE_MULTIPLE_INTERFACES
    usbSendDataPacketOnEP0((PBYTE)&abromConfigurationDescriptorGroupHID.stHid[
            INTERFACE_OFFSET(tSetupPacket.wIndex)].blength_hid_descriptor);
#else
    usbSendDataPacketOnEP0((PBYTE)&abromConfigurationDescriptorGroup.stHid[
            INTERFACE_OFFSET(tSetupPacket.wIndex)].blength_hid_descriptor);
#endif
    return (FALSE);
}

BYTE usbGetReportDescriptor (VOID)
{
    wBytesRemainingOnIEP0 =
        report_desc_size[INTERFACE_OFFSET(tSetupPacket.wIndex)];
    usbSendDataPacketOnEP0(report_desc[INTERFACE_OFFSET(tSetupPacket.wIndex)]);

    return (FALSE);
}

//----------------------------------------------------------------------------

BYTE usbSetReport (VOID)
{
    BYTE *buffer;

    //tSetupPacket.wValue = USB_REQ_HID_FEATURE or USB_REQ_HID_INPUT
    buffer = Handler_SetReport(tSetupPacket.wValue,
        tSetupPacket.wLength,
        tSetupPacket.wIndex);

    //What if buffer is NULL?
    if (buffer == 0){
        usbReceiveDataPacketOnEP0((PBYTE)&abUsbRequestIncomingData);
    } else {
        usbReceiveDataPacketOnEP0((PBYTE)buffer);   //receive data over EP0 from Host
    }

    return (FALSE);
}

//----------------------------------------------------------------------------

BYTE usbGetReport (VOID)
{
    BYTE *buffer;

    //tSetupPacket.wValue = USB_REQ_HID_FEATURE or USB_REQ_HID_INPUT
    buffer = Handler_GetReport((BYTE)tSetupPacket.wValue,
        tSetupPacket.wLength,
        tSetupPacket.wIndex);
    if (buffer != 0){
        usbSendDataPacketOnEP0((PBYTE)buffer);
    }

    return (FALSE);
}

BYTE usbSetProtocol (VOID)
{
    BYTE bWakeUp = FALSE;

    hidProtocol[INTERFACE_OFFSET(tSetupPacket.wIndex)] =
        (BYTE)tSetupPacket.wValue;
    //tSetupPacket.wValue = USB_REQ_HID_BOOT_PROTOCOL or USB_REQ_HID_REPORT_PROTOCOL
    bWakeUp = USBHID_handleBootProtocol((BYTE)tSetupPacket.wValue,
        tSetupPacket.wIndex);
    usbSendZeroLengthPacketOnIEP0();

    return (bWakeUp);
}

//----------------------------------------------------------------------------

BYTE usbGetProtocol (VOID)
{
    usbSendDataPacketOnEP0(&hidProtocol[INTERFACE_OFFSET(tSetupPacket.wIndex)]);

    return (FALSE);
}

//----------------------------------------------------------------------------

BYTE usbSetIdle (VOID)
{
    if (hidProtocol[INTERFACE_OFFSET(tSetupPacket.wIndex)] ==
        USB_REQ_HID_BOOT_PROTOCOL){
        hidIdleRate[INTERFACE_OFFSET(tSetupPacket.wIndex)] =
            tSetupPacket.wValue >> 8;
        usbSendZeroLengthPacketOnIEP0();
    } else {
        usbInvalidRequest();
    }

    return (FALSE);
}

//----------------------------------------------------------------------------

BYTE usbGetIdle (VOID)
{
    if (hidProtocol[INTERFACE_OFFSET(tSetupPacket.wIndex)] ==
        USB_REQ_HID_BOOT_PROTOCOL){
        usbSendDataPacketOnEP0(&hidIdleRate[INTERFACE_OFFSET(tSetupPacket.
                                                wIndex)]);
    } else {
        usbInvalidRequest();
    }

    return (FALSE);
}

BYTE setReportBuffer[64];

/*
 * This event indicates that a Set_Report request was received from the host
 */
BYTE *Handler_SetReport (WORD reportType_reportId,
    WORD dataLength,
    BYTE intfnum)
{
    return (&setReportBuffer[0]);
}

/*
 * This event indicates that a Set_Report request data has been received
 */
BYTE Handler_SetReportDataAvailable (BYTE intfnum)
{
    return (FALSE);
}

/*
 * This event indicates that a Get_Report request was received from the host
 */
BYTE *Handler_GetReport (WORD reportType_reportId,
    WORD requestedLength,
    BYTE intfnum)
{
    return (&setReportBuffer[0]);
}

//----------------------------------------------------------------------------

#endif  //_HID_
/*----------------------------------------------------------------------------+
 | End of source file                                                          |
 +----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

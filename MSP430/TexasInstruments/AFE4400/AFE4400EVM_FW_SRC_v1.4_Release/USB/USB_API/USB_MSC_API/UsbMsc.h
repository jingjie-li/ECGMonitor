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
 * ======== UsbMsc.h ========
 */
#ifndef _USB_MSC_H_
#define _USB_MSC_H_

#include "UsbMscScsi.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*Return values of getState() and USBMSC_poll() API */
#define kUSBMSC_idle               0
#define kUSBMSC_readInProgress     1
#define kUSBMSC_writeInProgress    2
#define kUSBMSC_cmdBeingProcessed  3
#define kUSBMSC_okToSleep          4
#define kUSBMSC_processBuffer      5

/*----------------------------------------------------------------------------+
 | Function Prototypes                                                         |
 +----------------------------------------------------------------------------*/
/*Function to handle the MSC SCSI state machine */
BYTE USBMSC_poll(VOID);

/* MSC functions */
BOOL MSCToHostFromBuffer ();
BOOL MSCFromHostToBuffer ();
BYTE USBMSC_bufferProcessed(VOID);
BYTE USBMSC_getState ();
BYTE USBMSC_updateMediaInfo (BYTE lun, struct USBMSC_mediaInfoStr *info);

BYTE USBMSC_handleBufferEvent(VOID);
BYTE USBMSC_registerBufInfo ( BYTE lun, BYTE* RWbuf_x, BYTE* RWbuf_y, WORD size);

#ifdef __cplusplus
}
#endif
#endif  //_USB_MSC_H_

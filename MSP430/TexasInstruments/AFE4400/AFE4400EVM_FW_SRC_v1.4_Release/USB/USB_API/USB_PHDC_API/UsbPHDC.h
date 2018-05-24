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
 * ======== UsbPHDC.h ========
 */
#ifndef _UsbPHDC_H_
#define _UsbPHDC_H_

#ifdef __cplusplus
extern "C"
{
#endif


#define kUSBPHDC_sendStarted         0x01
#define kUSBPHDC_sendComplete        0x02
#define kUSBPHDC_intfBusyError       0x03
#define kUSBPHDC_receiveStarted      0x04
#define kUSBPHDC_receiveCompleted    0x05
#define kUSBPHDC_receiveInProgress   0x06
#define kUSBPHDC_generalError        0x07
#define kUSBPHDC_busNotAvailable     0x08



/*----------------------------------------------------------------------------
 * These functions can be used in application
 +----------------------------------------------------------------------------*/

/*
 * Sends data over interface intfNum, of size size and starting at address data.
 * Returns:  kUSBPHDC_sendStarted
 *          kUSBPHDC_sendComplete
 *          kUSBPHDC_intfBusyError
 */
BYTE USBPHDC_sendData (const BYTE* data, WORD size, BYTE intfNum);

/*
 * Receives data over interface intfNum, of size size, into memory starting at address data.
 */
BYTE USBPHDC_receiveData (BYTE* data, WORD size, BYTE intfNum);

/*
 * Aborts an active receive operation on interface intfNum.
 * size: the number of bytes that were received and transferred
 * to the data location established for this receive operation.
 */
BYTE USBPHDC_abortReceive (WORD* size, BYTE intfNum);


#define kUSBPHDC_noDataWaiting 1    //returned by USBPHDC_rejectData() if no data pending

/*
 * This function rejects payload data that has been received from the host.
 */
BYTE USBPHDC_rejectData (BYTE intfNum);

/*
 * Aborts an active send operation on interface intfNum.  Returns the number of bytes that were sent prior to the abort, in size.
 */
BYTE USBPHDC_abortSend (WORD* size, BYTE intfNum);


#define kUSBPHDC_waitingForSend      0x01
#define kUSBPHDC_waitingForReceive   0x02
#define kUSBPHDC_dataWaiting         0x04
#define kUSBPHDC_busNotAvailable     0x08
#define kUSB_allPHDCEvents           0xFF

/*
 * This function indicates the status of the interface intfNum.
 * If a send operation is active for this interface,
 * the function also returns the number of bytes that have been transmitted to the host.
 * If a receiver operation is active for this interface, the function also returns
 * the number of bytes that have been received from the host and are waiting at the assigned address.
 *
 * returns kUSBPHDC_waitingForSend (indicates that a call to USBPHDC_SendData()
 * has been made, for which data transfer has not been completed)
 *
 * returns kUSBPHDC_waitingForReceive (indicates that a receive operation
 * has been initiated, but not all data has yet been received)
 *
 * returns kUSBPHDC_dataWaiting (indicates that data has been received
 * from the host, waiting in the USB receive buffers)
 */
BYTE USBPHDC_intfStatus (BYTE intfNum, WORD* bytesSent, WORD* bytesReceived);

/*
 * This function is called when the device receives a Get_Status request
 */
BYTE USBPHDC_GetDataStatusReq(VOID);


/*
 * Returns how many bytes are in the buffer are received and ready to be read.
 */
BYTE USBPHDC_bytesInUSBBuffer (BYTE intfNum);


/*----------------------------------------------------------------------------
 * Event-Handling routines
 +----------------------------------------------------------------------------*/

/*
 * This event indicates that data has been received for interface intfNum, but no data receive operation is underway.
 * returns TRUE to keep CPU awake
 */
BYTE USBPHDC_handleDataReceived (BYTE intfNum);

/*
 * This event indicates that a send operation on interface intfNum has just been completed.
 * returns TRUE to keep CPU awake
 */
BYTE USBPHDC_handleSendCompleted (BYTE intfNum);

/*
 * This event indicates that a receive operation on interface intfNum has just been completed.
 * returns TRUE to keep CPU awake
 */
BYTE USBPHDC_handleReceiveCompleted (BYTE intfNum);


#ifdef __cplusplus
}
#endif
#endif  //_UsbPHDC_H_

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
 * ======== UsbMscStateMachine.c ========
 */
/*File includes */
#include "../USB_Common/device.h"
#include "../USB_Common/types.h"
#include "../USB_Common/defMSP430USB.h"
#include "../USB_MSC_API/UsbMscScsi.h"
#include "../USB_MSC_API/UsbMsc.h"
#include "../USB_Common/usb.h"
#include <descriptors.h>
#include <string.h>

#ifdef _MSC_

/*Macros to indicate data direction */
#define DIRECTION_IN    0x80
#define DIRECTION_OUT   0x00

/*Buffer pointers passed by application */
extern __no_init tEDB __data16 tInputEndPointDescriptorBlock[];
extern struct _MscState MscState;

BYTE Scsi_Verify_CBW ();

/*----------------------------------------------------------------------------+
 | Functions                                                                  |
 +----------------------------------------------------------------------------*/
VOID Msc_ResetStateMachine (VOID)
{
    MscState.bMscSendCsw = FALSE;
    MscState.Scsi_Residue = 0;
    MscState.Scsi_Status = SCSI_PASSED;             /*Variable to track command status */
    MscState.bMcsCommandSupported = TRUE;           /*Flag to indicate read/write command is recieved from host */
    MscState.bMscCbwReceived = 0;                   /*Flag to inidicate whether any CBW recieved from host*/
    MscState.bMscSendCsw = FALSE;
    MscState.isMSCConfigured = FALSE;
    MscState.bUnitAttention = FALSE;
    MscState.bMscCbwFailed = FALSE;
    MscState.bMscResetRequired = FALSE;
	MscState.stallEndpoint = FALSE;
}

//----------------------------------------------------------------------------
/*This is the core function called by application to handle the MSC SCSI state
 * machine */
BYTE USBMSC_poll ()
{
    BYTE edbIndex;

    edbIndex = stUsbHandle[MSC0_INTFNUM].edb_Index;

    //check if currently transmitting data..
    if (MscReadControl.bReadProcessing == TRUE){
        BYTE bGIE;
        bGIE  = (__get_SR_register() & GIE);        //save interrupt status
        //atomic operation - disable interrupts
        __disable_interrupt();                      //Disable global interrupts
        if ((MscReadControl.dwBytesToSendLeft == 0) &&
            (MscReadControl.lbaCount == 0)){
            //data is no more processing - clear flags..
            MscReadControl.bReadProcessing = FALSE;
            __bis_SR_register(bGIE);                //restore interrupt status
        } else {
            if (!(tInputEndPointDescriptorBlock[edbIndex].bEPCNF &
                  EPCNF_STALL)){                    //if it is not stalled - contiune communication
                USBIEPIFG |= 1 << (edbIndex + 1);   //trigger IN interrupt to finish data tranmition
            }
            __bis_SR_register(bGIE);                //restore interrupt status
            return (kUSBMSC_processBuffer);
        }
    }

    if (MscState.isMSCConfigured == FALSE){
        return (kUSBMSC_okToSleep);
    }

    if (!MscState.bMscSendCsw){
        if (MscState.bMscCbwReceived){
            if (Scsi_Verify_CBW() == SUCCESS){
                //Successful reception of CBW
                //Parse the CBW opcode and invoke the right command handler function
                Scsi_Cmd_Parser(MSC0_INTFNUM);
                MscState.bMscSendCsw = TRUE;
            }
            MscState.bMscCbwReceived = FALSE;       //CBW is performed!
        } else {
            return (kUSBMSC_okToSleep);
        }
        //check if any of out pipes has pending data and trigger interrupt

        if ((MscWriteControl.pCT1 != NULL)   &&
            ((*MscWriteControl.pCT1 & EPBCNT_NAK ) ||
             (*MscWriteControl.pCT2 & EPBCNT_NAK ))){
            USBOEPIFG |= 1 << (edbIndex + 1);       //trigger OUT interrupt again
            return (kUSBMSC_processBuffer);            //do not asleep, as data is coming in
            //and follow up data perform will be required.
        }
    }

    if (MscState.bMscSendCsw){
        if (MscState.bMcsCommandSupported == TRUE){
            //watiting till transport is finished!
            if ((MscWriteControl.bWriteProcessing == FALSE) &&
                (MscReadControl.bReadProcessing == FALSE) &&
                (MscReadControl.lbaCount == 0)){
                //Send CSW
                if (SUCCESS == Scsi_Send_CSW(MSC0_INTFNUM)){
                    MscState.bMscSendCsw = FALSE;
                    return (kUSBMSC_okToSleep);
                }
            }		
            else {
            	MSCFromHostToBuffer();
            }
        }
    }

    return (kUSBMSC_processBuffer);                 //When MscState.bMcsCommandSupported = FALSE, bReadProcessing became true, and
                                                    //bWriteProcessing = true.
}

#endif //_MSC_
/*----------------------------------------------------------------------------+
 | End of source file                                                          |
 +----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

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
 * ======== UsbMscScsi.c ========
 */
/*----------------------------------------------------------------------------+
 | Includes                                                                    |
 +----------------------------------------------------------------------------*/
#include "../USB_Common/types.h"
#include "../USB_Common/device.h"
#include "../USB_Common/defMSP430USB.h"
#include "../USB_Common/usb.h"
#include "../USB_MSC_API/UsbMscScsi.h"
#include "../USB_MSC_API/UsbMsc.h"
#include <descriptors.h>
#include <string.h>

#ifdef _MSC_

/*----------------------------------------------------------------------------+
 | Internal Definitions                                                        |
 +----------------------------------------------------------------------------*/
//Error codes
#define RESCODE_CURRENT_ERROR                    0x70

#define S_NO_SENSE                               0x00
#define S_NOT_READY                              0x02
#define S_MEDIUM_ERROR                           0x03
#define S_ILLEGAL_REQUEST                        0x05
#define S_UNITATTN                               0x06
#define S_WRITE_PROTECTED                        0x07
#define S_ABORTED_COMMAND                        0x0B

#define ASC_NOT_READY                            0x04
#define ASCQ_NOT_READY                           0x03

#define ASC_MEDIUM_NOT_PRESENT                   0x3A
#define ASCQ_MEDIUM_NOT_PRESENT                  0x00

#define ASC_INVALID_COMMAND_OP_CODE              0x20
#define ASCQ_INVALID_COMMAND_OP_CODE             0x00

#define ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE   0x21
#define ASCQ_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE  0x00

#define ASC_INVALID_FIELD_IN_CDB                 0x24
#define ASCQ_INVALID_FIELD_IN_CDB                0x00

#define ASC_INVALID_PARAMETER_LIST               0x26
#define ASCQ_INVALID_PARAMETER_LIST              0x02

#define ASC_ABORTED_DATAPHASE_ERROR              0x4B
#define ASCQ_ABORTED_DATAPHASE_ERROR             0x00

#define ASC_ILLEGAL_REQUEST                      0x20
#define ASCQ_ILLEGAL_REQUEST                     0x00

#define ASC_UNITATTN_READY_NOTREADY              0x28
#define ASCQ_UNITATTN_READY_NOTREADY             0x00

#define ASC_WRITE_PROTECTED                      0X27
#define ASCQ_WRITE_PROTECTED                     0X00

#define ASC_WRITE_FAULT                          0x03
#define ASCQ_WRITE_FAULT                         0x00

#define ASC_UNRECOVERED_READ                     0x11
#define ASCQ_UNRECOVERED_READ                    0x00

#define DIRECTION_IN    0x80
#define DIRECTION_OUT   0x00

#define EP_MAX_PACKET_SIZE      0x40

VOID usbStallEndpoint (BYTE);
BYTE Scsi_Verify_CBW ();

extern struct config_struct USBMSC_config;

extern VOID *(*USB_TX_memcpy)(VOID * dest, const VOID * source, size_t count);
extern VOID *(*USB_RX_memcpy)(VOID * dest, const VOID * source, size_t count);

extern __no_init tEDB __data16 tInputEndPointDescriptorBlock[];
extern __no_init tEDB __data16 tOutputEndPointDescriptorBlock[];
/*----------------------------------------------------------------------------+
 | Global Variables                                                            |
 +----------------------------------------------------------------------------*/

struct _MscWriteControl MscWriteControl;
struct _MscReadControl MscReadControl;
struct _MscControl MscControl[MSC_MAX_LUN_NUMBER] = {0};

/* Structure internal to stack for maintaining LBA info,buffer address etc */
USBMSC_RWbuf_Info sRwbuf;

__no_init CBW McsCbw;
__no_init CSW McsCsw;

struct _MscState MscState;

/*----------------------------------------------------------------------------+
 | Initiliazing Command data                                                   |
 +----------------------------------------------------------------------------*/
BYTE Scsi_Standard_Inquiry_Data[256];

REQUEST_SENSE_RESPONSE RequestSenseResponse;

struct _Scsi_Read_Capacity Scsi_Read_Capacity_10[MSC_MAX_LUN_NUMBER];

const struct _Report_Luns Report_Luns =  {{0x02,0x00,0x00,0x00},
                                          {0x00,0x00,0x00,0x00},
                                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                           0x00}};

BYTE Scsi_Mode_Sense_6[SCSI_MODE_SENSE_6_CMD_LEN] = {0x03,0,0,0 };              //No mode sense parameter

BYTE Scsi_Mode_Sense_10[SCSI_MODE_SENSE_10_CMD_LEN] = {0,0x06,0,0,0,0,0,0 };    //No mode sense parameter

BYTE Scsi_Read_Format_Capacity[SCSI_READ_FORMAT_CAPACITY_CMD_LEN] =
{0x00,0x00,0x00,0x08,0x01,0x00,0x00,0x00,0x03,0x00,0x02,0x00};

/*Default values initialized for SCSI Inquiry data */
const BYTE bScsi_Standard_Inquiry_Data[SCSI_SCSI_INQUIRY_CMD_LEN] = {
#ifdef CDROM_SUPPORT
	0x05,                                                                       //Peripheral qualifier & peripheral device type
#else
	0x00,                                                                       //Peripheral qualifier & peripheral device type
#endif
	0x80,                                                                       //Removable medium
    0x02,                                                                       //Version of the standard (SPC-2)
    0x02,                                                                       //No NormACA, No HiSup, response data format=2
    0x1F,                                                                       //No extra parameters
    0x00,                                                                       //No flags
    0x00,                                                                       //0x80 => BQue => Basic Task Management supported
    0x00,                                                                       //No flags
    /* 'T','I',' ',' ',' ',' ',' ',' ',
     * 'M','a','s','s',' ','S','t','o','r','a','g','e', */
};

#ifdef CDROM_SUPPORT

/* SCSI TOC Record - Pg.459 of mmc6r02g.pdf */
const BYTE Scsi_Read_TOC_PMA_ATIP_F1[Scsi_Read_TOC_PMA_ATIP_F1_LEN] = {
                0x00, 0x12,                  // Length
                0x01,                        // First Track
                0x01,                        // Last Track

                0x00,                        // Reserved
                0x14,                        // ADR/CTL
                0x01,                        // Track Number
                0x00,                        // Reserved
                0x00, 0x00, 0x02, 0x00,      // Track Address (TIME Form)
                0x00,0x00,0x00,0x00,		 // Padding
                0x00,0x00,0x00,0x00
}; 

const BYTE Scsi_Read_TOC_PMA_ATIP_F2[Scsi_Read_TOC_PMA_ATIP_F2_LEN] = {
                0x00, 0x2E,                  // Length
                0x01,                        // First Track
                0x01,                        // Last Track
                0x01,                        // Reserved
                0x14,                        // ADR/CTL
                0x00,                        // Track Number
                0xA0,                        // Reserved
                0x00, 0x00, 0x00, 0x00,      // Track Address (TIME Form)
                0x01,0x00,0x00,0x01,		 // Padding/Descriptors
                0x14,0x00,0xA1,0x00,
                0x00,0x00,0x00,0x01,
                0x00,0x00,0x01,0x14,
                0x00,0xA2,0x00,0x00,
                0x00,0x00,0x1C,0x35,
                0x30,0x01,0x14,0x00,
                0x01,0x00,0x00,0x00,
                0x00,0x00,0x02,0x00
}; 

/* GET_CONFIGURATION Response Pg. 312 of mmc6r02g.pdf */
const BYTE Scsi_Get_Configuration_Descriptor[SCSI_GET_CONFIGURATION_LEN] = {

                /* Feature Header */
                0x00,0x00,0x00,0x00         // Length
};

/* EVENT STATUS Response Pg. 316 of mmc6r02g.pdf */
const BYTE Scsi_Event_Status_Descriptor[SCSI_EVENT_STATUS_LEN] = {

                /* Feature Header */
                0x00,0x06,                  // Event Descriptor Length
                0x04,                       // NEA/Reserved/Notification Class
                0x54,                       // Supported Event Classes
                0x02,                       // Reserved/Event Code
                0x02,
                0x00,0x00
};


/* READ_DISC_INFORMATION Response Pg. 374 of mmc6r02g.pdf  */
const BYTE Scsi_Disc_Information_Descriptor[SCSI_READ_DISC_INFORMATION_LEN] = {

                0x00,0x00,                      // Disc Information Length
                0x00,                           // Disc Information Type, Non-Erasable, Last Session, Finalized
                0x00,                           // First Track on Disc
                0x00,                           // Number of Sessions
                0x00,                           // First Track Number in Last Session
                0x00,                           // Last Track Number in Last Session
                0x00,                           // BG/Barcode/ID Disable
                0x00,                           // Disc Type (CD-ROM)
                0x00,                           // Number of Sessions (MSB)
                0x00,                           // First Track Number in Last Session (MSB)
                0x00,                           // Last Track Number in Last Sessions (MSB)
                0x00,0x00,0x00,0x00,            // Disc ID
                0x00,0x00,0x00,0x00,            // Last Session Lead-In Address
                0x00,0x00,0x00,0x00,            // Last Lead-Out Start Address
                0x00,0x00,0x00,0x00,            // Bar Code (Not Supported)
                0x00,0x00,0x00,0x00,
                0x00,                           // Disc Application Code (Not Supported)
                0x00,0x00,0x00                   // No OPC Entries
};

VOID Scsi_Read_TocPmaAtip(BYTE intfNum);
VOID Scsi_Get_Configuration(BYTE intfNum);
VOID Scsi_Event_Status_Notification(BYTE intfNum);
VOID Scsi_Read_Disc_Information(BYTE intfNum);

#endif
/*----------------------------------------------------------------------------+
 | Functions                                                                   |
 +----------------------------------------------------------------------------*/
VOID Reset_RequestSenseResponse (VOID)
{
    int i;

    RequestSenseResponse.ResponseCode = RESCODE_CURRENT_ERROR;
    RequestSenseResponse.VALID = 0;                                             //no data in the information field
    RequestSenseResponse.Obsolete = 0x00;
    RequestSenseResponse.SenseKey = S_NO_SENSE;
    RequestSenseResponse.ILI = 0;
    RequestSenseResponse.EOM = 0;
    RequestSenseResponse.FILEMARK = 0;
    RequestSenseResponse.Information[0] = 0x00;
    RequestSenseResponse.Information[1] = 0x00;
    RequestSenseResponse.Information[2] = 0x00;
    RequestSenseResponse.Information[3] = 0x00;
    RequestSenseResponse.AddSenseLen = 0x0a;
    RequestSenseResponse.CmdSpecificInfo[0] = 0x00;
    RequestSenseResponse.CmdSpecificInfo[1] = 0x00;
    RequestSenseResponse.CmdSpecificInfo[2] = 0x00;
    RequestSenseResponse.CmdSpecificInfo[3] = 0x00;
    RequestSenseResponse.ASC = 0x00;
    RequestSenseResponse.ASCQ = 0x00;
    RequestSenseResponse.FRUC = 0x00;
    RequestSenseResponse.SenseKeySpecific[0] = 0x00;
    RequestSenseResponse.SenseKeySpecific[1] = 0x00;
    RequestSenseResponse.SenseKeySpecific[2] = 0x00;
    for (i = 0; i < 14; i++){
        RequestSenseResponse.padding[i] = 0x00;
    }
}

//----------------------------------------------------------------------------

BYTE Check_CBW (BYTE intfNum,BYTE Dir_Dev_Exp, DWORD Bytes_Dev_Exp)
{
    if (McsCbw.CBWCB[0] == SCSI_INQUIRY || McsCbw.CBWCB[0] ==
        SCSI_REQUEST_SENSE){
        return (SUCCESS);
    }

    if (Dir_Dev_Exp == McsCbw.bmCBWFlags){                  //all is right. Host is sending direction as expected by device
        if (McsCbw.dCBWDataTransferLength < Bytes_Dev_Exp){ //Host expect less data to send or receive then device
            MscState.Scsi_Status = SCSI_PHASE_ERROR;
            MscState.Scsi_Residue = 0 ;
            if (McsCbw.bmCBWFlags == DIRECTION_IN){
                usbStallInEndpoint(intfNum);
            } else {
                usbStallOutEndpoint(intfNum);
            }
        } else if ((McsCbw.dCBWDataTransferLength > Bytes_Dev_Exp) &&
                   (McsCbw.CBWCB[0] != SCSI_MODE_SENSE_6) &&
                   (McsCbw.CBWCB[0] != SCSI_MODE_SENSE_10) &&
                   (McsCbw.CBWCB[0] != SCSI_READ_TOC_PMA_ATIP)){
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = McsCbw.dCBWDataTransferLength -
                                    Bytes_Dev_Exp;
            if (McsCbw.bmCBWFlags == DIRECTION_IN){
                usbStallInEndpoint(intfNum);
            } else {
                usbStallOutEndpoint(intfNum);
            }
        } else {
            return ( SUCCESS) ;
        }
    } else {    //Direction mismatch
        MscState.Scsi_Residue = McsCbw.dCBWDataTransferLength;
        MscState.Scsi_Status = SCSI_FAILED;
        if (McsCbw.bmCBWFlags == DIRECTION_IN){
            usbStallInEndpoint(intfNum);
        } else if ((McsCbw.bmCBWFlags == DIRECTION_OUT) &&
                   (McsCbw.CBWCB[0] == SCSI_READ_10)){
            usbStallOutEndpoint(intfNum);
        }
    }

    //Indicates a generic failure. Read/write failure/sense data is handled separately
    if (MscState.Scsi_Status != SCSI_READWRITE_FAIL){
        RequestSenseResponse.ResponseCode = RESCODE_CURRENT_ERROR;
        RequestSenseResponse.VALID = 1;
        RequestSenseResponse.AddSenseLen = 0xA0;
        RequestSenseResponse.SenseKey = S_ILLEGAL_REQUEST;
        RequestSenseResponse.ASC = ASC_INVALID_PARAMETER_LIST;
        RequestSenseResponse.ASCQ = ASCQ_INVALID_PARAMETER_LIST;
    }

    return (FAILURE);
}

//----------------------------------------------------------------------------
BYTE Scsi_Verify_CBW ()
{
    /*(5.2.3) Devices must consider the CBW meaningful if no reserved bits
     * are set, the LUN number indicates a LUN supported by the device,
     * bCBWCBLength is in the range of 1 through 16, and the length and
     * content of the CBWCB field are appropriate to the SubClass.
     */
    if ((MscState.bMscResetRequired || McsCbw.dCBWSignature !=
         CBW_SIGNATURE) ||              //Check for correct CBW signature
        ((McsCbw.bmCBWFlags != DIRECTION_IN && McsCbw.bmCBWFlags !=
          DIRECTION_OUT) ||
         (McsCbw.bCBWLUN & 0xF0) ||     //Upper bits have to be zero
         (McsCbw.bCBWCBLength > 16))){  //maximum length is 16
        MscState.bMscResetRequired = TRUE;
        usbStallEndpoint(MSC0_INTFNUM);
        usbClearOEPByteCount(MSC0_INTFNUM);
        MscState.Scsi_Status = SCSI_FAILED;
        MscState.Scsi_Residue = 0;
        return (FAILURE);
    }
    MscState.Scsi_Status = SCSI_PASSED;
    return (SUCCESS);
}

//----------------------------------------------------------------------------
BYTE Scsi_Send_CSW (BYTE intfNum)
{
    BYTE retval = 0;

    //Populate the CSW to be sent
    McsCsw.dCSWSignature = CSW_SIGNATURE;
    McsCsw.dCSWTag = McsCbw.dCBWTag;
    McsCsw.bCSWStatus = MscState.Scsi_Status;
    McsCsw.dCSWDataResidue = MscState.Scsi_Residue;
    retval = MscSendData((PBYTE)&McsCsw, CSW_LENGTH);   //Sending CSW
    MscState.Scsi_Status = SCSI_PASSED;
    return (retval);
}

//----------------------------------------------------------------------------

VOID Scsi_Inquiry (BYTE intfNum)
{
    //int index;

    //clear the inquiry array
    memset(Scsi_Standard_Inquiry_Data, 256, 0);
    //copy the inquiry data from flash to RAM

    memcpy(Scsi_Standard_Inquiry_Data,
        bScsi_Standard_Inquiry_Data,
        SCSI_SCSI_INQUIRY_CMD_LEN);



    //get the values from USB_Config
    Scsi_Standard_Inquiry_Data[1] = USBMSC_config.LUN[McsCbw.bCBWLUN].removable;
    memcpy(&Scsi_Standard_Inquiry_Data[8],
        USBMSC_config.LUN[McsCbw.bCBWLUN].t10VID,
        8);
    memcpy(&Scsi_Standard_Inquiry_Data[16],
        USBMSC_config.LUN[McsCbw.bCBWLUN].t10PID,
        16);
    memcpy(&Scsi_Standard_Inquiry_Data[32],
        USBMSC_config.LUN[McsCbw.bCBWLUN].t10rev,
        4);

    if (McsCbw.dCBWDataTransferLength < SCSI_SCSI_INQUIRY_CMD_LEN){
        if (McsCbw.dCBWDataTransferLength == 0){
            MscState.Scsi_Residue = 0;
            return;
        }
        if (SUCCESS ==
            MscSendData((PBYTE)Scsi_Standard_Inquiry_Data,
                McsCbw.dCBWDataTransferLength)){
            MscState.Scsi_Residue = 0;
        } else {
            MscState.Scsi_Status = SCSI_FAILED;
        }
    } else if (McsCbw.dCBWDataTransferLength > SCSI_SCSI_INQUIRY_CMD_LEN){
        Reset_RequestSenseResponse();

        RequestSenseResponse.ResponseCode = RESCODE_CURRENT_ERROR;
        RequestSenseResponse.VALID = 1;
        RequestSenseResponse.SenseKey = S_ILLEGAL_REQUEST;
        RequestSenseResponse.ASC = ASC_INVALID_FIELD_IN_CDB;
        RequestSenseResponse.ASCQ = ASCQ_INVALID_FIELD_IN_CDB;
        usbStallInEndpoint(intfNum);
        MscState.Scsi_Status = SCSI_FAILED;
    } else {
        if (SUCCESS ==
            MscSendData((PBYTE)Scsi_Standard_Inquiry_Data,
                SCSI_SCSI_INQUIRY_CMD_LEN)){
            MscState.Scsi_Residue = 0;
        } else {
            MscState.Scsi_Status = SCSI_FAILED;
        }
    }
}

//----------------------------------------------------------------------------

VOID Scsi_Read_Capacity10 (BYTE intfNum)
{
    if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_READ_CAPACITY_CMD_LEN)){
        return;
    }
    if (SUCCESS !=
        MscSendData( (PBYTE)&Scsi_Read_Capacity_10[McsCbw.bCBWLUN],
            SCSI_READ_CAPACITY_CMD_LEN)){
        MscState.Scsi_Status = SCSI_FAILED;
    }
}


//----------------------------------------------------------------------------

VOID Scsi_Read10 (BYTE intfNum)
{
    WORD wLBA_len;
    unsigned short bGIE;
    DWORD dLBA;

    /* Get first LBA: convert 4 bytes into DWORD */
    dLBA = McsCbw.CBWCB[2];
    dLBA <<= 8;
    dLBA += McsCbw.CBWCB[3];
    dLBA <<= 8;
    dLBA += McsCbw.CBWCB[4];
    dLBA <<= 8;
    dLBA += McsCbw.CBWCB[5];

    /* Get number of requested logical blocks */
    wLBA_len = McsCbw.CBWCB[7];
    wLBA_len <<= 8;
    wLBA_len += McsCbw.CBWCB[8];

    if (FAILURE ==
        Check_CBW( intfNum, DIRECTION_IN, ((DWORD)wLBA_len) *
            MscControl[McsCbw.bCBWLUN].lbaSize)){
        return;
    }

    bGIE  = (__get_SR_register() & GIE);    //save interrupt status
    __disable_interrupt();

    //Populating stack internal structure required for READ/WRITE
    MscReadControl.lba = dLBA;              //the first LBA number.
    MscReadControl.lbaCount = wLBA_len;     //how many LBAs to read.
    MscReadControl.XorY = 0;

    sRwbuf.bufferAddr = MscControl[McsCbw.bCBWLUN].xBufferAddr;
    sRwbuf.lun = McsCbw.bCBWLUN;

    //set LBA count
    sRwbuf.lbCount = wLBA_len >
        MscControl[McsCbw.bCBWLUN].lbaBufCapacity ? 
		MscControl[McsCbw.bCBWLUN].lbaBufCapacity : wLBA_len;
    sRwbuf.operation = kUSBMSC_READ;
    sRwbuf.lba = dLBA;
    sRwbuf.returnCode = kUSBMSC_RWSuccess;
    sRwbuf.XorY = 0;
    sRwbuf.xBufFull = 0;
    sRwbuf.xWordCnt = 0;
    sRwbuf.yBufFull = 0;
    sRwbuf.yWordCnt = 0;
    sRwbuf.bufferProcessed = 0;
    sRwbuf.firstFlag = 0;
    //buffer is prepared, let user's Application fill data.
    USBMSC_handleBufferEvent();

    __bis_SR_register(bGIE);                //restore interrupt status
}

//----------------------------------------------------------------------------

VOID Scsi_Write10 (BYTE intfNum)
{
    WORD wLBA_len;
    unsigned short bGIE;
    /* Get first LBA: convert 4 bytes into DWORD */
    DWORD dLBA = McsCbw.CBWCB[2];

    dLBA <<= 8;
    dLBA += McsCbw.CBWCB[3];
    dLBA <<= 8;
    dLBA += McsCbw.CBWCB[4];
    dLBA <<= 8;
    dLBA += McsCbw.CBWCB[5];

    /* Get number of requested logical blocks */
    wLBA_len = McsCbw.CBWCB[7];
    wLBA_len <<= 8;
    wLBA_len += McsCbw.CBWCB[8];

    if (FAILURE ==
        Check_CBW(intfNum,DIRECTION_OUT,((DWORD)wLBA_len) *
            MscControl[McsCbw.bCBWLUN].lbaSize)){
        return;
    }
    bGIE = (__get_SR_register() & GIE);         //save interrupt status
    __disable_interrupt();

    //calculate the whole size to receive (Host to MSP430)
    MscWriteControl.dwBytesToReceiveLeft = (DWORD)wLBA_len *
        MscControl[McsCbw.bCBWLUN].lbaSize;
    MscWriteControl.pUserBuffer = MscControl[McsCbw.bCBWLUN].xBufferAddr;
    MscWriteControl.wFreeBytesLeft =
        MscControl[McsCbw.bCBWLUN].wMscUserBufferSize;

    /*Populating stack internal structure required for READ/WRITE */

    MscWriteControl.bWriteProcessing = TRUE;    //indicate that we are in WRITE phase
    MscWriteControl.lba = dLBA;
    MscWriteControl.wCurrentByte = 0;           //reset internal variable
    MscWriteControl.lbaCount = 0;               //reset internal variable
    MscWriteControl.XorY = 0;

    sRwbuf.lun = McsCbw.bCBWLUN;
    sRwbuf.operation = 0;
    sRwbuf.lba = 0;
    sRwbuf.lbCount = 0;
    sRwbuf.bufferAddr = MscControl[McsCbw.bCBWLUN].xBufferAddr;
    sRwbuf.returnCode = 0;
    sRwbuf.XorY = 0;
    sRwbuf.xBufFull = 0;
    sRwbuf.yBufFull = 0;
    sRwbuf.bufferProcessed = 0;
    sRwbuf.firstFlag = 0;
    sRwbuf.xlba = 0;
    sRwbuf.xlbaCount = 0;
    sRwbuf.ylba = 0;
    sRwbuf.ylbaCount = 0;

    __bis_SR_register(bGIE);                    //restore interrupt status
}

//----------------------------------------------------------------------------

VOID Scsi_Mode_Sense6 (BYTE intfNum)
{
    if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_MODE_SENSE_6_CMD_LEN)){
        return;
    }
    /* Fix for SDOCM00077834 - Set WP bit. WP bit is BIT7 in byte 3 */
    Scsi_Mode_Sense_6[2] |= (MscControl[McsCbw.bCBWLUN].bWriteProtected << 0x7);

    if (SUCCESS !=
        MscSendData((PBYTE)Scsi_Mode_Sense_6, SCSI_MODE_SENSE_6_CMD_LEN)){
        MscState.Scsi_Status = SCSI_FAILED;
    }
}

//----------------------------------------------------------------------------

VOID Scsi_Mode_Sense10 (BYTE intfNum)
{
    if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_MODE_SENSE_10_CMD_LEN)){
        return;
    }
    /* Fix for SDOCM00077834 - Set WP bit. WP bit is BIT7 in byte 3 */
    Scsi_Mode_Sense_10[4] |= (MscControl[McsCbw.bCBWLUN].bWriteProtected << 0x7);

    if (SUCCESS !=
        MscSendData((PBYTE)Scsi_Mode_Sense_10, SCSI_MODE_SENSE_10_CMD_LEN)){
        MscState.Scsi_Status = SCSI_FAILED;
    }
}

//----------------------------------------------------------------------------

VOID Scsi_Request_Sense (BYTE intfNum)
{
    if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_REQ_SENSE_CMD_LEN)){
        return;
    }

    //If there is attention needed, setup the request sense response. The
    //bUnitAttention flag is set in USBMSC_updateMediaInfo() when the volume
    //is removed or inserted. Note that the response is different for the
    //removed and inserted case.
    if (MscState.bUnitAttention == TRUE){
        //Check if the volume was removed.
        if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
            kUSBMSC_MEDIA_NOT_PRESENT){
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_NOT_READY;
            RequestSenseResponse.ASC = ASC_MEDIUM_NOT_PRESENT;
            RequestSenseResponse.ASCQ = ASCQ_MEDIUM_NOT_PRESENT;
        }
        //Otherwise it was inserted.
        else {
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_UNITATTN;
            RequestSenseResponse.ASC = ASC_UNITATTN_READY_NOTREADY;
            RequestSenseResponse.ASCQ = ASCQ_UNITATTN_READY_NOTREADY;
        }
    }

    if (McsCbw.dCBWDataTransferLength < SCSI_REQ_SENSE_CMD_LEN){
        if (SUCCESS ==
            MscSendData((PBYTE)&RequestSenseResponse,
                McsCbw.dCBWDataTransferLength)){
            MscState.Scsi_Residue = 0;
        } else {
            MscState.Scsi_Status = SCSI_FAILED;
        }
    } else if (McsCbw.dCBWDataTransferLength > SCSI_REQ_SENSE_CMD_LEN){
        RequestSenseResponse.AddSenseLen +=
            (McsCbw.dCBWDataTransferLength -  SCSI_REQ_SENSE_CMD_LEN);
        if (SUCCESS ==
            MscSendData((PBYTE)&RequestSenseResponse,
                McsCbw.dCBWDataTransferLength)){
            MscState.Scsi_Residue = 0;
        } else {
            MscState.Scsi_Status = SCSI_FAILED;
        }
    } else {
        if (SUCCESS ==
            MscSendData((PBYTE)&RequestSenseResponse,SCSI_REQ_SENSE_CMD_LEN)){
            MscState.Scsi_Residue = 0;
        } else {
            MscState.Scsi_Status = SCSI_FAILED;
        }
    }

    //Clear the bUnitAttention flag after the response was properly sent via
    //MscSendData().
    if (MscState.bUnitAttention == TRUE){
        MscState.bUnitAttention = FALSE;
    }
}

//----------------------------------------------------------------------------

VOID Scsi_Test_Unit_Ready (BYTE intfNum)
{
    if (SUCCESS != Check_CBW(intfNum,DIRECTION_OUT,0)){
        MscState.Scsi_Status = SCSI_FAILED;
    }

    Reset_RequestSenseResponse();
}

//----------------------------------------------------------------------------

VOID Scsi_Unknown_Request (BYTE intfNum)
{
    Reset_RequestSenseResponse();

    RequestSenseResponse.ResponseCode = RESCODE_CURRENT_ERROR;
    RequestSenseResponse.VALID = 1;
    RequestSenseResponse.AddSenseLen = 0xA0;
    RequestSenseResponse.SenseKey = S_ILLEGAL_REQUEST;
    RequestSenseResponse.ASC = ASC_INVALID_COMMAND_OP_CODE;
    RequestSenseResponse.ASCQ = ASCQ_INVALID_COMMAND_OP_CODE;
    MscState.Scsi_Residue = 0;
    MscState.Scsi_Status = SCSI_FAILED;

    if (McsCbw.dCBWDataTransferLength && (McsCbw.bmCBWFlags == DIRECTION_IN)){
        MscState.bMcsCommandSupported = FALSE;
        usbStallInEndpoint(intfNum);
    }
    if (McsCbw.dCBWDataTransferLength && (McsCbw.bmCBWFlags == DIRECTION_OUT)){
        MscState.bMcsCommandSupported = FALSE;
        usbStallOutEndpoint(intfNum);
    }
}

//----------------------------------------------------------------------------

VOID Scsi_Report_Luns (BYTE intfNum)
{
    if (FAILURE ==
        Check_CBW( intfNum, DIRECTION_IN, SCSI_REPORT_LUNS_CMD_LEN)){
        return;
    }
    if (SUCCESS !=
        MscSendData( (PBYTE)&Report_Luns, SCSI_REPORT_LUNS_CMD_LEN)){
        MscState.Scsi_Status = SCSI_FAILED;
    }
}

//----------------------------------------------------------------------------

BYTE Scsi_Cmd_Parser (BYTE intfNum)
{
    BYTE ret = kUSBMSC_cmdBeingProcessed;

    //MscState.Scsi_Status = SCSI_FAILED;
    MscState.Scsi_Residue = McsCbw.dCBWDataTransferLength;

    //fails the commands during UNIT ATTENTION
    if ((MscState.bUnitAttention) && (McsCbw.CBWCB[0] != SCSI_INQUIRY) &&
        (McsCbw.CBWCB[0] != SCSI_REQUEST_SENSE)){
        MscState.Scsi_Status = SCSI_FAILED;
        return (kUSB_generalError);
    }

    if (!McsCbw.bCBWCBLength){
        return (kUSB_generalError);
    }

    switch (McsCbw.CBWCB[0])                                        //SCSI Operation code
    {
        case SCSI_READ_10:
            if (MscControl[McsCbw.bCBWLUN].xBufferAddr == NULL){    //Check for null address.
                ret = kUSB_generalError;
                SET_RequestsenseNotReady();
                MscState.Scsi_Status = SCSI_FAILED;
                usbStallInEndpoint(intfNum);
                break;
            }

            if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                kUSBMSC_MEDIA_NOT_PRESENT){                         //Check for media present. Do this for any command that accesses
                                                                    //media.
                ret = kUSB_generalError;
                SET_RequestsenseMediaNotPresent();
                usbStallInEndpoint(intfNum);
                break;
            }
            Scsi_Read10(intfNum);
            break;

        case SCSI_WRITE_10:
            if (MscControl[McsCbw.bCBWLUN].xBufferAddr == NULL){    //Check for null address.
                ret = kUSB_generalError;
                SET_RequestsenseNotReady();
                MscState.Scsi_Status = SCSI_FAILED;
                break;
            }

            if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                kUSBMSC_MEDIA_NOT_PRESENT){                         //Check for media present. Do this for any command that accesses
                                                                    //media.
                ret = kUSB_generalError;
                SET_RequestsenseMediaNotPresent();
                usbStallOutEndpoint(intfNum);
                break;
            }

            if (MscControl[McsCbw.bCBWLUN].bWriteProtected){        //Do this only for WRITE
                ret = kUSB_generalError;
                                                                    //Set REQUEST SENSE with "write protected"
                Reset_RequestSenseResponse();
                RequestSenseResponse.VALID = 1;
                RequestSenseResponse.SenseKey = S_WRITE_PROTECTED;
                RequestSenseResponse.ASC = ASC_WRITE_PROTECTED;
                RequestSenseResponse.ASCQ = ASCQ_WRITE_PROTECTED;
                MscWriteControl.bWriteProcessing = FALSE;
                                                                    //Send CSW with error status
                MscState.Scsi_Residue = 1;
                MscState.Scsi_Status = SCSI_FAILED;
                usbStallOutEndpoint(intfNum);
                break;
            }

            Scsi_Write10(intfNum);
            break;

        case START_STOP_UNIT:
        case PREVENT_ALLW_MDM:
        case SCSI_MODE_SELECT_10:
        case SCSI_MODE_SELECT_6:
        case SCSI_TEST_UNIT_READY:
            if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                kUSBMSC_MEDIA_NOT_PRESENT){                         //Check for media present. Do this for any command that accesses
                                                                    //media.
                ret = kUSB_generalError;
                SET_RequestsenseMediaNotPresent();
                break;
            }
            Scsi_Test_Unit_Ready(intfNum);
            break;
            
        case SCSI_SET_CD_SPEED:
        	break;
        case SCSI_INQUIRY:
            Scsi_Inquiry(intfNum);
            break;

        case SCSI_MODE_SENSE_6:
            Scsi_Mode_Sense6(intfNum);
            break;

        case SCSI_MODE_SENSE_10:
            Scsi_Mode_Sense10(intfNum);
            break;

        case SCSI_READ_CAPACITY_10:
            if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                kUSBMSC_MEDIA_NOT_PRESENT){             //Check for media present. Do this for any command that accesses media.
                ret = kUSB_generalError;
                SET_RequestsenseMediaNotPresent();
                usbStallInEndpoint(intfNum);
                break;
            }
            Scsi_Read_Capacity10(intfNum);
            break;

        case SCSI_REQUEST_SENSE:
            Scsi_Request_Sense(intfNum);
            break;

        case SCSI_REPORT_LUNS:
            if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                kUSBMSC_MEDIA_NOT_PRESENT){             //Check for media present. Do this for any command that accesses media.
                ret = kUSB_generalError;
                SET_RequestsenseMediaNotPresent();
                if (McsCbw.bmCBWFlags == DIRECTION_IN){
                    usbStallInEndpoint(intfNum);
                } else {
                    usbStallOutEndpoint(intfNum);
                }
                break;
            }
            Scsi_Report_Luns(intfNum);
            break;
        case SCSI_VERIFY:
                                                        /* Fix for SDOCM00078183 */
                                                        /* NOTE: we are assuming that BYTCHK=0 and PASSing the command. */
            break;
#ifdef CDROM_SUPPORT

        case SCSI_READ_TOC_PMA_ATIP:
            if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                kUSBMSC_MEDIA_NOT_PRESENT){             //Check for media present. Do this for any command that accesses media.
                ret = kUSB_generalError;
                SET_RequestsenseMediaNotPresent();
                usbStallInEndpoint(intfNum);
                break;
            }
            Scsi_Read_TocPmaAtip(intfNum);
            break;

        case SCSI_GET_CONFIGURATION:
                if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                    kUSBMSC_MEDIA_NOT_PRESENT){             //Check for media present. Do this for any command that accesses media.
                        ret = kUSB_generalError;
                        SET_RequestsenseMediaNotPresent();
                        usbStallInEndpoint(intfNum);
                        break;
                }
                Scsi_Get_Configuration(intfNum);
                break;
        case SCSI_EVENT_STATUS:
                if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                    kUSBMSC_MEDIA_NOT_PRESENT){             //Check for media present. Do this for any command that accesses media.
                        ret = kUSB_generalError;
                        SET_RequestsenseMediaNotPresent();
                        usbStallInEndpoint(intfNum);
                        break;
                }
                Scsi_Event_Status_Notification(intfNum);
                break;

        case SCSI_READ_DISC_INFORMATION:

                if (MscControl[McsCbw.bCBWLUN].bMediaPresent ==
                    kUSBMSC_MEDIA_NOT_PRESENT){             //Check for media present. Do this for any command that accesses media.
                        ret = kUSB_generalError;
                        SET_RequestsenseMediaNotPresent();
                        usbStallInEndpoint(intfNum);
                        break;
                }

                Scsi_Read_Disc_Information(intfNum);
                break;
#endif
        default:
            ret = kUSB_generalError;
            Scsi_Unknown_Request(intfNum);
            break;
    }
    return (ret);
}

//-------------------------------------------------------------------------------------------------------
/* This function is called only from ISR(only on Input endpoint interrupt to transfer data to host)
 * This function actually performs the data transfer to host Over USB */
BOOL MSCToHostFromBuffer ()
{
    //Check if there are any pending LBAs to process
    BYTE * pEP1;
    BYTE * pEP2;
    BYTE * pCT1;
    BYTE * pCT2;
    BYTE bWakeUp = FALSE;                               //per default we do not wake up after interrupt
    BYTE edbIndex;
    BYTE bCount;

    if (MscControl[sRwbuf.lun].yBufferAddr == NULL) {
	    //Check if there are any pending data to send
	    if (MscReadControl.dwBytesToSendLeft == 0){
	        //no more data to send - clear ready busy status
	        MscReadControl.bReadProcessing = FALSE;

	        //check if more LBA to send out pending...
	        if (MscReadControl.lbaCount > 0){
	            sRwbuf.lba = MscReadControl.lba;            //update current lba
	            sRwbuf.lbCount = MscControl[sRwbuf.lun].lbaBufCapacity >
	                             MscReadControl.lbaCount ?
	                             MscReadControl.lbaCount : MscControl[sRwbuf.lun].
	                             lbaBufCapacity;            //update LBA count
	            sRwbuf.operation = kUSBMSC_READ;            //start data READ phase
	            sRwbuf.returnCode = kUSBMSC_RWSuccess;
	            sRwbuf.bufferAddr = MscControl[sRwbuf.lun].xBufferAddr;
	            sRwbuf.XorY = 0;                        //only one buffer is active
	            //buffer is prepared, let user's Application fill data.
	            USBMSC_handleBufferEvent();
	        }
	        return (TRUE);                                  //data sent out - wake up!
    	}
	}
	else {
		if ((MscReadControl.lbaCount > 0) && (sRwbuf.bufferProcessed == 1)) {
	    	if ((sRwbuf.XorY == 0) && (sRwbuf.yBufFull == 0)){
	    		sRwbuf.bufferProcessed = 0;
	    		sRwbuf.XorY = 1;
	    		sRwbuf.bufferAddr = MscControl[sRwbuf.lun].yBufferAddr;
	            sRwbuf.lba = MscReadControl.lba;            //update current lba
	            sRwbuf.lbCount = MscControl[sRwbuf.lun].lbaBufCapacity >
	                             MscReadControl.lbaCount ?
	                             MscReadControl.lbaCount : MscControl[sRwbuf.lun].
	                             lbaBufCapacity;            //update LBA count
	            sRwbuf.operation = kUSBMSC_READ;            //start data READ phase
	            sRwbuf.returnCode = kUSBMSC_RWSuccess;
	            //buffer is prepared, let user's Application fill data.
	            USBMSC_handleBufferEvent();
	    	}
	    	else if ((sRwbuf.XorY == 1) && (sRwbuf.xBufFull == 0)){
	    		sRwbuf.bufferProcessed = 0;
	    		sRwbuf.XorY = 0;
	    		sRwbuf.bufferAddr = MscControl[sRwbuf.lun].xBufferAddr;
	            sRwbuf.lba = MscReadControl.lba;            //update current lba
	            sRwbuf.lbCount = MscControl[sRwbuf.lun].lbaBufCapacity >
	                             MscReadControl.lbaCount ?
	                             MscReadControl.lbaCount : MscControl[sRwbuf.lun].
	                             lbaBufCapacity;            //update LBA count
	            sRwbuf.operation = kUSBMSC_READ;            //start data READ phase
	            sRwbuf.returnCode = kUSBMSC_RWSuccess;
	            //buffer is prepared, let user's Application fill data.
	            USBMSC_handleBufferEvent();
	    	}
	    }

	    //Check if there are any pending data to send
	    if (MscReadControl.dwBytesToSendLeft == 0){
	        //no more data to send - clear ready busy status
	        MscReadControl.bReadProcessing = FALSE;

			if (MscReadControl.XorY == 0) {
				sRwbuf.xBufFull = 0;
				sRwbuf.xWordCnt = 0;
				if (sRwbuf.yBufFull) {
					MscSendData(MscControl[sRwbuf.lun].yBufferAddr, sRwbuf.yWordCnt);
					MscReadControl.XorY = 1;
				}
			}
			else {
				sRwbuf.yBufFull = 0;
				sRwbuf.yWordCnt = 0;
				if (sRwbuf.xBufFull) {
					MscSendData(MscControl[sRwbuf.lun].xBufferAddr, sRwbuf.xWordCnt);
					MscReadControl.XorY = 0;
				}
			}

	        return (TRUE);                                  //data sent out - wake up!
	    }
	}
	

    edbIndex = stUsbHandle[MSC0_INTFNUM].edb_Index;

    //check if the endpoint is stalled = do not send data.
    if (tInputEndPointDescriptorBlock[edbIndex].bEPCNF & EPCNF_STALL){
        return (TRUE);
    }

    //send one chunk of 64 bytes
    //check what is current buffer: X or Y
    if (MscReadControl.bCurrentBufferXY == X_BUFFER){   //X is current buffer
        //this is the active EP buffer
        pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].iep_X_Buffer;
        pCT1 = &tInputEndPointDescriptorBlock[edbIndex].bEPBCTX;

        //second EP buffer
        pEP2 = (BYTE*)stUsbHandle[MSC0_INTFNUM].iep_Y_Buffer;
        pCT2 = &tInputEndPointDescriptorBlock[edbIndex].bEPBCTY;
    } else {
        //this is the active EP buffer
        pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].iep_Y_Buffer;
        pCT1 = &tInputEndPointDescriptorBlock[edbIndex].bEPBCTY;

        //second EP buffer
        pEP2 = (BYTE*)stUsbHandle[MSC0_INTFNUM].iep_X_Buffer;
        pCT2 = &tInputEndPointDescriptorBlock[edbIndex].bEPBCTX;
    }

    //how many byte we can send over one endpoint buffer
    bCount =
        (MscReadControl.dwBytesToSendLeft >
         EP_MAX_PACKET_SIZE) ? EP_MAX_PACKET_SIZE : MscReadControl.
        dwBytesToSendLeft;

    if (*pCT1 & EPBCNT_NAK){
        USB_TX_memcpy(pEP1, MscReadControl.pUserBuffer, bCount);    //copy data into IEPx X or Y buffer
        *pCT1 = bCount;                                             //Set counter for usb In-Transaction
        MscReadControl.bCurrentBufferXY =
            (MscReadControl.bCurrentBufferXY + 1) & 0x01;           //switch buffer
        MscReadControl.dwBytesToSendLeft -= bCount;
        MscReadControl.pUserBuffer += bCount;                       //move buffer pointer

        //try to send data over second buffer
        if ((MscReadControl.dwBytesToSendLeft > 0) &&               //do we have more data to send?
            (*pCT2 & EPBCNT_NAK)){                                  //if the second buffer is free?
            //how many byte we can send over one endpoint buffer
            bCount =
                (MscReadControl.dwBytesToSendLeft >
                 EP_MAX_PACKET_SIZE) ? EP_MAX_PACKET_SIZE : MscReadControl.
                dwBytesToSendLeft;
            //copy data into IEPx X or Y buffer
            USB_TX_memcpy(pEP2, MscReadControl.pUserBuffer, bCount);
            //Set counter for usb In-Transaction
            *pCT2 = bCount;
            //switch buffer
            MscReadControl.bCurrentBufferXY =
                (MscReadControl.bCurrentBufferXY + 1) & 0x01;
            MscReadControl.dwBytesToSendLeft -= bCount;
            //move buffer pointer
            MscReadControl.pUserBuffer += bCount;
        }
    } //if(*pCT1 & EPBCNT_NAK)
    return (bWakeUp);
}

//------------------------------------------------------------------------------------------------------

//This function used to initialize the sending process.
//Use this by functiosn for send CSW or send LBA
//To use only by STACK itself, not by application
//Returns: SUCCESS or FAILURE
BYTE MscSendData (const BYTE* data, WORD size)
{
    BYTE edbIndex;
    unsigned short bGIE;

    edbIndex = stUsbHandle[MSC0_INTFNUM].edb_Index;

    if (size == 0){
        return (FAILURE);
    }

    bGIE  = (__get_SR_register() & GIE);            //save interrupt status
    //atomic operation - disable interrupts
    __disable_interrupt();                          //Disable global interrupts

    //do not access USB memory if suspended (PLL off). It may produce BUS_ERROR
    if ((bFunctionSuspended) ||
        (bEnumerationStatus != ENUMERATION_COMPLETE)){
        //data can not be read because of USB suspended
        __bis_SR_register(bGIE);                    //restore interrupt status
        return (FAILURE);
    }

    if ((MscReadControl.dwBytesToSendLeft != 0) ||  //data was not sent out
        (MscReadControl.bReadProcessing == TRUE)){  //still processing previous data
        //the USB still sends previous data, we have to wait
        __bis_SR_register(bGIE);                    //restore interrupt status
        return (FAILURE);
    }

    //This function generate the USB interrupt. The data will be sent out from interrupt

    MscReadControl.bReadProcessing = TRUE;          //set reading busy status.
    MscReadControl.dwBytesToSendLeft = size;
    MscReadControl.pUserBuffer = (BYTE*)data;

    //trigger Endpoint Interrupt - to start send operation
    USBIEPIFG |= 1 << (edbIndex + 1);               //IEPIFGx;

    __bis_SR_register(bGIE);                        //restore interrupt status

    return (SUCCESS);
}

//This function copies data from OUT endpoint into user's buffer
//This function to call only from MSCFromHostToBuffer()
//Arguments:
//pEP - pointer to EP to copy from
//pCT - pointer to EP control reg
//
VOID MscCopyUsbToBuff (BYTE* pEP, BYTE* pCT)
{
    BYTE nCount;

    nCount = *pCT & (~EPBCNT_NAK);

    //how many bytes we can receive to avoid overflow
    nCount =
        (nCount >
         MscWriteControl.dwBytesToReceiveLeft) ? MscWriteControl.
        dwBytesToReceiveLeft :
        nCount;

    USB_RX_memcpy(MscWriteControl.pUserBuffer, pEP, nCount);    //copy data from OEPx X or Y buffer
    MscWriteControl.dwBytesToReceiveLeft -= nCount;
    MscWriteControl.pUserBuffer += nCount;                      //move buffer pointer
                                                                //to read rest of data next time from this place
    MscWriteControl.wFreeBytesLeft -= nCount;                   //update counter

    MscWriteControl.wCurrentByte += nCount;
    if (MscWriteControl.wCurrentByte >= MscControl[sRwbuf.lun].lbaSize){
        MscWriteControl.wCurrentByte = 0;
        MscWriteControl.lbaCount++;
    }

    //switch current buffer
    MscWriteControl.bCurrentBufferXY =
        (MscWriteControl.bCurrentBufferXY + 1) & 0x01;

    //clear NAK, EP ready to receive data
    *pCT = 0x00;
}

//------------------------------------------------------------------------------------------------------
/* This function is called only from ISR(only on Output endpoint interrupt, to recv data from host)
 * This function actually recieves the data from host Over USB */
BOOL MSCFromHostToBuffer ()
{
    BYTE * pEP1;
    BYTE nTmp1;
    BYTE bWakeUp = FALSE;                                   //per default we do not wake up after interrupt
    BYTE edbIndex;

    edbIndex = stUsbHandle[MSC0_INTFNUM].edb_Index;

	if (MscState.stallEndpoint == TRUE) {
    	tOutputEndPointDescriptorBlock[edbIndex].bEPCNF |= EPCNF_STALL;
    	return TRUE;
    }
	
    if (MscState.bMscCbwReceived == TRUE){
        //previous CBW is not performed, so exit interrupt hendler
        //and trigger it again later
        return (TRUE);                                      //true for wake up!
    }

    if (!MscWriteControl.bWriteProcessing){                 //receiving CBW
        //CBW will be received here....
        //check what is current buffer: X or Y
        if (MscWriteControl.bCurrentBufferXY == X_BUFFER){  //X is current buffer
            //this is the active EP buffer
            pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_X_Buffer;
            MscWriteControl.pCT1 =
                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX;
            MscWriteControl.pCT2 =
                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTY;
        } else {
            //this is the active EP buffer
            pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_Y_Buffer;
            MscWriteControl.pCT1 =
                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTY;
            MscWriteControl.pCT2 =
                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX;
        }

        //how many byte we can get from one endpoint buffer
        nTmp1 = *MscWriteControl.pCT1;

        if (nTmp1 & EPBCNT_NAK){
            BYTE nCount;

            //switch current buffer
            MscWriteControl.bCurrentBufferXY =
                (MscWriteControl.bCurrentBufferXY + 1) & 0x01;

            nTmp1 = nTmp1 & 0x7f;                           //clear NAK bit
            nCount = (nTmp1 > sizeof(McsCbw)) ? sizeof(McsCbw) : nTmp1;
            USB_RX_memcpy(&McsCbw, pEP1, nCount);           //copy data from OEPx X or Y buffer

            //clear NAK, EP ready to receive data
            *MscWriteControl.pCT1 = 0x00;

            //set flag and check the CBW from the usbmsc_poll
            MscState.bMscCbwReceived = TRUE;

            //second 64b buffer will be not read out here because the CBW is <64 bytes
        }

        bWakeUp = TRUE;                                     //wake up to perform CBW
        return (bWakeUp);
    }

    //if we are here - LBAs will be received
	if (MscControl[sRwbuf.lun].yBufferAddr == NULL) {

	    /*Check if there are any pending LBAs to process */
	    if (MscWriteControl.dwBytesToReceiveLeft > 0){
	        //read one chunk of 64 bytes

	        //check what is current buffer: X or Y
	        if (MscWriteControl.bCurrentBufferXY == X_BUFFER){  //X is current buffer
	            //this is the active EP buffer
	            pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_X_Buffer;
	            MscWriteControl.pCT1 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX;

	            //second EP buffer
	            MscWriteControl.pEP2 =
	                (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_Y_Buffer;
	            MscWriteControl.pCT2 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTY;
	        } else {
	            //this is the active EP buffer
	            pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_Y_Buffer;
	            MscWriteControl.pCT1 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTY;

	            //second EP buffer
	            MscWriteControl.pEP2 =
	                (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_X_Buffer;
	            MscWriteControl.pCT2 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX;
	        }

	        //how many byte we can get from one endpoint buffer
	        nTmp1 = *MscWriteControl.pCT1;

	        if ((nTmp1 & EPBCNT_NAK) &&
	            (MscWriteControl.wFreeBytesLeft >= 64)){
	            //copy data from Endpoint
	            MscCopyUsbToBuff(pEP1, MscWriteControl.pCT1);

	            nTmp1 = *MscWriteControl.pCT2;

	            //try read data from second buffer
	            if ((MscWriteControl.dwBytesToReceiveLeft > 0) &&   //do we have more data to send?
	                (MscWriteControl.wFreeBytesLeft >= 64) &&
	                (nTmp1 & EPBCNT_NAK)){                          //if the second buffer has received data?
	                //copy data from Endpoint
	                MscCopyUsbToBuff(MscWriteControl.pEP2, MscWriteControl.pCT2);
	                //MscWriteControl.pCT1 = MscWriteControl.pCT2;
	            }

	            if ((MscWriteControl.wFreeBytesLeft == 0) ||        //user's buffer is full, give it to User
	                (MscWriteControl.dwBytesToReceiveLeft == 0)){   //or no bytes to read left - give it to User
	                sRwbuf.operation = kUSBMSC_WRITE;
	                sRwbuf.lba = MscWriteControl.lba;               //copy lba number
	                MscWriteControl.lba += MscWriteControl.lbaCount;
	                sRwbuf.lbCount = MscWriteControl.lbaCount;      //copy lba count
	                MscWriteControl.wCurrentByte = 0;
	                MscWriteControl.lbaCount = 0;

		            //call event handler, we are ready with data
		            bWakeUp = USBMSC_handleBufferEvent();
	            } //if (wFreeBytesLeft == 0)
	        }
	    } //if (MscWriteControl.dwBytesToReceiveLeft > 0)
	    else {
	        //perform error handling here, if required.
	        bWakeUp = TRUE;
	    }
	}
	else {
	    //if we are here - LBAs will be received
	    if (sRwbuf.bufferProcessed == 1) {
	    	if (sRwbuf.XorY == 0) {
	    		sRwbuf.xBufFull = 0;
	    		if (sRwbuf.yBufFull) {
	    			sRwbuf.bufferProcessed = 0;
	    			sRwbuf.XorY = 1;
	    			sRwbuf.bufferAddr = MscControl[McsCbw.bCBWLUN].yBufferAddr;
	            	sRwbuf.operation = kUSBMSC_WRITE;
	            	sRwbuf.lba = sRwbuf.ylba;               //copy lba number
	            	sRwbuf.lbCount = sRwbuf.ylbaCount;      //copy lba count

	            	//call event handler, we are ready with data
	            	bWakeUp = USBMSC_handleBufferEvent();
	    		}
	    	}
	    	else {
	    		sRwbuf.yBufFull = 0;
	    		if (sRwbuf.xBufFull) {
	    			sRwbuf.bufferProcessed = 0;
	    			sRwbuf.XorY = 0;
	    			sRwbuf.bufferAddr = MscControl[McsCbw.bCBWLUN].xBufferAddr;
	            	sRwbuf.operation = kUSBMSC_WRITE;
	            	sRwbuf.lba = sRwbuf.xlba;               //copy lba number
	            	sRwbuf.lbCount = sRwbuf.xlbaCount;      //copy lba count

	            	//call event handler, we are ready with data
	            	bWakeUp = USBMSC_handleBufferEvent();
	    		}
	    	}
	    }

	    /*Check if there are any pending LBAs to process */
	    if (MscWriteControl.dwBytesToReceiveLeft > 0){
	        //read one chunk of 64 bytes

	    	if (MscWriteControl.wFreeBytesLeft == 0) {
	    		P7OUT &= ~BIT1;
	    		P7OUT &= ~BIT2;
	    		P7OUT &= ~BIT3;
				if (MscWriteControl.XorY == 0) {
					if (sRwbuf.yBufFull == 0) {
						P7OUT |= BIT1;
						P7OUT |= BIT3;
						MscWriteControl.lba += MscWriteControl.lbaCount;
						MscWriteControl.wCurrentByte = 0;
						MscWriteControl.lbaCount = 0;
						MscWriteControl.pUserBuffer = MscControl[sRwbuf.lun].yBufferAddr;
						MscWriteControl.XorY = 1;
						MscWriteControl.wFreeBytesLeft =
							MscControl[sRwbuf.lun].wMscUserBufferSize;
					}
				}
				else {
					if (sRwbuf.xBufFull == 0) {
						P7OUT |= BIT1;
						P7OUT |= BIT2;
						MscWriteControl.lba += MscWriteControl.lbaCount;
						MscWriteControl.wCurrentByte = 0;
						MscWriteControl.lbaCount = 0;
						MscWriteControl.pUserBuffer = MscControl[sRwbuf.lun].xBufferAddr;
						MscWriteControl.XorY = 0;
						MscWriteControl.wFreeBytesLeft =
							MscControl[sRwbuf.lun].wMscUserBufferSize;
					}
				}
	    	}


	        //check what is current buffer: X or Y
	        if (MscWriteControl.bCurrentBufferXY == X_BUFFER){  //X is current buffer
	            //this is the active EP buffer
	            pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_X_Buffer;
	            MscWriteControl.pCT1 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX;

	            //second EP buffer
	            MscWriteControl.pEP2 =
	                (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_Y_Buffer;
	            MscWriteControl.pCT2 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTY;
	        } else {
	            //this is the active EP buffer
	            pEP1 = (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_Y_Buffer;
	            MscWriteControl.pCT1 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTY;

	            //second EP buffer
	            MscWriteControl.pEP2 =
	                (BYTE*)stUsbHandle[MSC0_INTFNUM].oep_X_Buffer;
	            MscWriteControl.pCT2 =
	                &tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX;
	        }

	        //how many byte we can get from one endpoint buffer
	        nTmp1 = *MscWriteControl.pCT1;

	        if ((nTmp1 & EPBCNT_NAK) &&
	            (MscWriteControl.wFreeBytesLeft >= 64)){
	            //copy data from Endpoint
	            MscCopyUsbToBuff(pEP1, MscWriteControl.pCT1);

	            nTmp1 = *MscWriteControl.pCT2;

	            //try read data from second buffer
	            if ((MscWriteControl.dwBytesToReceiveLeft > 0) &&   //do we have more data to send?
	                (MscWriteControl.wFreeBytesLeft >= 64) &&
	                (nTmp1 & EPBCNT_NAK)){                          //if the second buffer has received data?
	                //copy data from Endpoint
	                MscCopyUsbToBuff(MscWriteControl.pEP2, MscWriteControl.pCT2);
	                //MscWriteControl.pCT1 = MscWriteControl.pCT2;
	            }

	            if ((MscWriteControl.wFreeBytesLeft == 0) ||        //user's buffer is full, give it to User
	                (MscWriteControl.dwBytesToReceiveLeft == 0)){   //or no bytes to read left - give it to User

	                if (sRwbuf.firstFlag == 0) {
	                	sRwbuf.firstFlag = 1;
	                	sRwbuf.operation = kUSBMSC_WRITE;
	                	sRwbuf.lba = MscWriteControl.lba;               //copy lba number
	                	sRwbuf.lbCount = MscWriteControl.lbaCount;      //copy lba count

	                	//call event handler, we are ready with data
	                	bWakeUp = USBMSC_handleBufferEvent();
	                }
	            	if (MscWriteControl.XorY == 0) {
	                	sRwbuf.xBufFull = 1;
	                	sRwbuf.xlba = MscWriteControl.lba;
	                	sRwbuf.xlbaCount = MscWriteControl.lbaCount;
	                }
	                else {
	                	sRwbuf.yBufFull = 1;
	                	sRwbuf.ylba = MscWriteControl.lba;
	                	sRwbuf.ylbaCount = MscWriteControl.lbaCount;
	                }
	            	return (TRUE);
	            } //if (wFreeBytesLeft == 0)
	        }
	    } //if (MscWriteControl.dwBytesToReceiveLeft > 0)
	    else {
	    	if (sRwbuf.xBufFull ==0 && sRwbuf.yBufFull == 0) {
	    		MscWriteControl.pUserBuffer = NULL;         //no more receiving pending
	    		MscWriteControl.bWriteProcessing = FALSE;   //ready to receive next CBW
	    	}
	        bWakeUp = TRUE;
	    }
	}
    return (bWakeUp);
}

//--------------------------------------------------------------------------------------
/*This function is called by application to indicate buffer processed and ready for stack to operate on */
BYTE USBMSC_bufferProcessed ()
{
    unsigned short bGIE;
    BYTE edbIndex;

    bGIE  = (__get_SR_register() & GIE);            //save interrupt status
    //Disable interrupt
    __disable_interrupt();

	if (MscControl[sRwbuf.lun].yBufferAddr == NULL) {
	    /*
	     * Fix for SDOCM00078384
	     * Reset bWriteProcessing after last buffer is processed by the application
	     */
	    if (sRwbuf.operation == kUSBMSC_WRITE &&
	        MscWriteControl.dwBytesToReceiveLeft == 0){ //the Receive opereation (MSC_WRITE) is completed
	        MscWriteControl.pUserBuffer = NULL;         //no more receiving pending
	        MscWriteControl.bWriteProcessing = FALSE;   //ready to receive next CBW
	    }

	    if (sRwbuf.operation == kUSBMSC_WRITE && sRwbuf.returnCode ==
	        kUSBMSC_RWSuccess){
	        //initialize user buffer.
	        MscWriteControl.pUserBuffer = MscControl[sRwbuf.lun].xBufferAddr;
	        MscWriteControl.wFreeBytesLeft =
	            MscControl[sRwbuf.lun].wMscUserBufferSize;
	    	sRwbuf.operation = NULL;                    //no operation pending...
	    	//read out next portion of data if available.
	    	MSCFromHostToBuffer();
	    } else if (sRwbuf.operation == kUSBMSC_READ && sRwbuf.returnCode ==
	               kUSBMSC_RWSuccess){
	        WORD wCnt = sRwbuf.lbCount * MscControl[sRwbuf.lun].lbaSize;

	        //trigger sending LBA(s)
	        MscSendData(sRwbuf.bufferAddr, wCnt);

	        if (sRwbuf.lbCount >= MscReadControl.lbaCount){
	            //all bytes sent, reset structure
	            MscReadControl.lbaCount = 0;
	        } else {
	            //update read structure
	            MscReadControl.lbaCount -= sRwbuf.lbCount;
	            MscReadControl.lba += sRwbuf.lbCount;

	        }
	    	sRwbuf.operation = NULL;                                        //no operation pending...
	    }
	}
	else {
	    if (sRwbuf.operation == kUSBMSC_WRITE && sRwbuf.returnCode ==
	        kUSBMSC_RWSuccess){
	        P7OUT &= ~BIT0;
	        //initialize user buffer.
	    	sRwbuf.bufferProcessed = 1;
	    	if (sRwbuf.XorY == 0) {
	    		sRwbuf.xBufFull = 0;
	    	}
	    	else {
	    		sRwbuf.yBufFull = 0;
	    	}
	        sRwbuf.operation = NULL;                    //no operation pending...
	        //read out next portion of data if available.
	        MSCFromHostToBuffer();
	    } else if (sRwbuf.operation == kUSBMSC_READ && sRwbuf.returnCode ==
	               kUSBMSC_RWSuccess){
	        WORD wCnt = sRwbuf.lbCount * MscControl[sRwbuf.lun].lbaSize;

	        sRwbuf.bufferProcessed = 1;

	        if (sRwbuf.XorY == 0) {
	        	sRwbuf.xBufFull = 1;
	        	sRwbuf.xWordCnt = wCnt;
	        }
	        else {
	        	sRwbuf.yBufFull = 1;
	        	sRwbuf.yWordCnt = wCnt;
	        }

	        if (sRwbuf.firstFlag == 0) {
	        	//trigger sending LBA(s)
	        	sRwbuf.firstFlag = 1;
	        	MscSendData(sRwbuf.bufferAddr, wCnt);
	        }
	        else {
	            edbIndex = stUsbHandle[MSC0_INTFNUM].edb_Index;
	            //trigger Endpoint Interrupt - to start send operation
	            USBIEPIFG |= 1 << (edbIndex + 1);               //IEPIFGx;
	        }

	        if (sRwbuf.lbCount >= MscReadControl.lbaCount){
	            //all bytes sent, reset structure
	            MscReadControl.lbaCount = 0;
	            sRwbuf.operation = NULL;
	        } else {
	            //update read structure
	            MscReadControl.lbaCount -= sRwbuf.lbCount;
	            MscReadControl.lba += sRwbuf.lbCount;
	        }
	        sRwbuf.operation = NULL;                                        //no operation pending...
	    }
	}

    switch (sRwbuf.returnCode)
    {
        case kUSBMSC_RWSuccess:
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            break;
        //Set RequestSenseResponse if necessary?  Maybe initialized values OK?

        case kUSBMSC_RWNotReady:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 1;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_NOT_READY;
            RequestSenseResponse.ASC = ASC_NOT_READY;
            RequestSenseResponse.ASCQ = ASCQ_NOT_READY;
            break;

        case kUSBMSC_RWIllegalReq:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_ILLEGAL_REQUEST;
            RequestSenseResponse.ASC = ASC_ILLEGAL_REQUEST;
            RequestSenseResponse.ASCQ = ASCQ_ILLEGAL_REQUEST;
            break;

        case kUSBMSC_RWUnitAttn:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_UNITATTN;
            RequestSenseResponse.ASC = ASC_UNITATTN_READY_NOTREADY;
            RequestSenseResponse.ASCQ = ASCQ_UNITATTN_READY_NOTREADY;
            break;

        case kUSBMSC_RWLbaOutOfRange:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_ILLEGAL_REQUEST;
            RequestSenseResponse.ASC = ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
            RequestSenseResponse.ASCQ = ASCQ_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
            break;

        case kUSBMSC_RWMedNotPresent:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_NOT_READY;
            RequestSenseResponse.ASC = ASC_MEDIUM_NOT_PRESENT;
            RequestSenseResponse.ASCQ = ASCQ_MEDIUM_NOT_PRESENT;
            break;

        case kUSBMSC_RWDevWriteFault:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_MEDIUM_ERROR;
            RequestSenseResponse.ASC = ASC_WRITE_FAULT;
            RequestSenseResponse.ASCQ = ASCQ_WRITE_FAULT;
            break;

        case kUSBMSC_RWUnrecoveredRead:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey = S_MEDIUM_ERROR;
            RequestSenseResponse.ASC = ASC_UNRECOVERED_READ;
            RequestSenseResponse.ASCQ = ASCQ_UNRECOVERED_READ;
            break;

        case kUSBMSC_RWWriteProtected:
            MscState.Scsi_Status = SCSI_FAILED;
            MscState.Scsi_Residue = 0;
            Reset_RequestSenseResponse();
            RequestSenseResponse.VALID = 1;
            RequestSenseResponse.SenseKey =  S_WRITE_PROTECTED;
            RequestSenseResponse.ASC = ASC_WRITE_PROTECTED;
            RequestSenseResponse.ASCQ = ASCQ_WRITE_PROTECTED;
            break;
                                                        //case breakouts for all the codes
    }

    if (sRwbuf.returnCode != kUSBMSC_RWSuccess){
        sRwbuf.operation = NULL;                        //no operation pending...
        if (McsCbw.bmCBWFlags == DIRECTION_IN){
            usbStallInEndpoint(MSC0_INTFNUM);
            MscReadControl.bReadProcessing = FALSE;     //ready to receive next CBW
            MscReadControl.pUserBuffer = NULL;          //no more receiving pending
            MscReadControl.lbaCount = 0;
        } else {
            //we need to stall only if not all af data was transfered
            if (MscWriteControl.dwBytesToReceiveLeft > 0){
                usbStallOutEndpoint(MSC0_INTFNUM);
            }
            MscWriteControl.bWriteProcessing = FALSE;   //ready to receive next CBW
            MscWriteControl.pUserBuffer = NULL;         //no more receiving pending
            *MscWriteControl.pCT1 = 0x00;               //clear NAK, EP ready to receive next data
            *MscWriteControl.pCT2 = 0x00;               //clear NAK, EP ready to receive next data
        }
    }

    __bis_SR_register(bGIE);                            //restore interrupt status
    return (kUSB_succeed);
}

//-------------------------------------------------------------------------------------------
VOID Msc_ResetFlags ()
{
    MscState.bMscCbwReceived = FALSE;
}

//-------------------------------------------------------------------------------------------
VOID Msc_ResetStruct ()
{
    memset(&sRwbuf,0,sizeof(USBMSC_RWbuf_Info));
    memset(&McsCbw,0,sizeof(CBW));
    memset(&McsCsw,0,sizeof(CSW));

    MscReadControl.pUserBuffer = NULL;
    MscReadControl.dwBytesToSendLeft = 0;
    MscReadControl.bReadProcessing = FALSE;

    MscWriteControl.bWriteProcessing = FALSE;
    MscWriteControl.pUserBuffer = NULL;
    MscWriteControl.dwBytesToReceiveLeft = 0;   //holds how many bytes is still requested by WRITE operation (Host to MSP430)
    //we do not reset the bCurrentBufferXY, becuase the buffer doesnt changed if he MSC reseted.
    //The bCurrentBufferXY should be reseted in USB_Reset()

    Reset_RequestSenseResponse();
}

//-------------------------------------------------------------------------------------------
VOID MscResetData ()
{
    Msc_ResetStruct();

    memset(&MscWriteControl, 0, sizeof(MscWriteControl));
    memset(&MscReadControl, 0, sizeof(MscReadControl));
}

//-------------------------------------------------------------------------------------------
VOID MscResetCtrlLun ()
{
    int i;

    for (i = 0; i < MSC_MAX_LUN_NUMBER; i++)
    {
        MscControl[i].bMediaPresent = 0x80;
        MscControl[i].bWriteProtected = FALSE;
    }
}

//-------------------------------------------------------------------------------------------
/* This function can be called by application to get the current status of stack operation */
BYTE USBMSC_getState ()
{
    BYTE state;

    if (sRwbuf.operation == 0 && MscState.bMscSendCsw == FALSE){
        state = kUSBMSC_idle;
    } else if (sRwbuf.operation == kUSBMSC_READ && sRwbuf.lbCount > 0){
        state =  kUSBMSC_readInProgress;
    } else if (sRwbuf.operation == kUSBMSC_WRITE && sRwbuf.lbCount > 0){
        state =  kUSBMSC_writeInProgress;
    } else if (sRwbuf.operation == 0 && MscState.bMscSendCsw == TRUE){
        state =  kUSBMSC_cmdBeingProcessed;
    }
    return (state);
}

//-------------------------------------------------------------------------------------------
BYTE USBMSC_updateMediaInfo ( BYTE lun,  struct USBMSC_mediaInfoStr *info)
{
    BYTE state;

    Scsi_Read_Capacity_10[lun].lLba[0] = (BYTE)(info->lastBlockLba >> 24);
    Scsi_Read_Capacity_10[lun].lLba[1] = (BYTE)(info->lastBlockLba >> 16);
    Scsi_Read_Capacity_10[lun].lLba[2] = (BYTE)(info->lastBlockLba >> 8);
    Scsi_Read_Capacity_10[lun].lLba[3] = (BYTE)(info->lastBlockLba);

    Scsi_Read_Capacity_10[lun].bLength[0] = (BYTE)(info->bytesPerBlock >> 24);
    Scsi_Read_Capacity_10[lun].bLength[1] = (BYTE)(info->bytesPerBlock >> 16);
    Scsi_Read_Capacity_10[lun].bLength[2] = (BYTE)(info->bytesPerBlock >> 8);
    Scsi_Read_Capacity_10[lun].bLength[3] = (BYTE)(info->bytesPerBlock);

    MscControl[lun].lbaSize = (WORD)Scsi_Read_Capacity_10[lun].bLength[2] <<
                              8 | Scsi_Read_Capacity_10[lun].bLength[3];

    //If the LUN was reported as not removable, then leave mediaPresent/mediaChanged as
    //their initialized defaults.
    if (USBMSC_config.LUN[lun].removable){
        if (((MscControl[lun].bMediaPresent == kUSBMSC_MEDIA_NOT_PRESENT)) &&
            (info->mediaPresent == kUSBMSC_MEDIA_PRESENT)){             //If media was inserted...
            //Set Unit Attention flag. This flag is used in Scsi_Request_Sense().
            MscState.bUnitAttention = TRUE;
            MscState.Scsi_Status = SCSI_FAILED;
        }

        if ((MscControl[lun].bMediaPresent == kUSBMSC_MEDIA_PRESENT &&
             ((info->mediaPresent == kUSBMSC_MEDIA_NOT_PRESENT))) ||    //If media was removed...
            ((info->mediaPresent == kUSBMSC_MEDIA_PRESENT) &&
             (info->mediaChanged))){                                    //Or if media still present, but has changed...
            //Set Unit Attention flag. This flag is used in Scsi_Request_Sense().
            MscState.bUnitAttention = TRUE;
            MscState.Scsi_Status = SCSI_FAILED;
            state = USBMSC_getState();

            if (state ==  kUSBMSC_readInProgress || state ==
                kUSBMSC_writeInProgress){
                if (McsCbw.bmCBWFlags == DIRECTION_IN){
                    usbStallInEndpoint(MSC0_INTFNUM);
                } else {
                    usbStallOutEndpoint(MSC0_INTFNUM);
                }

                Msc_ResetStateMachine();
                Msc_ResetFlags();
                Msc_ResetStruct();
                MscState.isMSCConfigured = TRUE;

                Scsi_Send_CSW(MSC0_INTFNUM);
            }
        }
        MscControl[lun].bMediaPresent = info->mediaPresent;
    }

    MscControl[lun].bWriteProtected = info->writeProtected;
    return (kUSB_succeed);
}

//-------------------------------------------------------------------------------------------
BYTE USBMSC_registerBufInfo (BYTE lun, BYTE *RWbuf_x, BYTE *RWbuf_y, WORD size)
{
    MscControl[lun].wMscUserBufferSize = 0;
    MscControl[lun].xBufferAddr = NULL;
    MscControl[lun].yBufferAddr = NULL; //this version supports only X buffer.

    //check if arguments are valid
    if ((size < MscControl[lun].lbaSize) ||
        (RWbuf_x == NULL)){             //Need at least one buffer
        return (kUSB_generalError);
    }

    MscControl[lun].wMscUserBufferSize = size;
    MscControl[lun].lbaBufCapacity = MscControl[lun].wMscUserBufferSize /
                                     MscControl[lun].lbaSize;
    MscControl[lun].xBufferAddr = RWbuf_x;
    MscControl[lun].yBufferAddr = RWbuf_y;
    return (kUSB_succeed);
}

//-------------------------------------------------------------------------------------------
VOID SET_RequestsenseNotReady ()
{
    //Set REQUEST SENSE with "not ready"
    Reset_RequestSenseResponse();
    RequestSenseResponse.VALID = 1;
    RequestSenseResponse.SenseKey = S_NOT_READY;
    RequestSenseResponse.ASC = ASC_NOT_READY;
    RequestSenseResponse.ASCQ = ASCQ_NOT_READY;
    //Send CSW with error status
    MscState.Scsi_Status = SCSI_FAILED;
}

//-------------------------------------------------------------------------------------------
VOID SET_RequestsenseMediaNotPresent ()
{
    //Set REQUEST SENSE with "not ready"
    Reset_RequestSenseResponse();
    RequestSenseResponse.VALID = 1;
    RequestSenseResponse.SenseKey = S_NOT_READY;
    RequestSenseResponse.ASC = ASC_MEDIUM_NOT_PRESENT;
    RequestSenseResponse.ASCQ = ASCQ_MEDIUM_NOT_PRESENT;
    //Send CSW with error status
    MscState.Scsi_Status = SCSI_FAILED;
}

//-------------------------------------------------------------------------------------------
VOID usbClearOEPByteCount (BYTE intfNum)
{
    BYTE edbIndex;

    edbIndex = stUsbHandle[intfNum].edb_Index;
    tOutputEndPointDescriptorBlock[edbIndex].bEPBCTX = 0;
}

//-------------------------------------------------------------------------------------------
VOID usbStallEndpoint (BYTE intfNum)
{
    BYTE edbIndex;

    edbIndex = stUsbHandle[intfNum].edb_Index;
    tOutputEndPointDescriptorBlock[edbIndex].bEPCNF |= EPCNF_STALL;
    tInputEndPointDescriptorBlock[edbIndex].bEPCNF |= EPCNF_STALL;
}

//-------------------------------------------------------------------------------------------
VOID usbStallInEndpoint (BYTE intfNum)
{
    BYTE edbIndex;

    edbIndex = stUsbHandle[intfNum].edb_Index;
    tInputEndPointDescriptorBlock[edbIndex].bEPCNF |= EPCNF_STALL;
}

//-------------------------------------------------------------------------------------------
VOID usbStallOutEndpoint (BYTE intfNum)
{
    BYTE edbIndex;

    edbIndex = stUsbHandle[intfNum].edb_Index;
    tOutputEndPointDescriptorBlock[edbIndex].bEPCNF |= EPCNF_STALL;
	MscState.stallEndpoint = TRUE;
}

//-------------------------------------------------------------------------------------------
USBMSC_RWbuf_Info* USBMSC_fetchInfoStruct (VOID)
{
    return (&sRwbuf);
}

#ifdef CDROM_SUPPORT
//----------------------------------------------------------------------------

VOID Scsi_Read_TocPmaAtip(BYTE intfNum)
{
    if(McsCbw.CBWCB[2] & 0x01) {

	if (SUCCESS !=
			MscSendData( (PBYTE)&Scsi_Read_TOC_PMA_ATIP_F1[McsCbw.bCBWLUN],
					Scsi_Read_TOC_PMA_ATIP_F1_LEN)){
			MscState.Scsi_Status = SCSI_FAILED;
		}
    } else {

		if (SUCCESS !=
			MscSendData( (PBYTE)&Scsi_Read_TOC_PMA_ATIP_F2[McsCbw.bCBWLUN],
					Scsi_Read_TOC_PMA_ATIP_F2_LEN)){
			MscState.Scsi_Status = SCSI_FAILED;
		}
    }
}

VOID Scsi_Get_Configuration(BYTE intfNum) {

		if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_GET_CONFIGURATION_LEN)){
		  return;
		}

        if (SUCCESS !=
            MscSendData( (PBYTE)&Scsi_Get_Configuration_Descriptor[McsCbw.bCBWLUN],
                    SCSI_GET_CONFIGURATION_LEN)){
            MscState.Scsi_Status = SCSI_FAILED;
        }
}

VOID Scsi_Event_Status_Notification(BYTE intfNum) {

       if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_EVENT_STATUS_LEN)){
           return;
        }
        if (SUCCESS !=
            MscSendData( (PBYTE)&Scsi_Event_Status_Descriptor[McsCbw.bCBWLUN],
                    SCSI_EVENT_STATUS_LEN)){
            MscState.Scsi_Status = SCSI_FAILED;
        }
}

VOID Scsi_Read_Disc_Information(BYTE intfNum) {

                    
	if (FAILURE == Check_CBW(intfNum,DIRECTION_IN,SCSI_READ_DISC_INFORMATION_LEN)){
			return;
		 }
        if (SUCCESS !=
            MscSendData( (PBYTE)&Scsi_Disc_Information_Descriptor[McsCbw.bCBWLUN],
                    SCSI_READ_DISC_INFORMATION_LEN)){
            MscState.Scsi_Status = SCSI_FAILED;
        }
}

#endif

#endif  //_MSC_

/*----------------------------------------------------------------------------+
 | End of source file                                                          |
 +----------------------------------------------------------------------------*/
/*------------------------ Nothing Below This Line --------------------------*/

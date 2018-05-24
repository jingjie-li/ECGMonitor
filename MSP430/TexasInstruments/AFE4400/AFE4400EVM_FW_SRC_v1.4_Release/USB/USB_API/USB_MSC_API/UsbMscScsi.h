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
 * ======== UsbMscScsi.h ========
 */
#ifndef _UMSC_SCSI_H_
#define _UMSC_SCSI_H_

#include <descriptors.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*Macros for CBW, CSW signatures */
#define CBW_SIGNATURE 0x43425355u
#define CSW_SIGNATURE 0x53425355u

/*CBW, CSW length in bytes */
#define CBW_LENGTH   31
#define CSW_LENGTH   13

/*SCSI Commands - Mandatory only implemented */
#define SCSI_TEST_UNIT_READY            0x00
#define SCSI_REQUEST_SENSE          	0x03
#define SCSI_INQUIRY                	0x12
#define SCSI_MODE_SENSE_6           	0x1A
#define SCSI_MODE_SENSE_10          	0x5A
#define SCSI_READ_CAPACITY_10           0x25
#define SCSI_READ_10                	0x28
#define SCSI_WRITE_10               	0x2A
#define SCSI_READ_FORMAT_CAPACITIES     0x23
#define SCSI_MODE_SELECT_6              0x15
#define SCSI_MODE_SELECT_10             0x55
#define PREVENT_ALLW_MDM                0x1E
#define START_STOP_UNIT                 0x1B
#define SCSI_REPORT_LUNS                0xA0
#define SCSI_VERIFY                     0x2F

#define SCSI_READ_TOC_PMA_ATIP					0x43
#define Scsi_Read_TOC_PMA_ATIP_F1_LEN			20
#define Scsi_Read_TOC_PMA_ATIP_F2_LEN    		48
#define SCSI_GET_CONFIGURATION          		0x46
#define SCSI_GET_CONFIGURATION_LEN      		4
#define SCSI_EVENT_STATUS               		0x4A
#define SCSI_EVENT_STATUS_LEN           		8
#define SCSI_READ_DISC_INFORMATION     			0x51
#define SCSI_SET_CD_SPEED						0xBB
#define SCSI_READ_DISC_INFORMATION_LEN  		36

/*SCSI Status codes. Used in CSW response */
#define SCSI_PASSED           		0
#define SCSI_FAILED           		1
#define SCSI_PHASE_ERROR      		2
#define SCSI_READWRITE_FAIL       	2

#define kUSBMSC_RWSuccess           0
#define kUSBMSC_RWNotReady          1
#define kUSBMSC_RWIllegalReq        2
#define kUSBMSC_RWUnitAttn          3
#define kUSBMSC_RWLbaOutOfRange     4
#define kUSBMSC_RWMedNotPresent     5
#define kUSBMSC_RWDevWriteFault     6
#define kUSBMSC_RWUnrecoveredRead   7
#define kUSBMSC_RWWriteProtected    8


/* Macros to indicate READ or WRITE operation */
#define kUSBMSC_READ 1
#define kUSBMSC_WRITE 2

#define kUSBMSC_MEDIA_PRESENT 0x81
#define kUSBMSC_MEDIA_NOT_PRESENT 0x82

#define kUSBMSC_WRITE_PROTECTED 0x00

/* Defines for MSC SCSI State-Machine */
#define MSC_READY                   0x00
#define MSC_COMMAND_TRANSPORT       0x01
#define MSC_DATA_IN                 0x02
#define MSC_DATA_OUT                0x03
#define MSC_STATUS_TRANSPORT        0x04
#define MSC_DATA                    0x05
#define MSC_WAIT4RESET              0x06

/*Lengths of SCSI commands(in bytes) */
#define SCSI_SCSI_INQUIRY_CMD_LEN            36
#define SCSI_READ_CAPACITY_CMD_LEN           8
#define SCSI_MODE_SENSE_6_CMD_LEN            4
#define SCSI_MODE_SENSE_10_CMD_LEN           8
#define SCSI_REQ_SENSE_CMD_LEN               18
#define SCSI_READ_FORMAT_CAPACITY_CMD_LEN    12
#define SCSI_REPORT_LUNS_CMD_LEN             16

/*----------------------------------------------------------------------------+
 | Type defines and structures                                                 |
 +----------------------------------------------------------------------------*/
/*CBW Structure */
typedef struct {
    DWORD dCBWSignature;
    DWORD dCBWTag;
    DWORD dCBWDataTransferLength;
    BYTE bmCBWFlags;
    BYTE bCBWLUN;
    BYTE bCBWCBLength;
    BYTE CBWCB[16];
} CBW, *pCBW;

/*CSW structure */
typedef struct {
    DWORD dCSWSignature;
    DWORD dCSWTag;
    DWORD dCSWDataResidue;
    BYTE bCSWStatus;
} CSW, *pCSW;

/*Request Response union(Required for Request sense command) */
typedef struct {
    BYTE ResponseCode : 7;
    BYTE VALID : 1;
    BYTE Obsolete;
    BYTE SenseKey : 4;
    BYTE Resv : 1;
    BYTE ILI : 1;
    BYTE EOM : 1;
    BYTE FILEMARK : 1;
    BYTE Information[4];
    BYTE AddSenseLen;
    BYTE CmdSpecificInfo[4];
    BYTE ASC;
    BYTE ASCQ;
    BYTE FRUC;
    BYTE SenseKeySpecific[3];
    BYTE padding[14];   /* padding to cover case where host requests 24 bytes of sense data */
} REQUEST_SENSE_RESPONSE;

/*Read capacity union(Required for READ CAPACITY command)*/
typedef struct {
    DWORD Last_LBA;
    BYTE Resv;
    BYTE Size_LBA[3];
} SCSI_READ_CAPACITY;

/*Structure internal to stack for holding LBA,buffer addr etc information*/
typedef struct {
    //BYTE	intfNum;
    BYTE 	lun;
    BYTE 	operation;
    DWORD 	lba;
    BYTE 	lbCount;
    BYTE    *bufferAddr;
    BYTE 	returnCode;
    BYTE 	XorY;
    BYTE	xBufFull;
    WORD	xWordCnt;
    BYTE	yBufFull;
    WORD	yWordCnt;
    BYTE	bufferProcessed;
    BYTE	firstFlag;
    DWORD	xlba;
    BYTE	xlbaCount;
    DWORD	ylba;
    BYTE	ylbaCount;

}USBMSC_RWbuf_Info;

/*Media info structure */
struct USBMSC_mediaInfoStr {
    DWORD lastBlockLba;
    DWORD bytesPerBlock;
    BYTE mediaPresent;
    BYTE mediaChanged;
    BYTE writeProtected;
};

/*Lun entry Structures */
struct _LUN_entry_struct {
    BYTE number;
    BYTE PDT;
    BYTE removable;
    char t10VID[8];
    char t10PID[16];
    char t10rev[4];
};

struct config_struct {
    struct _LUN_entry_struct LUN[MSC_MAX_LUN_NUMBER];
};

struct _Report_Luns {
    BYTE LunListLength[4];
    BYTE Reserved[4];
    BYTE LunList1[8];
};

struct _Scsi_Read_Capacity {
    BYTE lLba[4];               //Last logical block address
    BYTE bLength[4];            //Block length, in this case 0x200 = 512 bytes for each Logical Block
};

//structure for controlling WRITE phase (HOST to MSP430)
struct _MscWriteControl {
    DWORD dwBytesToReceiveLeft; //holds how many bytes is still requested by WRITE operation:
    //Host to MSP430.
    WORD wFreeBytesLeft;        //free bytes left in UserBuffer
    DWORD lba;                  //holds the current LBA number. This is the first LBA in the UserBuffer
    BYTE *pUserBuffer;          //holds the current position of user's receiving buffer.
                                //If NULL- no receiving operation started
    WORD wCurrentByte;          //how many bytes in current LBA are received
    WORD lbaCount;              //how many LBA we have received in current User Buffer
    BYTE * pCT1;                //holds current EPBCTxx register
    BYTE * pCT2;                //holds next EPBCTxx register
    BYTE * pEP2;                //holds addr of the next EP buffer
    BYTE bCurrentBufferXY;      //indicates which buffer is used by host to transmit data via OUT
    BYTE bWriteProcessing;      //indicated if the current state is DATA WRITE phase or CBW receiwing
    BYTE XorY;
};

//structure for controlling READ phase (MSP430 to HOST)
struct _MscReadControl {
    DWORD dwBytesToSendLeft;    //holds how many bytes is still requested by WRITE operation (Host to MSP430)
    BYTE *pUserBuffer;          //holds the current position of user's receiving buffer.
                                //If NULL- no receiving operation started
    DWORD lba;                  //holds the current LBA number. This is the first LBA in the UserBuffer.
    BYTE * pCT1;                //holds current EPBCTxx register
    BYTE * pCT2;                //holds next EPBCTxx register
    BYTE * pEP2;                //holds addr of the next EP buffer
    WORD lbaCount;              //how many LBA we have to send to Host
    BYTE bCurrentBufferXY;      //indicates which buffer is used by host to transmit data via OUT
    BYTE bReadProcessing;       //indicated if the current state is DATA READ phase or CSW sending
                                //initiated by McsDataSend()
    BYTE XorY;
};

//structure for common control of MSC stack
struct _MscControl {
    WORD wMscUserBufferSize;
    WORD lbaSize;               //limitid to WORD, but could be increased if required.
    BYTE lbaBufCapacity;        //how many LBAs (max) contains UserBuffer for read/write operation (>=1)
    BYTE *xBufferAddr;
    BYTE *yBufferAddr;
    BYTE bMediaPresent;
    BYTE bWriteProtected;
};

struct _MscState {
    volatile DWORD Scsi_Residue;
    volatile BYTE Scsi_Status;  /*Variable to track command status */
    BOOL bMcsCommandSupported;  /*Flag to indicate read/write command is recieved from host */
    BOOL bMscCbwReceived;       /*Flag to inidicate whether any CBW recieved from host*/
    BOOL bMscSendCsw;
    BOOL isMSCConfigured;
    BYTE bUnitAttention;
    BYTE bMscCbwFailed;
    BYTE bMscResetRequired;
	BYTE stallEndpoint;
};

extern struct _MscWriteControl MscWriteControl;
extern struct _MscReadControl MscReadControl;
extern struct _MscControl MscControl[];

/*----------------------------------------------------------------------------+
 | Extern Variables                                                            |
 +----------------------------------------------------------------------------*/

extern CBW cbw;
extern CSW csw;
extern REQUEST_SENSE_RESPONSE RequestSenseResponse;

/*----------------------------------------------------------------------------+
 | Function Prototypes                                                         |
 +----------------------------------------------------------------------------*/

/*SCSI Wrapper functions */
BYTE Scsi_Cmd_Parser (BYTE opcode);
BYTE Scsi_Send_CSW (BYTE intfNum);

/*Function to reset MSC SCSI state machine */
VOID Msc_ResetStateMachine(VOID);
VOID Msc_ResetFlags(VOID);
VOID Msc_ResetStruct(VOID);
VOID SET_RequestsenseNotReady(VOID);
VOID SET_RequestsenseMediaNotPresent(VOID);
VOID MscResetCtrlLun(VOID);

USBMSC_RWbuf_Info* USBMSC_fetchInfoStruct(VOID);
#ifdef __cplusplus
}
#endif
#endif  //_MSC_SCSI_H_


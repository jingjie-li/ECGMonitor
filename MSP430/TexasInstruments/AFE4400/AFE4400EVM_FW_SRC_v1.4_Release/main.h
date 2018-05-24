/*
 * main.h
 *
 * Provides application driver with AFE44x0 PC GUI
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED  
 *
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#define SOT     0x02
#define EOT     0x03
#define CR      0x0D
#define LF      0x0A

#define WRITE_REG_CMD                   0x02
#define READ_REG_CMD                    0x03
#define START_READ_ADC_REG_CMD          0x01
#define STOP_READ_ADC_REG_CMD           0x06
#define DEV_ID_CMD                      0x04
#define FW_UPGRADE_CMD                  0x05
#define FW_VERSION_CMD                  0x07
#define CALIBRATION_CMD                 0x08

#define CALIBRATION_TRUE        0x54
#define CALIBRATION_FALSE       0x46

#define __AFE4400__
//#define __AFE4490__

/**************************************************************************************************************
 * AFE44x0 Firmware version details
 * 
 * 1. AFE44x0_Major_Number: The Major number can be in the range of 0-255
 * 
 * 2. AFE44x0_Minor_Number: The Minor number can be in the range of 0-255
 * 
 *************************************************************************************************************/
#define  AFE44x0_Major_Number 0x01
#define  AFE44x0_Minor_Number 0x04

#endif /*_MAIN_H_*/

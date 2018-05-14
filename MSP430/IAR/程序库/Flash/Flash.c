/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Flash.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          该程序完成Flash控制器模块的通用程序库，调用本程序可以
 *          完成Flash的擦除，写入字或字节，本程序没有实现块写入功
 *          能。由于程序可以完成擦除所有的段， 所以使用时一定要注
 *          意，不要把即将运行的程序擦除。使用时注意，Flash的内容
 *          每次写入后，不能在擦除之前再次写入数据， 否则会有数据
 *          损害。
 *      使用方式：
 *          工程中加入Flash.C文件，文件包含Flash.h。 然后即可使用
 *          本程序库的函数了。
 *          
 * 创建标识：   刘中原20110830
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "Flash.h"

unsigned char FlashSR;
/*=======================宏定义==========================*/
#define DINT    FlashSR=__get_SR_register();_DINT() // 关中断，并保存状态寄存器
#define EINT    if(FlashSR & GIE)           _EINT() //根据保存的结果判断 开中断
/*=======================================================*/

/************************************************************
* 函数名称：FlashInit
* 功    能：Flash相关寄存器等资源初始化
* 参    数：无
* 返 回 值：无
* 说    明：使用程序库之前应先调用此函数。
*************************************************************/
void FlashInit()
{
    FCTL2 = FWKEY + FSSEL_2 + FN1;          // 默认 SMCLK/3 =333KHz 
}

/****************************************************************************
* 名    称：WaitForEnable
* 功    能：Flash忙等待
* 入口参数：无 
* 出口参数：无
* 说    明: 若Flash忙则等待，直到Flash操作完成(空闲)才返回。
****************************************************************************/
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}

/****************************************************************************
* 名    称：FlashErase
* 功    能：擦除Flash的一个数据段
* 入口参数：Addr:被擦除数据段的首地址 
* 出口参数：无
****************************************************************************/
void FlashErase(unsigned int Addr)  
{ 
    char *FlashPtr;
    FlashPtr = (char *)Addr;
    FCTL1 = FWKEY + ERASE;                      // Set Erase bit
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = 0;                              // Dummy write to erase Flash segment B
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Lock
    FCTL3 = FWKEY + LOCK;                       // Set Lock bit  
}

/****************************************************************************
* 名    称：FlashWriteChar
* 功    能：向Flash中写入一个字节(Char型变量)
* 入口参数：Addr:存放数据的地址
            Data:待写入的数据
* 出口参数：无
* 说    明：地址只能是偶数，如果是奇数，会自动前移一位
* 范    例：FlashWriteChar(0x1000,123);将常数123写入0x1000单元
            FlashWriteChar(0x1002,a);将整型变量a写入0x1002单元 
****************************************************************************/
void FlashWriteChar(unsigned int addr,char Data)
{
    char *FlashPtr = (char *)addr;              // Segment A pointer
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}  

/****************************************************************************
* 名    称：FlashWriteChar
* 功    能：向Flash中写入一个字(无符号整型变量)
* 入口参数：Addr:存放数据的地址
            Data:待写入的数据
* 出口参数：无
* 范    例：FlashWriteChar(0x1000,123);将常数123写入0x1000单元
            FlashWriteChar(0x1002,a);将整型变量a写入0x1002单元 
****************************************************************************/
void FlashWriteWord(unsigned int addr,unsigned int Data)
{
    unsigned int *FlashPtr = (unsigned int *)addr;
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}  

/****************************************************************************
* 名    称：FlashReadChar
* 功    能：从Flash中读取一个字节
* 入口参数：Addr:存放数据的地址
* 出口参数：读回的数据
****************************************************************************/
char FlashReadChar(unsigned int Addr)
{ 
    char Data;
    char *FlashPtr = (char *) Addr; 
    Data = *FlashPtr;
    return(Data);
}

/****************************************************************************
* 名    称：FlashReadWord
* 功    能：从Flash中读取一个字
* 入口参数：Addr:存放数据的地址
* 出口参数：读回的数据（无符号整型）
****************************************************************************/
unsigned int FlashReadWord(unsigned int Addr)
{ 
    unsigned int Data;
    unsigned int *FlashPtr = (unsigned int *)Addr; 
    Data = *FlashPtr;
    return(Data);
}

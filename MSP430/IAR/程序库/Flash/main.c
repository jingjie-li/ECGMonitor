/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： main.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库使用演示
 *      说明：  
 *          完成Flash控制器函数库的使用演示。观察Flash内容：调
 *          试时，View-Memory可以打开Flash存储器串口,查看Flash
 *          存储器的内容。
 *          
 * 创建标识：   刘中原20110830
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "Flash.h"

/****************************************************************************
* 名    称：ClkInit
* 功    能：时钟系统初始化  MCLK为8MHz，SMCLK为1MHz
* 入口参数：无
* 出口参数：无
****************************************************************************/
void ClkInit()
{
    char i;
    BCSCTL1 &= ~XT2OFF;             //打开XT2振荡器
    IFG1&=~OFIFG;                   //清除振荡错误标志
    while((IFG1&OFIFG)!=0)
    {
        for(i=0;i<0xff;i++);
        IFG1&=~OFIFG;               //清除振荡错误标志
    }
    BCSCTL2 |= SELM_2+SELS+DIVS_3;  //MCLK为8MHz，SMCLK为1MHz
}

/****************************************************************************
* 名    称：main主程序
* 功    能：演示Flash程序库 的使用
* 入口参数：无
* 出口参数：无
****************************************************************************/
int a;
void main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    ClkInit();
    FlashInit();
    FlashWriteChar(InfoB,0x25);
    a=FlashReadChar (InfoB);        //InfoB在H文件中有宏定义
    FlashWriteWord(InfoB+2,0x5669);
    a = FlashReadWord(InfoB+2);
    FlashErase(InfoB);
    LPM0;
}

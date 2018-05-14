/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Printf.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机printf函数移植
 *      说明：  
 *          该程序完成printf的移植，printf同时输出到液晶和Uart0，
 *          方便各程序输出显示
 *          使用时只需把Printf.c添加到工程中，然后在要调用printf
 *          程序的源程序文件中加入对stdio.h的包含；然后就可以正
 *          常printf函数了；另外，液晶可能需要定位，如果需用
 *          GotoXY则需加入对Printf.h的文件包含。
 *          
 * 创建标识：   刘中原20110729
 * 
 * 修改标识：   刘中原20110820
 * 修改描述：   液晶的printf不支持退格，在此添加退格支持；退格在函数
 *              putchar2Lcd中,字符=\b=\x8时调用，退格函数:BackSpace
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "Lcd12864.h"
#include "Uart.h"
#include "Printf.h"

/****************************************************************************
* 名    称：putchar2Com
* 功    能：向标串口设备发送一字节数据(1个ASCII字符)
* 入口参数：ch: 待发送的字符  
* 出口参数：发出的字符
* 说    明: 此函数供putchar函数调用，完成printf函数底层输出到串口设备。
****************************************************************************/
int putchar2Com(int ch)
{
    if (ch == '\n')           //  '\n'(回车)扩展成 '\n''\r' (回车+换行) 
    {
        UartWriteChar('\r') ;   //0x0d 换行
    }
    UartWriteChar(ch);        //从串口发出数据  
    return (ch);
}

/****************************************************************************
* 名    称：AddNewline
* 功    能：液晶写满，添加一行，其他行向上移动
* 入口参数：无
* 出口参数：无
* 说    明: 此函数供putchar2Lcd函数调用，当输出满液晶后，自动向上滚动。
****************************************************************************/
void AddNewline()
{
    char str[17];
    str[16] = 0;
    
    //第二行 移至第一行
    LcdWriteComm(0x90);
    LcdReadData();              //空读取
    for(int i = 0;i<16;i++)
    {
        str[i] = LcdReadData();
    }
    LcdWriteString(0x80,str);
    
    //第三行 移至第二行
    LcdWriteComm(0x88);
    LcdReadData();
    for(int i = 0;i<16;i++)
    {
        str[i] = LcdReadData();
    }
    LcdWriteString(0x90,str);
    
    //第四行 移至第三行
    LcdWriteComm(0x98);
    LcdReadData();
    for(int i = 0;i<16;i++)
    {
        str[i] = LcdReadData();
    }
    LcdWriteString(0x88,str);
    
    //第四行 空白
    LcdWriteString(0x98,"                ");    //十六个空格
}

/****************************************************************************
* 名    称：ChangeNextRow
* 功    能：液晶显示换下一行
* 入口参数：无
* 出口参数：无
* 说    明: 此函数供putchar2Lcd函数调用，当液晶一行写满，或是遇到换行符后，调
            用此函数，写入下一行。
****************************************************************************/
void ChangeNextRow()
{
    char addr;
    
    addr = LcdReadAddr();       //当前地址
    if(addr <= 0x88)
    {
        LcdWriteComm(0x90);
    }
    else if(addr <= 0x90)
    {
        LcdWriteComm(0x98);
    }
    else if(addr <= 0x98)
    {
        LcdWriteComm(0x88);
    }
    else
    {
        AddNewline();           //添加行，同时向上滚动
        LcdWriteComm(0x98);
    }
}

/****************************************************************************
* 名    称：BackSpace
* 功    能：液晶显示，退格，地址指向前一个（退半字）
* 入口参数：无
* 出口参数：无
* 说    明: 此函数供putchar2Lcd函数调用，当液晶收到退格字符，后，调用此函数，
            地址退回一格(英文：半字，中文：一字)
****************************************************************************/
void BackSpace()
{
    char addr,dat;
    
    addr = LcdReadAddr();       //当前地址
    LcdWriteData(0x20);         //写入一个空字符，根据地址判断是否为前半字
    if(addr == LcdReadAddr())   //前半字
    {
        if(addr == 0x80)
            return;
        else if(addr == 0x90)
            addr = 0x87;
        else if(addr == 0x88)
            addr = 0x97;
        else if(addr == 0x98)
            addr = 0x8F;
        else 
            addr = addr - 1;
       
        LcdWriteComm(addr);
        LcdReadData();          //空读取
        dat = LcdReadData();
        LcdWriteComm(addr);
        if(dat < 0x80)
            LcdWriteData(dat);
    }
    else
    {
        LcdWriteComm(addr);
    }
}

/****************************************************************************
* 名    称：putchar2Lcd
* 功    能：向标12864液晶设备发送一字节数据(1个ASCII字符)
* 入口参数：ch: 待发送的字符  
* 出口参数：发出的字符
* 说    明: 此函数供putchar函数调用，完成printf函数底层输出到液晶。
****************************************************************************/
int putchar2Lcd(int ch)
{
    char addr,dat;
    char changeRowFlag = 0;
    
    if (ch == '\n')         //  '\n'(回车),换行
    {
        ChangeNextRow();
        changeRowFlag = 1;
    }
    else if (ch == '\b')    // '\b' (退格)
    {
        BackSpace();
    }
    else
    {
        addr = LcdReadAddr();
        if(ch < 0x80)
        {
            LcdWriteData(ch);
        }
        else
        {
            LcdWriteData(0x20);     //写入一个空字符，根据地址判断是否为前半字
            if(addr == LcdReadAddr())   //前半字 从新写入ch字符
            {
                LcdWriteComm(addr);
                LcdWriteData(ch);
            }
            else
            {
                LcdWriteComm(addr);
                dat = LcdReadData();
                if(dat < 0x80)           //前一个字符是英文字符
                {
                    LcdWriteData(0x20);                 //空格
                }
                if((addr != LcdReadAddr()) &&               //写入的是行最后位的后半字则换行
                   (addr==0x87 || addr==0x97 || addr==0x8F || addr==0x9F))
                {
                    ChangeNextRow();
                    changeRowFlag = 1;
                }
                LcdWriteData(ch);
            }
        }
    }
    if((addr != LcdReadAddr()) &&   //写入的是行最后位的后半字则换行,且未换过行
       (changeRowFlag == 0) &&   
       (addr==0x87 || addr==0x97 || addr==0x8F || addr==0x9F))
    {
        ChangeNextRow();
    }
    return (ch);
}

/****************************************************************************
* 名    称：putchar
* 功    能：向标准终端设备发送一字节数据(1个ASCII字符)
* 入口参数：ch: 待发送的字符  
* 出口参数：发出的字符
* 说    明: printf函数会调用该函数作为底层输出。这里从串口输出字符到PC机的超
            级终端软件上，printf的结果将打印到超级终端上。若修改该函数，将字
            符以其他方式输出，如显示到LCD上，printf的结果将显示在LCD上。本程
            把字符同时输出到超级终端和LCD上，这样调用printf时将会同时输出至
            超级终端和LCD上。
****************************************************************************/
int putchar(int ch)
{
    putchar2Com(ch);
    putchar2Lcd(ch);
    return (ch);
}

/****************************************************************************
* 名    称：GotoXY
* 功    能：定位至液晶的具体位置：（x，y）（0-15,0-3）
* 入口参数：无
* 出口参数：无
* 说    明: 调用printf之前调用此函数，可以定位至液晶的具体位置，中文则以偶数
            有效，若是奇数，自动后移一位
****************************************************************************/
void GotoXY(char x,char y)
{
    char addr;
    
    if(y==0)
    {
        addr = 0x80 + x / 2;
    }
    else if(y==1)
    {
        addr = 0x90 + x / 2;
    }
    else if(y==2)
    {
        addr = 0x88 + x / 2;
    }
    else
    {
        addr = 0x98 + x / 2;
    }
    LcdWriteComm(addr);
    if(x % 2)                   //是奇数，后移一位（写入空格）
    {
        LcdWriteData(0x20);
    }
}
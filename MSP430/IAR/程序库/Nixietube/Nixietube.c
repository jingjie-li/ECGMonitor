/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Nixietube.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机数码管程序库
 *      说明：  
 *          该驱动程序库包含了常用的数码显示功能,如显示数字、字母等可
 *          以作为各种程序的底层驱动使用。
 *          使用时只需把Nixietube.c添加到工程中，然后在要调用数码管程
 *          序的源程序文件中加入对Nixietube.h的包含；然后就可以调用头
 *          文件中声明的各个函数。
 *          
 * 创建标识：   刘中原20110822
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "Nixietube.h"

/*宏定义，数码管a-h各段对应的比特，更换硬件只用改动以下8行*/
#define a       0x01                            //  AAAA
#define b       0x02                            // F    B
#define c       0x04                            // F    B
#define d       0x08                            //  GGGG
#define e       0x10                            // E    C
#define f       0x20                            // E    C
#define g       0x40                            //  DDDD  HH
#define h       0x80        //小数点

/*用宏定义自动生成段码表，很好的写法，值得学习*/
/*更换硬件无需重写段码表*/
const char Tab[] = {
    a + b + c + d + e + f,                  // Displays "0"
    b + c,                                  // Displays "1"
    a + b + d + e + g,                      // Displays "2"
    a + b + c + d + g,                      // Displays "3"
    b + c + f + g,                          // Displays "4"
    a + c + d + f +g,                       // Displays "5"
    a + c + d + e + f + g,                  // Displays "6"
    a + b + c,                              // Displays "7"
    a + b + c + d + e + f + g,              // Displays "8"
    a + b + c + d + f + g,                  // Displays "9"
    a + b + c + e + f + g,                  // Displays "A"
    c + d + e + f + g,                      // Displays "B"  
    a + d + e + f,                          // Displays "C"
    b + c + d + e + g,                      // Displays "D"
    a + d + e + f + g,                      // Displays "E"
    a + e + f + g,                          // Displays "F"
    a + c + d + e + f,                      // Displays "G"
    b + c + e + f + g,                      // Displays "H"  
    e + f,                                  // Displays "I"
    b + c + d + e,                          // Displays "J"
    b + d + e + f + g,                      // Displays "K"
    d + e + f,                              // Displays "L"  
    a + c + e + g,                          // Displays "M" 
    a + b + c + e + f,                      // Displays "N"   
    c + e + g,                              // Displays "n"
    c + d + e + g,                          // Displays "o"
    a + b + c + d + e + f,                  // Displays "O"
    a + b + e + f + g,                      // Displays "P"
    a + b + c + f + g,                      // Displays "Q" 
    e + g,                                  // Displays "r"
    a + c + d + f +g,                       // Displays "S"
    d + e + f + g,                          // Displays "t"
    a + e + f ,                             // Displays "T" 
    b + c + d + e + f,                      // Displays "U"
    c + d + e,                              // Displays "v" 
    b + d + f + g,                          // Displays "W"
    b + c + d + f + g,                      // Displays "Y" 
    a + b + d + e + g,                      // Displays "Z"
    g,                                      // Displays "-"
    h,                                      // Displays "."  
    0                                       // Displays " "
}; 
#undef a
#undef b
#undef c
#undef d
#undef e
#undef f
#undef g 

/**********************************宏定义**************************************/
#define DATA_DIR_OUT	P5DIR|=0XFF
#define CTRL_DIR_OUT    P3DIR|=0XFF
#define DATA_OUT        P5OUT
#define CTRL_OUT        P3OUT
/******************************************************************************/

char Nixie[8] = "\0\0\0\0\0\0\0\0";     //初始状态 不显示

/************************************************
* 函数名称：NixiettubeInit
* 功    能：初始化数码管使用的相关资源
* 参    数：无
* 返 回 值：无
*************************************************/
void NixiettubeInit()
{
    WDTCTL = WDT_ADLY_1_9;  //看门狗内部定时器模式16ms
    IE1 |= WDTIE;           //允许看门狗中断
    CTRL_DIR_OUT;
    DATA_DIR_OUT;
}

/************************************************
* 函数名称：NixiettubeClear
* 功    能：清屏，清除当前一行的显示(共一行8字符)
* 参    数：无
* 返 回 值：无
*************************************************/
void NixiettubeClear()
{
    for(int i = 0;i < 8;i++)
        Nixie[i] = Tab[SP];     //显示空格
}

/************************************************
* 函数名称：NixiettubeDisplayChar
* 功    能：显示字符;可显示字母参考Nixietube.h中的
            宏定义
* 参    数：
            ch：要显示的字符
            addr：位置，0-7从低位到高位(右到左)
* 返 回 值：无
* 说    明：调用该函数后，不影响其他位的显示。只是
            覆盖addr指定的位。
*************************************************/
void NixiettubeDisplayChar(char ch,char addr)
{
    if(ch == DOT)       //小数点,不需单独占一位
    {
        Nixie[addr] |= Tab[ch];
    }
    else
    {
        Nixie[addr] = Tab[ch];
    }
}

/************************************************
* 函数名称：NixiettubeInsertChar
* 功    能：右端插入字符;可显示字母参考Nixietube.h
            中的宏定义
* 参    数：ch：要插入的字符
* 返 回 值：无
* 说    明：调用该函数后，所有已显示字符左移一位，
            新的字符插入在最右端一位。可以用于用于
            在数据后面显示单位等。
*************************************************/
void NixiettubeInsertChar(char ch)
{
    if(ch == DOT)       ////小数点,不需单独占一位
    {
        Nixie[0] |= Tab[ch];
        return;
    }
    for(int i = 7;i > 0;i--)
        Nixie[i] = Nixie[i - 1];     //已显示字符左移一位
    Nixie[0] = Tab[ch];
}

/************************************************
* 函数名称：Display
* 功    能：扫描显示缓存区的字符
* 参    数：无
* 返 回 值：无 
* 说    明：每次扫描显示一位，同时指针移动，以供下
*           一次显示用。
*************************************************/
void Display()
{
    static char i = 0;      //记录扫描显示到哪位
    CTRL_OUT = 1<<i;
    DATA_OUT = Nixie[i];
    i++;
    if(i>7)
        i = 0;
}

/************************************************
函数名称：WDT_ISR
功    能：看门狗定时中断（16ms）
参    数：无
返回值  ：无
*************************************************/
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR()
{
    Display();
}
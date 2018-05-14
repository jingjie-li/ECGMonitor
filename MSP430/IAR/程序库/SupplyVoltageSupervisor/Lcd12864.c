/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Lcd12864.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机12864液晶程序库
 *      说明：  
 *          该程序完成12864各底层驱动，方便液晶程序的编写，可以作为
 *          各程序的底层驱动使用
 *          使用时只需把Lcd12864.c添加到工程中，然后在要调用液晶程
 *          序的源程序文件中加入对Lcd12864.h的包含；然后就可以调用
 *          头文件中声明的各个函数。
 *          
 * 创建标识：   刘中原20110707
 * 
 * 修改标识：   刘中原20110729
 * 修改描述：   加入LcdReadAddr、LcdReadData以移植printf函数
 * 
 * 修改标识：   刘中原20110828
 * 修改描述：   GotoXY，应该位于此文件；把GotoXY函数移动到此
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "Lcd12864.h"

/**********************************宏定义**************************************/

#define DATA_DIR_IN     P5DIR&=~0XFF
#define DATA_DIR_OUT	P5DIR|=0XFF
#define CTRL_DIR_OUT    P3DIR|=0X07
#define DATA_IN         P5IN
#define DATA_OUT        P5OUT
#define CLR_RS          P3OUT&=~BIT0
#define SET_RS          P3OUT|=BIT0
#define CLR_RW          P3OUT&=~BIT1
#define SET_RW          P3OUT|=BIT1
#define CLR_EN          P3OUT&=~BIT2
#define SET_EN          P3OUT|=BIT2

/******************************************************************************/


/*******************************************
函数名称：Delay1ms
功    能：延时约1ms的时间
参    数：无
返回值  ：无
********************************************/
void Delay1ms(void)
{
    char i;
    
    for(i = 150;i > 0;i--)  _NOP();
} 

/*******************************************
函数名称：DelayNms
功    能：延时N个1ms的时间
参    数：n--延时长度
返回值  ：无
********************************************/
void DelayNms(int n)
{
    int i;
    
    for(i = n;i > 0;i--)    Delay1ms();
}

/*******************************************
函数名称：WaitForEnable
功    能：判忙，等到忙结束
参    数：无
返回值  ：无
********************************************/
void WaitForEnable()
{
    char busy;
    
    CLR_RS;
    SET_RW;
    
    DATA_DIR_IN;
    
    do                       //判忙
    {
        SET_EN;
        _NOP();					
        busy = DATA_IN; 
        CLR_EN;
    }
    while(busy & 0x80); 
    
    DATA_DIR_OUT;
}

/*******************************************
函数名称：LcdWriteComm
功    能：向液晶中写控制命令
参    数：cmd--控制命令
返回值  ：无
********************************************/
void LcdWriteComm(char cmd)
{
    WaitForEnable();    //检测忙信号？
    
    CLR_RS;
    CLR_RW;
    
    DATA_OUT = cmd;	//写命令
    
    SET_EN;
    _NOP();
    CLR_EN;
}

/*******************************************
函数名称：LcdWriteData
功    能：向液晶中写显示数据
参    数：data--显示数据
返回值  ：无
********************************************/
void LcdWriteData(char data)
{
    WaitForEnable();
    
    SET_RS;
    CLR_RW;
    
    DATA_OUT = data;	//写数据
    
    SET_EN;
    _NOP();
    CLR_EN;
}

/*******************************************
函数名称：LcdInit
功    能：初始化液晶模块
参    数：无
返回值  ：无
********************************************/
void LcdInit()
{
    CTRL_DIR_OUT;
    
    DelayNms(500);
    LcdWriteComm(0x30);     //基本指令集
    LcdWriteComm(0x01);     //清屏，地址00H
    LcdWriteComm(0x06);     //光标的移动方向
    LcdWriteComm(0x0c);     //开显示，关游标
}

/*******************************************
函数名称：LcdWriteString
功    能：向液晶写入字符串，可以是汉字
参    数：
        addr：写入地址（显示地址）
             0x80-0x87：第一行
             0x90-0x97：第二行
             0x88-0x8F：第三行
             0x98-0x9F：第四行
        str：要显示的字符串,原则上是中文字符
             串，如果是英文字符串，必须两个一
             起，如果只需一个，就添加一个空格
返回值  ：无
********************************************/
void LcdWriteString(char addr,char *str)
{
    LcdWriteComm(addr);
    while(*str!='\0')
    {
        LcdWriteData(*str);
        str++;
    }
}

/*******************************************
函数名称：LcdReadData
功    能：从液晶中读取数据
参    数：无
返回值  ：读取得到的数据
********************************************/
char LcdReadData()
{
    char ch;
    
    WaitForEnable();
    
    SET_RS;
    SET_RW;
    
    DATA_DIR_IN;
    
    SET_EN;
    _NOP();
    
    ch = DATA_IN;	//读数据
    CLR_EN;
    DATA_DIR_OUT;
    
    return ch;
}

/*******************************************
函数名称：LcdReadAddr
功    能：从液晶中读取当前位置地址
参    数：无
返回值  ：读取得到的地址（0x80-0x9F）
********************************************/
char LcdReadAddr()
{
    char ch;
    
    WaitForEnable();
    
    CLR_RS;
    SET_RW;
    
    DATA_DIR_IN;
    
    SET_EN;
    _NOP();
    
    ch = DATA_IN;	//读数据
    CLR_EN;
    DATA_DIR_OUT;
    
    return (ch|0x80);
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
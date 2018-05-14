/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： TAPwm.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Spi通讯函数库(简化版)
 *      说明：  这个程序库完成定时器TA输出两路PWM波,可以方便的设置
 *              占空比。本程序是从《MSP430系列单片机系统工程设计与
 *              实践》这本书中TA_PWM函数移植来的。只在原来的基础上
                改了端口
 *      使用方法：
 *              工程中加入TAPwm.c文件，文件包含TAPwm.h文件；然后即
 *              使用本程序的函数。
 * 		
 * 创建标识：   刘中原20110826
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "TAPwm.h"

/****************************************************************************
* 名    称：TAPwmInit
* 功    能：TA定时器作为PWM发生器的初始化设置函数             
* 入口参数：Clk:时钟源 'S'=SMCLK;   'A'=ACLK ;     _____
                       'E'=TACLK(外部输入)    'e'= TACLK(TACLK取反)
            Div:时钟分频系数: 1/2/4/8
            Mode1:通道1的输出模式 'P'设为高电平输出，'N'低电平 ，0=禁用
            Mode2:通道2的输出模式 'P'设为高电平输出，'N'低电平 ，0=禁用

* 出口参数：1表示设置成功，0表示参数错误，设置失败。
* 说    明: 在调用PWM相关函数之前，需要调用该函数设置TA的模式和时钟源。
* 范    例: TAPwmInit('A',1,'P','P')TA时钟设为ACLK,通道1和通道2均为高电平输出
            TAPwmInit('S',4,'N','N')TA时钟设为SMCLK/4, 通道1、2均为低电平输出
            TAPwmInit('A',1,'P',0)TA时钟设为ACLK,通道1高电平输出,通道2不用,被
            禁用的PWM通道的输出管脚仍可作为普通IO口使用。
****************************************************************************/
char TAPwmInit(char Clk,char Div,char Mode1,char Mode2)
{
    TACTL = 0;                  //清除以前设置
    TACTL |= MC_1;              //定时器TA设为增计数模式  
    switch(Clk)                 //选择时钟源
    { 
        case 'A': case 'a':  TACTL|=TASSEL_1; break;    //ACLK
        case 'S': case 's':  TACTL|=TASSEL_2; break;    //SMCLK
        case 'E':            TACTL|=TASSEL_0; break;    //外部输入(TACLK)
        case 'e':            TACTL|=TASSEL_3; break;    //外部输入(TACLK取反)
        default :  return(0);                           //参数有误
    } 
    switch(Div)                 //选择分频系数
    { 
        case 1:   TACTL|=ID_0; break;   //1
        case 2:   TACTL|=ID_1; break;   //2
        case 4:   TACTL|=ID_2; break;   //4
        case 8:   TACTL|=ID_3; break;   //8
        default :  return(0);           //参数有误
    } 
    switch(Mode1)               //设置PWM通道1的输出模式。
    { 
        case 'P':case 'p':          //如果设置为高电平模式
            TACCTL1 = OUTMOD_7;     //高电平PWM输出
            P1SEL |= BIT2;          //从P1.2输出 (不同型号单片机可能不一样)
            P1DIR |= BIT2;          //从P1.2输出 (不同型号单片机可能不一样)              
            break;
        case 'N':case 'n':          //如果设置为低电平模式          
            TACCTL1 = OUTMOD_3;     //低电平PWM输出
            P1SEL |= BIT2;          //从P1.2输出 (不同型号单片机可能不一样) 
            P1DIR |= BIT2;          //从P1.2输出 (不同型号单片机可能不一样)                
            break; 
        case '0':case 0:            //如果设置为禁用          
            P1SEL &= ~BIT2;         //P1.2恢复为普通IO口              
            break;                 
        default :  return(0);       //参数有误
    } 
    switch(Mode2)                   //设置PWM通道1的输出模式。
    { 
        case 'P':case 'p':          //如果设置为高电平模式
            TACCTL2 =OUTMOD_7;      //高电平PWM输出
            P1SEL |= BIT3;          //从P1.3输出 (不同型号单片机可能不一样)
            P1DIR |= BIT3;          //从P1.3输出 (不同型号单片机可能不一样)
            break;
        case 'N':case 'n':          //如果设置为低电平模式          
            TACCTL2 =OUTMOD_3;      //低电平PWM输出
            P1SEL |= BIT3;          //从P1.3输出 (不同型号单片机可能不一样)  
            P1DIR |= BIT3;          //从P1.3输出 (不同型号单片机可能不一样)              
            break; 
        case '0':case 0:            //如果设置为禁用          
            P1SEL &= ~BIT3;         //P1.3恢复为普通IO口              
            break;                 
        default :  return(0);       //参数有误
    }    
    return(1);  
}

/****************************************************************************
* 名    称：TAPwmSetPeriod
* 功    能：设置PWM发生器的周期             
* 入口参数：Period:周期(0~65535) 时钟个数
* 出口参数：无
* 说    明: 设置对2路PWM同时生效
* 范    例: TAPwmSetPeriod(500)设置PWM方波周期为500个时钟周期
****************************************************************************/
void TAPwmSetPeriod(unsigned int Period)
{
    TACCR0 = Period;
}

/****************************************************************************
* 名    称：TAPwmSetDuty
* 功    能：设置PWM输出"有效"的时间             
* 入口参数：Channel: 当前设置的通道号  1/2
            Duty:    PWM有效时间(0~65535) 时钟个数
* 出口参数：无
* 说    明: 若通道输出模式设为高电平输出模式，Duty值等于高电平时钟个数
            若通道输出模式设为低电平输出模式，Duty值等于低电平时钟个数
* 范    例: TAPwmSetDuty(1,30)设置PWM通道1方波的高电平周期为30个时钟
            TAPwmSetDuty(2,80)设置PWM通道2方波的高电平周期为80个时钟
****************************************************************************/
void TAPwmSetDuty(char Channel,unsigned int Duty)
{
    switch(Channel)
    {
        case 1: TACCR1=Duty; break; 
        case 2: TACCR2=Duty; break;    
    }
}

/****************************************************************************
* 名    称：TAPwmSetPermill
* 功    能：设置PWM输出的占空比(千分比)             
* 入口参数：Channel: 当前设置的通道号  1/2
            Percent: PWM有效时间的千分比 (0~1000) 
* 出口参数：无
* 说    明: 1000=100.0%  500=50.0% ，依次类推        
* 范    例: TAPwmSetPermill(1,300)设置PWM通道1方波的占空比为30.0%
            TAPwmSetPermill(2,825)设置PWM通道2方波的占空比为82.5%
****************************************************************************/
void TAPwmSetPermill(char Channel,unsigned int Percent)
{
    unsigned long int Period;
    unsigned int Duty;
    Period = TACCR0;
    Duty = Period * Percent / 1000;
    TAPwmSetDuty(Channel,Duty);
}
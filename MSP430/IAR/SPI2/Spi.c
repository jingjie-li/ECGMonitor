/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Spi.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Spi通讯函数库(简化版)
 *      说明：  这个程序库完成Spi的初始化、发送数据、接收数据；
 *              本程序只完成msp430的spi的主机模式，从机模式只需把时
 *              钟和波特率去掉即可，具体参考用户指南；
 *              MSP430 SPI 同步串行传输时，时钟不再提供小数分频，本
 *              程序采用brclk/baud作为分频系数，小数分频直接忽略
 *              使Spi功能用方法：把Spi.c加入到项目，同时在要调用此
 *              程序库的程序文件中加入包含Spi.h的语句；这样即可正常
 *              使用头文件中声明的程序了；详细可参考 本工程 和 
 *              main.c
 *              如 果要改为USART1模块，只需把宏定义的x 对应的0改为
 *              1即可；如果要同时使用0、1两个模块，就需要把函数的名
 *              字该为不同，两个文件分别访问0、1两个模块
 * 		
 * 创建标识：   刘中原20110808
 * 
 * 修改标识：   刘中原20110819
 * 修改描述：   添加写入同时返回读取的值函数SpiWriteData(char c)，
 *              因为这是主控模块，每次写入数据，均提供8位时钟周期，
 *              每次的写入必有数据返回；7位也是这样，所以这个函数是
 *              需要的.发送、接收均需调用此函数；头文件也做出相应更
 *              改，去掉了只读取、写入的函数声明；读取时,这样调用：
 *              =============SpiWriteDatWithReturn(0xFF)===========
 * 
**----------------------------------------------------------------*/

#include <msp430x14x.h>
#include "Spi.h"

/***********************************宏定义*********************************/
#define UxCTL   U0CTL
#define UxRCTL  U0RCTL
#define UxTCTL  U0TCTL

#define UxBR0   U0BR0
#define UxBR1   U0BR1
#define UxMCTL  U0MCTL

#define UxRXBUF U0RXBUF
#define UxTXBUF U0TXBUF

#define UxME    U0ME
#define UxIE    U0IE
#define UxIFG   U0IFG

#define USPIEx  USPIE0

#define URXIEx  URXIE0
#define UTXIEx  UTXIE0

#define USARTxTX_VECTOR USART0TX_VECTOR
#define USARTxRX_VECTOR USART0RX_VECTOR

#define USPI3ON P3SEL |= 0X0E           //SPI 0的第二功能打开(三线模式)
#define USPI4ON P3SEL |= 0X0F           //SPI 0的第二功能打开(四线模式)
/**************************************************************************/

char TxFlag=1;
char RxFlag=0;

/****************************************************************************
* 名    称：SpiMasterInit
* 功    能：初始化SPI。设置波特率等，主机模式
* 入口参数：
*           baud:       波特率      (300~500k)
                        只能是串口使用时钟的整数分频，spi模式UxMCTL寄存器无效
                        若为整数分频，将分频系数设为 整数部分，将不支持小数分
                        频
            datsBits:   数据位位数  (7或8)
            mode:       停止位位数  (3或4)
                        3：三线模式  
                        4：四线模式
            clkMode     时钟模式    (0-3)   控制时钟的极性和相位
                        0： 上升沿发送，下降沿接收 正常UCLK
                        1： 下降沿发送，上升沿接收 正常UCLK
                        2： 下降沿发送，上升沿接收 延时半个周期UCLK
                        3： 上升沿发送，下降沿接收 延时半个周期UCLK
* 出口参数：返回值为1时表初化成功，为0表示参数有错误
* 范    例: SpiMasterInit(9600,8,3,0)  //设成9600bps，8位数据，三线模式，时钟
                                        模式0,9600波特率，是32768三分频，小数
                                        分频无效，实际波特率，将大于9600
            SpiMasterInit(16364,7,4,1) //设成16364bps，7位数据，四线模式,模式
                                        32768，二分频
****************************************************************************/
char SpiMasterInit(long baud,char dataBits,char mode,char clkMode)
{
    long int brclk;                 //波特率发生器时钟频率
    
    UxCTL |= SWRST;                 //初始
    
    //反馈选择位，为1，发送的数被自己接收，用于测试，正常使用时注释掉
    //UxCTL |= LISTEN;
    
    UxCTL |= SYNC + MM;             //SPI 主机模式
    
    //时钟源设置
    UxTCTL &=~ (SSEL0+SSEL1);       //清除之前的时钟设置
    if(baud<=16364)                 //
    {
      UxTCTL |= SSEL0;              //ACLK，降低功耗
      brclk = 32768;                //波特率发生器时钟频率=ACLK(32768)
    }
    else
    {
      UxTCTL |= SSEL1;              //SMCLK，保证速度
      brclk = 1000000;              //波特率发生器时钟频率=SMCLK(1MHz)
    }
    
    //------------------------设置波特率-------------------------   
    if(baud < 300||baud > 115200)   //波特率超出范围
    {
        return 0;
    }
    //设置波特率寄存器
    int fen = brclk / baud;         //分频系数
    if(fen<2)return (0);            //分频系数必须大于2
    else
    {
        UxBR0 = fen / 256;
        UxBR1 = fen % 256;
    }
    
    //------------------------设置数据位-------------------------    
    switch(dataBits)
    {
        case 7:case'7': UxCTL &=~ CHAR; break;      //7位数据
        case 8:case'8': UxCTL |= CHAR;  break;      //8位数据
        default :       return(0);                  //参数错误
    } 
    //------------------------设置模式---------------------------    
    switch(mode)
    {
        case 3:case'3': UxTCTL |= STC;  USPI3ON;    break;  //三线模式
        case 4:case'4': UxTCTL &=~ STC; USPI4ON;    break;  //四线模式
        default :       return(0);                          //参数错误
    }
    
    //------------------------设置UCLK模式-----------------------  
    switch(clkMode)
    {
        case 0:case'0': UxTCTL &=~ CKPH; UxTCTL &=~ CKPL;   break;  //模式0
        case 1:case'1': UxTCTL &=~ CKPH; UxTCTL |= CKPL;    break;  //模式1
        case 2:case'2': UxTCTL |= CKPH;  UxTCTL &=~ CKPL;   break;  //模式2
        case 3:case'3': UxTCTL |= CKPH;  UxTCTL |= CKPL;    break;  //模式3
        default :       return(0);                                  //参数错误
    }
    
    UxME |= USPIEx;             //模块使能
    
    UxCTL &= ~SWRST;            // Initialize USART state machine
    
    UxIE |= URXIEx + UTXIEx;    // Enable USART0 RX interrupt 
    
    return(1);                  //设置成功
}

/****************************************************************************
* 名    称：UartLpm
* 功    能：串口收/发等待过程中，将时钟系统的部分时钟该关掉，休眠省电
* 入口参数：无
* 出口参数：无
* 说    明: 若与其他外设的时钟冲突，可注释掉该函数，但会增加功耗。
****************************************************************************/
void SpiLpm()
{
    if(UxTCTL&SSEL0) LPM3;  //若以ACLK 作时钟，进入LPM3休眠(仅打开ACLK)
    else             LPM0;  //若以SMCLK作时钟，进入LPM0休眠(不关闭SMCLK)
}

/****************************************************************************
* 名    称：UartWriteChar
* 功    能：向串口写一个字节数据
* 入口参数：c:  待发送的一字节数据
* 出口参数：无
* 说    明: 在等待发送完毕的过程中，CPU会休眠
****************************************************************************/
void SpiWriteDat(char c)
{ 
    while (TxFlag==0) SpiLpm();  // 等待上一字节发完，并休眠
    TxFlag=0;                     //
    UxTXBUF=c;
}

/****************************************************************************
* 名    称：UartReadChar
* 功    能：从串口读取1字节数据
* 入口参数：无  
* 出口参数：收到的一字节数据
* 说    明: 如果串口没有数据，会一直等待。等待过程中，CPU会休眠
****************************************************************************/
char SpiReadDat()
{ 
    while (RxFlag==0) SpiLpm(); // 收到一字节?
    RxFlag=0;
    return(UxRXBUF);
}

/****************************************************************************
* 名    称：SpiWriteData
* 功    能：有返回的写入
* 入口参数：c:  待发送的一字节数据
* 出口参数：char：写入的同时收到的字节
* 说    明: SPI是全双工通信，每次发送，接收时钟也在接收，发送完成后的半个时钟
*           周期后，读到一个字符，这个字符也许不是从设备返回的，仅仅是信号线
*           的默认电平，根据实际情况判断；当只需读数据时，也要用此函数，否则
*           没有时钟提供给从设备，不能读到数据；强烈建议使用时，发送接收只调
*           此函数，否则读取的可能是上一次采样的字符 \0（默认电平）
****************************************************************************/
char SpiWriteData(char c)
{
    SpiWriteDat(c);
    return SpiReadDat();
}

/****************************************************************************
* 名    称：UartRx
* 功    能：串口接收中断，每接收到1字节会发生一次中断
****************************************************************************/
#pragma vector=USARTxRX_VECTOR
__interrupt void UartRx()
{
    RxFlag=1;
    __low_power_mode_off_on_exit();
}

/****************************************************************************
* 名    称：UartTx
* 功    能：串口发送中断，每发完1字节会发生一次中断
****************************************************************************/
#pragma vector=USARTxTX_VECTOR
__interrupt void UartTx ()
{
    TxFlag=1;
    __low_power_mode_off_on_exit();
}

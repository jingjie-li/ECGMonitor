/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Uart.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机串口通讯函数库(简化版)
 *      说明：  这个程序库完成串口的初始化、发送字符和字符串、接收
 *              使字符功能用方法：把Uart.c加入到项目，同时在要调用
 *              此程序库的程序文件中加入包含Uart.h的语句；这样即可
 *              正常使用头文件中声明的程序了；详细可参考 本工程 和
 *               main.c
 *              如 果要改为UART1模块，只需把宏定义的x 对应的0改为1
 *              即可；如果要同时使用0、1两个模块，就需要把函数的名
 *              字该为不同，两个文件分别访问0、1两个模块
 * 		
 * 创建标识：   刘中原20110622
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/
#include <stdint.h>
#include <msp430x14x.h>
#include "Uart.h"

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

#define UTXEx   UTXE0
#define URXEx   URXE0

#define URXIEx  URXIE0
#define UTXIEx  UTXIE0

#define UARTxTX_VECTOR  UART0TX_VECTOR
#define UARTxRX_VECTOR  UART0RX_VECTOR

#define UARTON  P3SEL |= 0X30           // P3.4,5 = USART0 TXD/RXD
/**************************************************************************/

char TxFlagu=1;
char RxFlagu=0;


/****************************************************************************
* 名    称：abs
* 功    能：求绝对值
* 入口参数：i:整数
* 出口参数：int 求得的绝对值
****************************************************************************/
int abs(int i)
{
    return (i>=0?i:(-i));
}

/***************************************************************************
* 名    称：SetBaudRateRegisters
* 功    能：根据时钟 波特率设置对应寄存器
* 入口参数：
*           clk:        所选时钟频率（如：32768）
*           baud:       波特率      (300~115200)
* 出口参数：无
* 范    例: SetBaudRateRegisters(32768,9600)//用时钟频率32768产生9600的波特率
****************************************************************************/
void SetBaudRateRegisters(long clk,long baud)
{
    int n = clk / baud;     //整数波特率
    char mSum = 0;          //Σmi
    int txEr0;              //对应位为0时错误率
    int txEr1;              //对应位为1时错误率
    char i = 0;             //循环计数
    
    UxBR1 = n >> 8;         //高8位
    UxBR0 = n & 0xff;       //低8位
    UxMCTL = 0;
    
    //循环 比较错误率大小 设置UxMCTL
    for(;i < 8;i++)
    {
        txEr0 = 100 * baud * ((i + 1) * n + mSum) / clk - 100 * (i + 1);
        txEr1 = 100 * baud * ((i + 1) * n + mSum + 1) / clk - 100 * (i + 1);
        if(abs(txEr1) < abs(txEr0))
        {
            mSum++;
            UxMCTL |= (1<<i);
        }
    }
}

/****************************************************************************
* 名    称：UartInit()
* 功    能：初始化串口。设置波特率等
* 入口参数：
*           baud:       波特率      (300~115200)
            parity:     奇偶校验位  ('n'=无校验  'p'=偶校验  'o'=奇校验)
            datsBits:   数据位位数  (7或8)
            stopBits:   停止位位数  (1或2)
* 出口参数：返回值为1时表初化成功，为0表示参数有错误
* 范    例: UartInit(9600,'n',8,1) //设成9600bps，无校验，8位数据，1位停止位
            UartInit(2400,'p',7,2) //设成2400bps，偶校验，7位数据，2位停止位
****************************************************************************/
char UartInit(long baud,char parity,char dataBits,char stopBits)
{
    long int brclk;                 //波特率发生器时钟频率
    
    UxCTL |= SWRST;                 //初始
    
    //时钟源设置
    UxTCTL &=~ (SSEL0+SSEL1);       //清除之前的时钟设置
    if(baud<=9600)                  //
    {
      UxTCTL |= SSEL0;              //ACLK，降低功耗
      brclk = 32768;                //波特率发生器时钟频率=ACLK(32768)
    }
    else
    {
      UxTCTL |= SSEL1;              //SMCLK，保证速度
      brclk = 8000000;              //波特率发生器时钟频率=SMCLK(1MHz)
    }
    
    //------------------------设置波特率-------------------------   
    if(baud < 300||baud > 115200)   //波特率超出范围
    {
        return 0;
    }
    SetBaudRateRegisters(brclk,baud);         //设置波特率寄存器
  
    //------------------------设置校验位-------------------------  
    switch(parity)
    {
        case 'n':case'N': UxCTL &=~ PENA;               break;  //无校验
        case 'p':case'P': UxCTL |= PENA + PEV;          break;  //偶校验
        case 'o':case'O': UxCTL |= PENA; UxCTL &=~ PEV; break;  //奇校验  
        default :         return(0);                            //参数错误
    }
    
    //------------------------设置数据位-------------------------    
    switch(dataBits)
    {
        case 7:case'7': UxCTL &=~ CHAR; break;      //7位数据
        case 8:case'8': UxCTL |= CHAR;  break;      //8位数据
        default :       return(0);                  //参数错误
    } 
    //------------------------设置停止位-------------------------    
    switch(stopBits)
    {
        case 1:case'1': UxCTL &= ~SPB;  break;      //1位停止位
        case 2:case'2': UxCTL |= SPB;   break;      //2位停止位
        default :       return(0);                  //参数错误
    }
    
    UARTON;                     //端口使能
    UxME |= UTXEx + URXEx;      //发送 接收使能
    
    UCTL0 &= ~SWRST;            // Initialize USART state machine
    
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
void UartLpm()
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
void UartWriteChar(char c)
{ 
    while (TxFlagu==0) UartLpm();  // 等待上一字节发完，并休眠
    TxFlagu=0;                     //
    UxTXBUF=c;
}

void UartWriteint(uint8_t c)
{ 
  while (TxFlagu==0) UartLpm();  // 等待上一字节发完，并休眠
    TxFlagu=0;                     //
    UxTXBUF=c;
}
/****************************************************************************
* 名    称：UartReadChar
* 功    能：从串口读取1字节数据
* 入口参数：无  
* 出口参数：收到的一字节数据
* 说    明: 如果串口没有数据，会一直等待。等待过程中，CPU会休眠
****************************************************************************/
char UartReadChar()
{ 
    while (RxFlagu==0) UartLpm(); // 收到一字节?
    RxFlagu=0;
    return(UxRXBUF);
}

uint8_t UartReadint()
{ 
    while (RxFlagu==0) UartLpm(); // 收到一字节?
    RxFlagu=0;
    return(UxRXBUF);
}
/****************************************************************************
* 名    称：UartWriteStr
* 功    能：向串口写一个字符串
* 入口参数：s：要写入的字符串  
* 出口参数：无
* 说    明: 如果没有到 NULL 继续写入字符
****************************************************************************/
void UartWriteStr(char *s)
{
    while(*s)
    {
        UartWriteChar(*s++);
    }
}

void UartWritearray(uint8_t *s)
{
    while(*s)
    {
        UartWriteint(*s++);
    }
}
/****************************************************************************
* 名    称：UartRx
* 功    能：串口接收中断，每接收到1字节会发生一次中断
****************************************************************************/
#pragma vector=UARTxRX_VECTOR
__interrupt void UartRx()
{
    RxFlagu=1;
    __low_power_mode_off_on_exit();
}

/****************************************************************************
* 名    称：UartTx
* 功    能：串口发送中断，每发完1字节会发生一次中断
****************************************************************************/
#pragma vector=UARTxTX_VECTOR
__interrupt void UartTx ()
{
    TxFlagu=1;
    __low_power_mode_off_on_exit();
}

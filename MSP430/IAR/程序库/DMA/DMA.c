/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： DMA.c
 * 
 * 文件功能描述：   
 *          MSP430F16x系列单片机DMA程序库
 *      说明：  
 *          该程序完成DMA模块的通用程序库，调用本程序可以完成DMA设置
 *          或是重新使能DMA，以及需要软件启动时的启动传输函数。
 *      使用方式：
 *          工程中加入本文件DMA.c，源程序中文件包含DMA.h。然后调用相
 *          应函数完成DMA的设置等功能。
 *          
 * 创建标识：   刘中原20110829
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "DMA.h"

/************************************************************
* 函数名称：DMAInit
* 功    能：DMA用到的相关寄存器等资源初始化
* 参    数：channel:通道 0 1 2
*           trigger：触发源 
        触发源：0000    DMAREQ bit (software trigger)
                0001    TACCR2 CCIFG bit
                0010    TBCCR2 CCIFG bit
                0011    URXIFG0 (UART/SPI mode), USART0 data received (I2C mode)
                0100    UTXIFG0 (UART/SPI mode), USART0 transmit ready (I2C mode)
                0101    DAC12_0CTL DAC12IFG bit
                0110    ADC12 ADC12IFGx bit
                0111    TACCR0 CCIFG bit
                1000    TBCCR0 CCIFG bit
                1001    URXIFG1 bit
                1010    UTXIFG1 bit
                1011    Multiplier ready
                1100    No action
                1101    No action
                1110    DMA0IFG bit triggers DMA channel 1
                        DMA1IFG bit triggers DMA channel 2
                        DMA2IFG bit triggers DMA channel 0
                1111    External trigger DMAE0
*           transMode：传送模式
                'S'：单次传输   's'：重复单次传输(single)
                'B'：块传输     'b'：重复块传输(block)
                'I'：突发块传输 'i'：重复突发块传输(interleaved) 交错
*           srcMode：源地址端模式
                0   000：字传输，地址不变
                1   001：字传输，地址不变
                2   010：字传输，地址递减
                3   011：字传输，地址递增
                4   100：字节传输，地址不变
                5   101：字节传输，地址不变
                6   110：字节传输，地址递减
                7   111：字节传输，地址递增
*           dstMode：目的地址模式 取值的意义同srcMode
*           src：源地址 16位
*           dst：目的地址 16位
*           size：每个块的字节或字 数
* 返 回 值：无
* 说    明：调用此函数可以设置对应DMA通道的相关参数，其他默认
            如下：有DMA请求时，等CPU当前指令完成后响应； 优先
            级顺序固定 DMA0-2通道优先级减低； 不允许外部NMI中
            断DMA传输；不允许DMA中断；上升沿触发DMA传输。若有
            其他需要可以自行更改。
* 示    例：DMAInit(0,0x01,'s',0,1,0x0240,0x0220,1): 字到字重
            复 单字传输。
*************************************************************/
void DMAInit(char channel,char trigger,char transMode,char srcMode,char dstMode,
             unsigned int src,unsigned int dst,unsigned int size)
{
    unsigned int *DMAxCTL,*DMAxSA,*DMAxDA,*DMAxSZ;
    
    DMACTL0 = trigger << (channel << 2);
    DMACTL1 = 0x04;         //DMA收到触发请求时，等待当前指令执行完成后
    
    switch (channel)        //选择当前设置哪个DMA通道
    {
        case 0: 
            DMAxCTL = (unsigned int *)&DMA0CTL;
            DMAxSA = (unsigned int *)&DMA0SA;
            DMAxDA = (unsigned int *)&DMA0DA;
            DMAxSZ = (unsigned int *)&DMA0SZ;
            break;                                      //指针 = 0通道控制
        case 1: 
            DMAxCTL = (unsigned int *)&DMA1CTL;
            DMAxSA = (unsigned int *)&DMA1SA;
            DMAxDA = (unsigned int *)&DMA1DA;
            DMAxSZ = (unsigned int *)&DMA1SZ;
            break;                                      //指针 = 1通道控制
        case 2: 
            DMAxCTL = (unsigned int *)&DMA2CTL;
            DMAxSA = (unsigned int *)&DMA2SA;
            DMAxDA = (unsigned int *)&DMA2DA;
            DMAxSZ = (unsigned int *)&DMA2SZ;
            break;                                      //指针 = 2通道控制
    }
    
    switch (transMode)      //设置DMA通道的传输模式
    {
        case 'S': *DMAxCTL = DMADT_0;   break;          //单次传输
        case 's': *DMAxCTL = DMADT_4;   break;          //重复单次传输
        case 'B': *DMAxCTL = DMADT_1;   break;          //块传输
        case 'b': *DMAxCTL = DMADT_5;   break;          //重复块传输
        case 'I': *DMAxCTL = DMADT_2;   break;          //突发块传输 交错
        case 'i': *DMAxCTL = DMADT_6;   break;          //重复突发块传输 交错
    }
    
    *DMAxCTL |= (srcMode & 0x04) << 2;                  //源 字或字节
    *DMAxCTL |= (srcMode & 0x03) << 8;                  //源 地址改变方式
    
    *DMAxCTL |= (dstMode & 0x04) << 3;                  //目的 字或字节
    *DMAxCTL |= (dstMode & 0x03) << 10;                 //目的 地址改变方式
    
    *DMAxSA = src;
    *DMAxDA = dst;
    *DMAxSZ = size;
    
    *DMAxCTL |= DMAEN;                                  //DMA使能
}

/************************************************************
* 函数名称：DMAReEnable
* 功    能：DMA重新使能
* 参    数：channel:要使能的通道
* 返 回 值：无
* 说    明：DMA启动后，若不是重复模式，完成一次传输后，DMAEN位
            自动复位；要再次传输则需重新是能。如果是重复模式，
            DMAEN位不复位，可以继续触发传输。   重复模式包括：
            重复单次传输(single)\重复块传输(block)\重复突发块
            传输(interleaved 交错)
*************************************************************/
void DMAReEnable(char channel)
{
    switch (channel)        //使能对应通道
    {
        case 0: DMA0CTL |= DMAEN;   break;      //0通道
        case 1: DMA1CTL |= DMAEN;   break;      //1通道
        case 2: DMA2CTL |= DMAEN;   break;      //2通道
    }
}

/************************************************************
* 函数名称：DMAStart
* 功    能：当DMA设置为软件触发模式时，用此函数触发DMA传输。
* 参    数：channel:要触发传输的通道
* 返 回 值：无
* 说    明：当触发源设置为：0000 DMAREQ bit (software trigger)
            时，需要DMAREQ位触发DMA开始传输。 调用此函数即完成
            此功能。
*************************************************************/
void DMAStart(char channel)
{
    switch (channel)        //使能对应通道
    {
        case 0: DMA0CTL |= DMAREQ;  break;      //0通道
        case 1: DMA1CTL |= DMAREQ;  break;      //1通道
        case 2: DMA2CTL |= DMAREQ;  break;      //2通道
    }
}

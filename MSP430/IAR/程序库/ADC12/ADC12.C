/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： ADC12.c
 * 
 * 文件功能描述：   
 *          MSP430F16x系列单片机ADC12程序库
 *      说明：  
 *          该程序完成ADC12模块的通用程序框架，方便以后使用；
 *          程序主要实现了，ADC12模块的初始化函数，仅仅实现了
 *          多通道的单次和多次转换，单通道的可以用参数,多通道
 *          模式下设置一个通道.ADC12启动转换函数完成启动ADC12
 *          开始AD转换。中断程序必须自己添加处理函数(根据实际
 *          使用的通道情况。)
 *          
 *      
 *      使用方式：
 *          工程中加入ADC12.c文件,源文件加入对ADC12.h的文件包
 *          含;中断处理函数添加自己的处理逻辑。具体可以参考本
 *          项目
 *          
 * 创建标识：   刘中原20110823
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "ADC12.h"

int results[3][32];

/********************************************************
* 函数名称：ADC12Init
* 功    能：ADC12初始化
* 参    数：
*           n：使用通道数：共16（0-15）个可以使用
*           channels[]:对应通道设置，高四位，参考源选择；
            低四位，通道选择。具体如下：
            SREFx Bits
            6-4
            Select reference
            000 VR+ = AVCC and VR. = AVSS
            001 VR+ = VREF+ and VR. = AVSS
            010 VR+ = VeREF+ and VR. = AVSS
            011 VR+ = VeREF+ and VR. = AVSS
            100 VR+ = AVCC and VR. = VREF./ VeREF.
            101 VR+ = VREF+ and VR. = VREF./ VeREF.
            110 VR+ = VeREF+ and VR. = VREF./ VeREF.
            111 VR+ = VeREF+ and VR. = VREF./ VeREF.
            INCHx Bits
            3-0
            Input channel select
            0000 A0
            0001 A1
            0010 A2
            0011 A3
            0100 A4
            0101 A5
            0110 A6
            0111 A7
            1000 VeREF+
            1001 VREF./VeREF.
            1010 Temperature sensor
            1011 (AVCC – AVSS) / 2
            1100 (AVCC – AVSS) / 2
            1101 (AVCC – AVSS) / 2
            1110 (AVCC – AVSS) / 2
            1111 (AVCC – AVSS) / 2
*           rep：0：单次模式 非0：多次 
* 返 回 值：成功返回1，参数错误返回 0
* 说    明：此程序可以完成AD通用的初始化，这里选用的时钟是
            SMCLK，参考电压内部打开的是2.5v(必要时可以更改
            本函数，改变内部参考电压的值或关闭之)。
*********************************************************/
char ADC12Init(char n,char channels[],char rep)
{
    if(n>15)
        return 0;
    //SHT0_0 
    ADC12CTL0 = ADC12ON + MSC + SHT0_0 + REFON + REF2_5V;// 开启ad,参考电压2.5v
    ADC12CTL1 = SHP + ADC12SSEL_3;                  //Use sampling timer, SMCLK
    
    for(int i = 0;i < n;i++)
    {
        if(channels[i] >= 0x80)
            return 0;
        *(char*)(ADC12MCTL0_ + i) = channels[i];    //每个MCTL设置
    }
    *(char*)(ADC12MCTL0_ + n - 1) |= EOS;           //序列结束
    
    if(rep != 0)                                  //多次转换
    {
        ADC12CTL1 |= CONSEQ_3;
    }
    else
    {
        ADC12CTL1 |= CONSEQ_1;
    }
    
    ADC12IE = 1<<(n-1);                                 // Enable ADC12IFG.n-1
    return 1;
}

/********************************************************
* 函数名称：ADC12Start
* 功    能：ADC12开始转换
* 参    数：无
* 返 回 值：无
* 说    明：初始化完成后调用此函数，即可启动ADC12开始转换
*********************************************************/
void ADC12Start()
{
    ADC12CTL0 |= ENC;
    ADC12CTL0 |= ADC12SC;
}

/********************************************************
* 函数名称：ADC12ISR
* 功    能：ADC12中断处理程序
* 参    数：无
* 返 回 值：无
* 说    明：每次当多个通道转换完成后，打开中断时，单片机会
            自动调用本函数，使用时需要自己添加处理逻辑（删
            掉现在的函数体。）
*********************************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
    static int i;
    results[0][i] = ADC12MEM0;                // Move results, IFG is cleared
    results[1][i] = ADC12MEM1;                // Move results, IFG is cleared
    results[2][i] = ADC12MEM2;                // Move results, IFG is cleared
    i++;
    if(i>31)                                  //多次转换时 转换次数
    {
        //多次重复采样时，在这里方处理函数
        ADC12CTL0 &=~ ENC;                      //停止转换
        i=0;
    }

}
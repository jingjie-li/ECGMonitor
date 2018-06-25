/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： main.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机串口通讯函数库示例程序
 *      说明：  
 *          该程序示范串口通讯函数库内的各函数使用方法，同时可作为
 *          串口测试程序用。该程序的演示需要通过Windows自带的"超级
 *          终端"软件，或是串口调试器进行。
 *
 *          运行后，先输出两个字符串  
 *          UartWriteChar 函数工作正常!
 *          下面测试串口收发函数
 *          然后，将按原字符回复，串口调试器发送什么就接收什么
 *
 * 创建标识：   刘中原20110622
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/
#include <stdint.h>
#include "msp430x14x.h"   //430寄存器头文件
#include<msp430.h>  
#include "Uart.h"         //串口通讯程序库头文件
//#include "Spi.h"


char str[] = "UartWriteChar"; //ROM中一个字符串
char str1[] = "start conversation!"; //ROM中一个字符串
char str2[] = "stop conversation!"; //ROM中一个字符串
char q = 'Q';


int count = 0;
void select_xt2(void){  
      
    unsigned char i;  
      
    /*------选择系统主时钟为8MHz-------*/  
    BCSCTL1 &= ~XT2OFF;                 //打开XT2高频晶体振荡噿      
    do{  
        IFG1 &= ~OFIFG;                 //清除晶振失败标志  
        for (i = 0xFF; i > 0; i--);     //等待8MHz晶体起振  
    }while ((IFG1 & OFIFG));             //晶振失效标志仍然存在＿    
    BCSCTL2 |= SELM_2 + SELS;           //MCLK和SMCLK选择高频晶振    
  
}  
  
void main(){  
    WDTCTL = WDTPW + WDTHOLD;  
    select_xt2();  
      
    P2DIR = 0xfa;  
    P2OUT = 0xff;    
    CCTL1 = CCIE;                            // CCR1 中断使能  
    CCR1 = 10000;  
    TACTL = TASSEL_2 + MC_2 + ID_3;          // SMCLK = 1MHz, 连续计数模式 
    char chr;               //串口测试中，收到的字节
    UartInit(115200,'n',8,1);//串口初始化,设置成38400bps,无校验,8位数据,1位停止
    _EINT();  //打开全局中断  
      
    //P2OUT ^= BIT7;
    chr = UartReadChar(); 
    P2OUT ^= BIT6; 
    
    while(1){      
        switch(chr)
        {
        case 'S':
          P2OUT ^= BIT6; 
          UartWriteint(count);
          if(count >= 50){  
            count = 0;  
            P2OUT ^= BIT5;                   //led灯每0.5s变化一次  
            UartWriteStr(str1);
            _BIS_SR(CPUOFF);
            _NOP();
          }
          else{
            P2OUT ^= BIT4;
          }
          break;
        case 'M': 
          UartWriteint(count);
          break;
        }
          
    }  
  
}
#pragma vector=TIMERA1_VECTOR  
__interrupt void Timer_A1(void)  
{  
    switch(TAIV){  
        case 2:  
            CCR1 += 10000;                    //   
            count ++;  
    }  
      
      
}   




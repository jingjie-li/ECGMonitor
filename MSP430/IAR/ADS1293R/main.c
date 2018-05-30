
#include <msp430x14x.h>
#include "Spi.h"         //串口通讯程序库头文件
#include "MSP430_Spi.h" 
#include "TI_ADS1293.h" 
#include "TI_ADS1293_setting.h"

char str[] = "UartWriteChar 函数工作正常!"; //ROM中一个字符串

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
/*******************************************
函数名称：Delays
功    能：延时一会
参    数：无
返回值  ：无
********************************************/
void Delays(void)
{
    uchar i=20;
    uint8 j;

    while(i--)
    {
            j=2000;
            while(j--);
    }
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  ClkInit();
  // 主机模式，波特率25000,8位数据位，三线模式，时钟模式0（具体见spi.c）
  SpiMasterInit(25000,8,3,0);
  _EINT(); 
  
  P1DIR = 0xff;
  P1SEL = 0x00;  
  TI_ADS1293_WriteRegSettings();  
  while(1)                    //串口测试
  {
      TI_ADS1293_SPIWriteReg(0x01, 0x50);
      Delays();

  }

}


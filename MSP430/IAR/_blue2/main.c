
#include "msp430x14x.h"   //430寄存器头文件
#include "Uart.h"         //串口通讯程序库头文件

typedef unsigned char uchar;
typedef unsigned int  uint;

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
    uint j;

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

  char value = 0;
    
  //串口初始化之前必须调用此函数，SMCLK设为1M，9600以下波特率可以不调用
  ClkInit();
    
  UartInit(9600,'n',8,1);//串口初始化,设置成38400bps,无校验,8位数据,1位停止
  _EINT();
    
  UartWriteStr(str);
  UartWriteChar(0x0d);    //发送"换行"(\r)"
  UartWriteChar(0x0a);    //发送"回车"(\n)"   
    
  UartWriteStr("下面测试串口收发函数\r\n");
    
  while(1)                    //串口测试
  {
    int k=50;

    while(k--)
    {
       UartWriteChar(value);     //将收到的数据返回   
       value++;
       Delays();
    }
  }
  //return 0;
}

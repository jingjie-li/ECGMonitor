#include <stdint.h>
#include <msp430x14x.h>
#include "Spi.h"         //串口通讯程序库头文件
#include "MSP430_Spi.h" 
#include "TI_ADS1293.h" 
#include "TI_ADS1293_setting.h"
#include "Uart.h"

//#define SAMPLE_ARRAY_SIZE 10                                                   // Store last 10 ecg samples for processing
//#define CH_DATA_SIZE 6                                                         // 6 bytes: ch1 ecg + ch2 ecg
//uint8_t adc_sample_array[9];

char str1[] = "start conversation!"; //ROM中一个字符串
char str2[] = "stop conversation!"; //ROM中一个字符串
char q = 'Q';

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
    BCSCTL2 |= SELM_2+SELS+DIVS_0;  //MCLK为8MHz，SMCLK为8MHz
}
/*******************************************
函数名称：Delays
功    能：延时一会
参    数：无
返回值  ：无
********************************************/
void Delays(uint32_t k)
{
    uint8_t i=100;
    uint32_t j;
    while(i--)
    {
            j=k;
            while(j--);
    }
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  ClkInit();
  
  uint8_t count=3;
  uint8_t read_buf[3];
 // int i = 0;

//  count = CH_DATA_SIZE;                                                        // bytes to read: ADC_DOUT2 - ADCDOUT0

  
  char chr;               //串口测试中，收到的字节
  // 主机模式，波特率4000000,8位数据位，三线模式，时钟模式1（具体见spi.c）
  SpiMasterInit(4000000,8,3,1);
  UartInit(115200,'n',8,1);//串口初始化,设置成38400bps,无校验,8位数据,1位停止
  _EINT(); 
  
  P1DIR = 0xff;
  P1SEL = 0x00;  
  P2DIR = 0xfa;
  P2OUT = 0xf0;
  Delays(10000);
  TI_ADS1293_WriteRegSettings();  
  P2OUT = 0xb0;
  while(1)                    //串口测试
  {
      chr = UartReadChar();
      switch(chr)
      {
      case 'S': // start conversation
        UartWriteStr(str1);
        TI_ADS1293_SPIWriteReg(0x00, 0x01);
        UartWriteChar(q);
        break;
      case 'T': // stop conversation
        //UartWriteStr(str2);
        TI_ADS1293_SPIWriteReg(0x00, 0x00);
        //UartWriteChar(q);
        break;
      case 'M':
        for(uint32_t k = 0;k<1000000;k++)
        {
            TI_ADS1293_SPIStreamReadReg(read_buf, count);           
            UartWriteint(read_buf[0]);
            UartWriteint(read_buf[1]);
            UartWriteint(read_buf[2]);
            UartWriteChar(0x0d);    //发送"换行"(\r)"
            UartWriteChar(0x0a);    //发送"回车"(\n)"  
            Delays(10);
        }
            break;
      case 'N':
        for(uint8_t j = 0x00; j<0xff; j++)
        {
          uint8_t adsreg = TI_ADS1293_SPIReadReg(j);
          UartWriteint(adsreg);
        }
        break;
      case 'D':
        TI_ADS1293_SPIWriteReg(TI_ADS1293_FLEX_CH1_CN_REG, 
                          TI_ADS1293_FLEX_CH1_CN_REG_VALUE);
        uint8_t adsreg = TI_ADS1293_SPIReadReg(TI_ADS1293_FLEX_CH1_CN_REG);
        UartWriteint(adsreg);
        break;
      }
      
  }

}


/*--------------------------------------------------------------
 * Copyright (C) 2018 西安交通大学 生命学院 李金铭
 * 版权所有。 
 * 
 * 文件名： main.c
 * 
 * 文件功能描述：   
 *          MSP430F149控制ADS1293和AFE4400采集信号并通过蓝牙发送给
 *          手机端
 *      说明：  
 *          运行后先关闭看门狗和初始化时钟系统，然后初始化ADS1293
 *          和AFE4400，然后通过串口读取指令，并收发数据。本程序通过
 *          定时器中断进行定时采样，每次将采集到的三次心电和一次血氧
 *          信号压缩打包发送给手机
 *   
**----------------------------------------------------------------*/
#include <stdint.h>
#include "msp430x14x.h"   //430寄存器头文件
#include "Uart.h"         //串口通讯程序库头文件
#include "Spi.h"
#include "MSP430_AFE_SPI.h"
#include "TI_AFE4400.h"
#include "TI_AFE4400_setting.h"
#include "MSP430_Spi.h"
#include "TI_ADS1293.h"
#include "TI_ADS1293_setting.h"

uint8_t c=1;
//uint32_t val=1;
char str[] = "UartWriteChar"; //ROM中一个字符串
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
    BCSCTL2 |= SELM_2+SELS+DIVS_0;  //MCLK为8MHz，SMCLK为1MHz
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

/*******************************************
函数名称：readecg1
功    能：读取第一次ecg信号并压缩
参    数：
返回值  ：无
********************************************/
void readecg1(uint8_t *buffer, uint8_t *buffer1, uint8_t count)
{
    TI_ADS1293_SPIStreamReadReg(buffer, count);
    *(buffer1) = *(buffer) << 4;
    *(buffer1) = *(buffer1) | ((*( buffer+1 )>>4 ) & 0x0f);
    *(buffer1+1) = *( buffer+1 ) << 4;
    *(buffer1+1) = *(buffer1+1) | ((*( buffer+2 ) >> 4 )&0x0c );
}

/*******************************************
函数名称：readecg2
功    能：读取第二次ecg信号并压缩
参    数：
返回值  ：无
********************************************/
void readecg2(uint8_t *buffer, uint8_t *buffer1, uint8_t count)
{
    TI_ADS1293_SPIStreamReadReg(buffer, count);
    *(buffer1+1) = *(buffer1+1) | (( *(buffer) >> 2 )&0x03 );
    *(buffer1+2) = *(buffer) << 6;
    *(buffer1+2) = *(buffer1+2) | (( *( buffer+1 )>>2 ) & 0x3f);
    *(buffer1+3) = *( buffer+1 ) << 6;
    *(buffer1+3) = *(buffer1+3) | (( *( buffer+2 ) >> 2 )&0x30 );
}

/*******************************************
函数名称：readecg3
功    能：读取第三次ecg信号并压缩
参    数：
返回值  ：无
********************************************/
void readecg3(uint8_t *buffer, uint8_t *buffer1, uint8_t count)
{
    TI_ADS1293_SPIStreamReadReg(buffer, count);
    *(buffer1+3) = *(buffer1+3) | ( *(buffer)&0x0f );
    *(buffer1+4) = *( buffer+1 );
    *(buffer1+5) = *( buffer+2 ) & 0xc0;
}

/*******************************************
函数名称：readspo2
功    能：读取第一次spo2信号并压缩
参    数：
返回值  ：无
********************************************/
void readspo2(uint8_t *buffer1, uint8_t count)
{
    unsigned long value = TI_AFE4400_SPIAutoIncReadReg(LED1VAL, count);
    *(buffer1+5) = *(buffer1+5) | ((value>>15) & 0x3F);
    *(buffer1+6) = (value>>7) & 0xF8;
    value = TI_AFE4400_SPIAutoIncReadReg(LED2VAL, count);
    *(buffer1+6) = *(buffer1+6) | (( value>>19 ) & 0x07);
    *(buffer1+7) = (value>>11) & 0xFF;
}

/****************************************************************************
* 名    称：main主程序
* 功    能：设置串口，输出信息，从串口读计算机键盘输入数据，测试串口收发
* 入口参数：无
* 出口参数：无
****************************************************************************/
int main( void )
{
  

  /*下面六行程序关闭所有的IO口*/
  P1DIR = 0XFF;    P1OUT = 0X00;
  P2DIR = 0XFA;    P2OUT = 0XF0;
  P3DIR = 0XFF;    P3OUT = 0X00;
  P4DIR = 0x00;    P4OUT = 0x00;
  P4DIR |= 0x80;   P4OUT |= 0x80;
  P5DIR = 0XFF;    P5OUT = 0X00;
  P6DIR = 0XFF;    P6OUT = 0X00;
  
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  ClkInit();
  CCTL1 = CCIE;                            // CCR1 中断使能  
  CCR1 = 6667;
  //CCR1 = 50000;  
  TACTL = TASSEL_2 + MC_2 + ID_3;          // SMCLK = 1MHz, 连续计数模式 
  uint8_t count=3;

  uint8_t read_buf[3];
  uint8_t read_buff[8] = {0,0,0,0,0,0,0,0};
  
  //unsigned long val;
  
  char exit_state_flag = 0;
 // int i = 0;

//  count = CH_DATA_SIZE;                                                        // bytes to read: ADC_DOUT2 - ADCDOUT0

  
  char chr;               //串口测试中，收到的字节
  // 主机模式，波特率4000000,8位数据位，三线模式，时钟模式1（具体见spi.c）
  SpiMasterInit(4000000,8,3,0);
  UartInit(115200,'n',8,1);//串口初始化,设置成38400bps,无校验,8位数据,1位停止
  _EINT(); 
  
  //P1DIR = 0xff;
  //P1SEL = 0x00;
  Delays(10000);
  TI_ADS1293_WriteRegSettings();
  TI_AFE4400_WriteRegSettings(); 
  
  chr = UartReadChar();
  
  while(1)                    //串口测试
  {
      
    TI_ADS1293_SPIWriteReg(0x00, 0x01);
    TI_AFE4400_SPIAutoIncWriteReg(0x00, 1, 3); //enable read AFE (0x000001ul)
        
    switch(chr)
      {
      case 'T':
        P2OUT &= (~BIT5);
        P2OUT &= (~BIT6);
        exit_state_flag=0;
        while(exit_state_flag==0)
        {
          if(UartReadState()==1)
          {
            exit_state_flag=1;
            chr = UartForceReadChar();
          }
          P2OUT ^= BIT7;
          UartWriteint(0x00);
          UartWriteint(0x01);
          UartWriteint(0x02);
          UartWriteint(0x03);
          UartWriteint(0x04);
          UartWriteint(0x05);
          UartWriteint(0x06);
          UartWriteint(0x07);
          Delays(1);
          _BIS_SR(CPUOFF);
          _NOP();
        }
        break;
      case 'M': //moblie recieving mode
        exit_state_flag=0;
        while(exit_state_flag==0)
        {
          if(UartReadState()==1)
          {
            exit_state_flag=1;
            chr = UartForceReadChar();
          }
          if(c==1)
          {
            readecg1(read_buf, read_buff, count);
            P2OUT ^= BIT6; 
            _BIS_SR(CPUOFF);
            _NOP();
          }
          else if(c==2)
          {
            readecg2(read_buf, read_buff, count);
            P2OUT ^= BIT6;
            _BIS_SR(CPUOFF);
            _NOP();
          }
          else
          {
            c = 0;
            readecg3(read_buf, read_buff, count);
            P2OUT ^= BIT6;
            readspo2(read_buff, count);
            P2OUT ^= BIT5;
            UartWriteint(read_buff[0]);
            UartWriteint(read_buff[1]);
            UartWriteint(read_buff[2]);
            UartWriteint(read_buff[3]);
            UartWriteint(read_buff[4]);
            UartWriteint(read_buff[5]);
            UartWriteint(read_buff[6]);
            UartWriteint(read_buff[7]);
            Delays(1);
            // FOR PROCESSING, WE NEED 0D,OA
            //UartWriteChar(0x0d);
            //UartWriteChar(0x0a);
            _BIS_SR(CPUOFF);
            _NOP();
          }
        }
        
        break;
      }

    }
    
  }



#pragma vector=TIMERA1_VECTOR  
__interrupt void Timer_A1(void)  
{  
    switch(TAIV){  
        case 2:  
            //CCR1 += 20000;                    
            CCR1 += 6667;
            c = c + 1;
            __bic_SR_register_on_exit(CPUOFF);            
    }      
}  


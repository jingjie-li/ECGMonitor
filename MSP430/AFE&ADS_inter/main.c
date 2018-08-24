/*--------------------------------------------------------------
 * Copyright (C) 2018 Xi'an Jiaotong University, Jinming Li, Jingjie Li
 *  
 * 
 * main.c
 * 
 * Descriptions  
 *          Using MSP430F149 to control ADS1293 and AFE4400 to acquirsion signals and sent to the smartphone APP via bluetooth
 *      Basic idea：  
 *          Close down watchdog and init clock system, lisening on the UART port, wait for
 *          start signal, once started, it will initilize ADS and AFE chips, pack-up data then
 *          send it through UART-BT interfance.
 *          We used timer interupt to drive each sampling, the sample rate of ECG is 150Hz, PPG is 50Hz
 *          While running, we will continulously listening on the serial port, which can switch between different sampling state
*           For example, ADS only state, Waiting State, AFE only State.
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
//char str[] = "UartWriteChar"; //ROM中一个字符串
//char str1[] = "start conversation!"; //ROM中一个字符串
//char str2[] = "stop conversation!"; //ROM中一个字符串
//char q = 'Q';
uint8_t read_buff[8] = {0,0,0,0,0,0,0,0};

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
    *(buffer1+5) = *(buffer1+5) & 0xC0;
    *(buffer1+5) = *(buffer1+5) | ((value>>15) & 0x3F);
    *(buffer1+6) = (value>>7) & 0xF8;
    value = TI_AFE4400_SPIAutoIncReadReg(LED2VAL, count);
    *(buffer1+6) = *(buffer1+6) | (( value>>19 ) & 0x07);
    *(buffer1+7) = (value>>11) & 0xFF;
}

void UartOutputLong(uint8_t *data)
{
  UartWriteint(data[0]);
  UartWriteint(data[1]);
  UartWriteint(data[2]);
  UartWriteint(data[3]);
  UartWriteint(data[4]);
  UartWriteint(data[5]);
  UartWriteint(data[6]);
  UartWriteint(data[7]);
}

uint8_t ADSLeadOFF()
{
  uint8_t retval = 0x00;
  uint8_t leadoffreg = TI_ADS1293_SPIReadReg(0x18);
  P2OUT |= BIT4;
  if(leadoffreg>0)
  {
    retval = 0x01;
    P2OUT &= ~BIT4; //lead off
    read_buff[0]=0xff;
    read_buff[1]=0xff;
    read_buff[2]=0xff;
    read_buff[3]=0xff;
    read_buff[4]=0xff;
    read_buff[5]=0xff;
  }
  return retval;
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
  P4DIR = 0x01;    P4OUT = 0x00;
  P4DIR |= 0x80;   P4OUT |= 0x80;
  P5DIR = 0XFF;    P5OUT = 0X00;
  P6DIR = 0XFF;    P6OUT = 0X00;
  
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  ClkInit();
  CCTL1 = CCIE;                            // CCR1 中断使能  
  //CCR1 = 6667;
  CCR1 = 50000;  
  TACTL = TASSEL_2 + MC_2 + ID_3;          // SMCLK = 1MHz, 连续计数模式 
  uint8_t count=3;

  uint8_t read_buf[3];
  
  //unsigned long val;
  
  char exit_state_flag = 0;
  char AcqState = 0; // 0-ECG&PPG State, 1-ECG only State, 2-PPF only State
  char ComputerDebugFlag = 0;
 // int i = 0;

//  count = CH_DATA_SIZE;                                                        // bytes to read: ADC_DOUT2 - ADCDOUT0

  
  char chr;               //串口测试中，收到的字节
  // 主机模式，波特率4000000,8位数据位，三线模式，时钟模式1（具体见spi.c）
  SpiMasterInit(4000000,8,3,0);
  UartInit(115200,'n',8,1);//串口初始化,设置成38400bps,无校验,8位数据,1位停止
  _EINT(); 
  
  //P1DIR = 0xff;
  //P1SEL = 0x00;
  
  chr = UartReadChar();
  //int P4state = P4IN;
  //int PDALM = P4state & 0x02;
  //int ADSALM = P4state & 0x10;
  //int LEDALM = P4state & 0x20;
  
  uint8_t ECGLeadOff = 0;
  TI_ADS1293_SPIWriteReg(TI_ADS1293_CH_CNFG_REG, 0x20);
  while(1)                    //串口测试
  {
      
        
    switch(chr)
      {
      case 'T':
        P4OUT &= ~BIT0; //Turn off AFE;
        TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
        TI_ADS1293_SPIWriteReg(0x00, 0x02); //ADS Standby powerdown mode
        P2OUT |= BIT5; // TURN OFF PPG LED
        P2OUT |= BIT6; // TURN OFF ECG LED
        exit_state_flag=0;
        //TI_AFE4400_SPIAutoIncWriteReg(0x00, 5, 3); //enable read AFE (0x000001ul)
        while(exit_state_flag==0)
        {
          if(UartReadState()==1)
          {
            exit_state_flag=1;
            chr = UartForceReadChar();
          }
          P2OUT ^= BIT7; //FLASHING HPR LED
          //uint8_t dump[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
          ECGLeadOff = ADSLeadOFF();
          //uint8_t leadoffreg = TI_ADS1293_SPIReadReg(0x18);
          //UartOutputLong(dump);
          //UartWriteint(leadoffreg);
          //UartWriteChar(0x0d);
          //UartWriteChar(0x0a);
          Delays(1);
          _BIS_SR(CPUOFF);
          _NOP();
        }
        break;
      case 'M': case 'P': case 'F': case 'A': case 'X': case 'Y': case 'Z': case '3': case '5': //moblie recieving mode
        exit_state_flag=0;
        P2OUT |= BIT7;
  
        if(chr=='M'||chr=='P') //ADS & AFE Mode Mobile or Processing Mode
        {
           ComputerDebugFlag=0;
           if(chr=='P') ComputerDebugFlag=1;
           AcqState = 0; 
           P4OUT |= BIT0; //Turn On AFE;
           Delays(1000);
           TI_AFE4400_SPIAutoIncWriteReg(0x00, 8, 3); //AFE4400 Soft Reset
           TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
           TI_ADS1293_WriteRegSettings();
           TI_AFE4400_WriteRegSettings();
           TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
           TI_AFE4400_SPIAutoIncWriteReg(0x00, 1, 3); //enable read AFE (0x000001ul)
           P2OUT &= ~BIT6; //ADS&AFE indcatation LED on
           P2OUT &= ~BIT5;
        }
        else if(chr=='A')//ADS Only Mode
        {
          AcqState = 1;
          P4OUT &= ~BIT0; //Turn off AFE;
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          TI_ADS1293_WriteRegSettings();
          read_buff[5]=0x00;
          read_buff[6]=0x00;
          read_buff[7]=0x00;
          Delays(100);
          TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
          P2OUT &= ~BIT6; //ADS indcatation LED on
          P2OUT |= BIT5; //AFE indcatation LED off
        }
        else if(chr=='F')//AFE Only Mode
        {
          AcqState = 2;
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          TI_ADS1293_SPIWriteReg(0x00, 0x02); //ADS Standby powerdown mode
          P4OUT |= BIT0; //Turn On AFE;
          Delays(100);
          read_buff[0]=0x00;
          read_buff[1]=0x00;
          read_buff[2]=0x00;
          read_buff[3]=0x00;
          read_buff[4]=0x00;
          read_buff[5]=0x00;
          TI_AFE4400_SPIAutoIncWriteReg(0x00, 8, 3); //AFE4400 Soft Reset
          Delays(10);
          TI_AFE4400_WriteRegSettings();
          TI_AFE4400_SPIAutoIncWriteReg(0x00, 1, 3); //enable read AFE (0x000001ul)
          P2OUT &= ~BIT5; //AFE indcatation LED on
          P2OUT |= BIT6; //ADS indcatation LED off
        }
        else if(chr=='X')
        {
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          TI_ADS1293_SPIWriteReg(TI_ADS1293_CH_CNFG_REG, 0x10); //Configure Channel for Loop Read Back Mode, Reading CH1
          TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
        }
        else if(chr=='Y')
        {
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          TI_ADS1293_SPIWriteReg(TI_ADS1293_CH_CNFG_REG, 0x20); //Configure Channel for Loop Read Back Mode, Reading CH2
          TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
        }
        else if(chr=='Z')
        {
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          TI_ADS1293_SPIWriteReg(TI_ADS1293_CH_CNFG_REG, 0x40); //Configure Channel for Loop Read Back Mode, Reading CH3
          TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
        }
        else if(chr=='3')
        {
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          SET3();
          TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
        }
        else if(chr=='5')
        {
          TI_ADS1293_SPIWriteReg(0x00, 0x00); //ADS Stop_Conversation
          SET5();
          TI_ADS1293_SPIWriteReg(0x00, 0x01); //ADS Start_Conversation
        }
        while(exit_state_flag==0)
        {
          if(UartReadState()==1)
          {
            exit_state_flag=1;
            chr = UartForceReadChar();
          }
          if(AcqState!=2) ECGLeadOff = ADSLeadOFF();
          if(c==1)
          {
            if((AcqState==0||AcqState==1)&&ECGLeadOff==0)
            {
              readecg1(read_buf, read_buff, count);
              P2OUT ^= BIT6; 
            }
              _BIS_SR(CPUOFF);
              _NOP();
          }
          else if(c==2)
          {
            if((AcqState==0||AcqState==1)&&ECGLeadOff==0)
            {
              readecg2(read_buf, read_buff, count);
              P2OUT ^= BIT6;
            }
            _BIS_SR(CPUOFF);
            _NOP();
          }
          else
          {
            c = 0;
            if((AcqState==0||AcqState==1)&&ECGLeadOff==0)
            {
            readecg3(read_buf, read_buff, count);
            P2OUT ^= BIT6;
            }
            if(AcqState==0||AcqState==2)
            {
              readspo2(read_buff, count);
              P2OUT ^= BIT5;
            }
            UartOutputLong(read_buff);
            // FOR PROCESSING, WE NEED 0D,OA'
            if(ComputerDebugFlag == 1)
            {
              UartWriteChar(0x0d);
              UartWriteChar(0x0a);
            }
            Delays(1);
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


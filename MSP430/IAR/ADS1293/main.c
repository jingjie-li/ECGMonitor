
#include "msp430x14x.h" //430寄存器头文件
#include "ADS1293.h"     //ADS1293操作头文件，即声明本文件的有用函数
#include "Spi.h"        //SPI通讯程序库头文件
#include "TI_ADS1293_register_settings.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  return 0;
}

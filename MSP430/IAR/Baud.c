#include<stdio.h>
#include<math.h>

//函数声明
void SetBaudRateRegisters(long clk,int baud);

/************************宏定义***********************/
#define UxBR1	a[0]
#define	UxBR0	a[1]
#define	UxMCTL	a[2]

unsigned char a[3];                     //数组模拟寄存器
void main()
{
	long clk;                           //时钟
	long baud;                           //波特率
	printf("\t---波特率计算软件！---\n");
	printf("\n请输入时钟频率（Hz）：");
	scanf("%ld",&clk);					
	printf("\n请输入波特率：");
	scanf("%ld",&baud);
	getchar();                          //读取多余回车符

	SetBaudRateRegisters(clk,baud);     //设置寄存器值

    //显示寄存器值
	printf("\nUxBR1:0x%x\tUxBR0:0x%x\tUxMCTL:0x%x\n",UxBR1,UxBR0,UxMCTL);
	
	getchar();
}

/****************************************************************************
* 名    称：SetBaudRateRegisters
* 功    能：根据时钟 波特率设置对应寄存器
* 入口参数：
*           clk:        所选时钟频率（如：32768）
            baud        波特率      (300~115200)
* 出口参数：无
* 范    例: SetBaudRateRegisters(32768,9600) //用时钟频率32768产生9600的波特率
****************************************************************************/
void SetBaudRateRegisters(long clk,long baud)
{
	int n = clk / baud;     //整数波特率
	char mSum = 0;			//Σmi
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

/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Getchar.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机键盘scanf移植
 *      说明：  
 *          该程序完成键盘的getchar函数，以移植scanf函数
 *  
 *          使用时只需把getchar.c添加到工程中，然后在源程序文件
 *          中加入对stdio.h的包含；然后就可以调用scanf函数。
 *          
 * 创建标识：   刘中原20110820
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/
#include <stdio.h>
#include "Key.h"

#define LINE_LENGTH 20          //行缓冲区大小，决定每行最多输入的字符数

/*标准终端设备中，特殊ASCII码定义，请勿修改*/
#define InBACKSP 0x08           //ASCII  <--  (退格键)
#define InDELETE 0x7F           //ASCII <DEL> (DEL 键)
#define InEOL '\r'              //ASCII <CR>  (回车键)
#define InLF '\n'                 //ASCII <LF>  (回车)
#define InSKIP '\3'             //ASCII control-C
#define InEOF '\x1A'            //ASCII control-Z

#define OutDELETE "\x8 \x8"     //VT100 backspace and clear
#define OutSKIP "^C\n"          //^C and new line
#define OutEOF "^Z"             //^Z and return EOF

/****************************************************************************
* 名    称：getchar
* 功    能：从键盘设备接收一字节数据(1个ASCII字符)
* 入口参数：无
* 出口参数：收到的字符
* 说    明: scanf函数会调用该函数作为底层输入。这里4*4键盘输入按键字符。scanf
            函数的输入即源自PC机键盘。若修改该函数，将字符以其他方式输入，如
            单片机串口等。
            本函数带有缓存，能够处理退格等删除操作。若不需要删除操作，可直接
            调用ReadKey()函数。
****************************************************************************/
int getchar()
{
    static char inBuffer[LINE_LENGTH + 2];      //Where to put chars
    static char ptr;                            //Pointer in buffer
    char c;
    
    while(1)
    {
        if(inBuffer[ptr])                       //如果缓冲区有字符
            return (inBuffer[ptr++]);           //则逐个返回字符
        ptr = 0;                                //直到发送完毕，缓冲区指针归零
        while(1)                                //缓冲区没有字符，则等待字符输入
        {
            c = ReadKey();                      //等待接收一个字符==移植时关键
            if(c == InEOF && !ptr)              //==EOF==  Ctrl+Z 
            {                                   //只有在未入其他字符时才有效
                printf(OutEOF);                 //终端显示EOF符
                return EOF;                     //返回 EOF（-1）
            }
            if(c==InDELETE || c==InBACKSP)      //==退格或删除键==
            {
                if(ptr)                         //缓冲区有值
                {
                    ptr--;                      //从缓冲区移除一个字符
                    printf(OutDELETE);          //同时显示也删掉一个字符
                }
            }
            else if(c == InSKIP)                //==取消键 Ctrl+C ==
            {
                printf(OutSKIP);                //终端显示跳至下一行
                ptr = LINE_LENGTH + 1;          //==0 结束符==
                break;
            }
            else if(c == InEOL||c == InLF)      //== '\r' 回车=='\n'回车
            {
                putchar(inBuffer[ptr++] = '\n');//终端换行
                inBuffer[ptr] = 0;              //末尾添加结束符（NULL）
                ptr = 0;                        //指针清空
                break;
            }
            else if(ptr < LINE_LENGTH)          //== 正常字符 ==
            {
                if(c >= ' ')                    //删除 0x20以下字符
                {
                    //存入缓冲区
                    putchar(inBuffer[ptr++] = c);
                }
            }
            else                                //缓冲区已满
            {
                putchar('\7');                  //== 0x07 蜂鸣符，PC回响一声
            }
        }
    }
}

/****************************************************************************
* 名    称：getchar
* 功    能：从键盘设备接收一字节数据(1个ASCII字符)
* 入口参数：无
* 出口参数：收到的字符
* 说    明: scanf函数会调用该函数作为底层输入。这里直接调用ReadKey()函数。
****************************************************************************/
/*int getchar()
{
    return ReadKey();
}*/
/*----------------------------------------------------------------
 * Copyright (C) 2011 江苏大学 电气学院416 刘中原
 * 版权所有。 
 * 
 * 文件名： Nixietube.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机数码管printf移植
 *      说明：  
 *          该程序仅有一个puchar函数，把字符显示到数码管,printf函数在
 *          底层调用这个函数向数码管发送要显示的字符。
 *          使用时只需把Nixietube.c添加到工程中，然后在要使用printf的
 *          源程序文件中加入对stdio.h的包含；然后就可以使用printf函数
 *          向数码管发送要显示的字符了。支持的字符参考：Nixietube.h
 *          
 * 创建标识：   刘中原20110823
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/
#include <stdio.h>
#include "ctype.h"       /*isdigit函数需要该头文件*/
#include "Nixietube.h"

/****************************************************************************
* 名    称：putchar
* 功    能：向数码管显示输出一个ASCII字符。
* 入口参数：ch: 待发送的字符  
* 出口参数：发出的字符
* 说    明: printf函数会调用该函数作为底层输出。该函数将字符输出到数码管上
            因此printf的结果将显示在数码管上。
****************************************************************************/
int putchar(int ch)
{
    //'\f'表示走纸翻页，相当于清除显示
    if(ch=='\n'||ch=='\r')
        NixiettubeClear();
    
    //数字和对应ASCII字母之间差0x30   '1'=0x31 '2'=0x32... 
    //isdigit也是C语言标准函数
    if(isdigit(ch))
        NixiettubeInsertChar(ch-0x30);  //若字符是数字则显示数字
    else             //否则，不是数字，是字母
        {
        switch(ch)    //根据字母选择程序分支
        {
            case 'A': case 'a': NixiettubeInsertChar(AA);break; //字符A
            case 'B': case 'b': NixiettubeInsertChar(BB);break; //字符B
            case 'C': case 'c': NixiettubeInsertChar(CC);break; //...
            case 'D': case 'd': NixiettubeInsertChar(DD);break;  
            case 'E': case 'e': NixiettubeInsertChar(EE);break;
            case 'F': case 'f': NixiettubeInsertChar(FF);break;
            case 'G': case 'g': NixiettubeInsertChar(GG);break;
            case 'H': case 'h': NixiettubeInsertChar(HH);break;
            case 'I': case 'i': NixiettubeInsertChar(II);break; 
            case 'J': case 'j': NixiettubeInsertChar(JJ);break;
            case 'K': case 'k': NixiettubeInsertChar(KK);break;
            case 'L': case 'l': NixiettubeInsertChar(LL);break;
            case 'M': case 'm': NixiettubeInsertChar(mm);break;
            case 'N':           NixiettubeInsertChar(NN);break;
            case 'n':           NixiettubeInsertChar(nn);break;
            case 'O':           NixiettubeInsertChar(OO);break;
            case 'o':           NixiettubeInsertChar(oo);break;
            case 'P': case 'p': NixiettubeInsertChar(PP);break; 
            case 'Q': case 'q': NixiettubeInsertChar(QQ);break; 
            case 'R': case 'r': NixiettubeInsertChar(rr);break; 
            case 'S': case 's': NixiettubeInsertChar(SS);break; 
            case 'T': case 't': NixiettubeInsertChar(tt);break; 
            case 'U': case 'v': NixiettubeInsertChar(UU);break; 
            case 'V': case 'u': NixiettubeInsertChar(VV);break; 
            case 'W': case 'w': NixiettubeInsertChar(WW);break; 
            case 'Y': case 'y': NixiettubeInsertChar(YY);break; //...
            case 'Z': case 'z': NixiettubeInsertChar(ZZ);break; //字符Z
            case '-':           NixiettubeInsertChar(NEG);break;//字符-
            case '.':           NixiettubeInsertChar(DOT);break;//小数点，直接显示在右下角
            case ' ':           NixiettubeInsertChar(SP);break; //空格
            default :           NixiettubeInsertChar(SP);break;//显示不出来的字母用空格替代
        } 
    } 
    return(ch);  //返回显示的字符(putchar函数标准格式要求返回显示字符)
}

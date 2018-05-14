
#ifndef __NIXIETUBE_H
#define __NIXIETUBE_H

#define AA  10
#define BB  AA+1
#define CC  BB+1
#define DD  CC+1
#define EE  DD+1
#define FF  EE+1
#define GG  FF+1
#define HH  GG+1
#define II  HH+1
#define JJ  II+1
#define KK  JJ+1
#define LL  KK+1
#define mm  LL+1
#define NN  mm+1
#define nn  NN+1
#define oo  nn+1
#define OO  oo+1
#define PP  OO+1
#define QQ  PP+1
#define rr  QQ+1
#define SS  rr+1
#define tt  SS+1
#define TT  tt+1
#define UU  TT+1
#define VV  UU+1
#define WW  VV+1
#define YY  WW+1
#define ZZ  YY+1
#define NEG ZZ+1    /*   -  */  //负号
#define DOT NEG+1   /*   .  */  //小数点
#define SP  DOT+1   /* 空白 */  //空格

void NixiettubeInit();
void NixiettubeClear();
void NixiettubeDisplayChar(char ch,char addr);
void NixiettubeInsertChar(char ch);

#endif /* __NIXIETUBE_H */

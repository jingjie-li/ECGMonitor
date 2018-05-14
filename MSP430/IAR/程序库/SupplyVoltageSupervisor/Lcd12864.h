
#ifndef __LCD12864_H
#define __LCD12864_H

void LcdInit();
char LcdReadAddr();
char LcdReadData();
void LcdWriteComm(char cmd);
void GotoXY(char x,char y);
void LcdWriteData(char data);
void LcdWriteString(char addr,char *str);

#endif /* __LCD12864 */
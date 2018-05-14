
#ifndef __AD7708_H
#define __AD7708_H

void AD7708Init(char chop);
long AD7708ReadResultData();
void AD7708WriteRegister(char addr,long dat);
long AD7708ReadRegister(char addr);
void AD7708Start(char channel);

#endif /* __AD7708_H */
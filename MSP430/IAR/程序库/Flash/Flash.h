
#ifndef __DMA_H
#define __DMA_H

#define InfoA   (0x1080)    //信息存储器 InfoA
#define InfoB   (0x1000)    //信息存储器 InfoB

void FlashInit();
void FlashErase(unsigned int Addr);
void FlashWriteChar (unsigned int addr,char Data);
char FlashReadChar (unsigned int Addr);
void FlashWriteWord(unsigned int addr,unsigned int Data);
unsigned int FlashReadWord(unsigned int Addr);

#endif /* __DMA_H */

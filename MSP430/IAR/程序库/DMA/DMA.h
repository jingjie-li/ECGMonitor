
#ifndef __DMA_H
#define __DMA_H

void DMAInit(char channel,char trigger,char transMode,char srcMode,char dstMode,
             unsigned int src,unsigned int dst,unsigned int size);
void DMAReEnable(char channel);
void DMAStart(char channel);

#endif /* __DMA_H */

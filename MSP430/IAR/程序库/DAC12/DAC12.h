
#ifndef __DAC12_H
#define __DAC12_H

char DAC12Init(char module,char DAC12AMPx);
void DAC12Out(char module,int out);
void DAC12Cal(char module);

#endif /* __DAC12_H */

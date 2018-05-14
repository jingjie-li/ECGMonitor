
#ifndef __TAPWM_H
#define __TAPWM_H

char TAPwmInit(char Clk,char Div,char Mode1,char Mode2);
void TAPwmSetPeriod(unsigned int Period);
void TAPwmSetDuty(char Channel,unsigned int Duty);
void TAPwmSetPermill(char Channel,unsigned int Percent);

#endif /* __TAPWM_H */
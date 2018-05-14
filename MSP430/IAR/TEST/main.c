#include <iocc2540.h>
#define BV(n) (1<<(n))

void delay(unsigned int time)
{
  int i,j;
  for(i=0;i<=time;i++)
    for(j=0;j<=time;j++);
}

void main()
{
  P1DIR |= BV(0);
  P1SEL &= ~BV(0);
  while(1)
  {
    P1_0=1;
    delay(1000);
    P1_0=0;
    delay(1000);
  }
}
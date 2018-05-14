
#ifndef __SVS_H
#define __SVS_H

void SVSSetup(char voltageLevel,char reset);
char SvsFlg();
void ClearSvs(char sync);

#endif /* __SVS_H */
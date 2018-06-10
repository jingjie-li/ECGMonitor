#include <SPI.h>
byte LowByte = 0;
byte SecondByte = 0;
//unsigned char SPIval16[5]={0xD0,0x01,0x12,0x35,0x0A};
unsigned long SPIval16[2]={22,22};
int SUPhighInt=0;
int highInt=0;
int midInt=0;
int lowInt=0;
unsigned int readstuff=0;
unsigned long receivedVal=0;

unsigned int receivedSupUpper=0;
unsigned int receivedUpper=0;
unsigned int receivedMiddle=0;
unsigned int receivedLower=0;

unsigned int CH1EcgData=0;
unsigned int CH2EcgData=0;
unsigned int CH3EcgData=0;

byte OutputType = 0;
byte OutputTypeS = 0;

byte AFEwriteVal[3]={0x00,0x00,0x00};

const byte READ = 0b10000000;   //  read command
const byte WRITE = 0b00000000;   //  write command

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  SerialUSB.println("Starting SPI\n");
  SPI.begin(4);
  SPI.setClockDivider(4, 21); 
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE2);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(OutputType=='Q'||OutputType==0){
    SerialUSB.println("We do what? (A-AFEWite,B-AFERead,E-InitilizeAFE,F-ReadAFEData,W-WriteSPI,R-ReadSPI,D-StartGetData,N-NormalConfig,S-StartConversition,T-StopConversition,Z-null)\n");
    while (SerialUSB.available() == 0) {}
    OutputType = SerialUSB.read();
  }
  switch(OutputType) {
    case 'W': {
      SerialUSB.println("#Write State!,you can trpe Q to quit");
      SerialUSB.print("Input Addr:  ");
      while (SerialUSB.available() == 0) {}
      OutputTypeS=SerialUSB.read();
      if(OutputTypeS=='Q'){
        OutputType=OutputTypeS;
        while(Serial.read() >=0){}
      }
      else{
        lowInt=OutputTypeS-'0';
        SerialUSB.print(lowInt);
        while (SerialUSB.available() == 0) {}
        midInt=SerialUSB.read()-'0';
        SerialUSB.print(midInt);
        while (SerialUSB.available() == 0) {}
        highInt=SerialUSB.read()-'0';
        SerialUSB.print(highInt);
        SerialUSB.print("\n");
        // get some numbers
        SPIval16[0]=100*lowInt+10*midInt+highInt;
  
        SerialUSB.print("Input Data:  ");
  
  
        while (SerialUSB.available() == 0) {}
        lowInt=SerialUSB.read()-'0';
        SerialUSB.print(lowInt);
        while (SerialUSB.available() == 0) {}
        midInt=SerialUSB.read()-'0';
        SerialUSB.print(midInt);
        while (SerialUSB.available() == 0) {}
        highInt=SerialUSB.read()-'0';
        SerialUSB.print(highInt);
        SerialUSB.print("\n");
        // get some numbers
        SPIval16[1]=100*lowInt+10*midInt+highInt;
        
        SerialUSB.print("Now We are going to write:");
        SerialUSB.print(SPIval16[0],HEX);
        SerialUSB.print(" ");
        SerialUSB.print(SPIval16[1],HEX);
        SerialUSB.print("\n");
        //SPI.transfer(4,SPIval16[0],SPI_CONTINUE);
        //SPI.transfer(4,SPIval16[1]);
        writeRegister(4,SPIval16[0],SPIval16[1]);
        
      }
      break;
    }
    case 'N': {
      writeRegister(4,0x01,0x11);
      writeRegister(4,0x02,0x19);
      writeRegister(4,0x03,0x2E);
      writeRegister(4,0x0A,0x07);
      writeRegister(4,0x0C,0x04);

      writeRegister(4,0x0D,0x01);
      writeRegister(4,0x0E,0x02);
      writeRegister(4,0x0F,0x03);
      
      writeRegister(4,0x10,0x01);

      writeRegister(4,0x12,0x04);
      writeRegister(4,0x21,0x02);
      writeRegister(4,0x22,0x02);
      writeRegister(4,0x23,0x02);
      writeRegister(4,0x24,0x02);
      writeRegister(4,0x27,0x08);
      writeRegister(4,0x2F,0x70);

      SerialUSB.println("#ADS Initilized!");
      OutputType = 0;
      break;
    }
    
    case 'S': {//start conversion
      SerialUSB.println("#Start Conversion!");
      writeRegister(4,0x00,0x01);
      //SPI.transfer(4,0x00,SPI_CONTINUE);
      //SPI.transfer(4,0x01);
      OutputType='Q';
      break;
    }
    
    case 'T': {//stop conversion
      SerialUSB.println("#Stop Conversion!");
      writeRegister(4,0x00,0x00);
      //SPI.transfer(4,0x00,SPI_CONTINUE);
      //SPI.transfer(4,0x00);
      OutputType='Q';
      break;
    }
    
    case 'R':{ //
      SerialUSB.println("#Read from Addr State! You can type in Q to quit this state");
      SerialUSB.print("Addr: ");
      while (SerialUSB.available() == 0) {}
      OutputTypeS=SerialUSB.read();
      if(OutputTypeS=='Q'){
        OutputType=OutputTypeS;
        while(Serial.read() >=0){}
      }
      else{
        lowInt=OutputTypeS-'0';
        //SerialUSB.print(lowInt);
        while (SerialUSB.available() == 0) {}
        midInt=SerialUSB.read()-'0';
        //SerialUSB.print(midInt);
        while (SerialUSB.available() == 0) {}
        highInt=SerialUSB.read()-'0';
        //SerialUSB.print(highInt);
        // get some numbers
        SPIval16[0]=100*lowInt+10*midInt+highInt;
        SerialUSB.print("0x");
        SerialUSB.print(SPIval16[0],HEX);
        SerialUSB.print("   ");
        //SPI.transfer(4,SPIval16[0],SPI_CONTINUE);
        //receivedVal = SPI.transfer(4,0x00);
        
        receivedVal=readRegister(4,SPIval16[0]);
        
        SerialUSB.print("we got:");
        SerialUSB.print(receivedVal,HEX);
        SerialUSB.print("\n");
      }
      break;
    }
    
    case 'Z':{
      SerialUSB.println("null state");
      OutputType='Q';
      break;
      
    }

    case 'D':{
      SerialUSB.println("Now we are going to start steaming reading");

      while (SerialUSB.available() == 0) {
        //SPI.transfer(4,SPIval16[0],SPI_CONTINUE);
        SPI.transfer(4,0xD0,SPI_CONTINUE);
        
        receivedUpper = SPI.transfer(4,0x00,SPI_CONTINUE);//0x37
        receivedMiddle = SPI.transfer(4,0x00,SPI_CONTINUE);//0x38
        receivedLower = SPI.transfer(4,0x00,SPI_CONTINUE);//0x39
  
        CH1EcgData=256*256*receivedUpper+256*receivedMiddle+receivedLower;
        
        receivedUpper = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3A
        receivedMiddle = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3B
        receivedLower = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3C
  
        CH2EcgData=256*256*receivedUpper+256*receivedMiddle+receivedLower;
  
        receivedUpper = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3D
        receivedMiddle = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3E
        receivedLower = SPI.transfer(4,0x00);//0x3F
  
        CH3EcgData=256*256*receivedUpper+256*receivedMiddle+receivedLower;
  
        SerialUSB.print("ECG Channel I Data: ");
        SerialUSB.print(CH1EcgData-2000);
        SerialUSB.print(" ECG Channel II Data: ");
        SerialUSB.print(CH2EcgData);
        SerialUSB.print(" ECG Channel III Data: ");
        //SerialUSB.print(CH3EcgData+2000);
        SerialUSB.print(" \n");

        delay(5);
      
      }
      OutputType = SerialUSB.read();
      break;
    }
    case 'A':{ //AFE Write
      DisableAFERead(4);
      SerialUSB.println("#AFE Write!,you can trpe Q to quit");
      SerialUSB.print("Input Addr:  ");
      while (SerialUSB.available() == 0) {}
      OutputTypeS=SerialUSB.read();
      if(OutputTypeS=='Q'){
        OutputType=OutputTypeS;
        while(Serial.read() >=0){}
      }
      else{
        lowInt=OutputTypeS-'0';
        SerialUSB.print(lowInt);
        while (SerialUSB.available() == 0) {}
        midInt=SerialUSB.read()-'0';
        SerialUSB.print(midInt);
        while (SerialUSB.available() == 0) {}
        highInt=SerialUSB.read()-'0';
        SerialUSB.print(highInt);
        while (SerialUSB.available() == 0) {}
        SUPhighInt=SerialUSB.read()-'0';
        SerialUSB.print(SUPhighInt);
        SerialUSB.print("\n");
        // get some numbers
        SPIval16[0]=1000*lowInt+100*midInt+10*highInt+SUPhighInt;
  
        SerialUSB.print("Input Data:  ");
  
  
        while (SerialUSB.available() == 0) {}
        lowInt=SerialUSB.read()-'0';
        SerialUSB.print(lowInt);
        while (SerialUSB.available() == 0) {}
        midInt=SerialUSB.read()-'0';
        SerialUSB.print(midInt);
        while (SerialUSB.available() == 0) {}
        highInt=SerialUSB.read()-'0';
        SerialUSB.print(highInt);
        while (SerialUSB.available() == 0) {}
        SUPhighInt=SerialUSB.read()-'0';
        SerialUSB.print(SUPhighInt);
        SerialUSB.print("\n");
        // get some numbers
        SPIval16[1]=1000*lowInt+100*midInt+10*highInt+SUPhighInt;
        
        SerialUSB.print("Now We are going to write:");
        SerialUSB.print(SPIval16[0],HEX);
        SerialUSB.print("  ");
        SerialUSB.print(lowInt);
        SerialUSB.print(midInt);
        SerialUSB.print(highInt);
        SerialUSB.print("\n");

        AFE4400_Set_Register(4,SPIval16[0],SPIval16[1]);
        //byte toWrite[3]={highInt,midInt,lowInt};
        //writeAFERegister(4,SPIval16[0],toWrite);
      }
      OutputType = 0;
      break;
    }
    case 'B':{ //AFE Read
      //EnableAFERead(4);
      AFE4400_Set_READABLE(4,1);
      SerialUSB.println("#Read from AFE Addr! You can type in Q to quit this state");
      SerialUSB.print("Addr: ");
      while (SerialUSB.available() == 0) {}
      OutputTypeS=SerialUSB.read();
      if(OutputTypeS=='Q'){
        OutputType=OutputTypeS;
        while(Serial.read() >=0){}
      }
      else{
        lowInt=OutputTypeS-'0';
        //SerialUSB.print(lowInt);
        while (SerialUSB.available() == 0) {}
        midInt=SerialUSB.read()-'0';
        //SerialUSB.print(midInt);
        while (SerialUSB.available() == 0) {}
        highInt=SerialUSB.read()-'0';
        while (SerialUSB.available() == 0) {}
        SUPhighInt=SerialUSB.read()-'0';
        //SerialUSB.print(highInt);
        // get some numbers
        SPIval16[0]=1000*lowInt+100*midInt+10*highInt+SUPhighInt;
        //SerialUSB.print("0x");
        SerialUSB.print(SPIval16[0]);
        SerialUSB.print("   ");

        receivedVal=AFE4400_Read_Register(4,SPIval16[0]);
        //receivedVal=readAFERegister(4,SPIval16[0]);
        
        SerialUSB.print("we got:");
        SerialUSB.print(receivedVal);
        SerialUSB.print("\n");
      }
      //DisableAFERead(4);
      AFE4400_Set_READABLE(4,0);
      OutputType = 0;
      break;
    }
    case 'E':{ //AFE Setup
      AFE4400_Set_READABLE(4,0);
      AFE4400_Set_Register(4,1,6050); //LED2STC
      AFE4400_Set_Register(4,2,7998); //LED2ENDC
      AFE4400_Set_Register(4,3,6000); //LED2LEDSTC
      AFE4400_Set_Register(4,4,7999); //LED2LEDENDC
      AFE4400_Set_Register(4,5,50);   //ALED2STC
      AFE4400_Set_Register(4,6,1998); //ALED2ENDC
      AFE4400_Set_Register(4,7,2050); //LED1STC
      AFE4400_Set_Register(4,8,3998); //LED1ENDC
      AFE4400_Set_Register(4,9,2000); //LED1LEDSTC
      AFE4400_Set_Register(4,10,3999); //LED1LEDENDC
      AFE4400_Set_Register(4,11,4050); //ALED1STC
      AFE4400_Set_Register(4,12,5998); //ALED1ENDC
      AFE4400_Set_Register(4,13,4); //LED2CONVST
      AFE4400_Set_Register(4,14,1999); //LED2CONVEND
      AFE4400_Set_Register(4,15,2004); //ALED2CONVST
      AFE4400_Set_Register(4,16,3999); //ALED2CONVEND
      AFE4400_Set_Register(4,17,4004); //LED1CONVST
      AFE4400_Set_Register(4,18,5999); //LED1CONVEND
      AFE4400_Set_Register(4,19,6004); //ALED1CONVST
      AFE4400_Set_Register(4,20,7999); // ALED1CONVEND

      AFE4400_Set_Register(4,21,0); //ADCRSTSTXT0
      AFE4400_Set_Register(4,22,3); //ADCRSTENDCT0
      AFE4400_Set_Register(4,23,2000); //ADCRSTSTCT1
      AFE4400_Set_Register(4,24,2003); //ADCRSTENDCT1
      AFE4400_Set_Register(4,25,4000); //ADCRSTSTCT2
      AFE4400_Set_Register(4,26,4003); //ADCRSTENDCT2
      AFE4400_Set_Register(4,27,6000); //ADCRSTSTCT3
      AFE4400_Set_Register(4,28,6003); //ADCRSTENDCT3

      AFE4400_Set_Register(4,29,7999); //PRPCOUNT

      AFE4400_Set_Register(4,30,0x100); //CONTROL1
      //AFE4400_Set_Register(4,31,0x004481); TIA_AMB_GAIN
      AFE4400_Set_Register(4,33,0x004141); //TIA_AMB_GAIN
      AFE4400_Set_Register(4,34,0x8F8F); //LEDCNTRL
      AFE4400_Set_Register(4,35,0x100); //CONTROL2

      SerialUSB.println("AFE Chip Sucessfully initilized!");
      OutputType = 0;
      break;
    }
    case 'F':{ //AFE Continue Read (For testing)
      //AFE4400_Set_READABLE(4,1);
      SerialUSB.println("Now Lets read Data from AFE CHip");
      while (SerialUSB.available() == 0){
        AFE4400_Set_READABLE(4,1);
        SerialUSB.print("LED I Data: ");
        receivedVal=AFE4400_Read_Register(4,44); //LED1
        SerialUSB.print(receivedVal);
        SerialUSB.print(" LED II Data: ");
        receivedVal=AFE4400_Read_Register(4,42); //LED2
        SerialUSB.print(receivedVal);
        SerialUSB.print("\n");
        delay(10);
      }
      OutputTypeS=SerialUSB.read();
      OutputType=OutputTypeS;
      while(Serial.read() >=0){};
      AFE4400_Set_READABLE(4,0);
      break;
    }

    
  }
  // Setting ADS1293
  
  //SPI.transfer(val16);
}

void writeRegister(byte cs, byte thisRegister, byte thisValue) {
  byte addrToSend = thisRegister | WRITE;
  SPI.transfer(cs,addrToSend,SPI_CONTINUE);
  SPI.transfer(cs,thisValue);
}

void writeAFERegister(byte cs, byte thisRegister, byte AFEValue[]) {
  byte addrToSend = thisRegister;
  SPI.transfer(cs,addrToSend,SPI_CONTINUE);
  SPI.transfer(cs,AFEValue[0],SPI_CONTINUE);
  SPI.transfer(cs,AFEValue[1],SPI_CONTINUE);
  SPI.transfer(cs,AFEValue[2]);
}

void AFE4400_Set_Register(byte cs, byte thisRegister, unsigned long data){
  SPI.transfer(cs,thisRegister,SPI_CONTINUE);
  SPI.transfer(cs,(data>>16)&0xFF,SPI_CONTINUE);
  SPI.transfer(cs,(data>>8)&0xFF,SPI_CONTINUE);
  SPI.transfer(cs,(data)&0xFF);
}

unsigned long AFE4400_Read_Register(byte cs,byte addrToRead){
  unsigned long result = 0;   // result to return
  unsigned long resultTEMP[3] = {0,0,0};
  SPI.transfer(cs,addrToRead,SPI_CONTINUE);
  resultTEMP[0]=SPI.transfer(cs,0x00,SPI_CONTINUE);
  resultTEMP[1]=SPI.transfer(cs,0x00,SPI_CONTINUE);
  resultTEMP[2]=SPI.transfer(cs,0x00);
  result = resultTEMP[0]<<16 | resultTEMP[1]<<8 | resultTEMP[2];
  return (result);
}

void AFE4400_Set_READABLE(byte cs, byte isReadable){
  SPI.transfer(cs,0x00,SPI_CONTINUE); //0x00 means CONTROL0
  SPI.transfer(cs,0x00,SPI_CONTINUE);
  SPI.transfer(cs,0x00,SPI_CONTINUE);
  SPI.transfer(cs,isReadable);
}

void EnableAFERead(byte cs){
  byte toWrite[3]={0x00,0x00,0x01};
  writeAFERegister(cs,0x00,toWrite);
}

void DisableAFERead(byte cs){
  byte toWrite[3]={0x00,0x00,0x00};
  writeAFERegister(cs,0x00,toWrite);
}

unsigned int readAFERegister(byte cs, byte thisRegister) {
  unsigned int result = 0;   // result to return
  unsigned int resultTEMP[3] = {0,0,0};   // result to return
  byte addrToRead = thisRegister;
  SPI.transfer(cs,addrToRead,SPI_CONTINUE);
  resultTEMP[0]=SPI.transfer(cs,0x00,SPI_CONTINUE);
  resultTEMP[1]=SPI.transfer(cs,0x00,SPI_CONTINUE);
  resultTEMP[2]=SPI.transfer(cs,0x00);
  result=resultTEMP[2]*255*255+resultTEMP[1]*255+resultTEMP[0];
  return (result);
}

unsigned int readRegister(byte cs, byte thisRegister) {
  unsigned int result = 0;   // result to return
  byte addrToRead = thisRegister | READ;
  SPI.transfer(cs,addrToRead,SPI_CONTINUE);
  result=SPI.transfer(cs,0x00);
  return (result);
}

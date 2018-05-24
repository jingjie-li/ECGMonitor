#include <SPI.h>
byte LowByte = 0;
byte SecondByte = 0;
//unsigned char SPIval16[5]={0xD0,0x01,0x12,0x35,0x0A};
int SPIval16[2]={22,22};
int highInt=0;
int midInt=0;
int lowInt=0;
unsigned int readstuff=0;
unsigned int receivedVal=0;

unsigned int receivedUpper=0;
unsigned int receivedMiddle=0;
unsigned int receivedLower=0;

unsigned int CH1EcgData=0;
unsigned int CH2EcgData=0;
unsigned int CH3EcgData=0;

byte OutputType = 0;
byte OutputTypeS = 0;

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
    SerialUSB.println("We do what? (W-WriteSPI,R-ReadSPI,D-StartGetData,N-NormalConfig,S-StartConversition,T-StopConversition,Z-null)\n");
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
      
      //SPI.transfer(4,0x01,SPI_CONTINUE);
      //SPI.transfer(4,0x11);
      //SPI.transfer(4,0x02,SPI_CONTINUE);
      //SPI.transfer(4,0x19);
      //SPI.transfer(4,0x03,SPI_CONTINUE);
      //SPI.transfer(4,0x2E);
      //SPI.transfer(4,0x0A,SPI_CONTINUE);
      //SPI.transfer(4,0x07);
      //SPI.transfer(4,0x0C,SPI_CONTINUE);
      //SPI.transfer(4,0x04);

      writeRegister(4,0x0D,0x01);
      writeRegister(4,0x0E,0x02);
      writeRegister(4,0x0F,0x03);
      
      //SPI.transfer(4,0x0D,SPI_CONTINUE);
      //SPI.transfer(4,0x01);
      //SPI.transfer(4,0x0E,SPI_CONTINUE);
      //SPI.transfer(4,0x02);
      //SPI.transfer(4,0x0F,SPI_CONTINUE);
      //SPI.transfer(4,0x03);
      
      writeRegister(4,0x10,0x01);

      //SPI.transfer(4,0x10,SPI_CONTINUE);
      //SPI.transfer(4,0x01);

      writeRegister(4,0x12,0x04);
      writeRegister(4,0x21,0x02);
      writeRegister(4,0x22,0x02);
      writeRegister(4,0x23,0x02);
      writeRegister(4,0x24,0x02);
      writeRegister(4,0x27,0x08);
      writeRegister(4,0x2F,0x70);
      
      
      //SPI.transfer(4,0x12,SPI_CONTINUE);
      //SPI.transfer(4,0x04);
      //SPI.transfer(4,0x21,SPI_CONTINUE);
      //SPI.transfer(4,0x02);
      //SPI.transfer(4,0x22,SPI_CONTINUE);
      //SPI.transfer(4,0x02);
      //SPI.transfer(4,0x23,SPI_CONTINUE);
      //SPI.transfer(4,0x02);
      //SPI.transfer(4,0x24,SPI_CONTINUE);
      //SPI.transfer(4,0x02);
      //SPI.transfer(4,0x27,SPI_CONTINUE);
      //SPI.transfer(4,0x08);
      //SPI.transfer(4,0x2F,SPI_CONTINUE);
      //SPI.transfer(4,0x70);

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
  
        CH1EcgData=64*receivedUpper+8*receivedMiddle+receivedLower;
        
        receivedUpper = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3A
        receivedMiddle = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3B
        receivedLower = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3C
  
        CH2EcgData=64*receivedUpper+8*receivedMiddle+receivedLower;
  
        receivedUpper = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3D
        receivedMiddle = SPI.transfer(4,0x00,SPI_CONTINUE);//0x3E
        receivedLower = SPI.transfer(4,0x00);//0x3F
  
        CH3EcgData=64*receivedUpper+8*receivedMiddle+receivedLower;
  
        SerialUSB.print("ECG Channel 1 Data: ");
        SerialUSB.print(CH1EcgData);
        SerialUSB.print(" ECG Channel 2 Data: ");
        SerialUSB.print(CH2EcgData);
        SerialUSB.print(" ECG Channel 3 Data: ");
        SerialUSB.print(CH3EcgData);
        SerialUSB.print(" \n");

        delay(100);
      
      }
      OutputType = SerialUSB.read();
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

unsigned int readRegister(byte cs, byte thisRegister) {
  unsigned int result = 0;   // result to return
  byte addrToRead = thisRegister | READ;
  SPI.transfer(cs,addrToRead,SPI_CONTINUE);
  result=SPI.transfer(cs,0x00);
  return (result);
}



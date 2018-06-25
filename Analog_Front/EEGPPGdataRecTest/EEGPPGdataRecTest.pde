import processing.serial.*; 
Serial myPort;    // The serial port

byte[] inBuffer = new byte[30];
byte[] inBufferWaste=new byte[52];
int lf = 10;      // ASCII linefeed 
int[] ECGdatas = new int[3];
int[] PPGDatas = new int[2];
float a=100,b=240;
int pointer=0;
int pointerPPG=0;
float[] displaydata = new float[1000]; //200Hz sampleing rate, display 10s

float[] displayPPG1data = new float[333]; //200Hz sampleing rate, display 10s
float[] displayPPG2data = new float[333]; //200Hz sampleing rate, display 10s

ComputeBaseline EEG_baseline = new ComputeBaseline();
ComputeBaseline PPG1_baseline = new ComputeBaseline();
ComputeBaseline PPG2_baseline = new ComputeBaseline();

float x_old = 1;
float y_old = 100;
float x = 1;
float y = 100;

class ComputeBaseline {
  int datapointer;
  int datasum;
  float[] baselinedatas = new float[20];
  float meansumval=0;
  int prevdata=0;
  ComputeBaseline (){
    datapointer=0;
    datasum=0;
  }
  void addPPGData(int data){
    if(datapointer>19){
      datapointer=0;
    }
    if(isabnormalPPGin(data)){// delete abnomal val
      data=prevdata;
    }
    baselinedatas[datapointer]=float(data);
    datapointer++;
    datasum++;
    prevdata=data;
  }
  boolean isabnormalPPG(int data){
    return (abs(data-prevdata)>200&&prevdata!=0);
  }
  boolean isabnormalPPGin(int data){
    return (abs(data-prevdata)>200&&prevdata!=0);
  }
  boolean isabnormal(int data){
    return (abs(data-prevdata)>1000&&prevdata!=0);
  }
  boolean isabnormalin(int data){
    return (abs(data-prevdata)>200&&prevdata!=0);
  }
  void addECGData(int data){
    if(datapointer>19){
      datapointer=0;
    }
    if(isabnormalin(data)){// delete abnomal val
      data=prevdata;
    }
    baselinedatas[datapointer]=float(data);
    datapointer++;
    datasum++;
    prevdata=data;
  }
  float compute(float factor, float base){
    if(datasum>20){
      meansumval=0;
      for(int i=0;i<20;i++){
        meansumval+=baselinedatas[i];
      }
      return ((meansumval/20)*factor+base);
    }
    else{
      return 200;
    }
  }
}

void setup() {
  size(1000, 800);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 115200); 
  //myPort.bufferUntil(lf); // wait for '0x0A'
  myPort.write('S');
  myPort.write('M');
  inBufferWaste = myPort.readBytes(50);
}

void draw() {
  //background(200);
  while (myPort.available() > 0) {
    myPort.readBytesUntil(lf, inBuffer); // until 0x0A
    if(inBuffer[8]==0x0D && inBuffer[9]==0x0A){
      ECGdatas[0]=(convertByte(inBuffer[0])<<6)+((convertByte(inBuffer[1])&0xfc)>>2); //14 bits 8<<6+6
      ECGdatas[1]=((convertByte(inBuffer[1])&0x03)<<12)+(convertByte(inBuffer[2])<<4)+((convertByte(inBuffer[3])&0xf0)>>4); //14bits 2<<12+8<<4+4
      ECGdatas[2]=((convertByte(inBuffer[3])&0x0f)<<10)+(convertByte(inBuffer[4])<<2)+((convertByte(inBuffer[5])&0xc0)>>6); //14bits 4<<10+8<<2+2
      //ECGdatas[3]=(convertByte(inBuffer[3])&0x03)*256+convertByte(inBuffer[4]);//2<<8+8
      PPGDatas[0]=((convertByte(inBuffer[5])&0x3f)<<5)+((convertByte(inBuffer[6])&0xf8)>>3);//11bits 6<<5+5
      PPGDatas[1]=((convertByte(inBuffer[6])&0x03)<<8)+convertByte(inBuffer[7]); //11bits 3<<8+8
      print(" ECGdata1: "+ECGdatas[0]+" ECGdata2: "+ECGdatas[1]+" ECGdata3: "+ECGdatas[2]);
      //println(" ECGdata4: "+ECGdatas[3]);
      print(" PPGdata1: "+PPGDatas[0]);
      println(" PPGdata2: "+PPGDatas[1]);
      //updateDataManECG(PPGDatas[1]);
      //drawlines();
      updateDataManPPG(PPGDatas[0],PPGDatas[1]);
      updateDataManECG3Data(ECGdatas[0],ECGdatas[1],ECGdatas[2]);
      drawPPGlines();
      drawEEGlines();
    }
  }
}

void stop() {
  myPort.write('T');
} 

void updateDataManPPG(int data1, int data2) {
  if (pointerPPG>=332){
    pointerPPG=0;
  }
  PPG1_baseline.addPPGData(data1);
  if(PPG1_baseline.isabnormalPPG(data1)){
    data1=PPG1_baseline.prevdata;
  }
  PPG2_baseline.addPPGData(data2);
  if(PPG2_baseline.isabnormalPPG(data2)){
    data2=PPG2_baseline.prevdata;
  }
  //comp & add PPG1
  a=0.25;
  //b=00;
  b=PPG1_baseline.compute(a,100);
  displayPPG1data[pointerPPG]=abs((-a*(float(data1))+b));//resize 0x1FFFFF
  //comp & add PPG2
  a=0.5;
  //b=300;
  b=PPG2_baseline.compute(a,200);
  displayPPG2data[pointerPPG]=abs((-a*(float(data2))+b));//resize 0x1FFFFF
  //print("PPG1: "+displayPPG1data[pointerPPG]);//
  //print("PPG2: "+displayPPG2data[pointerPPG]);//
  //println(" Pointer:"+pointerPPG);
  pointerPPG++;
}

void updateDataManECG3Data(int data1,int data2, int data3) {
  background(200);
  a=1; 
  //b=12500; 
  EEG_baseline.addECGData(data1);
  if(EEG_baseline.isabnormal(data1)){
    data1=EEG_baseline.prevdata;
  }
  EEG_baseline.addECGData(data2);
  if(EEG_baseline.isabnormal(data2)){
    data2=EEG_baseline.prevdata;
  }
  EEG_baseline.addECGData(data3);
  if(EEG_baseline.isabnormal(data3)){
    data3=EEG_baseline.prevdata;
  }
  b=EEG_baseline.compute(a,400);
  if (pointer>=997){
    pointer=0;
  }
  
  displaydata[pointer]=abs((-a*(float(data1))+b));
  displaydata[pointer+1]=abs((-a*(float(data2))+b));
  displaydata[pointer+2]=abs((-a*(float(data3))+b));
  //displaydata[pointer+3]=abs((-a*(float(data4))+b));
  //print("EEG Data: "+ displaydata[pointer]);//
  //println(" Pointer:"+pointer);
  pointer+=3;
}

void updateDataManECG(int data) {
  background(200);
  //a=1; //PPG2
  //b=300; //PPG2
  a=1; //PPG1
  b=-100; //PPG1
  float temp=0;
  if (pointer>=999){
    pointer=0;
  }
  temp=abs((-a*(float(data))+b));//resize 0x1FFFFF
  displaydata[pointer]=temp;
  print("received: " + data); 
  print("PreConv: "+(float(data)));
  print(" DisplayData Pre: "+temp);//
  println(" Pointer:"+pointer);
  pointer++;
}

void drawPPGlines() {
  float y_old=displayPPG1data[332];
  for(int i=0;i<333;i++){
    y=displayPPG1data[i];
    stroke(204, 102, 0);
    line(3*i-2,y_old,(3*i+1),y);
    y_old=y;
  }
  y_old=displayPPG2data[249];
  for(int i=0;i<333;i++){
    y=displayPPG2data[i];
    stroke(204, 150, 0);
    line(3*i-2,y_old,(3*i+1),y);
    y_old=y;
  }
  //point(pointer,displaydata[pointer]); 
}

void drawEEGlines() {
  float y_old=displaydata[999];
  for(int i=0;i<1000;i+=1){
    y=displaydata[i];
    stroke(1);
    line(i,y_old,(i+1),y);
    y_old=y;
  }
  //point(pointer,displaydata[pointer]); 
}

void drawlines() {
  float y_old=displaydata[999];
  for(int i=0;i<1000;i+=4){
    //random(0, 120)
    y=displaydata[i];
    line(i,y_old,(i+4),y);
    y_old=y;
    //print(i);
    //print(" ");
    //println(y);
  }
  point(pointer,displaydata[pointer]); 
}

int convertByte(byte data){
  int val=0;
  val=data;
  if(data<0){
    val=data+256;
  }
  return val;
}

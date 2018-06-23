import processing.serial.*; 
Serial myPort;    // The serial port

float x_old = 1;
float y_old = 100;
float x = 1;
float y = 100;
int lf = 10;      // ASCII linefeed 
String inString;  // Input string from serial port
int ECGdata=0;
float[] displaydata = new float[1000]; //200Hz sampleing rate, display 10s
int pointer=0;
String myString = null;
float a=100,b=240;
byte[] inBuffer = new byte[30];
byte[] inBufferWaste=new byte[52];

float maxdata=0;
float mindata=0;

void setup() {
  size(1000, 800);
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 115200); 
  //myPort.bufferUntil(lf); // wait for '0x0A'
  for(int i=0;i<1000;i++){
    displaydata[i]=240;
  }
  myPort.write('S');
  myPort.write('M');
  inBufferWaste = myPort.readBytes(50);
}


void draw() {
  background(200);
  //myPort.readBytesUntil(lf, inBuffer);
  //ECGdata=inBuffer[0]*255*255+inBuffer[1]*255+inBuffer[2];
  myPort.write('T');
  while (myPort.available() > 0) {
    //myString = myPort.readStringUntil(lf);
    //inBuffer = myPort.readBytes(5);
    myPort.readBytesUntil(lf, inBuffer); // until 0x0A
    if(inBuffer[3]==0x0D && inBuffer[4]==0x0A){
      ECGdata=inBuffer[0]*255*255+inBuffer[1]*255+inBuffer[2];
      updateDataMan(ECGdata);
    }
    //print("received: " + ECGdata); 
    //print(inBuffer[0]*256*256+inBuffer[1]*256+inBuffer[2]);
    
  }
  drawlines();
  //delay(100);
  //println(ECGdata);
}

void updateDataMan(int data) {
  background(200);
  a=3000;
  b=2640;
  float temp=0;
  if (pointer>=999){
    pointer=0;
  }
  data=data&0x3FFFFF; // remove first two BSW bits in AFE mode
  if(data>=0x200000){ // in AFE mode, diefferential input is less than zero
    data=data&0x1FFFFF; // remove first "-" sign
    data=~data;
    displaydata[pointer]=float(data/0x1FFFFF)*a+b;//resize
  }
  else{
    temp=abs((-a*(float(data)/2097151)+b));//resize 0x1FFFFF
    displaydata[pointer]=temp;
    print("received: " + data); 
    print(" DisplayData Pre: "+temp);//
    println(" Pointer:"+pointer);
  }
  pointer++;
}

void updateData(int data){
  float temp=0;
  if (pointer>=999){
    pointer=0;
  }
  data=data&0x3FFFFF; // remove first two BSW bits in AFE mode
  if(data>=0x200000){ // in AFE mode, diefferential input is less than zero
    data=data&0x1FFFFF; // remove first "-" sign
    data=~data;
    displaydata[pointer]=float(data/0x1FFFFF)*a+b;//resize
  }
  else{
    temp=abs((-a*(float(data)/2097151)+b));//resize 0x1FFFFF
    displaydata[pointer]=temp;
    print("received: " + data); 
    print(" DisplayData Pre: "+(240-100*float(data)/2097151));//
  }
  //if(displaydata[pointer]>10*(maxdata-mindata)){
    //displaydata[pointer]=240;
  //}
  //if(data>100000){
    //displaydata[pointer]=241;
  //}
  print(" DisplayData Pre: "+displaydata[pointer]);
  print(" max:"+maxdata+" min:"+mindata);
  float a_old=a;
  float b_old=b;
  boolean flag=false;
  maxdata=max(displaydata);
  mindata=min(displaydata);
  if ((maxdata-mindata)>480){
    a=520/((maxdata-mindata)/a);
    if(abs(a/a_old)>10||a>1000){
      a=a_old;
    }
    else{
      flag=true;
    }
  }
  if ((maxdata-mindata)<100){
    //print("dis:"+(100/((maxdata-mindata)/a)));
    a=100/((maxdata-mindata)/a);
    //if(abs(a_old-a))
    flag=true;
  }
  if(mindata<1){ // over ranging, inc b
    b=-1.1*(mindata-b);
    if(abs(b-b_old)==250||abs(b)>10000){
      b=b_old;
    }
    else{
      flag=true;
    }
  }
  else if(maxdata>480){ // out range, dec b
    println("!!Adjust b");
    b=450-(maxdata-b);
    if(abs(b-b_old)==250||abs(b)>10000){
      b=b_old;
    }
    else{
      flag=true;
    }
  }
  a=100;
  b=240;
  if(flag){
    for(int i=0;i<1000;i++){
      displaydata[i]=((displaydata[i]-b_old)/a_old)*a+b;
    }
  }
  println(" a:"+a+" b:"+b+" Pointer:"+pointer);
  pointer++;
}

void drawlines() {
  float y_old=displaydata[999];
  for(int i=0;i<1000;i++){
    //random(0, 120)
    y=displaydata[i];
    line(i,y_old,(i+1),y);
    y_old=y;
    //print(i);
    //print(" ");
    //println(y);
  }
  point(pointer,displaydata[pointer]); 
}

//void serialEvent(Serial p) { 
  //byte[] inBuffer = new byte[3];
  //inBuffer = p.readBytes();
  //ECGdata=inBuffer[0]*255*255+inBuffer[1]*255+inBuffer[2];
//} 

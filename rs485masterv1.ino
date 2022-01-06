#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX



const int LED =  13;   
const int Enable =  2;
char mystr[20]; 
void setup() 
{ 
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(300);
  mySerial.setTimeout(250);

  Serial.println("initializing...");

  pinMode(LED, OUTPUT);
  pinMode(Enable, OUTPUT);
  
  digitalWrite(LED, LOW); 
  
  digitalWrite(Enable, HIGH);


}
 char data;
 int count=0,c1=0;
 int slaveNumber=1;
void loop() 
{ 
  
  slaveNumber=1;
  getData(slaveNumber);
  delay(500);

  slaveNumber=2;
  getData(slaveNumber);
  delay(500);

  slaveNumber=3;
  getData(slaveNumber);
  delay(500);

  slaveNumber=4;
  getData(slaveNumber);
  delay(500);

  slaveNumber=5;
  getData(slaveNumber);
  delay(500);
//===========

//==      
      Serial.println();
      Serial.println(count);
      Serial.println();
      delay(500);
      count++;
      if(count>100)
        count=0;
}

void getData(int slaveNumber) {
  bool noR=0;
  int count=0;
  digitalWrite(Enable, HIGH);
  mySerial.print('I');
  mySerial.print(slaveNumber);
  mySerial.print('L');
  mySerial.println('F');
  mySerial.flush();
  digitalWrite(Enable, LOW);
  
  //------------------------
  
   while(Serial.available()== 0 && count<20000){
   //noR=0;
   count++;
   delayMicroseconds(1);
   }
   Serial.println(count);
   if(count>9999){
    
    noR=1;
}
if(Serial.available()){
  delay(100);
  Serial.println(Serial.available());
  //Serial.readBytesUntil('f',mystr,16);
  //Serial.println(mystr);
}
   //===
   //while(Serial.available()== 0);
   if (Serial.find('i'))
  {

    int slave = Serial.parseInt();
      
    
    float anglex = Serial.parseFloat();
    
    float angley = Serial.parseFloat();
    
    Serial.readBytesUntil('f',mystr,20);
    Serial.print(slave);
    Serial.print(':');
    Serial.print(anglex);
    Serial.print(',');
    Serial.println(angley);
    Serial.println();
    //Serial.print(mystr);

  } else {
    Serial.print("timeout s:");
    Serial.println(slaveNumber);
    if(!noR){
      Serial.readBytesUntil('f',mystr,16);
      Serial.println(mystr);
    }
  }
//}
if(noR){
  Serial.print("no Resp:");
  Serial.println(slaveNumber);
}
}
